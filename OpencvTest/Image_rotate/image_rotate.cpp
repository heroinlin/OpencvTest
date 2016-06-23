#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
//��תͼ��
using namespace cv;

//ȫ�ֱ���
Mat src, dst;
Mat map_x, map_y;
char* remap_window = "Remap demo";
int ind = 0;
//����ͷ����
void update_map(void);

int main(int argc, char** argv)
{
	//���ز�ɫͼ��
	//src = imread(argv[1], 1);
	src = imread("../images/1.jpg", 1);
	//����������ͼ���С��dst,map_x,map_y
	dst.create(src.size(), src.type());
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);

	//��������
	namedWindow(remap_window, CV_WINDOW_AUTOSIZE);

	//����ѭ��
	while (true)
	{
		//ÿ��һ�룬����ESC�˳�����
		int c = waitKey(1000);

		if ((char)c == 27)
		{
			break;
		}

		//����map_x,map_y,Ȼ��Ӧ��remap����
		update_map();
		remap(src, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

		//��ʾ������
		imshow(remap_window, dst);
	}
	return 0;
}
//�������͵�mappings
void update_map()
{
	ind = ind % 4;//����ֵ������caseѡ��

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			switch (ind)
			{
			case 0://��Сͼ������
				if (i > src.cols*0.25 && i < src.cols*0.75 && j > src.rows*0.25 && j < src.rows*0.75)
				{
					map_x.at<float>(j, i) = 2 * (i - src.cols*0.25) + 0.5;
					map_y.at<float>(j, i) = 2 * (j - src.rows*0.25) + 0.5;
				}
				else
				{
					map_x.at<float>(j, i) = 0;
					map_y.at<float>(j, i) = 0;
				}
				break;
			case 1://���·�תͼ��
				map_x.at<float>(j, i) = i;
				map_y.at<float>(j, i) = src.rows - j;
				break;
			case 2://���ҷ�תͼ��
				map_x.at<float>(j, i) = src.cols - i;
				map_y.at<float>(j, i) = j;
				break;
			case 3://�������ҷ�תͼ��
				map_x.at<float>(j, i) = src.cols - i;
				map_y.at<float>(j, i) = src.rows - j;
				break;
			} //ѡ�����
		}
	}
	ind++;
}
