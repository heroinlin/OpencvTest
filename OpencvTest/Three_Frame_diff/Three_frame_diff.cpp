// frame_3diff.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#define threshold_diff1 10 //���ü�֡���ֵ
#define threshold_diff2 10 //���ü�֡���ֵ

using namespace cv;
using namespace std;

int main(int argc, unsigned char* argv[])
{
	Mat img_src1, img_src2, img_src3;//3֡����Ҫ3֡ͼƬ
	Mat img_dst, gray1, gray2, gray3;
	Mat gray_diff1, gray_diff2;//�洢2�������ͼƬ
	Mat gray;//������ʾǰ����
	//char *path = argv[1];
	char *path = "../videos/1.avi";
	VideoCapture vido_file(path);//���������Ӧ���ļ���
	namedWindow("foreground", 0);
		while (vido_file.get(CV_CAP_PROP_POS_FRAMES)<vido_file.get(CV_CAP_PROP_FRAME_COUNT) - 1)
		{
			vido_file >> img_src1;
			cvtColor(img_src1, gray1, CV_BGR2GRAY);

			waitKey(5);
			vido_file >> img_src2;
			cvtColor(img_src2, gray2, CV_BGR2GRAY);
			imshow("video_src", img_src2);//

			waitKey(5);
			vido_file >> img_src3;
			cvtColor(img_src3, gray3, CV_BGR2GRAY);

			subtract(gray2, gray1, gray_diff1);//�ڶ�֡����һ֡
			subtract(gray3, gray2, gray_diff2);//����֡���ڶ�֡

			for (int i = 0; i<gray_diff1.rows; i++)
				for (int j = 0; j<gray_diff1.cols; j++)
				{
					if (abs(gray_diff1.at<unsigned char>(i, j)) >= threshold_diff1)//����ģ�����һ��Ҫ��unsigned char�������һֱ����
						gray_diff1.at<unsigned char>(i, j) = 255;            //��һ�������ֵ����
					else gray_diff1.at<unsigned char>(i, j) = 0;

					if (abs(gray_diff2.at<unsigned char>(i, j)) >= threshold_diff2)//�ڶ��������ֵ����
						gray_diff2.at<unsigned char>(i, j) = 255;
					else gray_diff2.at<unsigned char>(i, j) = 0;
				}
			bitwise_and(gray_diff1, gray_diff2, gray);
			imshow("foreground", gray);

		}
		waitKey(1);
		img_src1.release();
	    return 0;
}