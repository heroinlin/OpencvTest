#include "cv.h"  
#include "highgui.h"  
using namespace std;
using namespace cv;
//抠图，鼠标左键画轨迹，右键显示抠图结果


CvPoint prev_pt = { -1, -1 };
Mat img;

Mat img_mask;
Mat dst;


void on_mouse(int event, int x, int y, int flags, void*)
{
	if (!img.data)
		return;
	if (event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON))  //判断事件为松开鼠标左键或者不是左拖拽  
	{
		prev_pt = cvPoint(-1, -1);
	}
	else if (event == CV_EVENT_LBUTTONDOWN)  //判断为按下左键  
	{
		prev_pt = cvPoint(x, y);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))  //判断移动鼠标并且左拖拽  
	{
		CvPoint pt = cvPoint(x, y);
		if (prev_pt.x < 0)
		{
			prev_pt = pt;
		}
		line(img_mask, prev_pt, pt, Scalar(0), 2, 8, 0); //模板上划线  
		line(img, prev_pt, pt, Scalar::all(255), 2, 8, 0);          //原图上划线  
		prev_pt = pt;
		imshow("image", img);





	}
	if (event == CV_EVENT_RBUTTONUP)
	{

		floodFill(img_mask, Point(x, y), Scalar(0));//填充抠图模板  
		/*imshow("img_mask", img_mask);*/
		img.copyTo(dst, img_mask);
		imshow("dst", dst);


	}

}



int main(int argc, char* argv[])
{
	char*imagepath = argv[1];
	Mat image = imread(imagepath);
	image.copyTo(img);

	//将模板设置成白色  
	img_mask.create(img.rows, img.cols, CV_8U);
	img_mask.setTo(Scalar(255));
	//显示原图  
	imshow("image", img);


	////显示模板原图  
	//imshow("watershed transform", img_mask);  

	//鼠标回调函数  
	cvSetMouseCallback("image", on_mouse, 0);



	waitKey(0);
	return 0;
}