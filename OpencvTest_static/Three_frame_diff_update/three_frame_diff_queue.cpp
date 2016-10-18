#include "stdio.h"  
#include <cstdio>     
#include <windows.h>   
#include "highgui.h"     
#include "cv.h"   
#define MAX_QUEUE 4  
using namespace std;

//int main(int argc,char *argv[])//读取本地视频
//{
//	char *videopath = argv[1];
//	IplImage *diffQueue[4] = { NULL };//用于三帧帧差法的循环队列,增加一个空位用来队列判满  
//	int front, rear;                //队头，队尾  
//	int ncount = 0;                 //记录帧数  
//	IplImage *frontImg = NULL;  //前一帧  
//	IplImage *midImg = NULL;    //中间帧  
//	IplImage *rearImg = NULL;   //后一帧  
//	IplImage *Imask = NULL;
//	IplImage *Imask1 = NULL;
//	IplImage *Imask2 = NULL;
//	IplImage *Imask3 = NULL;
//	IplImage *mframe = NULL;
//	DWORD start = GetTickCount();
//	CvCapture *capture = cvCreateFileCapture(videopath);
//	int fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
//	printf("\n使用循环队列的三帧帧差法\n");
//	printf("\n视频帧率: %d 帧/秒\n", fps);
//	int frameNum = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
//	printf("\n总帧数%d\n", frameNum);
//	while (mframe = cvQueryFrame(capture))
//	{
//		ncount++;
//		//初始化  
//		if (!mframe){        //视频结束  
//			break;
//		}
//		if (ncount == 1)
//		{
//			Imask = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
//			Imask1 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
//			Imask2 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
//			rear = front = 0;               //初始化队首、队尾  
//			for (int i = 0; i < MAX_QUEUE; i++){                        //初始化循环队列  
//				diffQueue[i] = cvCreateImage(cvGetSize(mframe), mframe->depth, 1);//循环队列只存需要帧差的灰度图  
//			}
//			rear = (rear + 1) % MAX_QUEUE;        //第一帧疑似火焰图像入队  
//			cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY); //将图形帧的灰度图保存在循环队列中  
//			printf("\n视频帧宽度%d\n", mframe->width);
//			printf("视频帧高度%d\n\n", mframe->height);
//		}
//		//队列不满则火焰疑似帧继续入队  
//		else if ((rear + 1) % MAX_QUEUE != front){
//			//for Debug,March.12,2015  
//			//printf("\n入队\n");   
//			rear = (rear + 1) % MAX_QUEUE;
//			cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY);     //疑似火焰图像入队  
//		}
//		//队满,即队列中符合要求的视频帧数为3，开始对中间帧的每一个ROI进行帧差法  
//		else{
//			frontImg = diffQueue[(front + 1) % MAX_QUEUE];
//			midImg = diffQueue[(front + 2) % MAX_QUEUE];
//			rearImg = diffQueue[(front + 3) % MAX_QUEUE];
//			cvAbsDiff(midImg, frontImg, Imask1);
//			cvAbsDiff(rearImg, midImg, Imask2);
//
//			cvThreshold(Imask1, Imask1, 20, 255, CV_THRESH_BINARY);
//			cvThreshold(Imask2, Imask2, 20, 255, CV_THRESH_BINARY);
//			cvAnd(Imask1, Imask2, Imask);
//			cvShowImage("diff Frame", Imask);
//			cvWaitKey(33);
//			front = (front + 1) % MAX_QUEUE;        //前一帧出队  
//		}
//	}
//	DWORD finish = GetTickCount();
//	cout << finish - start << "ms" << endl;
//	return 0;
//}
int main(int argc, char *argv[])//读取实时摄像头
{
	IplImage *diffQueue[4] = { NULL };//用于三帧帧差法的循环队列,增加一个空位用来队列判满  
	int front, rear;                //队头，队尾  
	int ncount = 0;                 //记录帧数  
	IplImage *frontImg = NULL;  //前一帧  
	IplImage *midImg = NULL;    //中间帧  
	IplImage *rearImg = NULL;   //后一帧  
	IplImage *Imask = NULL;
	IplImage *Imask1 = NULL;
	IplImage *Imask2 = NULL;
	IplImage *Imask3 = NULL;
	IplImage *mframe = NULL;
	DWORD start = GetTickCount();
	CvCapture *capture = cvCreateCameraCapture(0);//0表示外部摄像头设备，1表示笔记本自带摄像头
	int fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	printf("\n使用循环队列的三帧帧差法\n");
	printf("\n视频帧率: %d 帧/秒\n", fps);
	//int frameNum = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//printf("\n总帧数%d\n", frameNum);
	while (1)
	{
		
		//初始化  
		mframe = cvQueryFrame(capture);
		if (!mframe & ncount > 0){        //视频结束  
			break;
		}
		if (ncount > 0)
		{
			if (ncount == 1)
			{
				Imask = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
				Imask1 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
				Imask2 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
				rear = front = 0;               //初始化队首、队尾  
				for (int i = 0; i < MAX_QUEUE; i++){                        //初始化循环队列  
					diffQueue[i] = cvCreateImage(cvGetSize(mframe), mframe->depth, 1);//循环队列只存需要帧差的灰度图  
				}
				rear = (rear + 1) % MAX_QUEUE;        //第一帧疑似火焰图像入队  
				cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY); //将图形帧的灰度图保存在循环队列中  
				printf("\n视频帧宽度%d\n", mframe->width);
				printf("视频帧高度%d\n\n", mframe->height);
			}
			//队列不满则火焰疑似帧继续入队  
			else if ((rear + 1) % MAX_QUEUE != front){
				//for Debug,March.12,2015  
				//printf("\n入队\n");   
				rear = (rear + 1) % MAX_QUEUE;
				cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY);     //疑似火焰图像入队  
			}
			//队满,即队列中符合要求的视频帧数为3，开始对中间帧的每一个ROI进行帧差法  
			else{
				frontImg = diffQueue[(front + 1) % MAX_QUEUE];
				midImg = diffQueue[(front + 2) % MAX_QUEUE];
				rearImg = diffQueue[(front + 3) % MAX_QUEUE];
				cvAbsDiff(midImg, frontImg, Imask1);
				cvAbsDiff(rearImg, midImg, Imask2);

				cvThreshold(Imask1, Imask1, 20, 255, CV_THRESH_BINARY);
				cvThreshold(Imask2, Imask2, 20, 255, CV_THRESH_BINARY);
				cvAnd(Imask1, Imask2, Imask);
				cvShowImage("diff Frame", Imask);
				cvWaitKey(1);
				front = (front + 1) % MAX_QUEUE;        //前一帧出队  
			}
		}
		ncount++;
	}
	DWORD finish = GetTickCount();
	cout << finish - start << "ms" << endl;
	return 0;
}
