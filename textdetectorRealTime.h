#pragma once
#include "textdetector.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <time.h>
#include <mutex>
#include <thread>

using namespace cv;
class textdetectorRealTime : public textdetector 
{	
	Q_OBJECT  // Required macro for signal-slot mechanism
public:
	explicit textdetectorRealTime(QObject* parent = nullptr,int Id = 0,int width = 1280,int height = 720);

	
	
	~textdetectorRealTime()
	{

	}

	void startCameraThread();
	void stopCameraThread();
	int  openCamera(int input);
	void getInputImage();
	void textdetection();
	void extractText(cv::Mat const &matrix);
signals:
	void newFrameProcessed(cv::Mat const &img);
	void wordsProcessed(QString const  &vec);

private:
	bool mProcessFlag = false;
	bool mNewImageFlag = false;

	int camId = 0;
	cv::VideoCapture mCap;

	std::mutex mImageMutex;

	std::vector<std::thread> mThreads;
	cv::Mat mImgBuffer;
	int mWidth = 1280;
	int mHeight = 720;
	std::vector<const char*> characterVec;
};

