#include <opencv2/opencv.hpp> 

#include "box.h"
#include "getfile.h"

using namespace std;
using namespace cv;
Mat src, dst;
static box boxs;
static char labelname[256];

//int main(int argc,char **argv)
//{
//
//	src = imread(argv[1]);
//
//	src.copyTo(dst);
//	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
//	cvSetMouseCallback("src", on_mouse, 0);
//
//	imshow("src", src);
//	cvWaitKey(0);
//	cvDestroyAllWindows();
//	return 0;
//}
void on_mouse(int event, int x, int y, int flags, void* ustc)
{
	//src = imread("Lena.jpg");    
	
	static Point pre_pt = (-1, -1);
	static Point cur_pt = (-1, -1);
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);
	char temp[50];
	static int count = 0;
	//Vec3b intensity = src.at<Vec3b>(Point(x, y));//(x,y)点的像素值
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		dst.copyTo(src);
		//sprintf(temp, "(%d,%d,%d,%d,%d)", x, y, intensity.val[0], intensity.val[1], intensity.val[2]);
		sprintf(temp, "(%d,%d)", x, y);
		pre_pt = cvPoint(x, y);
		putText(src, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(0, 0, 0, 255), 1, 8);
		//circle(src, pre_pt, 3, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		imshow("Annotated", src);
		src.copyTo(dst);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		dst.copyTo(src);
		//sprintf(temp, "(%d,%d,%d,%d,%d)", x, y, intensity.val[0], intensity.val[1], intensity.val[2]);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = cvPoint(x, y);
		putText(src, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(0, 0, 0, 255), 1, 8);
		//line(src, pre_pt, cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);//画pre_pt, cur_pt两点间的线段

		/*画以pre_pt, cur_pt两点为对角的矩形*/
		line(src, pre_pt, cvPoint(x, pre_pt.y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, pre_pt, cvPoint(pre_pt.x, y), cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, cvPoint(x, pre_pt.y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		line(src, cvPoint(pre_pt.x, y), cur_pt, cvScalar(0, 255, 0, 0), 1, CV_AA, 0);
		/**/
		imshow("Annotated", src);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		dst.copyTo(src);
		//sprintf(temp, "(%d,%d,%d,%d,%d)", x, y, intensity.val[0], intensity.val[1], intensity.val[2]);
		sprintf(temp, "(%d,%d)", x, y);
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
		imshow("Annotated", src);
		src.copyTo(dst);
		boxs.x = (float)(pre_pt.x + cur_pt.x) / 2.0;//框中心点坐标
		boxs.y = (float)(pre_pt.y + cur_pt.y) / 2.0;
		boxs.w = fabs((float)(cur_pt.x - pre_pt.x));
		boxs.h = fabs((float)(cur_pt.y - pre_pt.y));
		printf("boxs: %f %f %f %f\n", boxs.x, boxs.y, boxs.w, boxs.h);
		count++;
		//追加写入labelname
		FILE *fps;
		fps = fopen(labelname, "a+");
		fprintf(fps, "0 %f %f %f %f\n", boxs.x, boxs.y, boxs.w, boxs.h);
		fclose(fps);
	}
}

void anno_video_folder( char *dir_path,int weight,int height)
{
	//char *dir_path = argv[1];
	vector<string> video_names;
	Mat image;
	CvSize size;
	{
		size.width = weight, size.height = height;
	}
	getFiles(dir_path, "",video_names);
	int i;
	//printf("%d\n", video_names.size());
	for (i = 0; i < video_names.size(); i++)
	{
		VideoCapture video_cap(video_names[i]);
		if (video_cap.isOpened() == false)
		{
			cout << " video_cap.isOpened() == false " << endl;
			system("pause");
		}
		int fnumber = 0;
		int flag = 0;
		int numframe = (int)video_cap.get(CV_CAP_PROP_FRAME_COUNT);
		while (fnumber < numframe)
		{
			if (flag == 1) break;
			if (!video_cap.read(image))
				break;
			//*****按帧读入****//
			fnumber++;
			printf("fnumber= %d, numframe= %d\n",fnumber,numframe);
			char savename[256];
			sprintf(savename, "./results/%d_%04d.jpg", i, fnumber);
			
			sprintf(labelname, "./results/%d_%04d.txt", i, fnumber);
			image.copyTo(src);
			src.copyTo(dst);
			resize(src, dst,size);
			cvNamedWindow("Annotated", CV_WINDOW_AUTOSIZE);
			int count = 0;
			cvSetMouseCallback("Annotated", on_mouse, 0);

			imshow("Annotated", dst);
			
			int key = cvWaitKey(0);
			switch (key)
			{
			case 'c':{ remove(labelname); fnumber -= 1; video_cap.set(CV_CAP_PROP_POS_FRAMES, fnumber); break; }
			case 'C':{ remove(labelname); fnumber -= 1; video_cap.set(CV_CAP_PROP_POS_FRAMES, fnumber); break; }
			case 'd':{ fnumber -= 2; if (fnumber < 0)fnumber = 0; video_cap.set(CV_CAP_PROP_POS_FRAMES, fnumber); break; }
			case 'D':{ fnumber -= 2; if (fnumber < 0)fnumber = 0; video_cap.set(CV_CAP_PROP_POS_FRAMES, fnumber); break; }
			case 's':{ imwrite(savename, image); break; }
			case 'S':{ imwrite(savename, image); break; }
			//case 's':{ imwrite(savename, src); break; }
			//case 'S':{ imwrite(savename, src); break; }
			case 'l':{ fnumber += 5; if (fnumber < 0)fnumber = 0; video_cap.set(CV_CAP_PROP_POS_FRAMES, fnumber); break; }
			case 'L':{ fnumber += 5; if (fnumber < 0)fnumber = 0; video_cap.set(CV_CAP_PROP_POS_FRAMES, fnumber); break; }
			case 27:{ flag = 1; break; }
			default:{}
			}	
		}
	}
	cvDestroyAllWindows();
}
void anno_image_folder(char *dir_path,int weight,int height)
{
	//char *dir_path = argv[1];
	vector<string> images_names;
	CvSize size;
	{
		size.width = weight, size.height = height;
	}
	getFiles(dir_path, "", images_names);
	int i;
	printf("%d\n", images_names.size());
	for (i = 0; i < images_names.size(); i++)
	{
		    string fileName = images_names[i];
			printf("Load %d images\n", i);
		    Mat image = imread(fileName, 1); 
			char savename[256];
			sprintf(savename, "./results/%04d.jpg", i);

			sprintf(labelname, "./results/%04d.txt", i);
			image.copyTo(src);
			src.copyTo(dst);
			cvNamedWindow("Annotated", CV_WINDOW_AUTOSIZE);
			int count = 0;
			cvSetMouseCallback("Annotated", on_mouse, 0);

			imshow("Annotated", src);

			int key = cvWaitKey(0);
			switch (key)
			{
			case 'c':{ remove(labelname); i -= 1; break; }
			case 'C':{ remove(labelname); i -= 1; break; }
			case 'd':{ i -= 2; if (i < 0) i = 0; break; }
			case 'D':{ i -= 2; if (i < 0) i = 0; break; }
			case 's':{ imwrite(savename, image); break; }
			case 'S':{ imwrite(savename, image); break; }
			//case 's':{ imwrite(savename, src); break; }
			//case 'S':{ imwrite(savename, src); break; }
			default:{}
			}
		}
	cvDestroyAllWindows();
}

int main(int argc, char **argv)
{
	char*dir_path = argv[1];
	anno_video_folder(dir_path,640,576);
	return 0;
}