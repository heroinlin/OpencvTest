#include"im_pro.h"
#define MAX 100
static IplImage *src,*dst;
static box boxs;
static char labelname[256];
void on_mouse(int event, int x, int y, int flags, void* ustc)
{
	static CvPoint pre_pt = { -1, -1 };
	static CvPoint cur_pt = { -1, -1 };
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);
	char temp[16];

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cvCopy(dst, src,0);
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x > src->width) x = src->width;
		if (y > src->height) y =src->height;
		sprintf(temp, "(%d,%d)", x, y);
		pre_pt = cvPoint(x, y);
		//cvPutText(src, temp, pre_pt, &font, cvScalar(0, 0, 0, 255));
		//cvCircle(src, pre_pt, 3, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		cvShowImage("src", src);
		cvCopy(src, dst,0);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))
	{
		cvCopy(dst, src,0);
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x > src->width) x = src->width;
		if (y > src->height) y = src->height;
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		//cvPutText(src, temp, cur_pt, &font, cvScalar(0, 0, 0, 255));
		cvLine(src, cvPoint(x, 0), cvPoint(x, src->height), cvScalar(255, 0, 0, 0), 1, 4, 0);
		cvLine(src, cvPoint(0, y), cvPoint(src->width, y), cvScalar(255, 0, 0, 0), 1, 4, 0);
		cvShowImage("src", src);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		cvCopy(dst, src,0);
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x > src->width) x = src->width;
		if (y > src->height) y = src->height;
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		//cvPutText(src, temp, cur_pt, &font, cvScalar(0, 0, 0, 255));
		if (abs(pre_pt.x - cur_pt.x) > 10 && abs(pre_pt.y - cur_pt.y) > 10)
		{
			//cvRectangle(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, 8, 0);
			cvLine(src, pre_pt, cvPoint(x, pre_pt.y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
			cvLine(src, pre_pt, cvPoint(pre_pt.x, y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
			cvLine(src, cvPoint(x, pre_pt.y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
			cvLine(src, cvPoint(pre_pt.x, y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		}
		cvShowImage("src", src);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x > src->width) x = src->width;
		if (y > src->height) y = src->height;
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		//cvPutText(src, temp, cur_pt, &font, cvScalar(0, 0, 0, 255));
		//cvCircle(src, cur_pt, 3, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		if (abs(pre_pt.x - cur_pt.x) > 10 && abs(pre_pt.y - cur_pt.y) > 10)
		{
			//cvRectangle(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, 8, 0);
			cvLine(src, pre_pt, cvPoint(x, pre_pt.y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
			cvLine(src, pre_pt, cvPoint(pre_pt.x, y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
			cvLine(src, cvPoint(x, pre_pt.y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
			cvLine(src, cvPoint(pre_pt.x, y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		}
		cvShowImage("src", src);
		cvCopy(src, dst,0);	
		float width = abs(pre_pt.x - cur_pt.x);
		float height = abs(pre_pt.y - cur_pt.y);
		CvRect rect;
		if (pre_pt.x < cur_pt.x && pre_pt.y<cur_pt.y)
		{
			rect = cvRect(pre_pt.x, pre_pt.y, width, height);
		}
		else if (pre_pt.x>cur_pt.x && pre_pt.y<cur_pt.y)
		{
			rect = cvRect(cur_pt.x, pre_pt.y, width, height);
		}
		else if (pre_pt.x>cur_pt.x && pre_pt.y > cur_pt.y)
		{
			rect = cvRect(cur_pt.x, cur_pt.y, width, height);
		}
		else if (pre_pt.x<cur_pt.x && pre_pt.y>cur_pt.y)
		{
			rect = cvRect(pre_pt.x, cur_pt.y, width, height);
		}
		boxs.x = (float)(pre_pt.x + cur_pt.x) / 2.0;
		boxs.y = (float)(pre_pt.y + cur_pt.y) / 2.0;
		boxs.w = width;
		boxs.h = height;
		if (boxs.w > 10 && boxs.h > 10)
		{
			FILE *fps;
			fps = fopen(labelname, "a+");
			fprintf(fps, "0 %f %f %f %f\n", boxs.x / src->width, boxs.y / src->height, boxs.w / src->width, boxs.h / src->height);
			fclose(fps);
		}
	}
}
IplImage* ResizeImage(IplImage *src,float scale)
{
	// allocate memory for the dsc    
	IplImage* dsc = cvCreateImage(cvSize(src->width*scale, src->height*scale),
		src->depth, src->nChannels);

	// resizes Image(input array is resized to fit the output array )   
	cvResize(src, dsc, CV_INTER_LINEAR);
	return dsc;

}
void anno_video_list(char *filename, float scale)
{
	char Folder_name[256];
	printf("Please Enter the Folder to save pictures:\n");
	scanf("%s/n", &Folder_name);
	vector<string> video_names;
	getFiles(filename, "", video_names);
	//printf("%d\n", video_names.size());
	int i;
	char buff[256];
	char *input = buff;
	int numFrames = 0;
	float nms = .4;
	int speed = 33;
	int stopflag = 0;
	int key;
	int m = video_names.size();
	int exit_flag = 0;
	printf("%d\n",m);
	//CvSize size;
	//{
	//	size.width = weight, size.height = height;
	//}
	for (i = 0; i < m; i++)
	{
		if (exit_flag == 1)break;
		sprintf( input ,"%s",video_names[i].c_str());
		printf("load %s\n", input);
		CvCapture  *cap1 = cvCreateFileCapture(input);
		//cap = cvCaptureFromFile(input);
		if (!cap1)
		{
			printf("%d  Couldn't load %s.\n", i + 1, input);
			continue;
		}
		printf("%d  Load %s\n   Remain %d videos\n", i + 1, input, m - i - 1);
		numFrames = (int)cvGetCaptureProperty(cap1, CV_CAP_PROP_FRAME_COUNT);
		int j;
		int countFrames = 0;
		int flag = 0;
		IplImage *frame = cvCreateImage(cvSize(320, 288), IPL_DEPTH_8U, 1);
		while (countFrames < numFrames){
			if (flag == 1)  break; 
			frame = cvQueryFrame(cap1);
			src = ResizeImage(frame,scale);
			/*src=cvCreateImage(size, frame->depth, frame->nChannels);
			cvResize(frame, src, CV_INTER_CUBIC);*/
			dst = cvCloneImage(src);
			cvNamedWindow("src", CV_WINDOW_NORMAL);
			cvSetMouseCallback("src", on_mouse, 0);

			cvShowImage("src", src);
			
			countFrames++;
			printf("countFrames=%d,numFrame=%d\n", countFrames, numFrames);//debuging
		
			char savename[256];
			char savename1[256];
			char head_savepath[256];
			char nohead_savepath[256];
			sprintf(head_savepath, "%s/head", Folder_name);
			sprintf(nohead_savepath, "%s/nohead", Folder_name);

			sprintf(savename, "%s/%d_%07d.jpg", head_savepath, i, countFrames);
			sprintf(savename1, "%s/%d_%07d.jpg", nohead_savepath, i, countFrames);
			sprintf(labelname, "%s/%d_%07d.txt", head_savepath, i, countFrames);
			if (stopflag == 1)
				key = cvWaitKey(speed);
			else key = cvWaitKey(0);
			switch (key)
			{
			case 32:{ stopflag = !stopflag; break; }
			case 'c':{ remove(labelname); countFrames -= 1; cvSetCaptureProperty(cap1, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
			case 'C':{ remove(labelname); countFrames -= 1;  cvSetCaptureProperty(cap1, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
			case 'd':{ countFrames -= 2; if (countFrames < 0)countFrames = 0; cvSetCaptureProperty(cap1, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
			case 'D':{ countFrames -= 2; if (countFrames < 0)countFrames = 0;  cvSetCaptureProperty(cap1, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
			case 's':{ cvSaveImage(savename,frame,0); break; }
			case 'S':{ cvSaveImage(savename,frame, 0); break; }
			case 'a':{ cvSaveImage(savename1, frame, 0); break; }
			case 'A':{ cvSaveImage(savename1, frame, 0); break; }
			case 'o':{ speed += 10; break; }
			case 'i':{ speed -= 10; break; }
			case 'q':{ flag = 1; i -= 2; if (i < 0) i = -1; break; }
			case 'Q':{ flag = 1; i -= 2; if (i < 0) i = -1; break; }
			case 'l':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(cap1, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
			case 'L':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(cap1, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
			case 27:{ flag = 1; exit_flag = 1; break; }
			default:{}
			}		
			cvReleaseImage(&src);
			cvReleaseImage(&dst);
		}
		cvReleaseCapture(&cap1);
		
	}
	
	cvDestroyAllWindows();
	
}
void anno_images_list(char *filename, float scale)
{
	char Folder_name[256];
	printf("Please Enter the Folder to save pictures:\n");
	scanf("%s/n", Folder_name);
	vector<string> images_names;
	getFiles(filename, "", images_names);
	int i;
	char buff[256];
	char *input = buff;
	float nms = .4;
	int key;
	int flag = 0;
	int m =images_names.size();
	//CvSize size;
	//{
	//	size.width = weight, size.height = height;
	//}
	for (i = 0; i < m; i++)
	{
		if (flag == 1)	break;
		sprintf(input, "%s", images_names[i].c_str());
		IplImage *images = cvLoadImage(input,1);
		//cap = cvCaptureFromFile(input);
		printf("%d  Load %s\n   Remain %d images\n", i + 1, input, m - i - 1);	
		src = ResizeImage(images, scale);
		/*src=cvCreateImage(size, frame->depth, frame->nChannels);
		cvResize(frame, src, CV_INTER_CUBIC);*/
		dst = cvCloneImage(src);
		cvNamedWindow("src", CV_WINDOW_NORMAL);
		cvSetMouseCallback("src", on_mouse, 0);
		cvShowImage("src", src);
		char savename[256];
		char savename1[256];
		char head_savepath[256];
		char nohead_savepath[256];
		sprintf(head_savepath, "%s/head", Folder_name);
		sprintf(nohead_savepath, "%s/nohead", Folder_name);
		
		sprintf(savename, "%s/%07d.jpg", head_savepath, i);
		sprintf(savename1, "%s/%07d.jpg", nohead_savepath, i);
		sprintf(labelname, "%s/%07d.txt", head_savepath, i);
		key = cvWaitKey(0);
		switch (key)
		{
		case 'c':{ remove(labelname); i -= 1;  break; }
		case 'C':{ remove(labelname); i -= 1;  break; }
		case 'd':{ i -= 2; if (i < 0)i = -1; break; }
		case 'D':{ i -= 2; if (i < 0)i = -1;  break; }
		case 's':{ cvSaveImage(savename, images, 0); break; }
		case 'S':{ cvSaveImage(savename, images, 0); break; }
		case 'a':{ cvSaveImage(savename1, images, 0); break; }
		case 'A':{ cvSaveImage(savename1, images, 0); break; }
		case 27:{ flag = 1; break; }
		default:{}
		}
		cvReleaseImage(&src);
		cvReleaseImage(&dst);
		cvReleaseImage(&images);
	}
	cvDestroyAllWindows();
}