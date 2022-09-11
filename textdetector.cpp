#include "textdetector.h"
using namespace cv ;
void textdetector::textdetection(std::string file_name,float k,std::string lang)
{
    Mat img;
    img = imread(file_name);
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
     // Initialize tesseract-ocr with English, with specifying tessdata path
     if (api->Init(TESSDATA_PREFIX, lang.c_str())) {

         exit(1);
     }



 Pix *image = pixRead(file_name.c_str());

     api->SetImage(image);

     api->Recognize(0);

 tesseract::ResultIterator* ri=api->GetIterator();//Get the GetIterator func from the api.
 tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
 if (ri != 0) {//If a word found,
         do {
             //const char* word = ri->GetUTF8Text(level);//Give the word in UTF8Text format
             float conf = ri->Confidence(level);//Its confidence level
             int x1, y1, x2, y2;
             ri->BoundingBox(level, &x1, &y1, &x2, &y2);//In that instance of iteration,this gives the BoundingBox locations of that word.

             // k is the user input.
             if(conf>k){
                 cv::Point pt1(x1, y1);//Make the Boundingbox points as cv::Point to make rectangle
                 cv::Point pt2(x2, y2);//
                 cv::rectangle(img, pt1, pt2, cv::Scalar(0, 255, 0), 1, 8, 0);//Draw rectangle,If confidence level of that word is higher than the user input confidence level.
                 //Give these "thresholded" words to the richTextbox
                 // inputStr += resultStr;
             }



         } while (ri->Next(level));
     cv::imwrite("Result122.png", img);



     }


}
void textdetector::extractText(std::string file_name,std::string lang){
    char *outText;
    Mat im = cv::imread(file_name, IMREAD_COLOR);
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(TESSDATA_PREFIX, lang.c_str())) {

             exit(1);
         }

    api->SetImage(im.data, im.cols, im.rows, 3, im.step);
    outText = (api->GetUTF8Text());

    api->End();



   std::ofstream outfile ("OCR-RESULTS.txt");

    outfile <<outText << std::endl;

    outfile.close();
    delete []outText;





}
