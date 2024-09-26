#pragma once
#include "tesseract/resultiterator.h"
#include "leptonica/allheaders.h"
#include "tesseract/baseapi.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>

class textdetector
{
public:
    textdetector()
    {
        mApi = new tesseract::TessBaseAPI();
        setPILevel(tesseract::PageIteratorLevel::RIL_WORD);
        mLanguageMap["English"] = "eng";
        mLanguageMap["Deutch"] = "deu";
        mLanguageMap["French"] = "fra";
        mLanguageMap["Turkish"] = "tur";
    }

    ~textdetector()
    {
        if (mApi)
        {
            mApi->End();
            delete mApi;
            mApi = nullptr;
        }
    }

    void setPILevel(int level);
    tesseract::PageIteratorLevel getPILevel();

    void setDetectionLevel(float level);
    float getDetectionLevel();

    void setLanguage(const std::string& lang);
    std::string getLanguage();

    tesseract::TessBaseAPI* getApi();

    void textdetection(const std::string& file_name);
    void extractText(const std::string& file_name);

    void setOutText(char* txt);
    char* getOutText();

    void setProcessedImg(cv::Mat img);
    cv::Mat getProcessedImg();
    
    void setRGB(double R, double G, double B);
    cv::Scalar getRGB();

private:
    tesseract::TessBaseAPI* mTesseractAPI;   // Instance-specific API object
    tesseract::ResultIterator* ri;           // Result iterator
    tesseract::PageIteratorLevel mLevel;     // Page iterator level
    std::string mLanguage = "eng";           // Default language
    float detectLevel = 75;                  // Default detection level
    tesseract::TessBaseAPI* mApi;            // Static/shared API object
    char* mOutText  = nullptr;
    std::unordered_map<std::string, std::string> mLanguageMap;
    cv::Mat mProcessedImg;
    cv::Scalar RGB = {0,0,0};
};
