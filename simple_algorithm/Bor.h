#pragma once
#include <map>
#include <vector>
#include <set>
using namespace std;

class Bor
{
public:
	Bor() : root(new Node('*')) {}
	void AddToBor(string const & str, int const quIndex, bool markAllLetters = false); // Добавить в бор строку
	set<int> const * const SearchInBor(string const & str); // Найти в боре строку и вернуть set
	void SearchPartial(string const & str, vector<int> & queCnt, int const quAmount);
	void PrintBor();
private:	
	static int CharToId(char c);

	class Node
	{
	public:
		Node(char const c) : letter(Bor::CharToId(c)) {}
		int letter; // 0..32 + 33..58 - номер буквы
		set<int> quIndeces;  /*если это терминальная вершина,
								то здесь хранится номер вопроса, к которому принадлежит слово*/
		map<int, Node*> pointers; /*указатели на следующие вершины*/
	};
	Node * root;
	void PrintNode(Node * node);
};