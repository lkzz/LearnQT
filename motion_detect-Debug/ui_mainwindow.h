/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *Start;
    QComboBox *comboBox;
    QLabel *src_label;
    QLabel *diff_label;
    QLabel *binary_label;
    QPushButton *Close;
    QSlider *threshold_slider;
    QSlider *alpha_slider;
    QLabel *label;
    QLabel *label_2;
    QLabel *threshold;
    QLabel *alpha_value;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1337, 666);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Start = new QPushButton(centralWidget);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(10, 470, 80, 20));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(210, 470, 101, 22));
        src_label = new QLabel(centralWidget);
        src_label->setObjectName(QString::fromUtf8("src_label"));
        src_label->setGeometry(QRect(0, 0, 400, 450));
        src_label->setAutoFillBackground(true);
        src_label->setAlignment(Qt::AlignCenter);
        diff_label = new QLabel(centralWidget);
        diff_label->setObjectName(QString::fromUtf8("diff_label"));
        diff_label->setGeometry(QRect(420, 0, 400, 450));
        diff_label->setAutoFillBackground(true);
        diff_label->setAlignment(Qt::AlignCenter);
        binary_label = new QLabel(centralWidget);
        binary_label->setObjectName(QString::fromUtf8("binary_label"));
        binary_label->setGeometry(QRect(840, 0, 400, 450));
        binary_label->setAutoFillBackground(true);
        binary_label->setAlignment(Qt::AlignCenter);
        Close = new QPushButton(centralWidget);
        Close->setObjectName(QString::fromUtf8("Close"));
        Close->setGeometry(QRect(110, 470, 80, 20));
        threshold_slider = new QSlider(centralWidget);
        threshold_slider->setObjectName(QString::fromUtf8("threshold_slider"));
        threshold_slider->setGeometry(QRect(10, 500, 181, 16));
        threshold_slider->setOrientation(Qt::Horizontal);
        alpha_slider = new QSlider(centralWidget);
        alpha_slider->setObjectName(QString::fromUtf8("alpha_slider"));
        alpha_slider->setGeometry(QRect(210, 500, 201, 16));
        alpha_slider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 520, 61, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\346\255\243\351\273\221"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 520, 54, 12));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        threshold = new QLabel(centralWidget);
        threshold->setObjectName(QString::fromUtf8("threshold"));
        threshold->setGeometry(QRect(155, 520, 31, 20));
        alpha_value = new QLabel(centralWidget);
        alpha_value->setObjectName(QString::fromUtf8("alpha_value"));
        alpha_value->setGeometry(QRect(390, 520, 31, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1337, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        Start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\270\247\351\227\264\345\267\256\345\210\206\346\263\225", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\350\203\214\346\231\257\345\267\256\345\210\206\346\263\225", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\345\205\211\346\265\201\346\263\225", 0, QApplication::UnicodeUTF8)
        );
        src_label->setText(QApplication::translate("MainWindow", "SRC", 0, QApplication::UnicodeUTF8));
        diff_label->setText(QApplication::translate("MainWindow", "Diff", 0, QApplication::UnicodeUTF8));
        binary_label->setText(QApplication::translate("MainWindow", "Binary", 0, QApplication::UnicodeUTF8));
        Close->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Threshold", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "alpha", 0, QApplication::UnicodeUTF8));
        threshold->setText(QApplication::translate("MainWindow", "v", 0, QApplication::UnicodeUTF8));
        alpha_value->setText(QApplication::translate("MainWindow", "v", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
