#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Xml.h"
#include "Bor.h"
#include "Str.h"

const int quAmount = 40;

int main()
{
	while (true) {
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
				for (int t = 0; t < (int)aWords[i][j].length() - 3; t++)
				{
					bor.AddToBor(aWords[i][j].substr(t, (int)aWords[i][j].length() - t), i, true);
				}
			}
		}

		cout << "TYPE SOME WORDS:" << endl;
		string userStr;
		getline(cin, userStr);
		vector<string> userWords;
		CutStrIntoWords(userStr, userWords);

		vector<pair<int, int> > queCnt;
		for (int i = 0; i < (int)userWords.size(); i++)
		{
			for (int j = 0; j < (int)userWords[i].length() - 3; j++)
			{
				bor.SearchPartial(userWords[i].substr(j, (int)userWords[i].length() - j),
					queCnt, quAmount);
			}
		}
		sort(queCnt.begin(), queCnt.end(), [](pair<int, int> & a, pair<int, int> & b)
		{
			return a.first > b.first;
		});
		for (int i = 0; i < 6; i++)
		{
			cout << endl << "FOUND QUESTION #" << queCnt[i].second + 1 << ":" << endl <<
				que[queCnt[i].second] << endl;
		}

		//int imax = -1;
		//for (int i = 0; i < (int)queCnt.size(); i++)
		//{
		//	if (imax == -1 || queCnt[imax] < queCnt[i]) imax = i;
		//}
		//cout << "FOUND QUESTION #" << imax + 1 << ":" << endl << que[imax] << endl;
		system("pause");
		system("cls");
	}
}