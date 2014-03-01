#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv/ml.h>
#include <time.h>
#include <qimage.h>
#include <qmessagebox.h>
#include <QKeyEvent>
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

    CvCapture* pCapture;
    int nFrameNum;
    int cbox_index;
    int lowThreshold=30;
    double alpha=0.1;

    long current_frame = 0;

    void FrameDiff();
    void BackgroundDiff();
    void OpticalFlow();
    void OpticalFlowDetect();
    void OpencvOpticalFlow();
    void optical_flow();

    cv::Mat image_rotate(IplImage* src);

    IplImage* src=NULL;
    IplImage* last_img=NULL;//last frame
    IplImage* img_diff=NULL;//diff frame
    IplImage* gray_diff=NULL;//gray diff frame
    IplImage* binary_img=NULL;//bianry

    //声明IplImage指针
    IplImage* pFrame = NULL;
    IplImage* pFrImg = NULL;
    IplImage* pBkImg = NULL;

    CvMat* pFrameMat = NULL;
    CvMat* pFrMat = NULL;
    CvMat* pBkMat = NULL;

    void Display(IplImage* src_image,IplImage* diff_img,IplImage* binary_mhi);

    void releaseMemory();

    IplImage* imgA=NULL;
    IplImage* imgB=NULL;
    IplImage* imgC=NULL;

    IplImage* imgA_gray=NULL;
    IplImage* imgB_gray=NULL;

    IplImage* eig_img=NULL;
    IplImage* tmp_img=NULL;

    IplImage* pyrA=NULL;
    IplImage* pyrB=NULL;

    int MAX_CORNERS = 500;
    int win_size=10;

    CvPoint p0=cvPoint(0,0);
    CvPoint p1=cvPoint(0,0);


    static const double pi = 3.14159265358979323846;

    inline static double square(int a)
    {
        return a * a;
    }

    inline static void allocateOnDemand( IplImage **img, CvSize size, int depth, int channels )
    {
        if ( *img != NULL )	return;

        *img = cvCreateImage( size, depth, channels );
        if ( *img == NULL )
        {
            fprintf(stderr, "Error: Couldn't allocate image.  Out of memory?\n");
            exit(-1);
        }
    }



private slots:
    void on_Start_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_Close_clicked();

    void on_threshold_slider_valueChanged(int value);

    void on_alpha_slider_valueChanged(int value);



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
