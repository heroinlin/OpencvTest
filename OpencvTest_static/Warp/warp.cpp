#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
//图像仿射变换
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
using namespace cv;
using namespace std;

//全局变量
char* source_window = "Source image";
char* warp_window = "Warp";
char* warp_rotate_window = "Warp + Rotate";

int main(int argc, char** argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];//两个数组指针用于存储变换用的点

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst;

	//加载彩色图像
	//src = imread(argv[1], 1);
	src = imread("../images/1.jpg", 1);

	//设置目标图像的类型和大小与原输入图像一致
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	//设置3个点来计算仿射变换
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols*0.0, src.rows*0.33);
	dstTri[1] = Point2f(src.cols*0.85, src.rows*0.25);
	dstTri[2] = Point2f(src.cols*0.15, src.rows*0.7);

	//获得仿射变换 warp_mat仿射变换2x3矩阵
	warp_mat = getAffineTransform(srcTri, dstTri);

	//对原输入图像应用仿射变换
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	//===变换后旋转图像===\\ 

	//以图像为中心计算一个旋转矩阵
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	//获得满足上述条件的旋转矩阵
	rot_mat = getRotationMatrix2D(center, angle, scale);

	//旋转变换后的图像
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());


	//创建窗口用于显示输出
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	//namedWindow(source_window, (320,240));
	imshow(source_window, src);

	namedWindow(warp_window, CV_WINDOW_AUTOSIZE);
	//namedWindow(warp_window, (320, 240));
	imshow(warp_window, warp_dst);

	namedWindow(warp_rotate_window, CV_WINDOW_AUTOSIZE);
	//namedWindow(warp_rotate_window, (320, 240));
	imshow(warp_rotate_window, warp_rotate_dst);

	//等待
	waitKey(0);

	return 0;
}