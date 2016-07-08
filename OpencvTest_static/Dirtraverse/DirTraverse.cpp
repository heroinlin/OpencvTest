#include "getfile.h"
#include <stdio.h>
#include <windows.h>
#include <io.h>
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
int main(int argc, char * argv[])
{
	string dir_path = argv[1];
	vector<string> image_names;
	getFiles(dir_path, ".jpg", image_names);
	int i;
	printf("%d\n", image_names.size());
	for ( i = 0; i < image_names.size(); i++)
	{
		char fileName[256];
		char save_imageName[256];
		sprintf(fileName,"%s", image_names[i]);
		printf("%s", fileName);
		char save_labelName[256];
		sprintf(save_imageName, "../images/images/%07d.jpg", i + 1);
		sprintf(save_labelName, "../images/jpg/%07d.txt", i + 1);
		char *labeltxt = find_replace(fileName, ".jpg", ".txt");
		rename(fileName, save_imageName);
		rename(labeltxt, save_labelName);
	}
	return 0;
}
