// define the show image
#include "PS_Algorithm.h"
#include <iostream>
#include <string>
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

void Show_Image(Mat& Image, const string& str)
{
	namedWindow(str.c_str(), CV_WINDOW_AUTOSIZE);
	imshow(str.c_str(), Image);

}