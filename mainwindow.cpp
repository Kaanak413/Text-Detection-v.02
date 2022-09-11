#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include "textdetector.h"
#include<QTextStream>
#include<QFile>

using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(DisplayImage()));

    Timer->start();
}

MainWindow::~MainWindow()
{

    delete ui;
}
void MainWindow::DisplayImage(QString path){
    std::string str=path.toStdString();

    Mat img;
    img = imread(str);
    cv::resize(img, img, Size(640, 480), 0, 0, INTER_LINEAR);
    cv::cvtColor(img,img,CV_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    ui->display_image->setPixmap(QPixmap::fromImage(imdisplay));

}





void MainWindow::on_pushButton_clicked()

{
    QString confidence=ui->lineEdit->text();
    float k=confidence.toFloat();
    QString language=ui->lineEdit_2->text();
    std::string lang=language.toStdString();

    QString file_name=QFileDialog::getOpenFileName(this,"Open File","",tr("Image Files(*.png *.jpg)"));
    std::string path=file_name.toStdString();
    DisplayImage(file_name);



    textdetector::textdetection(path,k,lang);
    Mat img;
    img = imread("Result122.png");
    cv::resize(img, img, Size(640, 480), 0, 0, INTER_LINEAR);
    cv::cvtColor(img,img,CV_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    ui->display_image2->setPixmap(QPixmap::fromImage(imdisplay));
    textdetector::extractText(path,lang);

    QFile file("OCR-RESULTS.txt");
    if (!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"ERROR","File not found");
        }
    QTextStream in(&file);
    QString text=in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();





}





