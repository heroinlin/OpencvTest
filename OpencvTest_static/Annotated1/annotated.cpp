
#include <opencv2/opencv.hpp>  
#include "box.h"

using namespace cv;

Mat src, dst;
box boxs;
static int count = 0;
void on_mouse(int event, int x, int y, int flags, void* ustc)
{
	//src = imread("Lena.jpg");    

	static Point pre_pt = (-1, -1);
	static Point cur_pt = (-1, -1);
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);
	char temp[50];

	Vec3b intensity = src.at<Vec3b>(Point(x, y));//(x,y)点的像素值
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		dst.copyTo(src);
		sprintf(temp, "(%d,%d,%d,%d,%d)", x, y, intensity.val[0], intensity.val[1], intensity.val[2]);
		pre_pt = cvPoint(x, y);
		putText(src, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(0, 0, 0, 255), 1, 8);
		//circle(src, pre_pt, 3, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		imshow("src", src);
		src.copyTo(dst);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		dst.copyTo(src);
		sprintf(temp, "(%d,%d,%d,%d,%d)", x, y, intensity.val[0], intensity.val[1], intensity.val[2]);
		cur_pt = cvPoint(x, y);
		putText(src, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(0, 0, 0, 255), 1, 8);
		//line(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);//画pre_pt, cur_pt两点间的线段

		/*画以pre_pt, cur_pt两点为对角的矩形*/
		line(src, pre_pt, cvPoint(x,pre_pt.y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, pre_pt, cvPoint(pre_pt.x, y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, cvPoint(x, pre_pt.y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, cvPoint(pre_pt.x, y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		/**/
		imshow("src", src);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		dst.copyTo(src);
		sprintf(temp, "(%d,%d,%d,%d,%d)", x, y, intensity.val[0], intensity.val[1], intensity.val[2]);
		cur_pt = Point(x, y);
		putText(src, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(0, 0, 0, 255), 1, 8);
		//circle(src, cur_pt, 3, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		//line(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		/*画以pre_pt, cur_pt两点为对角的矩形*/
		line(src, pre_pt, cvPoint(x, pre_pt.y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, pre_pt, cvPoint(pre_pt.x, y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, cvPoint(x, pre_pt.y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, cvPoint(pre_pt.x, y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		/**/
		imshow("src", src);
		src.copyTo(dst);
		boxs.x = (float)(pre_pt.x + cur_pt.x) / 2.0;//框中心点坐标
		boxs.y = (float)(pre_pt.y + cur_pt.y) / 2.0;
		boxs.w = fabs((float)(cur_pt.x - pre_pt.x));
		boxs.h = fabs((float)(cur_pt.y - pre_pt.y));
		printf("boxs[%d]: %f %f %f %f\n", count, boxs.x, boxs.y, boxs.w, boxs.h);
		count++;
	}
}

int main(int argc,char **argv)
{

	src = imread(argv[1]);

	src.copyTo(dst);
	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("src", on_mouse, 0);

	imshow("src", src);
	cvWaitKey(0);
	cvDestroyAllWindows();
	return 0;
}
