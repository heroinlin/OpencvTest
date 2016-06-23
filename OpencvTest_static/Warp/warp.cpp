#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
//ͼ�����任
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

//ȫ�ֱ���
char* source_window = "Source image";
char* warp_window = "Warp";
char* warp_rotate_window = "Warp + Rotate";

int main(int argc, char** argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];//��������ָ�����ڴ洢�任�õĵ�

	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst;

	//���ز�ɫͼ��
	//src = imread(argv[1], 1);
	src = imread("../images/1.jpg", 1);

	//����Ŀ��ͼ������ͺʹ�С��ԭ����ͼ��һ��
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	//����3�������������任
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols*0.0, src.rows*0.33);
	dstTri[1] = Point2f(src.cols*0.85, src.rows*0.25);
	dstTri[2] = Point2f(src.cols*0.15, src.rows*0.7);

	//��÷���任 warp_mat����任2x3����
	warp_mat = getAffineTransform(srcTri, dstTri);

	//��ԭ����ͼ��Ӧ�÷���任
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	//===�任����תͼ��===\\ 

	//��ͼ��Ϊ���ļ���һ����ת����
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	//�������������������ת����
	rot_mat = getRotationMatrix2D(center, angle, scale);

	//��ת�任���ͼ��
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());


	//��������������ʾ���
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	//namedWindow(source_window, (320,240));
	imshow(source_window, src);

	namedWindow(warp_window, CV_WINDOW_AUTOSIZE);
	//namedWindow(warp_window, (320, 240));
	imshow(warp_window, warp_dst);

	namedWindow(warp_rotate_window, CV_WINDOW_AUTOSIZE);
	//namedWindow(warp_rotate_window, (320, 240));
	imshow(warp_rotate_window, warp_rotate_dst);

	//�ȴ�
	waitKey(0);

	return 0;
}