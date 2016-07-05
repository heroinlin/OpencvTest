#include "cv.h"  
#include "highgui.h"  
using namespace std;
using namespace cv;
//��ͼ�����������켣���Ҽ���ʾ��ͼ���


CvPoint prev_pt = { -1, -1 };
Mat img;

Mat img_mask;
Mat dst;


void on_mouse(int event, int x, int y, int flags, void*)
{
	if (!img.data)
		return;
	if (event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON))  //�ж��¼�Ϊ�ɿ����������߲�������ק  
	{
		prev_pt = cvPoint(-1, -1);
	}
	else if (event == CV_EVENT_LBUTTONDOWN)  //�ж�Ϊ�������  
	{
		prev_pt = cvPoint(x, y);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))  //�ж��ƶ���겢������ק  
	{
		CvPoint pt = cvPoint(x, y);
		if (prev_pt.x < 0)
		{
			prev_pt = pt;
		}
		line(img_mask, prev_pt, pt, Scalar(0), 2, 8, 0); //ģ���ϻ���  
		line(img, prev_pt, pt, Scalar::all(255), 2, 8, 0);          //ԭͼ�ϻ���  
		prev_pt = pt;
		imshow("image", img);





	}
	if (event == CV_EVENT_RBUTTONUP)
	{

		floodFill(img_mask, Point(x, y), Scalar(0));//����ͼģ��  
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

	//��ģ�����óɰ�ɫ  
	img_mask.create(img.rows, img.cols, CV_8U);
	img_mask.setTo(Scalar(255));
	//��ʾԭͼ  
	imshow("image", img);


	////��ʾģ��ԭͼ  
	//imshow("watershed transform", img_mask);  

	//���ص�����  
	cvSetMouseCallback("image", on_mouse, 0);



	waitKey(0);
	return 0;
}