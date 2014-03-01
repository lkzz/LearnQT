#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv/ml.h>
#include <time.h>
#include <qimage.h>
#include <qmessagebox.h>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ProcessFrame(const IplImage* src_img,IplImage* binary_img);
    void BackgroundProcess();

    CvCapture *capture=NULL;
    IplImage* binary_mhi=NULL;
    IplImage* src_image=NULL;
    int low_Threshold=30;
    int nFrameNum=0;

//    IplImage* bsrc_image=NULL;
//    IplImage* bk_binary_image=NULL;

private slots:

    void on_Start_clicked();

    void on_End_clicked();

    void on_Close_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
