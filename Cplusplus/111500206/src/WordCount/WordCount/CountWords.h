#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
// DFA
int transition(int state, char input, int count);
// ͳ�Ƶ��ʵ�����
int CountWords(char * filename);