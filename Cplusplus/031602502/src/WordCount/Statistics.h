#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class Statistics//ͳ���� ��װ������ͳ�Ƶķ���
{
public:
	Statistics(vector<string> &file_lines);	//���죬�ļ����ݰ�vector<string>����
	~Statistics();							//����
	inline bool isLetter(const char &c);	//�жϸ����ַ��Ƿ�Ϊ��ĸ
	inline bool isNumber(const char &c);	//�жϸ����ַ��Ƿ�Ϊ����
	void calc();							//ͳ�ƹ��ܣ��ɲ����ֶ�����
	int getCharNumber();					//��ȡ�ַ�����������δ����ͳ�ƣ����Զ�����calc()
	int getWordNumber();					//��ȡ�ַ�����������δ����ͳ�ƣ����Զ�����calc()
	int getLineNumber();					//��ȡ�ַ�����������δ����ͳ�ƣ����Զ�����calc()
	vector<map<string, int>::iterator> &getTopWords(unsigned int top_num);	//��ȡ���ִ�������ǰ���ĵ���
	map<string, int> _getAllWords();		//��ȡ�����ֵ�Ŀ����������ڵ��ԡ�
private:
	vector<string> &m_file_lines;
	map<string, int> m_wd_mp;
	vector<map<string, int>::iterator> m_top_words;
	int m_char_num;
	int m_word_num;
	int m_line_num;
	bool calculated;
};
