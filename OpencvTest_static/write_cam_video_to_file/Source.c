#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
void show_video(int camera_index, char *videopath, char *out_video_path)
{
	IplImage *frame = NULL;
	CvCapture *capture;
	int ncount = 0;
	int Writer_flag = 0;
	CvVideoWriter* output_video = NULL;
	if (camera_index == -1){
		/* Load the video from file  */
		capture = cvCreateFileCapture(videopath);
	}
	else{
		/* Load the video from camera */
		capture = cvCreateCameraCapture(camera_index);
	}
	while (1)
	{
		frame = cvQueryFrame(capture);
		double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
		int width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
		int height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
		CvSize size = cvSize(width, height);
		if (output_video == NULL){
			/*注意size大小与后来写入帧的大小要一致，否则输出的将是6k文件*/
			output_video = cvCreateVideoWriter(out_video_path, CV_FOURCC('X', 'V', 'I', 'D'), 25.0, size, 1);
		}
		if (!frame && ncount > 1){
			break;
		}
		if (ncount > 1){
			if (Writer_flag){
				cvWriteFrame(output_video, frame);
			}
			cvShowImage("video", frame);
			int key = cvWaitKey(1);
			if (key == 's'){
				Writer_flag = !Writer_flag;
			}
			if (key == 27)
				break;
		}
		ncount++;
	}
	cvReleaseCapture(&output_video);
	cvDestroyAllWindows();
}

int main(int argc, char *argv[])
{
	//char *video_path = "../c2/2017_2_21-14_3_15-2.avi";
	char *video_path = argv[1];
	//char *image_path = "2.jpg";
	show_video(0, 1, "./out.avi");
	system("pause");
	return 0;
}