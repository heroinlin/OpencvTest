#include "im_pro.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	char*dir_path = argv[1];
	float scale = 1.0;
	//anno_video_folder(dir_path,640,576);
	//anno_video_list(dir_path, scale);
	anno_images_list(dir_path, scale);
	return 0;
}