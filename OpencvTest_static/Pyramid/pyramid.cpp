#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//ͼ�������
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

/// ȫ�ֱ���
Mat src, dst, tmp;
char* window_name = "Pyramids Demo";


/**
* @���� main
*/
int main(int argc, char** argv)
{
	/// ָʾ˵��
	printf("\n Zoom In-Out demo  \n ");
	printf("------------------ \n");
	printf(" * [u] -> Zoom in  \n");
	printf(" * [d] -> Zoom out \n");
	printf(" * [ESC] -> Close program \n \n");

	/// ����ͼ�� - �ߴ�����ܱ� 2^{n} ����
	src = imread("../images/1.jpg");
	if (!src.data)
	{
		printf(" No data! -- Exiting the program \n");
		return -1;
	}

	tmp = src;
	dst = tmp;

	/// ������ʾ����
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	imshow(window_name, dst);

	/// ѭ��
	while (true)
	{
		int c;
		c = waitKey(10);

		if ((char)c == 27)
		{
			break;
		}
		if ((char)c == 'u')
		{
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		}
		else if ((char)c == 'd')
		{
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}

		imshow(window_name, dst);
		tmp = dst;
	}
	return 0;
}