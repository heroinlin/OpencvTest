#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
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

/// ȫ�ֱ������弰��ֵ

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

/// �Զ��庯������
void Threshold_Demo(int, void*);

/**
* @������
*/
int main(int argc, char** argv)
{
	/// ��ȡһ��ͼƬ�����ı�ͼƬ�������ɫ���ͣ��ö�ȡ��ʽΪDOS����ģʽ��
	src = imread(argv[1], 1);
	//src = imread("../images/1.jpg", 1);
	/// ��ͼƬת���ɻҶ�ͼƬ
	cvtColor(src, src_gray, CV_RGB2GRAY);

	/// ����һ��������ʾͼƬ
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// ������������������ֵ
	createTrackbar(trackbar_type,
		window_name, &threshold_type,
		max_type, Threshold_Demo);

	createTrackbar(trackbar_value,
		window_name, &threshold_value,
		max_value, Threshold_Demo);

	/// ��ʼ���Զ������ֵ����
	Threshold_Demo(0, 0);

	/// �ȴ��û������������ESC�����˳��ȴ����̡�
	while (true)
	{
		int c;
		c = waitKey(20);
		if ((char)c == 27)
		{
			break;
		}
	}

}


/**
* @�Զ������ֵ����
*/
void Threshold_Demo(int, void*)
{
	/* 0: ��������ֵ
	1: ����������ֵ
	2: �ض���ֵ
	3: 0��ֵ
	4: ��0��ֵ
	*/

	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);

	imshow(window_name, dst);
}