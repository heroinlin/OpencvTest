#include "getfile.h"
//浏览文件夹下所有某种特定格式文件
int main(int argc, char * argv[])
{
	//string dir_path = argv[1];
	string dir_path = "../images/";
	vector<string> image_names;
	getFiles(dir_path, "jpg", image_names);

	for (int i = 0; i < image_names.size(); i++)
	{
		string fileName = image_names[i];
		string fileFullName = dir_path + fileName;
		cout << "file name:" << fileName << endl;
		cout << "file paht:" << fileFullName << endl << endl;

		//Image processing
		Mat pScr;
		pScr = imread(fileFullName, 1); //以文件名命名窗口 
		namedWindow("Imshow", CV_WINDOW_AUTOSIZE);
		//imshow(fileName, pScr);
		imshow("Imshow", pScr);
		waitKey(1000);


	}

	//system("pause");
	return EXIT_SUCCESS;
}
