/**************************************************
* cvLoadImage, cvSaveImage, cvCreateImage, cvCopy以及图像显示的例子
**************************************************/

/***********************************************************************
* OpenCV example
* By Shiqi Yu 2006
***********************************************************************/
#ifdef _DEBUG 

#pragma comment( lib, "opencv_core249d.lib" )
#pragma comment( lib, "opencv_highgui249d.lib" )
#pragma comment( lib, "opencv_imgproc249d.lib" )
//#pragma comment( lib, "opencv_calib3d249d.lib" )
//#pragma comment( lib, "opencv_contrib249d.lib" )
//#pragma comment( lib, "opencv_features2d249d.lib" )
//#pragma comment( lib, "opencv_flann249d.lib" )
//#pragma comment( lib, "opencv_gpu249d.lib" )
//#pragma comment( lib, "opencv_legacy249d.lib" )
//#pragma comment( lib, "opencv_ml249d.lib" )
//#pragma comment( lib, "opencv_nonfree249d.lib" )
//#pragma comment( lib, "opencv_objdetect249d.lib" )
//#pragma comment( lib, "opencv_ocl249d.lib" )
//#pragma comment( lib, "opencv_photo249d.lib" )
//#pragma comment( lib, "opencv_stitching249d.lib" )
//#pragma comment( lib, "opencv_superres249d.lib" )
//#pragma comment( lib, "opencv_ts249d.lib" )
//#pragma comment( lib, "opencv_video249d.lib" )
//#pragma comment( lib, "opencv_videostab249d.lib" )
#else 
#pragma comment( lib, "opencv_core249.lib" )
#pragma comment( lib, "opencv_highgui249.lib" )
#pragma comment( lib, "opencv_imgproc249.lib" )
//#pragma comment( lib, "opencv_calib3d249.lib" )
//#pragma comment( lib, "opencv_contrib249.lib" )
//#pragma comment( lib, "opencv_features2d249.lib" )
//#pragma comment( lib, "opencv_flann249.lib" )
//#pragma comment( lib, "opencv_gpu249.lib" )
//#pragma comment( lib, "opencv_legacy249.lib" )
//#pragma comment( lib, "opencv_ml249.lib" )
//#pragma comment( lib, "opencv_nonfree249.lib" )
//#pragma comment( lib, "opencv_objdetect249.lib" )
//#pragma comment( lib, "opencv_ocl249.lib" )
//#pragma comment( lib, "opencv_photo249.lib" )
//#pragma comment( lib, "opencv_stitching249.lib" )
//#pragma comment( lib, "opencv_superres249.lib" )
//#pragma comment( lib, "opencv_ts249.lib" )
//#pragma comment( lib, "opencv_video249.lib" )
//#pragma comment( lib, "opencv_videostab249.lib" )
#endif
//#pragma comment( lib, "vfw32.lib" )  
//#pragma comment( lib, "comctl32.lib" ) 
#include "cv.h"
#include "highgui.h"

int main(int argc, char** argv)
{
	IplImage* pImg; //声明IplImage指针
	//pImg = cvLoadImage(argv[1], 0);
	pImg = cvLoadImage("../images/cat.jpg", 0);
	//char *path = argv[2];
	char *path = "../images/cat_copy.jpg";
	//载入图像，强制转化为Gray
	//if (argc == 3 &&
	if (argc <= 3 &&
		(pImg  != 0))
	{

		IplImage* pImg2 = cvCreateImage(cvGetSize(pImg),
			pImg->depth,
			pImg->nChannels);
		cvCopy(pImg, pImg2, NULL);

		cvSaveImage(path, pImg2);//把图像写入文件

		cvNamedWindow("Image", 1);//创建窗口
		cvShowImage("Image", pImg);//显示图像

		cvWaitKey(0); //等待按键

		cvDestroyWindow("Image");//销毁窗口
		cvReleaseImage(&pImg); //释放图像
		cvReleaseImage(&pImg2); //释放图像
		return 0;
	}

	return -1;
}