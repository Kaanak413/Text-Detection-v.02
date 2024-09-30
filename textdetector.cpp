#include "textdetector.h"
using namespace cv;

textdetector::textdetector(QObject* parent)
{
    mApi = new tesseract::TessBaseAPI();
    setPILevel(tesseract::PageIteratorLevel::RIL_WORD);
    mLanguageMap["English"] = "eng";
    mLanguageMap["Deutch"] = "deu";
    mLanguageMap["French"] = "fra";
    mLanguageMap["Turkish"] = "tur";
    setRGB(0, 255, 0);
}

void textdetector::setPILevel(int level)
{
    mLevel = tesseract::PageIteratorLevel(level);
}

tesseract::PageIteratorLevel textdetector::getPILevel()
{
    return mLevel;
}

void textdetector::setDetectionLevel(float level)
{
    detectLevel = level;
}

float textdetector::getDetectionLevel()
{
    return detectLevel;
}

void textdetector::setLanguage(const std::string& lang)
{
    mLanguage = lang;
}

std::string textdetector::getLanguage()
{
    return mLanguage;
}

tesseract::TessBaseAPI* textdetector::getApi()
{
    return mApi;
}

void textdetector::textdetection(const std::string& file_name)
{
    // Load the image
    if (file_name.size() == 0)
    {
        return;
    }
    Mat im = cv::imread(file_name, IMREAD_COLOR);
   
    if (im.empty())
    {
        std::cerr << "Could not open or find the image: " << file_name << std::endl;
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

    getApi()->SetImage(im.data, im.cols, im.rows, 3, im.step);
   
    getApi()->Recognize(0);
    getApi()->SetPageSegMode(tesseract::PSM_SINGLE_LINE);

    getApi()->ClearAdaptiveClassifier();


    tesseract::ResultIterator* ri = getApi()->GetIterator();
    if (ri != nullptr)
    {
        do
        {
            const char* word = ri->GetUTF8Text(getPILevel());
            float conf = ri->Confidence(getPILevel()); // Confidence level
            int x1, y1, x2, y2;
            ri->BoundingBox(getPILevel(), &x1, &y1, &x2, &y2); // Get the bounding box coordinates

            if (conf > getDetectionLevel())
            {
                // Draw a rectangle around the word with confidence higher than the threshold
                cv::rectangle(im, Point(x1, y1), Point(x2, y2), getRGB(), 1, 8, 0);
            }
            
        } while (ri->Next(getPILevel()));

        
    }
    setProcessedImg(im);
    delete ri;
    
}

void textdetector::extractText(const std::string& file_name)
{
    // Load the image
    if (file_name.size()==0)
    {
        return;
    }
    Mat im = cv::imread(file_name, IMREAD_COLOR);
    cv::imwrite("img.png", im);
    im = cv::imread("img.png");
    if (im.empty())
    {
        std::cerr << "Could not open or find the image: " << file_name << std::endl;
        return;
    }
    std::string currentLang ;
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
    getApi()->SetImage(im.data, im.cols, im.rows, 3, im.step);
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

void textdetector::setOutText(char* txt)
{
    mOutText = txt;
}

char* textdetector::getOutText()
{
    return mOutText;
}

void textdetector::setProcessedImg(cv::Mat img)
{
    mProcessedImg = img;
}

cv::Mat textdetector::getProcessedImg()
{
    return mProcessedImg;
}

void textdetector::setRGB(double R, double G, double B)
{
    RGB = {R,G,B};
}

cv::Scalar textdetector::getRGB()
{
    return RGB;
}
