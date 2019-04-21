#include<string>
#include<iostream>
#include<fstream>
#include<io.h>
#include<vector>
using namespace std;
void getFiles(string path, vector<string>& files,vector<string>&filenames)
{
	//�ļ����  
	long long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files,filenames);
			}
			else
			{
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				filenames.push_back(fileinfo.name);
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

//�ú���ͨ����ȡlable�ļ�����ͼ��xml��Ӧ��label�ļ����ж��Ƿ��ͼ����person��ǩ������ͼƬ����Ӧ��xml�ļ����Ƶ����ļ�����
void choose_onlypeople()
{
	vector<string>filenames;
	vector<string>files;
	string str_label_old ="C:\\Users\\С��\\Downloads\\VOCtest_06-Nov-2007\\VOCdevkit\\VOC2012\\labels";
	string str_image_old = "C:\\Users\\С��\\Downloads\\VOCtest_06-Nov-2007\\VOCdevkit\\VOC2012\\JPEGImages";
	string str_xml_old = "C:\\Users\\С��\\Downloads\\VOCtest_06-Nov-2007\\VOCdevkit\\VOC2012\\Annotations";
	string str_image_new = "C:\\Users\\С��\\Downloads\\VOCtest_06-Nov-2007\\VOCdevkit\\VOC2012\\image_people";
	string str_xml_new = "C:\\Users\\С��\\Downloads\\VOCtest_06-Nov-2007\\VOCdevkit\\VOC2012\\xml_people";
	getFiles(str_label_old, files, filenames);
	ifstream all_file;
	for (int i = 0; i < files.size(); ++i)
	{
		all_file.open(files.at(i));
		string line;
		while (getline(all_file, line))
		{
			string line_first = line.substr(0,line.find_first_of(' '));
			if (line_first == "14")
			{
				string name = filenames.at(i).substr(0, filenames.at(i).find_first_of('.'));
				string image_old = str_image_old + "/" + name + ".jpg";
				string image_new= str_image_new + "/" + name + ".jpg";
				string xml_old = str_xml_old + "/" + name + ".xml";
				string xml_new = str_xml_new + "/" + name + ".xml";
				rename(image_old.c_str(),image_new.c_str());
				rename(xml_old.c_str(), xml_new.c_str());
				break;
			}
		}
		all_file.close();
	}
	
}

void delete_label_others()
{
	vector<string>filenames;
	vector<string>files;
	string str_label_old = "L:\\labels";
	string str_label_new = "L:\\labels1";
	getFiles(str_label_old, files, filenames);
	ifstream all_file;
	ofstream new_all_files;
	for (int i = 0; i < files.size(); ++i)
	{
		all_file.open(files.at(i));
		string str2 = str_label_new + "/" + filenames.at(i);
		cout << str2 << endl;
		new_all_files.open(str2);
		string line;
		while (getline(all_file, line))
		{
			cout << line << endl;
			string line_first = line.substr(0, line.find_first_of(' '));
			cout << line_first << endl;
			if (line_first == "0")
			{
				new_all_files << line << endl;
			}
		}
		all_file.close();
		new_all_files.close();
	}
}
//int main()
//{
//	delete_label_others();
//}

int main()
{
	string path = "C:\\Users\\С��\\Desktop\\212";
	vector<string>filenames;
	vector<string>files;
	getFiles(path, files, filenames);
	for (int i = 0; i < files.size(); ++i)
	{
		cout << "files :"<<files.at(i) << endl;
	}

}