//��Ƶ��ɫ
#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "getfile.h"

void VideoInverse(CvCapture* pCapture, char* output_name)
{
	//����IplImageָ��
	IplImage* pFrame = NULL;
	uchar *data;
	int nFrmNum = 0;
	//��������
	//cvNamedWindow("video", 1);
	static CvVideoWriter* output_video = NULL;    // cv::VideoWriter output_video
	//��Ƶ������Ϣ
	int frameH = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_WIDTH);
	int fps = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FPS);
	int numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	CvSize size;
	{
		size.width = frameW, size.height = frameH;
	}
	//��֡��ȡ��Ƶ
	while (pFrame = cvQueryFrame(pCapture))
	{
		nFrmNum++;
		printf("��ǰ֡:%d,��Ƶ��֡��:%d\n",nFrmNum,numFrames);
			data = (uchar *)pFrame->imageData;
			int height = pFrame->height;                     // ͼ��߶� 
			int width = pFrame->width;                       // ͼ���ȣ�����Ϊ��λ�� 
			int step = pFrame->widthStep;                 // �����е�ͬ�е�֮����ֽ��� 
			int channels = pFrame->nChannels;             // ��ɫͨ����Ŀ (1,2,3,4) 
			//��ɫ����
			for (int i = 0; i != height; ++i)
			{
				for (int j = 0; j != width; ++j)
				{
					for (int k = 0; k != channels; ++k)
					{
						data[i*step + j*channels + k] = 255-data[i*step + j*channels + k];//���Խ������ȵĵ�������*.5
						//data[i*step + j*channels + k] = (data[i*step + j*channels + k]>255)?255:((data[i*step + j*channels + k]<0)?0:data[i*step + j*channels + k]);
					}
				}
			}
			if (output_video == NULL)
			{
				//char* output_name = "out.avi";
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('H', '2', '6', '4'), 25, size, 1);
				output_video = cvCreateVideoWriter(output_name, CV_FOURCC('D', 'I', 'V', 'X'), fps, size, 1);
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('X', 'V', 'I', 'D'), fps, size, 1);
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('M', 'J', 'P', 'G'), 25, size, 1);
			}
			//��ʾͼ��
			cvWriteFrame(output_video, pFrame);
			//cvShowImage("video", pFrame);
			//����а����¼���������ѭ��
			//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ
			//�ȴ�ʱ����Ը���CPU�ٶȵ���
			if (cvWaitKey(1) >= 0)
				break;
		}
	cvReleaseVideoWriter(&output_video);
	cvReleaseImage(&pFrame);
}
int main(int argc, char** argv)
{
	
	/*
	//����Ƶ����  ColorInverse.exe [video_file_name]  [video_savefile_name]
	CvCapture* pCapture = NULL;
	if (argc > 3)
	{
		fprintf(stderr, "Usage: bkgrd [video_file_name]  [video_savefile_name]\n");
		return -1;
	}
	//������ͷ
	if (argc == 1)
		if (!(pCapture = cvCaptureFromCAM(-1)))
		{
			fprintf(stderr, "Can not open camera.\n");
			return -2;
		}
	//����Ƶ�ļ�
	if (argc >= 2)
		if (!(pCapture = cvCaptureFromFile(argv[1])))
		{
			fprintf(stderr, "Can not open video file %s\n", argv[1]);
			return -2;
		}
	char* output_name = argv[2];
	VideoInverse(pCapture,output_name);
	return 1;
	*/
	//��Ƶ�ļ��д��� ColorInverse.exe [video_file_fold]
	if (argc != 2)
	{
		fprintf(stderr, "Usage: bkgrd [videofile_fold]\n");
		return -1;
	}
	char *video_list = argv[1];
	vector<string> image_names;
	getFiles(video_list, "", image_names);
	for (int i = 0; i < image_names.size(); i++)
	{
		CvCapture* pCapture = NULL;
		string fileName = image_names[i];
		cout << "file name:" << fileName << endl;
		pCapture = cvCaptureFromFile(fileName.c_str());
		char output_name[256];
		sprintf(output_name, "./videos_result/%03d.avi", i);
		VideoInverse(pCapture, output_name);
	}
	return 1;
}
	