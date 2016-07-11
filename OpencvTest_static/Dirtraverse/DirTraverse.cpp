#include "getfile.h"
#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <stdlib.h>
char *find_replace(char *str, char *orig, char *rep)
{
	static char buffer[4096];
	static char buffer2[4096];
	static char buffer3[4096];
	char *p;

	if (!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
		return str;

	strncpy(buffer2, str, p - str); // Copy characters from 'str' start to 'orig' st$
	buffer2[p - str] = '\0';

	sprintf(buffer3, "%s%s%s", buffer2, rep, p + strlen(orig));
	sprintf(buffer, "%s", buffer3);

	return buffer;
}
//浏览文件夹下所有某种特定格式文件
//int main(int argc, char * argv[])
//{
//	//string dir_path = argv[1];
//	string dir_path = "../images/";
//	vector<string> image_names;
//	getFiles(dir_path, "jpg", image_names);
//
//	for (int i = 0; i < image_names.size(); i++)
//	{
//		string fileName = image_names[i];
//		string fileFullName = dir_path + fileName;
//		cout << "file name:" << fileName << endl;
//		cout << "file paht:" << fileFullName << endl << endl;
//
//		//Image processing
//		Mat pScr;
//		pScr = imread(fileFullName, 1); //以文件名命名窗口 
//		namedWindow("Imshow", CV_WINDOW_AUTOSIZE);
//		//imshow(fileName, pScr);
//		imshow("Imshow", pScr);
//		waitKey(1000);
//	}
//	//system("pause");
//	return EXIT_SUCCESS;
//}
int main(int argc, char ** argv)
{
	string dir_path = argv[1];
	vector<string> image_names;
	getFiles(dir_path, "", image_names);
	int i;
	printf("%d\n", image_names.size());
	FILE *fps;
	char save_imageName[256];
	sprintf(save_imageName, "../images/images.txt");
	fps = fopen(save_imageName, "w");
	for ( i = 0; i < image_names.size(); i++)
	{
		fprintf(fps, "%s\n", image_names[i]);
	}
	fclose(fps);
	return 0;
}
