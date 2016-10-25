#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>
CvCapture* g_capture = NULL;//声明一个CvCapture类型指针,用于接收cvCreateFileCapture的返回值
int g_slider_pos = 0;//记录滚动条的当前位置
int countFrames = 0;//对视频帧进行计数的变量
int key;
int stopflag = 1;
int speed = 33;
//滚动条的回调函数  参数int pos 是指当前滚动条所在位置
void on_changed(int pos)
{
	//设置g_capture的属性,使得从位置pos开始播放视频
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
	//在拉动滚动条后  保持变量frame_count与滚动条的位置是同步的
	countFrames = pos;
}
void videoplayer(CvCapture* capture)
{
	//获取视频的总帧数
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//在窗口show上创建名字为Position的滚动条
	if (numFrames > 0)
	{
		cvCreateTrackbar("Position", "videoplayer", &g_slider_pos, numFrames, on_changed);
	}
	while (countFrames<numFrames)
	{
		IplImage* frame = cvQueryFrame(capture);
		if (!frame) break;
		countFrames++;
		cvShowImage("videoplayer", frame);
		char savename[256];
		sprintf(savename,"./images/%07d.jpg",countFrames);
		if (stopflag == 1)
			key = cvWaitKey(speed);
		else key = cvWaitKey(0);
		switch (key)
		{
		case 32:{ stopflag = !stopflag; break; }
		case 'c':{ countFrames -= 1; cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'C':{  countFrames -= 1;  cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'd':{ countFrames -= 2; if (countFrames < 0)countFrames = 0; cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'D':{ countFrames -= 2; if (countFrames < 0)countFrames = 0;  cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 's':{ cvSaveImage(savename, frame, 0); break; }
		case 'S':{ cvSaveImage(savename, frame, 0); break; }
		case 'o':{ speed += 10; break; }
		case 'i':{ speed -= 10; break; }
		case 'l':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'L':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		default:{}
		}
		//滚动条 随着视频的播放 进行移动
		cvSetTrackbarPos("Position", "videoplayer", countFrames);
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("videoplayer");
	}
void Invplayer(CvCapture* pCapture)
//反色播放视频
{
	//声明IplImage指针
	IplImage* pFrame = NULL;
	uchar *data;
	int nFrmNum = 0;
	//创建窗口
	//cvNamedWindow("video", 1);
	//视频参数信息
	int numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	//逐帧读取视频
	if (numFrames > 0)
	{
		cvCreateTrackbar("Position", "videoplayer", &g_slider_pos, numFrames, on_changed);
		/*在标签中显示的文字（提示滑动条的用途） "Position"
		  创建的滑动条要放置窗体的名字 "videoplayer"
		  滑动条的取值范围从 0 到 numFrames(最小值只能为 zero).
		  滑动后的值存放在 g_slider_pos 变量里
		  每当滑动条的值改变, 就会调用 on_changed 回调函数*/
	}
	while (pFrame = cvQueryFrame(pCapture))
	{
		nFrmNum++;
		printf("当前帧:%d,视频总帧数:%d\n", nFrmNum, numFrames);
		data = (uchar *)pFrame->imageData;
		int height = pFrame->height;                     // 图像高度 
		int width = pFrame->width;                       // 图像宽度（像素为单位） 
		int step = pFrame->widthStep;                 // 相邻行的同列点之间的字节数 
		int channels = pFrame->nChannels;             // 颜色通道数目 (1,2,3,4) 
		//反色操作
		for (int i = 0; i != height; ++i)
		{
			for (int j = 0; j != width; ++j)
			{
				for (int k = 0; k != channels; ++k)
				{
					data[i*step + j*channels + k] = 255 - data[i*step + j*channels + k];//可以进行亮度的调整，如*.5
					//data[i*step + j*channels + k] = (data[i*step + j*channels + k]>255)?255:((data[i*step + j*channels + k]<0)?0:data[i*step + j*channels + k]);
				}
			}
		}
		if (!pFrame) break;
		cvShowImage("videoplayer", pFrame);
		char c = cvWaitKey(33);
		if (c == 27) break;
		//滚动条 随着视频的播放 进行移动
		cvSetTrackbarPos("Position", "videoplayer", countFrames);
		countFrames++;
	}
	cvReleaseCapture(&pCapture);
	cvDestroyWindow("videoplayer");	
}
int main(int argc, char* argv[])
{
	char *videopath = argv[1];
	g_capture = cvCreateFileCapture(videopath); //打开有一个视频文件

	cvNamedWindow("videoplayer", CV_WINDOW_AUTOSIZE);
	 videoplayer(g_capture);
	//Invplayer(g_capture);
	return 0;
}