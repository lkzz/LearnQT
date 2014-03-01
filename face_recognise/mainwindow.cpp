#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalSlider->setRange(0,255);
    ui->verticalSlider->setPageStep(10);
    ui->verticalSlider->setValue(30);
    ui->verticalSlider->setTickPosition(QSlider::TicksBelow);

    low_Threshold=30;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ProcessFrame(const IplImage* src_img,IplImage* binary_img)
{
    cvCvtColor(src_image,src_image,CV_BGR2RGB);
    #define MHI_DURATION 1
    double timestamp = clock()/100;

    static IplImage* last_img=NULL;//last frame
    static IplImage* color_silh=NULL;//diff frame
    static IplImage* gray_silh=NULL;//gray diff frame

    static IplImage* mhi=NULL;

    if(NULL==last_img && NULL==color_silh && NULL==gray_silh)
    {
        CvSize size=cvGetSize(src_img);

        last_img = cvCreateImage(size,8,3);
        color_silh = cvCreateImage(size,8,3);
        gray_silh = cvCreateImage(size,8,1);

        mhi = cvCreateImage(size,IPL_DEPTH_32F,1);

        cvCopy(src_img,last_img);

        cvZero(binary_img);
    }
    else
    {
        cvAbsDiff(src_img,last_img,color_silh);
        cvCopy(src_img,last_img);
        cvCvtColor(color_silh,gray_silh,CV_RGB2GRAY);


        cvSmooth(gray_silh,gray_silh,CV_GAUSSIAN,3,0,0);//gaussian smooth
        cvThreshold(gray_silh,gray_silh,low_Threshold,255,CV_THRESH_BINARY);

        cvDilate(gray_silh,gray_silh);//dilate
        cvErode(gray_silh,gray_silh);//erode

        cvUpdateMotionHistory(gray_silh,mhi,timestamp,MHI_DURATION);

        cvCvtScale(mhi,binary_img,255/MHI_DURATION);
        cvThreshold(binary_img,binary_img,0,255,CV_THRESH_BINARY);
    }
}

void MainWindow::BackgroundProcess()
{
    //声明IplImage指针
    IplImage* pFrame = NULL;
    IplImage* pFrImg = NULL;
    IplImage* pBkImg = NULL;
    
    CvMat* pFrameMat = NULL;
    CvMat* pFrMat = NULL;
    CvMat* pBkMat = NULL;
    CvCapture* pCapture = NULL;
    int nFrmNum = 0;

    cvNamedWindow("video");
    cvNamedWindow("background");
    cvNamedWindow("foreground");


    pCapture = cvCaptureFromCAM(0);           //从摄像头读入视频用此
    while(pFrame = cvQueryFrame( pCapture ))
    {
        nFrmNum++;
        //如果是第一帧，需要申请内存，并初始化
        if(nFrmNum == 1)
        {
            pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),IPL_DEPTH_8U,1);
            pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U,1);
            pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
            pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
            pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
            //转化成单通道图像再处理
            cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
            cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
            cvConvert(pFrImg, pFrameMat);
            cvConvert(pFrImg, pFrMat);
            cvConvert(pFrImg, pBkMat);
        }
        else
        {
            cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
            cvConvert(pFrImg, pFrameMat);
            //先做高斯滤波，以平滑图像
            cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
            //当前帧跟背景图相减
            cvAbsDiff(pFrameMat, pBkMat, pFrMat);
            //二值化前景图
            cvThreshold(pFrMat, pFrImg, 10, 255.0, CV_THRESH_BINARY);
            //更新背景
            cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
            //将背景转化为图像格式，用以显示
            cvConvert(pBkMat, pBkImg);
            pFrame->origin = IPL_ORIGIN_BL;
            pFrImg->origin = IPL_ORIGIN_BL;
            pBkImg->origin = IPL_ORIGIN_BL;
            cvShowImage("video", pFrame);
            cvShowImage("background", pBkImg);
            cvShowImage("foreground", pFrImg);
            //如果有按键事件，则跳出循环
            //此等待也为cvShowImage函数提供时间完成显示
            //等待时间可以根据CPU速度调整
            if( cvWaitKey(2) >= 0 )
                break;
        }
    }
    //销毁窗口
    cvDestroyWindow("video");
    cvDestroyWindow("background");
    cvDestroyWindow("foreground");
    //释放图像和矩阵
    cvReleaseImage(&pFrImg);
    cvReleaseImage(&pBkImg);
    cvReleaseMat(&pFrameMat);
    cvReleaseMat(&pFrMat);
    cvReleaseMat(&pBkMat);
    cvReleaseCapture(&pCapture);
}

void MainWindow::on_Start_clicked()
{
    capture=cvCaptureFromCAM(0);

    if(capture)
    {
        IplImage* frame=NULL;
        int width=(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
        int height=(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);

        CvSize frame_size = cvSize(width,height);
      //  CvSize frame_size = cvSize(ui->binary_label->width(),ui->binary_label->height());
        binary_mhi = cvCreateImage(frame_size,8,1);
        src_image = cvCreateImage(frame_size,8,3);

        while(frame = cvQueryFrame(capture))
        {
            nFrameNum++;

            cvCopy(frame,src_image);
            ProcessFrame(src_image,binary_mhi);

            if(27==cvWaitKey(33))
                break;

            QImage src_qimg=QImage((uchar*)src_image->imageData,width,height,QImage::Format_RGB888);
            ui->src_label->clear();
            ui->src_label->setPixmap(QPixmap::fromImage(src_qimg));
            ui->src_label->resize((int)frame->width,(int)frame->height);

            QImage binary_qimg=QImage((uchar*)binary_mhi->imageData,width,height,QImage::Format_Indexed8);
            ui->binary_label->clear();
            ui->binary_label->setPixmap(QPixmap::fromImage(binary_qimg));
            ui->binary_label->resize(ui->binary_label->pixmap()->size());

        }


    }
}


void MainWindow::on_End_clicked()//pause the camera
{
    cvReleaseCapture(&capture);

}

void MainWindow::on_Close_clicked()//exit QDialog
{
    cvReleaseCapture(&capture);
    cvReleaseImage(&src_image);
    cvReleaseImage(&binary_mhi);
    close();
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    low_Threshold=value;
    ui->low_Threshold->setText(tr("%1").arg(low_Threshold));
  //  ui->low_Threshold->move(ui->verticalSlider->tickPosition().pos());
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(1==index)
    {
        MainWindow::on_End_clicked();
        BackgroundProcess();
    }


}

