#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
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
#pragma comment( lib, "IlmImfd.lib")
#pragma comment( lib, "libjasperd.lib")
#pragma comment( lib, "libjpegd.lib")
#pragma comment( lib, "libpngd.lib")
#pragma comment( lib, "libtiffd.lib")
#pragma comment( lib, "zlibd.lib")
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
#pragma comment( lib, "IlmImf.lib")
#pragma comment( lib, "libjasper.lib")
#pragma comment( lib, "libjpeg.lib")
#pragma comment( lib, "libpng.lib")
#pragma comment( lib, "libtiff.lib")
#pragma comment( lib, "zlib.lib")
#endif
#pragma comment( lib, "vfw32.lib" )  
#pragma comment( lib, "comctl32.lib" ) 
using namespace cv;

void main()
{
	cv::Mat image = cv::Mat::zeros(320, 288, CV_32FC3);
	int i,j;
	
	for (i = 0; i < 320; i++)
		for (j = 0; j <288; j++)
		{
			image.at<Vec3f>(i, j)[0] = 0.2;
			image.at<Vec3f>(i, j)[1] = 0.2;
			image.at<Vec3f>(i, j)[2] = 0.1;
		}
	//cv::Mat image_flip;
	//cv::flip(image, image_flip, 1);
	imshow("flip",image);
	cvWaitKey(0);
	//cv::imwrite("../images/flip.jpg", image_flip);
}