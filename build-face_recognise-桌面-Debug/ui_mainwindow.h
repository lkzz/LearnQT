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
    QPushButton *End;
    QComboBox *comboBox;
    QLabel *src_label;
    QLabel *binary_label;
    QPushButton *Close;
    QSlider *verticalSlider;
    QLabel *low_Threshold;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(954, 669);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Start = new QPushButton(centralWidget);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(679, 20, 91, 31));
        End = new QPushButton(centralWidget);
        End->setObjectName(QString::fromUtf8("End"));
        End->setGeometry(QRect(679, 80, 91, 31));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(680, 200, 91, 31));
        src_label = new QLabel(centralWidget);
        src_label->setObjectName(QString::fromUtf8("src_label"));
        src_label->setGeometry(QRect(0, 0, 300, 300));
        src_label->setAutoFillBackground(true);
        src_label->setAlignment(Qt::AlignCenter);
        binary_label = new QLabel(centralWidget);
        binary_label->setObjectName(QString::fromUtf8("binary_label"));
        binary_label->setGeometry(QRect(0, 340, 300, 300));
        binary_label->setAlignment(Qt::AlignCenter);
        Close = new QPushButton(centralWidget);
        Close->setObjectName(QString::fromUtf8("Close"));
        Close->setGeometry(QRect(679, 140, 91, 31));
        verticalSlider = new QSlider(centralWidget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(790, 30, 20, 201));
        verticalSlider->setOrientation(Qt::Vertical);
        low_Threshold = new QLabel(centralWidget);
        low_Threshold->setObjectName(QString::fromUtf8("low_Threshold"));
        low_Threshold->setGeometry(QRect(780, 10, 41, 16));
        low_Threshold->setLayoutDirection(Qt::LeftToRight);
        low_Threshold->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        src_label->raise();
        Start->raise();
        End->raise();
        comboBox->raise();
        binary_label->raise();
        Close->raise();
        verticalSlider->raise();
        low_Threshold->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 954, 17));
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
        End->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\270\247\351\227\264\345\267\256\345\210\206\346\263\225", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\350\203\214\346\231\257\345\267\256\345\210\206\346\263\225", 0, QApplication::UnicodeUTF8)
        );
        src_label->setText(QApplication::translate("MainWindow", "src", 0, QApplication::UnicodeUTF8));
        binary_label->setText(QApplication::translate("MainWindow", "dst", 0, QApplication::UnicodeUTF8));
        Close->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        low_Threshold->setText(QApplication::translate("MainWindow", "pos", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
