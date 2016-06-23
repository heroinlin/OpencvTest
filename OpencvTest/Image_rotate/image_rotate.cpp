#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
//旋转图像
using namespace cv;

//全局变量
Mat src, dst;
Mat map_x, map_y;
char* remap_window = "Remap demo";
int ind = 0;
//函数头声明
void update_map(void);

int main(int argc, char** argv)
{
	//加载彩色图像
	//src = imread(argv[1], 1);
	src = imread("../images/1.jpg", 1);
	//创建和输入图像大小的dst,map_x,map_y
	dst.create(src.size(), src.type());
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);

	//创建窗口
	namedWindow(remap_window, CV_WINDOW_AUTOSIZE);

	//函数循环
	while (true)
	{
		//每个一秒，按键ESC退出程序
		int c = waitKey(1000);

		if ((char)c == 27)
		{
			break;
		}

		//更新map_x,map_y,然后应用remap函数
		update_map();
		remap(src, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

		//显示输出结果
		imshow(remap_window, dst);
	}
	return 0;
}
//四种类型的mappings
void update_map()
{
	ind = ind % 4;//索引值，用于case选择

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			switch (ind)
			{
			case 0://缩小图像并置中
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
			case 1://上下翻转图像
				map_x.at<float>(j, i) = i;
				map_y.at<float>(j, i) = src.rows - j;
				break;
			case 2://左右翻转图像
				map_x.at<float>(j, i) = src.cols - i;
				map_y.at<float>(j, i) = j;
				break;
			case 3://上下左右翻转图像
				map_x.at<float>(j, i) = src.cols - i;
				map_y.at<float>(j, i) = src.rows - j;
				break;
			} //选择结束
		}
	}
	ind++;
}
