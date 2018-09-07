#include "Statistics.h"


Statistics::Statistics(vector<string> &file_lines)//���죬�ļ����ݰ�vector<string>����
	:m_file_lines(file_lines), m_char_num(0), m_word_num(0), m_line_num(0), calculated(false)
{

}

Statistics::~Statistics()//����
{

}

bool Statistics::isLetter(const char &c)//�жϸ����ַ��Ƿ�Ϊ��ĸ
{
	return c >= 'a' && c <= 'z';
}

bool Statistics::isNumber(const char &c)//�жϸ����ַ��Ƿ�Ϊ����
{
	return c >= '0' && c <= '9';
}

void Statistics::calc()//ͳ�ƹ��ܣ��ɲ����ֶ�����
{
	for (unsigned int i = 0; i < m_file_lines.size(); i++)
	{
		const string &thisline = m_file_lines[i];
		m_char_num += thisline.size();

		bool is_a_line = false;
		for (unsigned int k = 0; k < thisline.size(); k++)//�ж��Ƿ�Ϊ�հ���
		{
			if (thisline[k] > 32)//����32Ϊ�ǿհ��ַ�
			{
				is_a_line = true;
				break;
			}
		}
		if (!is_a_line)
			continue;

		m_line_num++;
		unsigned int j = 0;
		while (j <= thisline.size() - 1)//ͳ�Ƶ��ʸ���
		{
			char c = thisline[j];
			if (isLetter(c))
			{
				string word;
				word.insert(word.end(), c);
				j++;
				if (j <= thisline.size() - 3)
				{
					while (j <= thisline.size() - 1 && (isLetter(thisline[j]) || isNumber(thisline[j])))
					{
						word.insert(word.end(), thisline[j]);
						j++;
					}
				}
				if (word.size() >= 4 && isLetter(word[0]) && isLetter(word[1]) && isLetter(word[2]) && isLetter(word[3]))
				{
					m_word_num++;
					if (m_wd_mp.find(word) == m_wd_mp.end())
						m_wd_mp[word] = 1;
					else
						m_wd_mp[word]++;
				}
			}
			else if (isNumber(c))
			{
				for (j++; j <= thisline.size() - 1 && (isLetter(thisline[j]) || isNumber(thisline[j])); j++);
			}
			else
			{
				j++;
			}
		}
	}
	calculated = true;
}

int Statistics::getCharNumber()//��ȡ�ַ�����������δ����ͳ�ƣ����Զ�����calc()
{
	if (!calculated)
		calc();
	return m_char_num;
}

int Statistics::getWordNumber()//��ȡ�ַ�����������δ����ͳ�ƣ����Զ�����calc()
{
	if (!calculated)
		calc();
	return m_word_num;
}

int Statistics::getLineNumber()//��ȡ�ַ�����������δ����ͳ�ƣ����Զ�����calc()
{
	if (!calculated)
		calc();
	return m_line_num;
}

vector<map<string, int>::iterator> &Statistics::getTopWords(unsigned int top_num)//��ȡ���ִ�������ǰ���ĵ���
{
	top_num = min(m_wd_mp.size(), top_num);
	for (unsigned int i = 0; i < top_num; i++)
	{
		int maxval = -1;
		string maxstr;
		map<string, int>::iterator maxit = m_wd_mp.begin();
		for (map<string, int>::iterator it = m_wd_mp.begin(); it != m_wd_mp.end(); it++)
		{
			if (it->second > maxit->second)
			{
				maxit = it;
			}
		}
		m_top_words.push_back(maxit);
		maxit->second = -maxit->second;
	}
	for (unsigned int i = 0; i < m_top_words.size(); i++)
	{
		m_top_words[i]->second = -m_top_words[i]->second;
	}
	return m_top_words;
}

map<string, int> Statistics::_getAllWords()//��ȡ�����ֵ�Ŀ����������ڵ��ԡ�
{
	return m_wd_mp;
}