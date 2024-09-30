#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qthread.h"

using namespace cv;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Timer = new QTimer(this);

    connect(Timer, SIGNAL(timeout()), this, SLOT(DisplayImage()));
    
    ui->comboBoxLanguageSelection->addItem("Deutch");
    ui->comboBoxLanguageSelection->addItem("English");
    ui->comboBoxLanguageSelection->addItem("French");
    ui->comboBoxLanguageSelection->addItem("Turkish");

    mTextDetector = new textdetector(nullptr);
    mTextDetectorRealTime = new textdetectorRealTime(nullptr,0);
    
    ui->doubleSpinBoxConfidenceLevel->setValue(mTextDetector->getDetectionLevel());
    auto dialog = new QColorDialog();
    dialog->setWindowFlags(Qt::Widget);
    dialog->setOptions(QColorDialog::DontUseNativeDialog | QColorDialog::ShowAlphaChannel);
    ui->toolButtonChangeColor->setStatusTip(tr("Choose fill color"));
    ui->toolButtonChangeColor->setPopupMode(QToolButton::InstantPopup);

    floatingLabelImgOriginal = new QLabel;
    floatingLabelImgProcessed = new QLabel;

    floatingLabelImgOriginal->setAttribute(Qt::WA_TranslucentBackground);
    floatingLabelImgOriginal->setWindowFlags(Qt::Window);
    floatingLabelImgOriginal->hide();

    floatingLabelImgProcessed->setAttribute(Qt::WA_TranslucentBackground);
    floatingLabelImgProcessed->setWindowFlags(Qt::Window);
    floatingLabelImgProcessed->hide();

    connect(ui->toolButtonChangeColor, &QPushButton::clicked, [this, dialog]() {
        // Open the QColorDialog
        QColor selectedColor = QColorDialog::getColor(Qt::white, this, "Select a color");

        // If a valid color was selected, update the label and background
        if (selectedColor.isValid()) {
            QRgb selectedRgb = selectedColor.rgb();
            mTextDetector->setRGB(qRed(selectedRgb), qGreen(selectedRgb), qBlue(selectedRgb));
            update(mTextDetector);
            mTextDetectorRealTime->setRGB(qRed(selectedRgb), qGreen(selectedRgb), qBlue(selectedRgb));
        }
        });
    
    connect(ui->pushButtonStartStopDetection, &QPushButton::clicked, this, &MainWindow::toggleRealTimeDetection);
    connect(Timer, SIGNAL(timeout()), this, SLOT(DisplayImage()));
    connect(ui->comboBoxLanguageSelection, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxItemChanged(QString)));
    connect(ui->doubleSpinBoxConfidenceLevel, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::confidenceLevelChanged);
    connect(mTextDetectorRealTime, &textdetectorRealTime::newFrameProcessed, this, &MainWindow::onNewFrame);
    connect(mTextDetectorRealTime, &textdetectorRealTime::wordsProcessed, this, &MainWindow::onNewWords);
    ui->comboBoxLanguageSelection->setCurrentText("English");

    Timer->start();
}
void MainWindow::onNewFrame(cv::Mat const &frame) {
    
    ui->plainTextEdit->setPlainText(mTextDetectorRealTime->getOutText());

    DisplayImage(frame, floatingLabelImgProcessed);  // Call DisplayImage whenever a new frame is received
}
void MainWindow::onNewWords(const QString &text)
{
    
    ui->plainTextEdit->setPlainText(text);
    
}

void MainWindow::toggleRealTimeDetection()
{
    if (!mRealTimeDetection) {
        float k = getConfLevel();
        QString language = getLang();
        std::string lang = language.toStdString();

        mTextDetectorRealTime->setDetectionLevel(k);
        mTextDetectorRealTime->setLanguage(lang);

        
        ui->pushButtonStartStopDetection->setText("Stop Detection");
        if (mTextDetectorRealTime->openCamera(0))
        {
            mTextDetectorRealTime->startCameraThread();
        }
    }
    else {
        
        ui->pushButtonStartStopDetection->setText("Start Detection");
        
         mTextDetectorRealTime->stopCameraThread();
        
    }
    mRealTimeDetection = !mRealTimeDetection;
}
MainWindow::~MainWindow()
{
    delete mTextDetector;
    delete ui;
}
void MainWindow::setConfLevel(int lvl)
{
    mConfidenceLevel = lvl;
}
int MainWindow::getConfLevel()
{
    return mConfidenceLevel;
}
void MainWindow::setLang(QString lang)
{
    mLanguage = lang;
}
QString MainWindow::getLang()
{
    return mLanguage;
}
void MainWindow::setPath(std::string path)
{
    mCurrentPath = path;
}
std::string MainWindow::getPath()
{
    return mCurrentPath;
}
void MainWindow::DisplayImage(cv::Mat img,QLabel* label){
    
    if (img.empty())
    {
        return;
    }
    
    cv::Mat rgbImg;
    cv::cvtColor(img, rgbImg, cv::COLOR_BGR2RGB);

    QImage imdisplay((uchar*)rgbImg.data, rgbImg.cols, rgbImg.rows, rgbImg.step, QImage::Format_RGB888);
    
    label->setPixmap(QPixmap::fromImage(imdisplay));
    label->adjustSize();
    label->show();

}





void MainWindow::on_pushButton_clicked()

{
    
    float k = getConfLevel();
    QString language=getLang();
    std::string lang=language.toStdString();

    QString file_name=QFileDialog::getOpenFileName(this,"Open File","",tr("Image Files(*.png *.jpg)"));
    std::string path=file_name.toStdString();
    cv::Mat img = imread(path);
    setPath(path);

    DisplayImage(img, floatingLabelImgOriginal);


    mTextDetector->setDetectionLevel(k);
    mTextDetector->setLanguage(lang);
    mTextDetector->extractText(getPath());
    mTextDetector->textdetection(getPath());

    ui->plainTextEdit->setPlainText(mTextDetector->getOutText());
    mLastUsedImg = mTextDetector->getProcessedImg();
    DisplayImage(mTextDetector->getProcessedImg(), floatingLabelImgProcessed);


}
void MainWindow::update(textdetector* detector)
{
    if (!detector)
    {
        return;
    }
    detector->setDetectionLevel(getConfLevel());
    detector->setLanguage(getLang().toStdString());
    detector->extractText(getPath());
    detector->textdetection(getPath());
    ui->plainTextEdit->setPlainText(detector->getOutText());
    DisplayImage(detector->getProcessedImg(), floatingLabelImgProcessed);
}

void MainWindow::on_pushButton_SaveTxt_clicked()
{
    saveAsTxtFile(this->ui->plainTextEdit, this);
}

void MainWindow::on_pushButton_SaveImageFile_clicked()
{
    saveAsImgFile(mLastUsedImg, this);
}

void MainWindow::comboboxItemChanged(QString)
{
    setLang(ui->comboBoxLanguageSelection->currentText());
    if (mRealTimeDetection)
    {
        update(mTextDetector);
    }
    else
    {
        update(mTextDetectorRealTime);
    }
    
}

void MainWindow::confidenceLevelChanged()
{
    setConfLevel(ui->doubleSpinBoxConfidenceLevel->value());
    if(mRealTimeDetection)
    {
        update(mTextDetector);
    }
    else
    {
        update(mTextDetectorRealTime);
    }
}

void MainWindow::saveAsTxtFile(QPlainTextEdit* plainTextEdit, QWidget* parent)
{
    // Get the current time to generate a default filename
    QString defaultFileName = "output_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".txt";

    // Open a file dialog to let the user choose the file location and name
    QString filePath = QFileDialog::getSaveFileName(parent, "Save File", defaultFileName, "Text Files (*.txt)");
    

    // If the user presses cancel return
    if (filePath.isEmpty()) {
        return;
    }

    QString text = plainTextEdit->toPlainText();

    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Create a QTextStream object for writing text to the file
        QTextStream out(&file);

        // Write the text to the file
        out << text;

        // Close the file after writing
        file.close();
    }
    else {
        // Show an error message if the file could not be opened
        QMessageBox::warning(parent, "Error", "Could not open file for writing");
    }
    
}
void MainWindow::saveAsImgFile(cv::Mat const & mat, QWidget* parent) 
{
    // Fetch the QPixmap directly (no pointer)
    

    // Ensure there is a valid pixmap in the QLabel
    if (mat.empty()) {
        QMessageBox::warning(parent, "Error", "No image to save!");
        return;
    }

    // Get the current time to generate a default filename
    QString defaultFileName = "output_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".png";

    // Let the user choose the location and filename
    QString filePath = QFileDialog::getSaveFileName(parent, "Save Image", defaultFileName, "PNG Files (*.png);;JPG Files (*.jpg);;BMP Files (*.bmp)");

    // Check if the user didn't select a file
    if (filePath.isEmpty()) {
        return; // User cancelled, do nothing
    }

    // Save the pixmap to the specified file
    if (!cv::imwrite(filePath.toStdString(), mat)) {
        QMessageBox::warning(parent, "Error", "Failed to save the image!");
    }
}



