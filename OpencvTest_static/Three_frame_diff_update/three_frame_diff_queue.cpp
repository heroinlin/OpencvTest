#include "stdio.h"  
#include <cstdio>     
#include <windows.h>   
#include "highgui.h"     
#include "cv.h"   
#define MAX_QUEUE 4  
using namespace std;

//int main(int argc,char *argv[])//��ȡ������Ƶ
//{
//	char *videopath = argv[1];
//	IplImage *diffQueue[4] = { NULL };//������֡֡���ѭ������,����һ����λ������������  
//	int front, rear;                //��ͷ����β  
//	int ncount = 0;                 //��¼֡��  
//	IplImage *frontImg = NULL;  //ǰһ֡  
//	IplImage *midImg = NULL;    //�м�֡  
//	IplImage *rearImg = NULL;   //��һ֡  
//	IplImage *Imask = NULL;
//	IplImage *Imask1 = NULL;
//	IplImage *Imask2 = NULL;
//	IplImage *Imask3 = NULL;
//	IplImage *mframe = NULL;
//	DWORD start = GetTickCount();
//	CvCapture *capture = cvCreateFileCapture(videopath);
//	int fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
//	printf("\nʹ��ѭ�����е���֡֡�\n");
//	printf("\n��Ƶ֡��: %d ֡/��\n", fps);
//	int frameNum = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
//	printf("\n��֡��%d\n", frameNum);
//	while (mframe = cvQueryFrame(capture))
//	{
//		ncount++;
//		//��ʼ��  
//		if (!mframe){        //��Ƶ����  
//			break;
//		}
//		if (ncount == 1)
//		{
//			Imask = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
//			Imask1 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
//			Imask2 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
//			rear = front = 0;               //��ʼ�����ס���β  
//			for (int i = 0; i < MAX_QUEUE; i++){                        //��ʼ��ѭ������  
//				diffQueue[i] = cvCreateImage(cvGetSize(mframe), mframe->depth, 1);//ѭ������ֻ����Ҫ֡��ĻҶ�ͼ  
//			}
//			rear = (rear + 1) % MAX_QUEUE;        //��һ֡���ƻ���ͼ�����  
//			cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY); //��ͼ��֡�ĻҶ�ͼ������ѭ��������  
//			printf("\n��Ƶ֡���%d\n", mframe->width);
//			printf("��Ƶ֡�߶�%d\n\n", mframe->height);
//		}
//		//���в������������֡�������  
//		else if ((rear + 1) % MAX_QUEUE != front){
//			//for Debug,March.12,2015  
//			//printf("\n���\n");   
//			rear = (rear + 1) % MAX_QUEUE;
//			cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY);     //���ƻ���ͼ�����  
//		}
//		//����,�������з���Ҫ�����Ƶ֡��Ϊ3����ʼ���м�֡��ÿһ��ROI����֡�  
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
//			front = (front + 1) % MAX_QUEUE;        //ǰһ֡����  
//		}
//	}
//	DWORD finish = GetTickCount();
//	cout << finish - start << "ms" << endl;
//	return 0;
//}
int main(int argc, char *argv[])//��ȡʵʱ����ͷ
{
	IplImage *diffQueue[4] = { NULL };//������֡֡���ѭ������,����һ����λ������������  
	int front, rear;                //��ͷ����β  
	int ncount = 0;                 //��¼֡��  
	IplImage *frontImg = NULL;  //ǰһ֡  
	IplImage *midImg = NULL;    //�м�֡  
	IplImage *rearImg = NULL;   //��һ֡  
	IplImage *Imask = NULL;
	IplImage *Imask1 = NULL;
	IplImage *Imask2 = NULL;
	IplImage *Imask3 = NULL;
	IplImage *mframe = NULL;
	DWORD start = GetTickCount();
	CvCapture *capture = cvCreateCameraCapture(0);//0��ʾ�ⲿ����ͷ�豸��1��ʾ�ʼǱ��Դ�����ͷ
	int fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	printf("\nʹ��ѭ�����е���֡֡�\n");
	printf("\n��Ƶ֡��: %d ֡/��\n", fps);
	//int frameNum = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//printf("\n��֡��%d\n", frameNum);
	while (1)
	{
		
		//��ʼ��  
		mframe = cvQueryFrame(capture);
		if (!mframe & ncount > 0){        //��Ƶ����  
			break;
		}
		if (ncount > 0)
		{
			if (ncount == 1)
			{
				Imask = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
				Imask1 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
				Imask2 = cvCreateImage(cvGetSize(mframe), IPL_DEPTH_8U, 1);
				rear = front = 0;               //��ʼ�����ס���β  
				for (int i = 0; i < MAX_QUEUE; i++){                        //��ʼ��ѭ������  
					diffQueue[i] = cvCreateImage(cvGetSize(mframe), mframe->depth, 1);//ѭ������ֻ����Ҫ֡��ĻҶ�ͼ  
				}
				rear = (rear + 1) % MAX_QUEUE;        //��һ֡���ƻ���ͼ�����  
				cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY); //��ͼ��֡�ĻҶ�ͼ������ѭ��������  
				printf("\n��Ƶ֡���%d\n", mframe->width);
				printf("��Ƶ֡�߶�%d\n\n", mframe->height);
			}
			//���в������������֡�������  
			else if ((rear + 1) % MAX_QUEUE != front){
				//for Debug,March.12,2015  
				//printf("\n���\n");   
				rear = (rear + 1) % MAX_QUEUE;
				cvCvtColor(mframe, diffQueue[rear], CV_BGR2GRAY);     //���ƻ���ͼ�����  
			}
			//����,�������з���Ҫ�����Ƶ֡��Ϊ3����ʼ���м�֡��ÿһ��ROI����֡�  
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
				front = (front + 1) % MAX_QUEUE;        //ǰһ֡����  
			}
		}
		ncount++;
	}
	DWORD finish = GetTickCount();
	cout << finish - start << "ms" << endl;
	return 0;
}
