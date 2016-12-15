#pragma once
#include <string>
#include <vector>
using namespace std;

#define LETTER(c) ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' ||\
'à' <= c && c <= 'ÿ' || 'À' <= c && c <= 'ß')

string & ToLowerCase(string & str)
{
	for (int i = 0; i < (int)str.length(); i++)
	{
		if ('A' <= str[i] && str[i] <= 'Z') str[i] = 'a' + str[i] - 'A';
		else
			if ('À' <= str[i] && str[i] <= 'ß') str[i] = 'à' + str[i] - 'À';
	}
	return str;
}

void CutStrIntoWords(string const & str, vector<string> & words)
{
	words.clear();
	int beginIndex;
	bool found = false;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (LETTER(str[i]))
		{
			if (!found)
			{
				found = true;
				beginIndex = i;
			}
		} else
		{
			if (found)
			{
				found = false;
				words.push_back(str.substr(beginIndex, i - beginIndex));
			}
		}
	}
	if (found) words.push_back(ToLowerCase(str.substr(beginIndex,
		str.length() - beginIndex)));
}