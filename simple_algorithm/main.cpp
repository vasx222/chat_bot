#include <iostream>
#include <libxl.h>
#include <string>
using namespace libxl;

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

void ParseXMLQuestions()
{
	Book * book = xlCreateXMLBook();
	book->load("questions.xlsx");
	Sheet * sheet = book->getSheet(0);
	std::string str = sheet->readStr(1, 1);
	std::cout << str << std::endl;
	book->release();
}

int main()
{
	setlocale(LC_ALL, "Rus");
	ParseXMLQuestions();
	system("pause");
}