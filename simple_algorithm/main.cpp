#include <iostream>
#include <libxl.h>
#include <string>
using namespace libxl;
using namespace std;
void CreateSimpleXML()
{
	Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
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

void ParseXMLQuestions(string * que, string * ans)
{
	Book * book = xlCreateXMLBook();
	book->load("questions.xlsx");
	Sheet * sheet = book->getSheet(0);

	for (int i = 0; i < 40; i++)
	{
		que[i] = sheet->readStr(i + 1, 1);
		ans[i] = sheet->readStr(i + 1, 2);
	}
	book->release();
}

int main()
{
	setlocale(LC_ALL, "Rus");
	string que[40], ans[40];
	ParseXMLQuestions(que, ans);
	for (int i = 0; i < 40; i++)
	{
		cout << "QUESTION: " << que[i] << "\nANSWER: " << ans[i] << "\n\n";
	}
	system("pause");
}