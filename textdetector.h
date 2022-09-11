#ifndef TEXTDETECTOR_H
#define TEXTDETECTOR_H
#include "tesseract/resultiterator.h"
#include "leptonica/allheaders.h"
#include "tesseract/baseapi.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

class textdetector
{
public:

    textdetector();
    tesseract::TessBaseAPI *tesseractAPI;
    tesseract::ResultIterator* ri;
    tesseract::TessBaseAPI *GetIterator();
    tesseract::PageIteratorLevel level=tesseract::RIL_WORD;
public:
    static void textdetection(std::string file_name,float k,std::string lang);
    static void extractText(std::string file_name,std::string lang);

};

#endif // TEXTDETECTOR_H

