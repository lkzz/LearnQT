#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pCapture=NULL;//init
    nFrameNum=0;//init
    cbox_index=0;

    ui->threshold_slider->setRange(0,255);
    ui->threshold_slider->setPageStep(10);
    ui->threshold_slider->setValue(30);
    ui->threshold_slider->setTickPosition(QSlider::TicksBelow);

    ui->alpha_slider->setRange(0,30);
    ui->alpha_slider->setPageStep(3);
    ui->alpha_slider->setValue(9);
    ui->alpha_slider->setTickPosition(QSlider::TicksBelow);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Start_clicked()
{
    MainWindow::on_comboBox_currentIndexChanged(cbox_index);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    cbox_index=index;
    if(cbox_index==0)
        MainWindow::FrameDiff();
    else
        if(cbox_index==1)
            MainWindow::BackgroundDiff();
    else
            if(cbox_index==2)
                optical_flow();
               // MainWindow::OpticalFlowDetect();
                //MainWindow::OpticalFlow();
                   // MainWindow::OpencvOpticalFlow();

}

void MainWindow::optical_flow()
{
    cvReleaseCapture(&pCapture);
    CvCapture *pCapture = cvCaptureFromFile( "/home/kevin/optical_flow_input.avi" );
    if (pCapture == NULL)
    {
        fprintf(stderr, "Error: Can't open video.\n");
    }

    /* Read the video's frame size out of the AVI. */
    CvSize frame_size;
    frame_size.height = (int) cvGetCaptureProperty( pCapture, CV_CAP_PROP_FRAME_HEIGHT );
    frame_size.width =  (int) cvGetCaptureProperty( pCapture, CV_CAP_PROP_FRAME_WIDTH );

    /* Determine the number of frames in the AVI. */
    long number_of_frames;
    /* Go to the end of the AVI (ie: the fraction is "1") */
    cvSetCaptureProperty( pCapture, CV_CAP_PROP_POS_AVI_RATIO, 1. );
    /* Now that we're at the end, read the AVI position in frames */
    number_of_frames = (int) cvGetCaptureProperty( pCapture, CV_CAP_PROP_POS_FRAMES );
    /* Return to the beginning */
    cvSetCaptureProperty( pCapture, CV_CAP_PROP_POS_FRAMES, 0. );

    while(true)
    {
        static IplImage *frame = NULL, *frame1 = NULL, *frame1_1C = NULL;
        static IplImage *frame2_1C = NULL, *eig_image = NULL, *temp_image = NULL;
        static IplImage *pyramid1 = NULL, *pyramid2 = NULL;

        cvSetCaptureProperty( pCapture, CV_CAP_PROP_POS_FRAMES, current_frame );

        frame = cvQueryFrame( pCapture );
        if (frame == NULL)
        {
            /* Why did we get a NULL frame?  We shouldn't be at the end. */
            fprintf(stderr, "Error: Hmm. The end came sooner than we thought.\n");
        }

        allocateOnDemand( &frame1_1C, frame_size, IPL_DEPTH_8U, 1 );

        cvConvertImage(frame, frame1_1C, CV_CVTIMG_FLIP);

        allocateOnDemand( &frame1, frame_size, IPL_DEPTH_8U, 3 );
        cvConvertImage(frame, frame1, CV_CVTIMG_FLIP);

        /* Get the second frame of video.  Same principles as the first. */
        frame = cvQueryFrame( pCapture );
        if (frame == NULL)
        {
            fprintf(stderr, "Error: Hmm. The end came sooner than we thought.\n");
        }
        allocateOnDemand( &frame2_1C, frame_size, IPL_DEPTH_8U, 1 );
        cvConvertImage(frame, frame2_1C, CV_CVTIMG_FLIP);

        /* Preparation: Allocate the necessary storage. */
        allocateOnDemand( &eig_image, frame_size, IPL_DEPTH_32F, 1 );
        allocateOnDemand( &temp_image, frame_size, IPL_DEPTH_32F, 1 );

        /* Preparation: This array will contain the features found in frame 1. */
        CvPoint2D32f frame1_features[400];

        int number_of_features;
        number_of_features = 400;

        cvGoodFeaturesToTrack(frame1_1C, eig_image, temp_image, frame1_features,
                              &number_of_features, .01, .01, NULL);

        /* Pyramidal Lucas Kanade Optical Flow! */

        /* This array will contain the locations of the points from frame 1 in frame 2. */
        CvPoint2D32f frame2_features[400];

        char optical_flow_found_feature[400];
        float optical_flow_feature_error[400];

        /* This is the window size to use to avoid the aperture problem (see slide "Optical Flow: Overview"). */
        CvSize optical_flow_window = cvSize(3,3);
        CvTermCriteria optical_flow_termination_criteria
            = cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3 );

        /* This is some workspace for the algorithm.
         * (The algorithm actually carves the image into pyramids of different resolutions.)
         */
        allocateOnDemand( &pyramid1, frame_size, IPL_DEPTH_8U, 1 );
        allocateOnDemand( &pyramid2, frame_size, IPL_DEPTH_8U, 1 );

        cvCalcOpticalFlowPyrLK(frame1_1C, frame2_1C, pyramid1, pyramid2,
                               frame1_features, frame2_features, number_of_features,
                               optical_flow_window, 5, optical_flow_found_feature,
                               optical_flow_feature_error, optical_flow_termination_criteria, 0 );

        /* For fun (and debugging :)), let's draw the flow field. */
        for(int i = 0; i < number_of_features; i++)
        {
            /* If Pyramidal Lucas Kanade didn't really find the feature, skip it. */
            if ( optical_flow_found_feature[i] == 0 )	continue;

            int line_thickness;
            line_thickness = 1;
            /* CV_RGB(red, green, blue) is the red, green, and blue components
             * of the color you want, each out of 255.
             */
            CvScalar line_color;
            line_color = CV_RGB(255,0,0);

            CvPoint p,q;
            p.x = (int) frame1_features[i].x;
            p.y = (int) frame1_features[i].y;
            q.x = (int) frame2_features[i].x;
            q.y = (int) frame2_features[i].y;

            double angle;
            angle = atan2( (double) p.y - q.y, (double) p.x - q.x );

            double hypotenuse;
            hypotenuse = sqrt( square(p.y - q.y) + square(p.x - q.x) );

            /* Here we lengthen the arrow by a factor of three. */
            q.x = (int) (p.x - 3 * hypotenuse * cos(angle));
            q.y = (int) (p.y - 3 * hypotenuse * sin(angle));

            cvLine( frame1, p, q, line_color, line_thickness, CV_AA, 0 );
            /* Now draw the tips of the arrow.  I do some scaling so that the
             * tips look proportional to the main line of the arrow.
             */
            p.x = (int) (q.x + 9 * cos(angle + pi / 4));
            p.y = (int) (q.y + 9 * sin(angle + pi / 4));
            cvLine( frame1, p, q, line_color, line_thickness, CV_AA, 0 );
            p.x = (int) (q.x + 9 * cos(angle - pi / 4));
            p.y = (int) (q.y + 9 * sin(angle - pi / 4));
            cvLine( frame1, p, q, line_color, line_thickness, CV_AA, 0 );
        }

        cv::Mat frame1_mat=MainWindow::image_rotate(frame1);
        cv::flip(frame1_mat,frame1_mat,1);
        IplImage dst = frame1_mat;

        cv::Mat frame2_mat=MainWindow::image_rotate(frame2_1C);
        cv::flip(frame2_mat,frame2_mat,1);
        IplImage dst1 = frame2_mat;

        MainWindow::Display(frame,&dst,&dst1);

        int key_pressed;
        key_pressed = cvWaitKey(0);

        if (key_pressed == 'b' || key_pressed == 'B')
            current_frame--;
        else
            current_frame++;
        /* Don't run past the front/end of the AVI. */
        if (current_frame < 0)
            current_frame = 0;

        if (current_frame >= number_of_frames - 1)
            current_frame = number_of_frames - 2;
    }

}

void MainWindow::FrameDiff()
{

    ui->alpha_slider->setDisabled(true);

    cvReleaseCapture(&pCapture);
    pCapture=cvCaptureFromCAM(0);
    IplImage* frame=NULL;
    nFrameNum=0;

    while(frame = cvQueryFrame(pCapture))
    {
//        cvCvtColor(frame,frame,CV_BGR2RGB);
        nFrameNum++;

        cvReleaseImage(&src);//memory control

        src=cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U,3);
        cvCopy(frame,src);

        if( nFrameNum==1 )
        {
            last_img=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,3);
            img_diff=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,3);
            gray_diff=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
            binary_img=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);

            cvCopy(src,last_img);
            cvZero(binary_img);
        }
        else
        {
            cvAbsDiff(src,last_img,img_diff);

            cvCvtColor(img_diff,gray_diff,CV_BGR2GRAY);
            cvSmooth(gray_diff,gray_diff,CV_GAUSSIAN,3,0,0);//gaussian smooth

            cvThreshold(gray_diff,binary_img,lowThreshold,255,CV_THRESH_BINARY);

            cvDilate(binary_img,binary_img);
            cvErode(binary_img,binary_img);

            cvCopy(src,last_img);
        }

        if(27==cvWaitKey(33))
            break;

        MainWindow::Display(src,img_diff,binary_img);

  //      MainWindow::releaseMemory();

    }
}


void MainWindow::BackgroundDiff()
{
    ui->alpha_slider->setEnabled(true);

    cvReleaseCapture(&pCapture);
    pCapture=cvCaptureFromCAM(0);
  //  IplImage* pFrame=NULL;
    nFrameNum=0;

    while(pFrame = cvQueryFrame( pCapture ))
    {
        nFrameNum++;
        //如果是第一帧，需要申请内存，并初始化

        if(nFrameNum == 1)
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
            cvDilate(pFrMat,pFrMat);
            cvErode(pFrMat,pFrMat);

            cvThreshold(pFrMat, pFrImg, lowThreshold, 255.0, CV_THRESH_BINARY);
            //更新背景
            cvRunningAvg(pFrameMat, pBkMat, alpha,0);
            //将背景转化为图像格式，用以显示
            cvConvert(pBkMat, pBkImg);
            pFrame->origin = IPL_ORIGIN_BL;
            pFrImg->origin = IPL_ORIGIN_BL;
            pBkImg->origin = IPL_ORIGIN_BL;

        }

        if(27==cvWaitKey(33))
            break;

        MainWindow::Display(pFrame,pBkImg,pFrImg);
    }

}

void MainWindow::OpticalFlow()
{
    cvReleaseCapture(&pCapture);
 //   pCapture=cvCaptureFromCAM(0);

    //use webcam
    CvCapture* cam = cvCaptureFromCAM( 0 ) ;
    while(1)
    {
        //get a color image
        IplImage* frame = cvQueryFrame(cam) ;

        CvSize img_sz = cvGetSize(frame);
        const int win_size = 10 ;

        //convert the image to grey image
        IplImage* frame_prev = cvQueryFrame(cam) ;
        IplImage* img_prev = cvCreateImage(img_sz,IPL_DEPTH_8U,1) ;
        cvCvtColor( frame_prev,img_prev ,CV_BGR2GRAY);

        //convert the image to grey image
        IplImage* frame_cur = cvQueryFrame(cam) ;
        IplImage* img_curr = cvCreateImage(img_sz,IPL_DEPTH_8U,1) ;
        cvCvtColor( frame_cur,img_curr ,CV_BGR2GRAY);

        //create a imge to display result
        IplImage* img_res = cvCreateImage(img_sz,IPL_DEPTH_8U,1) ;
        for ( int y = 0 ; y < img_sz.height ; ++y )
        {
            uchar* ptr = (uchar*)( img_res->imageData + y * img_res->widthStep ) ;
            for ( int x = 0 ; x <img_res->width; ++x )
            {
                ptr[x] = 255 ;
            }
        }

        //get good features
        IplImage* img_eig = cvCreateImage(img_sz,IPL_DEPTH_32F,1) ;
        IplImage* img_temp = cvCreateImage(img_sz,IPL_DEPTH_32F,1) ;
        int corner_count = MAX_CORNERS ;
        CvPoint2D32f*  features_prev = new CvPoint2D32f[MAX_CORNERS] ;

        cvGoodFeaturesToTrack(
                    img_prev,
                    img_eig,
                    img_temp,
                    features_prev,
                    &corner_count,
                    0.01,
                    5.0,
                    0,
                    3,
                    0,
                    0.4
                    );

        cvFindCornerSubPix(
                    img_prev,
                    features_prev,
                    corner_count,
                    cvSize(win_size,win_size),
                    cvSize(-1,-1),
                    cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER,20,0.03)
                    );

                // L-K
                char feature_found[ MAX_CORNERS ] ;
                float feature_errors[ MAX_CORNERS ] ;

                CvSize pyr_sz = cvSize( frame->width + 8 ,frame->height / 3 ) ;

                IplImage* pyr_prev = cvCreateImage(pyr_sz,IPL_DEPTH_32F,1) ;
                IplImage* pyr_cur = cvCreateImage(pyr_sz,IPL_DEPTH_32F,1) ;
                CvPoint2D32f*  features_cur = new CvPoint2D32f[ MAX_CORNERS ] ;

                cvCalcOpticalFlowPyrLK(
                    img_prev,
                    img_curr,
                    pyr_prev,
                    pyr_cur,
                    features_prev,
                    features_cur,
                    corner_count,
                    cvSize(win_size,win_size),
                    5,
                    feature_found,
                    feature_errors,
                    cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER,20,0.3),
                    0
                    );

                for ( int i = 0 ; i < corner_count ; i++)
                {
                    if ( 0 == feature_found[i] || feature_errors[i] > 550 )
                    {
                 //       printf("error is %f \n" , feature_errors[i] ) ;
                        continue ;
                    }

                 //   printf("find it !\n") ;

                    CvPoint pt_prev = cvPoint( features_prev[i].x , features_prev[i].y ) ;
                    CvPoint pt_cur = cvPoint( features_cur[i].x , features_cur[i].y ) ;

                    cvLine( img_res,pt_prev,pt_cur,CV_RGB( 255,0,0),2 );
                }

        if(27==cvWaitKey(33))
            break;

        MainWindow::Display(frame_cur,img_curr,img_res);

        cvReleaseImage(&img_curr);
        cvReleaseImage(&img_eig);
        cvReleaseImage(&img_prev);
        cvReleaseImage(&img_res);
        cvReleaseImage(&img_temp);

    }
}


void MainWindow::OpticalFlowDetect()
{
    cvReleaseCapture(&pCapture);
    pCapture=cvCaptureFromCAM(0);

    int corner_count = 1000;

     CvTermCriteria criteria;
     criteria = cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 64, 0.01);

     IplImage *src_img1;
     IplImage *src_img2;

     IplImage *dst_img;
     IplImage *pre_img;
     IplImage *result;


     IplImage *eig_img;
     IplImage *temp_img;

     IplImage *prev_pyramid;
     IplImage *curr_pyramid;

     CvPoint2D32f *corners1;
     CvPoint2D32f *corners2;
     corners1 = (CvPoint2D32f *) cvAlloc (corner_count * sizeof (CvPoint2D32f));
     corners2 = (CvPoint2D32f *) cvAlloc (corner_count * sizeof (CvPoint2D32f));

     char *status;
     status = (char *) cvAlloc (corner_count);

     while (1)
     {

      pre_img = cvQueryFrame(pCapture);

      CvSize img_sz = cvGetSize(pre_img);
      src_img1 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
      cvCvtColor(pre_img, src_img1, CV_RGB2GRAY);

      dst_img = cvQueryFrame(pCapture);
      src_img2 = cvCreateImage(img_sz, IPL_DEPTH_8U, 1);
      cvCvtColor(dst_img, src_img2, CV_RGB2GRAY);

      result=cvCreateImage(img_sz,IPL_DEPTH_8U,1);
      cvZero(result);

      eig_img = cvCreateImage (img_sz, IPL_DEPTH_32F, 1);
      temp_img = cvCreateImage (img_sz, IPL_DEPTH_32F, 1);


      prev_pyramid = cvCreateImage (cvSize (src_img1->width + 8, src_img1->height / 3), IPL_DEPTH_8U, 1);
      curr_pyramid = cvCreateImage (cvSize (src_img1->width + 8, src_img1->height / 3), IPL_DEPTH_8U, 1);



      cvGoodFeaturesToTrack (src_img1, eig_img, temp_img, corners1, &corner_count, 0.001, 5, NULL);

      cvCalcOpticalFlowPyrLK (src_img1, src_img2, prev_pyramid, curr_pyramid,
       corners1, corners2, corner_count, cvSize (10, 10), 4, status, NULL, criteria, 0);

      for (int i = 0; i < corner_count; i++)
      {

          if (status[i])
              cvLine (dst_img, cvPointFrom32f (corners1[i]), cvPointFrom32f (corners2[i]), CV_RGB (255, 0, 0), 1, CV_AA, 0);
      }

      if(27==cvWaitKey(33))
          break;

    //  cvCvtScale(dst_img,result,1.0/255,0);
      MainWindow::Display(pre_img,src_img2,dst_img);

     }
}

void MainWindow::OpencvOpticalFlow()
{
    cvReleaseCapture(&pCapture);
    pCapture=cvCaptureFromCAM(0);

    IplImage* pre;
    IplImage* next;

    int corner_count=MAX_CORNERS;

    while(1)
    {
        //
        pre=cvQueryFrame(pCapture);
        next=cvQueryFrame(pCapture);

        CvSize img_sz=cvGetSize(pre);
        IplImage* imgC=cvCreateImage(img_sz,IPL_DEPTH_8U,1);

        //
        IplImage* imgA=cvCreateImage(img_sz,IPL_DEPTH_8U,1);
        IplImage* imgB=cvCreateImage(img_sz,IPL_DEPTH_8U,1);
        cvCvtColor(pre,imgA,CV_BGR2GRAY);
        cvCvtColor(next,imgB,CV_BGR2GRAY);

        //

        IplImage* eig_image=cvCreateImage(img_sz,IPL_DEPTH_32F,1);
        IplImage* tmp_image=cvCreateImage(img_sz,IPL_DEPTH_32F,1);

        CvPoint2D32f* cornersA = new CvPoint2D32f[ MAX_CORNERS ];


        //
        cvGoodFeaturesToTrack(
             imgA,
             eig_image,
             tmp_image,
             cornersA,
             &corner_count,
             0.01,
             5.0,
             0,
             3,
             0,
             0.04
         );

        cvFindCornerSubPix(
            imgA,
            cornersA,
            corner_count,
            cvSize(win_size,win_size),
            cvSize(-1,-1),
            cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03)
        );


        char features_found[ MAX_CORNERS ];
        float feature_errors[ MAX_CORNERS ];

        //
        CvSize pyr_sz = cvSize( imgA->width+8, imgB->height/3 );

        IplImage* pyrA = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
        IplImage* pyrB = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
        CvPoint2D32f* cornersB  = new CvPoint2D32f[ MAX_CORNERS ];

        cvCalcOpticalFlowPyrLK(
             imgA,
             imgB,
             pyrA,
             pyrB,
             cornersA,
             cornersB,
             corner_count,
             cvSize( win_size,win_size ),
             5,
             features_found,
             feature_errors,
             cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3 ),
             0
          );

        for( int i=0; i<corner_count; i++ ) {
           if( features_found[i]==0|| feature_errors[i]>550 ) {
       //       printf("Error is %f/n",feature_errors[i]);
              continue;
           }
       //    printf("Got it/n");
           CvPoint p0 = cvPoint(
              cvRound( cornersA[i].x ),
              cvRound( cornersA[i].y )
           );

           CvPoint p1 = cvPoint(
              cvRound( cornersB[i].x ),
              cvRound( cornersB[i].y )
           );

           cvLine( imgC, p0, p1, CV_RGB(255,0,0),2 );
        }

        if(27==cvWaitKey(33))
            break;
        MainWindow::Display(imgA,imgB,imgC);

    }

}


void MainWindow::Display(IplImage *src_image, IplImage *diff_img, IplImage *binary_mhi)
{
    cvCvtColor(src_image,src_image,CV_BGR2RGB);

    int width=src_image->width;
    int height=src_image->height;

    //display src image
    QImage src_qimg=QImage((uchar*)src_image->imageData,width,height,QImage::Format_RGB888);
    ui->src_label->clear();
    ui->src_label->setPixmap(QPixmap::fromImage(src_qimg));
    //ui->src_label->resize((int)frame->width,(int)frame->height);

    //display difference image
 //   QMessageBox::warning(this,"Channel",tr("(%1)").arg(diff_img->nChannels));

    if(diff_img->nChannels == 1)
    {
        QImage diff_qimg=QImage((uchar*)diff_img->imageData,width,height,QImage::Format_Indexed8);
        ui->diff_label->clear();
        ui->diff_label->setPixmap(QPixmap::fromImage(diff_qimg));
    }
    else
    {
        cvCvtColor(diff_img,diff_img,CV_BGR2RGB);
        QImage diff_qimg=QImage((uchar*)diff_img->imageData,width,height,QImage::Format_RGB888);
        ui->diff_label->clear();
        ui->diff_label->setPixmap(QPixmap::fromImage(diff_qimg));
    }


    //display binary image
    QImage binary_qimg=QImage((uchar*)binary_mhi->imageData,width,height,QImage::Format_Indexed8);
    ui->binary_label->clear();
    ui->binary_label->setPixmap(QPixmap::fromImage(binary_qimg));
  //  ui->binary_label->resize(ui->binary_label->pixmap()->size());


}

void MainWindow::on_Close_clicked()
{
    //释放图像和矩阵
    MainWindow::releaseMemory();
    cvReleaseCapture(&pCapture);

    close();
}

void MainWindow::releaseMemory()
{
    cvReleaseImage(&src);
    cvReleaseImage(&last_img);
    cvReleaseImage(&img_diff);
    cvReleaseImage(&gray_diff);
    cvReleaseImage(&binary_img);

    cvReleaseImage(&pFrImg);
    cvReleaseImage(&pBkImg);
    cvReleaseMat(&pFrameMat);
    cvReleaseMat(&pFrMat);
    cvReleaseMat(&pBkMat);

    cvReleaseImage(&imgA);
    cvReleaseImage(&imgB);
    cvReleaseImage(&imgC);
    cvReleaseImage(&imgA_gray);
    cvReleaseImage(&imgB_gray);
    cvReleaseImage(&pyrA);
    cvReleaseImage(&pyrB);
    cvReleaseImage(&eig_img);
    cvReleaseImage(&tmp_img);


}

void MainWindow::on_threshold_slider_valueChanged(int value)
{
    lowThreshold=value;
    ui->threshold->setText(tr("%1").arg(lowThreshold));
}

void MainWindow::on_alpha_slider_valueChanged(int value)
{
    alpha=double(value/100.0);
    ui->alpha_value->setText(tr("%1").arg(alpha));
}

cv::Mat MainWindow::image_rotate(IplImage *src)
{
    cv::Mat image(src);

     if (image.empty())
     {
      std::cout<<"read image failure"<<std::endl;
   //   return -1;
     }

     cv::Point2f center = cv::Point2f(image.cols / 2, image.rows / 2);  // 旋转中心
     double angle = 180;  // 旋转角度
     double scale = 1.0; // 缩放尺度

     cv::Mat rotateMat;
     rotateMat = cv::getRotationMatrix2D(center, angle, scale);

     cv::Mat rotateImg;
     cv::warpAffine(image, rotateImg, rotateMat, image.size());

   //  IplImage dst = rotateImg;

     return rotateImg;

}
