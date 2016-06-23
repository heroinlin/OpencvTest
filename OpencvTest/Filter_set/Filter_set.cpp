#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
//�Զ����˲���
using namespace cv;

/** @����main */
int main(int argc, char** argv)
{
	/// ��������
	Mat src, dst;

	Mat kernel;
	Point anchor;
	double delta;
	int ddepth;
	int kernel_size;
	char* window_name = "filter2D Demo";

	int c;

	/// ����ͼ��
	//src = imread(argv[1]);
	src = imread("../images/1.jpg");
	if (!src.data)
	{
		return -1;
	}

	/// ��������
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// ��ʼ���˲�������
	anchor = Point(-1, -1);
	delta = 0;
	ddepth = -1;

	/// ѭ�� - ÿ��0.5�룬��һ����ͬ�ĺ�����ͼ������˲�
	int ind = 0;
	while (true)
	{
		c = waitKey(500);
		/// ��'ESC'���˳�����
		if ((char)c == 27)
		{
			break;
		}

		/// ���¹�һ�����˲����ĺ˴�С
		kernel_size = 3 + 2 * (ind % 5);
		kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);

		/// ʹ���˲���
		filter2D(src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
		imshow(window_name, dst);
		ind++;
	}

	return 0;
}