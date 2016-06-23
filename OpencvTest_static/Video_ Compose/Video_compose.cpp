//图片合成为视频
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	CvSize size = cvSize(480, 360);
	double fps = 1;
	char *output = "out.avi";
	//创建一个写视频 设备writer 
	CvVideoWriter* writer = cvCreateVideoWriter(output, CV_FOURCC('X', 'V', 'I', 'D'), fps, size,1);
	/*读入一个文件夹下的所有图片*/
	int image_id = 1;
	char filename[256];
	char *filepath=argv[1];
	sprintf(filename, "%s/%07d.jpg", filepath,image_id);
	printf("%s\n",filename);
	//加载图像
	IplImage* src = cvLoadImage(filename);
	if (!src)
	{
		return 0;
	}
	//为resize后的图像分配空间
	IplImage* src_resize = cvCreateImage(size, 8, 3);
	cvNamedWindow("avi");
	while (src)
	{
		/*显示图像 本步骤不是必须的*/
		cvShowImage("avi", src_resize);
		cvWaitKey(1);
		/*resize图像 使得写入视频文件的图像src_resize 与 视频文件的宽 高 是一样的 视频文件的宽 高是CvSize size = cvSize(480,360);*/
		cvResize(src, src_resize);
		/*将图像src_resize 写入到视频设备writer*/
		cvWriteFrame(writer, src_resize);
		/*释放内存空间*/
		cvReleaseImage(&src);
		//加载文件夹中的下一幅图像 
		image_id++;
		sprintf(filename, "%s/%07d.jpg", filepath, image_id);
		src = cvLoadImage(filename);
	}
	/*释放写设备*/
	cvReleaseVideoWriter(&writer);
	/*释放图像空间*/
	cvReleaseImage(&src_resize);
	return 0;

}