#include <opencv2/opencv.hpp> 


using namespace std;
using namespace cv;
Mat src, dst;
char* str;
void string_write_in_image(Mat src,char* str,int x,int y)
{
	putText(src, str, cvPoint(x, y), FONT_HERSHEY_DUPLEX, 1.0, cvScalar(0, 0, 255, 0), 1, 16);
	imshow("src", src);
	waitKey(0);
}
void on_mouse(int event, int x, int y, int flags, void* ustc)
{
	static Point pre_pt = (-1, -1);
	static Point cur_pt = (-1, -1);
	CvFont font;
	cvInitFont(&font, FONT_HERSHEY_DUPLEX, 0.5, 0.5, 0, 1, CV_AA);
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		dst.copyTo(src);
		pre_pt = cvPoint(x, y);
		imshow("Annotated", src);
		src.copyTo(dst);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		dst.copyTo(src);
		cur_pt = cvPoint(x, y);
		putText(src, str, cur_pt, FONT_HERSHEY_DUPLEX, 1.0, cvScalar(0, 0, 255, 255), 1, 16);
		imshow("Annotated", src);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		dst.copyTo(src);
		//sprintf(temp, "(%d,%d,%d,%d,%d)", x, y, intensity.val[0], intensity.val[1], intensity.val[2]);
		cur_pt = Point(x, y);
		putText(src, str, cur_pt, FONT_HERSHEY_DUPLEX, 1.0, cvScalar(0, 0, 255, 255), 1, 16);
		/**/
		imshow("Annotated", src);
		src.copyTo(dst);
	}
}

int main(int argc, char **argv)
{
	char *imagepath = argv[1];
	src = imread(imagepath,1);
	str = argv[2];
	//int x = src.rows / 2;
	//int y = src.cols / 2;
	//string_write_in_image(src, str, x, y); 
	//
	char savename[256];
	src.copyTo(dst);
	cvNamedWindow("Annotated", CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback("Annotated", on_mouse, 0);
	imshow("Annotated", src);
	waitKey(0);
	return 1;
}