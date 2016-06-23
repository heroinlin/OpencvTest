#include <iostream>
#include <core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#ifdef _DEBUG 

#pragma comment( lib, "opencv_core249d.lib" )
#pragma comment( lib, "opencv_highgui249d.lib" )
#pragma comment( lib, "opencv_imgproc249d.lib" )
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
#pragma comment( lib, "IlmImf.lib")
#pragma comment( lib, "libjasper.lib")
#pragma comment( lib, "libjpeg.lib")
#pragma comment( lib, "libpng.lib")
#pragma comment( lib, "libtiff.lib")
#pragma comment( lib, "zlib.lib")
#endif
#pragma comment( lib, "vfw32.lib" )  
#pragma comment( lib, "comctl32.lib" ) 
using namespace std;
using namespace cv;
int main()
{
	/*cv::Mat a = (cv::Mat_<int>(2,2)<<1,2,3,4);
	cv::Mat b = (cv::Mat_<int>(2,2)<<5,6,7,8);
	cv::Mat c = (cv::Mat_<int>(2,2)<<9,10,11,12);
	cv::Mat d = (cv::Mat_<int>(2,2)<<13,14,15,16);*/
	Mat combine, combine1, combine2;
	Mat a = imread("../images/cat.jpg");
	Mat b = imread("../images/cat_copy.jpg");
	Mat c = imread("../images/cat_copy.jpg");
	Mat d = imread("../images/cat.jpg");
	hconcat(a, b, combine1);
	hconcat(c, d, combine2);
	vconcat(combine1, combine2, combine);
	namedWindow("Combine", CV_WINDOW_AUTOSIZE);
	imshow("Combine", combine);
	waitKey(0);
	//cout<<"Combine=:"<<combine<<endl;
	system("pause");
	return 0;
}