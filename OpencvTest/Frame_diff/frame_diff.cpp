#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace std;
using namespace cv;

//our sensitivity value to be used in the absdiff() function
const static int SENSITIVITY_VALUE = 20;
//size of blur used to smooth the intensity image output from absdiff() function
const static int BLUR_SIZE = 10;
//we'll have just one object to search for
//and keep track of its position.
int theObject[2] = { 0, 0 };
//bounding rectangle of the object, we will use the center of this as its position.
Rect objectBoundingRectangle = Rect(0, 0, 0, 0);


//int to string helper function
string intToString(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}

int main(int argc, char** argv){

	//these two can be toggled by pressing 'd' or 't'
	bool debugMode = true;
	//pause and resume code
	bool pause = false;
	//set up the matrices that we will need
	//the two frames we will be comparing
	Mat frame1, frame2;
	//their grayscale images (needed for absdiff() function)
	Mat grayImage1, grayImage2;
	//resulting difference image
	Mat differenceImage;
	//thresholded difference image (for use in findContours() function)
	Mat thresholdImage;
	//video capture object.
	VideoCapture capture;
	//char *path = argv[1];
	char *path = "../videos/1.avi";
	//while (1){

		//we can loop the video by re-opening the capture every time the video reaches its last frame

		capture.open(path);

		if (!capture.isOpened()){
			cout << "ERROR ACQUIRING VIDEO FEED\n";
			getchar();
			return -1;
		}

		//check if the video has reach its last frame.
		//we add '-1' because we are reading two frames from the video at a time.
		//if this is not included, we get a memory error!
		while (capture.get(CV_CAP_PROP_POS_FRAMES)<capture.get(CV_CAP_PROP_FRAME_COUNT) - 1){

			//read first frame
			capture.read(frame1);
			//convert frame1 to gray scale for frame differencing
			cv::cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);
			//copy second frame
			capture.read(frame2);
			//convert frame2 to gray scale for frame differencing
			cv::cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);
			//perform frame differencing with the sequential images. This will output an "intensity image"
			//do not confuse this with a threshold image, we will need to perform thresholding afterwards.
			cv::absdiff(grayImage1, grayImage2, differenceImage);
			//threshold intensity image at a given sensitivity value
			cv::threshold(differenceImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){
				//show the difference image and threshold image
				cv::imshow("Difference Image", differenceImage);
				cv::imshow("Threshold Image", thresholdImage);
			}
			else{
				//if not in debug mode, destroy the windows so we don't see them anymore
				cv::destroyWindow("Difference Image");
				cv::destroyWindow("Threshold Image");
			}
			//blur the image to get rid of the noise. This will output an intensity image
			cv::blur(thresholdImage, thresholdImage, cv::Size(BLUR_SIZE, BLUR_SIZE));
			//threshold again to obtain binary image from blur output
			cv::threshold(thresholdImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){
				//show the threshold image after it's been "blurred"

				imshow("Final Threshold Image", thresholdImage);

			}
			else {
				//if not in debug mode, destroy the windows so we don't see them anymore
				cv::destroyWindow("Final Threshold Image");
			}

			//if tracking enabled, search for contours in our thresholded image


			//show our captured frame
			imshow("Frame1", frame1);
			//check to see if a button has been pressed.
			//this 10ms delay is necessary for proper operation of this program
			//if removed, frames will not have enough time to referesh and a blank 
			//image will appear.
			waitKey(1);
		}
		//release the capture before re-opening and looping again.
		capture.release();
	//}

	return 0;

}