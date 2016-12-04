#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <windows.h>
#include "Xml.h"
#include "Bor.h"
#include "Str.h"

const int quAmount = 40;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); // + в настройках консоли включить lucida console
	vector<string> que(quAmount), ans(quAmount);
	ParseXMLQuestions(que, ans, quAmount);

	Bor bor;
	vector<vector<string> > aWords(quAmount);
	for (int i = 0; i < (int)aWords.size(); i++)
	{
		CutStrIntoWords(que[i], aWords[i]);
		for (int j = 0; j < (int)aWords[i].size(); j++)
		{
			bor.AddToBor(aWords[i][j], i, true);
		}
	}

	cout << "TYPE SOME WORDS:" << endl;
	string userStr;
	getline(cin, userStr);
	vector<string> userWords;
	CutStrIntoWords(userStr, userWords);
	
	vector<int> queCnt(quAmount);
	for (int i = 0; i < (int)userWords.size(); i++)
	{
		bor.SearchPartial(userWords[i], queCnt, quAmount);
	}
	int imax = -1;
	for (int i = 0; i < (int)queCnt.size(); i++)
	{
		if (imax == -1 || queCnt[imax] < queCnt[i]) imax = i;
	}
	cout << "FOUND QUESTION #" << imax + 1 << ":" << endl << que[imax] << endl;
	system("pause");
}