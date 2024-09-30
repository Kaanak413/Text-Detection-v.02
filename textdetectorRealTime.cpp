#include "textdetectorRealTime.h"

int textdetectorRealTime::openCamera(int input)
{
    int deviceID = input;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    mCap.open(deviceID, apiID);
    // check if we succeeded
    if (!mCap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    else
    {
        mCap.set(CAP_PROP_FRAME_WIDTH, 640);
        mCap.set(CAP_PROP_FRAME_HEIGHT, 480);
    }

}
textdetectorRealTime::textdetectorRealTime(QObject* parent,int Id,int width,int height)
{
    camId = Id;
    mWidth = width;
    mHeight = height;
    /*setRGB(0,255,0);*/
}
void textdetectorRealTime::startCameraThread()
{
	mProcessFlag = true;
	mThreads.push_back(std::thread(&textdetectorRealTime::getInputImage, this));
	mThreads.push_back(std::thread(&textdetectorRealTime::textdetection, this));
}

void textdetectorRealTime::stopCameraThread()
{
	mProcessFlag = false;
	mNewImageFlag = false;
	for (int i = 0; i < mThreads.size(); i++)
	{
		mThreads[i].join();
	}
	mThreads.clear();
}
void textdetectorRealTime::getInputImage()
{
	while (mProcessFlag)
	{
		cv::Mat captureImg;
		mCap.read(captureImg);
		mImageMutex.lock();
		captureImg.copyTo(mImgBuffer);
		mNewImageFlag = true;
		mImageMutex.unlock();
	}


}

void textdetectorRealTime::textdetection()
{
	cv::Mat img;
	bool newImageCame;
    
	while (mProcessFlag)
	{
		if (!mNewImageFlag)
		{
			continue;
		}
		mImageMutex.lock();
		mImgBuffer.copyTo(img);
		newImageCame = mNewImageFlag;
		if (newImageCame && !img.empty())//detection state
		{
            std::string currentLang;
            if (mLanguageMap.find(this->getLanguage()) == mLanguageMap.end())
            {
                std::cout << this->getLanguage() << " :is not present" << std::endl;
            }
            else
            {
                currentLang = mLanguageMap[this->getLanguage()];
            }
            // Initialize tesseract
            if (getApi()->Init(NULL, currentLang.c_str(), tesseract::OEM_LSTM_ONLY))
            {
                std::cerr << "Could not initialize tesseract with language: " << getLanguage() << std::endl;
                return;
            }

            getApi()->SetImage(img.data, img.cols, img.rows, 3, img.step);

            getApi()->Recognize(0);
            getApi()->SetPageSegMode(tesseract::PSM_SINGLE_LINE);

            getApi()->ClearAdaptiveClassifier();


            tesseract::ResultIterator* ri = getApi()->GetIterator();
            std::string plainText;  // String to store the concatenated words

            if (ri != nullptr)
            {
                do
                {
                    const char * word = ri->GetUTF8Text(getPILevel());
                    float conf = ri->Confidence(getPILevel()); // Confidence level
                    int x1, y1, x2, y2;
                    ri->BoundingBox(getPILevel(), &x1, &y1, &x2, &y2); // Get the bounding box coordinates

                    if (conf > getDetectionLevel())
                    {
                        // Draw a rectangle around the word with confidence higher than the threshold
                        cv::rectangle(img, Point(x1, y1), Point(x2, y2), this->getRGB(), 1, 8, 0);
                    }
                    if (word != nullptr) {
                        plainText += std::string(word) + " ";  // Concatenate word with a space
                        characterVec.push_back(word);  // Store the word in the vector
                    }
                    
                } while (ri->Next(getPILevel()));


            }
            
            delete ri;
            mImageMutex.unlock();
            emit newFrameProcessed(img);
            emit wordsProcessed(QString::fromStdString(plainText));
            mNewImageFlag = false;

		}
		else
		{
			mImageMutex.unlock();
		}

	}

}

void textdetectorRealTime::extractText(cv::Mat const& matrix)
{
    if (matrix.empty())
    {
        std::cerr << "Could not open or find the image: " << matrix << std::endl;
        return;
    }
    std::string currentLang;
    if (mLanguageMap.find(getLanguage()) == mLanguageMap.end())
    {
        std::cout << getLanguage() << " :is not present" << std::endl;
    }
    else
    {
        currentLang = mLanguageMap[getLanguage()];
    }
    // Initialize tesseract
    if (getApi()->Init(NULL, currentLang.c_str(), tesseract::OEM_LSTM_ONLY))
    {
        std::cerr << "Could not initialize tesseract with language: " << getLanguage() << std::endl;
        return;
    }

    // Set image for OCR
    getApi()->SetImage(matrix.data, matrix.cols, matrix.rows, 3, matrix.step);
    getApi()->SetPageSegMode(tesseract::PSM_AUTO);
    getApi()->ClearAdaptiveClassifier();

    // Get the OCR result
    mOutText = getApi()->GetUTF8Text();
    if (!mOutText)
    {
        std::cerr << "Error during OCR." << std::endl;
        return;
    }

}
