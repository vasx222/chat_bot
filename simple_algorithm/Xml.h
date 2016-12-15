#pragma once
#include <libxl.h>
#include <string>
#include <vector>
using namespace libxl;
using namespace std;

void CreateSimpleXML()
{
	Book * book = xlCreateBook(); // xlCreateXMLBook() for xlsx
	if (book)
	{
		Sheet* sheet = book->addSheet("Sheet1");
		if (sheet)
		{
			sheet->writeStr(2, 1, "Hello, World !");
			sheet->writeNum(3, 1, 1000);
		}
		book->save("my_example.xls");
		book->release();
	}
}

void ParseXMLQuestions(vector<string> & que, vector<string> & ans, int const quAmount)
{
	que.resize(quAmount);
	ans.resize(quAmount);
	Book * book = xlCreateXMLBook();
	book->load("voprosy.xlsx");
	Sheet * sheet = book->getSheet(0);

	for (int i = 0; i < quAmount; i++)
	{
		que[i] = sheet->readStr(i + 1, 1);
		ans[i] = sheet->readStr(i + 1, 2);
	}
	book->release();
}