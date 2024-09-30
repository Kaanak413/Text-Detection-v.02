#pragma once

#include "textdetector.h"
#include "textdetectorRealTime.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <QPlainTextEdit>

#include<QTextStream>
#include<QFile>
#include <QColorDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void DisplayImage(cv::Mat img, QLabel* label);
    void comboboxItemChanged(QString);
    void confidenceLevelChanged();
    void toggleRealTimeDetection();
    void onNewFrame(cv::Mat const& frame);
    void onNewWords(const QString& text);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage imdisplay;
    QTimer* Timer;

    void setConfLevel(int lvl);
    int getConfLevel();

    void setLang(QString lang);
    QString getLang();

    void setPath(std::string path);
    std::string getPath();

    void update(textdetector* detector);

    void saveAsTxtFile(QPlainTextEdit* plainTextEdit, QWidget* parent);
    void saveAsImgFile(cv::Mat const& mat, QWidget* parent);

    QLabel* floatingLabelImgOriginal;
    QLabel* floatingLabelImgProcessed;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_SaveTxt_clicked();
    void on_pushButton_SaveImageFile_clicked();





private:
    bool mRealTimeDetection = true;
    Ui::MainWindow *ui;
    textdetector* mTextDetector;
    textdetectorRealTime* mTextDetectorRealTime;
    QString mLanguage;
    int mConfidenceLevel;
    std::string mCurrentPath;
    cv::Mat mLastUsedImg;


};
