/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *display_image;
    QPushButton *pushButton;
    QLabel *display_image2;
    QTextEdit *textEdit_3;
    QPlainTextEdit *plainTextEdit;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    QTextEdit *textEdit;
    QDoubleSpinBox *doubleSpinBoxConfidenceLevel;
    QSplitter *splitter;
    QTextEdit *textEdit_2;
    QComboBox *comboBoxLanguageSelection;
    QSplitter *splitter_5;
    QSplitter *splitter_4;
    QPlainTextEdit *plainTextEdit_2;
    QPushButton *pushButton_SaveTxt;
    QPushButton *pushButton_SaveImageFile;
    QToolButton *toolButtonChangeColor;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1354, 833);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setBold(true);
        font.setItalic(true);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        display_image = new QLabel(centralwidget);
        display_image->setObjectName("display_image");
        display_image->setGeometry(QRect(0, 0, 640, 480));
        display_image->setMaximumSize(QSize(640, 480));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(280, 680, 631, 71));
        display_image2 = new QLabel(centralwidget);
        display_image2->setObjectName("display_image2");
        display_image2->setGeometry(QRect(641, 0, 640, 480));
        display_image2->setMaximumSize(QSize(640, 480));
        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName("textEdit_3");
        textEdit_3->setGeometry(QRect(10, 500, 211, 201));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(720, 490, 471, 181));
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setGeometry(QRect(250, 500, 331, 81));
        splitter_3->setOrientation(Qt::Orientation::Horizontal);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Orientation::Vertical);
        textEdit = new QTextEdit(splitter_2);
        textEdit->setObjectName("textEdit");
        splitter_2->addWidget(textEdit);
        doubleSpinBoxConfidenceLevel = new QDoubleSpinBox(splitter_2);
        doubleSpinBoxConfidenceLevel->setObjectName("doubleSpinBoxConfidenceLevel");
        doubleSpinBoxConfidenceLevel->setMaximum(100.000000000000000);
        splitter_2->addWidget(doubleSpinBoxConfidenceLevel);
        splitter_3->addWidget(splitter_2);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Vertical);
        textEdit_2 = new QTextEdit(splitter);
        textEdit_2->setObjectName("textEdit_2");
        splitter->addWidget(textEdit_2);
        comboBoxLanguageSelection = new QComboBox(splitter);
        comboBoxLanguageSelection->setObjectName("comboBoxLanguageSelection");
        splitter->addWidget(comboBoxLanguageSelection);
        splitter_3->addWidget(splitter);
        splitter_5 = new QSplitter(centralwidget);
        splitter_5->setObjectName("splitter_5");
        splitter_5->setGeometry(QRect(1190, 490, 121, 81));
        splitter_5->setOrientation(Qt::Orientation::Vertical);
        splitter_4 = new QSplitter(splitter_5);
        splitter_4->setObjectName("splitter_4");
        splitter_4->setOrientation(Qt::Orientation::Vertical);
        plainTextEdit_2 = new QPlainTextEdit(splitter_4);
        plainTextEdit_2->setObjectName("plainTextEdit_2");
        splitter_4->addWidget(plainTextEdit_2);
        pushButton_SaveTxt = new QPushButton(splitter_4);
        pushButton_SaveTxt->setObjectName("pushButton_SaveTxt");
        splitter_4->addWidget(pushButton_SaveTxt);
        splitter_5->addWidget(splitter_4);
        pushButton_SaveImageFile = new QPushButton(splitter_5);
        pushButton_SaveImageFile->setObjectName("pushButton_SaveImageFile");
        splitter_5->addWidget(pushButton_SaveImageFile);
        toolButtonChangeColor = new QToolButton(centralwidget);
        toolButtonChangeColor->setObjectName("toolButtonChangeColor");
        toolButtonChangeColor->setGeometry(QRect(1200, 580, 101, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1354, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        display_image->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "SELECT FILE and DETECT", nullptr));
        display_image2->setText(QString());
        textEdit_3->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">INSTRUCTIONS:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">1) Write the confidence level as an integer.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span s"
                        "tyle=\" font-size:11pt;\">2)Select the language you want to process</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">3)Click SELECT FILE and DETECT</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">4)You can save the detection as a file.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p></body></html>", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:700; font-style:italic;\">Confidence Level</span></p></body></html>", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:700; font-style:italic;\">LANGUAGE SELECTION</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt; font-weight:700; font-style:italic;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; "
                        "margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Arial'; font-size:11pt; font-weight:700; font-style:italic;\"><br /></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt; font-weight:700; font-style:italic;\"><br /></p></body></html>", nullptr));
        plainTextEdit_2->setPlainText(QCoreApplication::translate("MainWindow", "OCR-RESULTS", nullptr));
        pushButton_SaveTxt->setText(QCoreApplication::translate("MainWindow", "Save As Text File", nullptr));
        pushButton_SaveImageFile->setText(QCoreApplication::translate("MainWindow", "Save As Image File", nullptr));
        toolButtonChangeColor->setText(QCoreApplication::translate("MainWindow", "Change Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
