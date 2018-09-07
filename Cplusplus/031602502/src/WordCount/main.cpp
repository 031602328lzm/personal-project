//---------------------------------------------------------------------------------------------
//�����ܣ����ı��ļ��ļ��еĵ��ʵĴ�Ƶ����ͳ��
//���з�ʽ��ֱ������exe�����������д��δ�(WordCount.exe input.txt)����
//ͳ��ָ�꣺
//		�ַ���(����ascll�ַ����ո�ˮƽ�Ʊ�������з�����)
//		������(�����Բ�����4����ĸ��ͷ��������Ը�����ĸ���֡������Էָ����ָ�����ִ�Сд)
//		�ָ���(������ĸ���ֶ��Ƿָ���)
//		��Ч�������κΰ����ǿհ��ַ�(ascllֵ����32)����
//		����Ƶ����ߵ�10�����ʡ�Ƶ����ͬ�ĵ��ʣ���������ֵ���ǰ�ĵ��ʡ�
//�����ļ�����input.txt��������ļ�output.txt�������ΪСд��
//---------------------------------------------------------------------------------------------
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Statistics.h"

string GetFileNameFromArgs(int argc, char *argv[]) ;			 // ���ڴ������д���Ĳ�������ȡ�������ļ���
bool ReadFileLines(string file_name, vector<string> &file_lines);//�����ļ�������vector<string>��ʽ�����ļ����ݣ�ÿ��Ԫ�ش���һ��
bool Output(int char_num, int word_num, int line_num, vector<map<string, int>::iterator> &top10wd,
			bool toConsole = true, bool toFile = true, string file_name = "result.txt");// ������

int main(int argc, char *argv[])//int argc,char **argv   
{//argc��������,args��������
	try {
		string file_name = GetFileNameFromArgs(argc, argv);
		vector<string> file_lines;

		if (ReadFileLines(file_name, file_lines))//����ȡ�ļ����ݳɹ�����ִ��ͳ�ƹ���
		{
			Statistics stats(file_lines);
			int char_num = stats.getCharNumber();
			int word_num = stats.getWordNumber();
			int line_num = stats.getLineNumber();
			vector<map<string, int>::iterator> &top10wd = stats.getTopWords(10);
			Output(char_num, word_num, line_num, top10wd, true, true, "result.txt");
			//�����������Ϊ���Ƿ����������̨���Ƿ�������ļ����ļ���
		}
	}
	catch (const char* err)
	{
		cout << err << endl;
	}

	//system("pause");
	return 0;
}

string GetFileNameFromArgs(int argc, char *argv[]) // ���ڴ������д���Ĳ�������ȡ�������ļ���
{
	if (argc == 1)//ֱ������
	{
		return "input.txt";
	}
	else if (argc == 2)//ͨ�������д��δ�
	{
		return argv[1];
	}
	else
	{
		throw "�������࣬����";
	}
}

bool ReadFileLines(string file_name, vector<string> &file_lines) //�����ļ�������vector<string>��ʽ�����ļ����ݣ�ÿ��Ԫ�ش���һ��
{
	ifstream ifs(file_name);
	if (!ifs)
	{
		throw "��ȡ�ļ�ʱ���ļ��쳣";
		//return false;
	}
	else
	{
		string line_buf, str_low;
		char c;
		int _cnum = 0;
		while (true)//��ȡ�ļ������ַ����룬ƴװ���У�����file_lines��
		{
			c = ifs.get();
			if (c == EOF)
			{
				if (line_buf.size() > 0)
				{
					str_low.resize(line_buf.size());
					transform(line_buf.begin(), line_buf.end(), str_low.begin(), tolower);
					file_lines.push_back(str_low);
					//cout << str_low;
				}
				break;
			}
			line_buf += c;
			_cnum++;
			if (c == '\n')
			{
				str_low.resize(line_buf.size());
				transform(line_buf.begin(), line_buf.end(), str_low.begin(), tolower);
				file_lines.push_back(str_low);
				//cout << str_low;
				line_buf = "";
			}
		}
		//cout << "std char num:" << _cnum << endl;
		ifs.close();
		return true;
	}
}

bool Output(int char_num, int word_num, int line_num, vector<map<string, int>::iterator> &top10wd,
	bool toConsole, bool toFile, string file_name)// ��������ͨ��toConsole��toFile���ôӿ���̨���ļ������
{
	if (toConsole)// output to console
	{
		cout << "characters: " << char_num << endl;
		cout << "words: " << word_num << endl;
		cout << "lines: " << line_num << endl;
		for (unsigned int i = 0; i < top10wd.size(); i++)
		{
			cout << "<" << top10wd[i]->first << ">: " << top10wd[i]->second << endl;
		}
	}
	if (toFile)// output to file
	{
		ofstream ofs(file_name);
		if (!ofs)
		{
			throw "����ļ�ʱ���ļ��쳣";
			//return false;
		}
		else
		{
			ofs << "characters: " << char_num << endl;
			ofs << "words: " << word_num << endl;
			ofs << "lines: " << line_num << endl;
			for (unsigned int i = 0; i < top10wd.size(); i++)
			{
				ofs << "<" << top10wd[i]->first << ">: " << top10wd[i]->second << endl;
			}
			ofs.close();
		}
	}
	return true;
}
