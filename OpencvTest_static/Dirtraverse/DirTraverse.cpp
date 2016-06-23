#include "getfile.h"
//����ļ���������ĳ���ض���ʽ�ļ�
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
		pScr = imread(fileFullName, 1); //���ļ����������� 
		namedWindow("Imshow", CV_WINDOW_AUTOSIZE);
		//imshow(fileName, pScr);
		imshow("Imshow", pScr);
		waitKey(1000);


	}

	//system("pause");
	return EXIT_SUCCESS;
}
