#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include "Xml.h"
#include "Bor.h"
#include "Str.h"

const int quAmount = 120;
const int minWordLength = 4;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); // + в настройках консоли включить lucida console
	vector<string> que(quAmount), ans(quAmount);
	
	ParseXMLQuestions(que, ans, quAmount);
	for (int i = 0; i < quAmount; i++)
	{
		EraseExtraSymbols(que[i]);
		EraseExtraSymbols(ans[i]);
	}

	Bor bor;
	vector<vector<string> > aWords(quAmount);
	for (int i = 0; i < (int)aWords.size(); i++)
	{
		CutStrIntoWords(que[i], aWords[i]);
		for (int j = 0; j < (int)aWords[i].size(); j++)
		{
			for (int t = 0; t < (int)aWords[i][j].length() - (minWordLength - 1); t++)
			{
				bor.AddToBor(aWords[i][j].substr(t, (int)aWords[i][j].length() - t), i, true);
			}
		}
	}

	while (true) {
		//cerr << "TYPE SOME WORDS:" << endl;
		string userStr;
		getline(cin, userStr);
		/*ifstream fin;
		fin.open("in.txt");
		if (!fin.is_open()) cerr << "FILE DOES NOT EXIST" << endl;
		else
		{
			getline(fin, userStr); cerr << userStr << endl;
		}
		fin.close();*/
		vector<string> userWords;
		CutStrIntoWords(userStr, userWords);

		vector<pair<int, int> > queCnt(quAmount);
		for (int i = 0; i < quAmount; i++) queCnt[i] = make_pair(0, i);

		for (int i = 0; i < (int)userWords.size(); i++)
		{
			for (int j = 0; j < (int)userWords[i].length() - (minWordLength - 1); j++)
			{
				bor.SearchPartial(userWords[i].substr(j, (int)userWords[i].length() - j),
					queCnt, quAmount);
			}
		}
		sort(queCnt.begin(), queCnt.end(), [](pair<int, int> & a, pair<int, int> & b)
		{
			return a.first > b.first;
		});
		for (int i = 0; i < 5; i++)
		{
			cerr << endl << "FOUND QUESTION #" << queCnt[i].second + 1 << ":" << endl;
			cout << que[queCnt[i].second];
			cout << endl;
			cerr << endl << "ANSWER: ";
			cout << ans[queCnt[i].second];
			cout << endl;
			cerr << endl;
		}
		//system("pause");
		//system("cls");
	}
}