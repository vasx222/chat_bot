#include "Bor.h"
#include <iostream>

int Bor::CharToId(char const c)
{
	if ('à' <= c && c <= 'ÿ')
	{
		return c - 'à';
	}
	if ('a' <= c && c <= 'z')
	{
		return c - 'a' + 33;
	}
	return -1;
}

void Bor::AddToBor(string const & str, int const quIndex,
	bool markAllLetters)
{
	if (str.length() == 0) return;
	int index = 0;
	Node * node = root;
	while (index <= str.length())
	{
		if (markAllLetters && index > 0 && index < str.length())
		{
			node->quIndeces.insert(quIndex);
		}
		if (index == str.length())
		{
			node->quIndeces.insert(quIndex);
			return;
		}
		auto it = node->pointers.find(CharToId(str[index]));
		if (it == node->pointers.end())
		{
			Node * newNode = new Node(str[index]);
			node->pointers[CharToId(str[index])] = newNode;
			node = newNode;
		} else
		{
			node = (*it).second;
		}
		index++;
	}
}

set<int> const * const Bor::SearchInBor(string const & str)
{
	if (str.length() == 0) return nullptr;
	int index = 0;
	Node * node = root;
	while (index <= str.length())
	{
		auto it = node->pointers.find(CharToId(str[index]));
		if (it == node->pointers.end()) return nullptr;
		node = (*it).second;
		index++;
		if (index == str.length())
		{
			if (node->quIndeces.empty()) return nullptr;
			return &node->quIndeces;
		}
	}
	return nullptr;
}

void Bor::SearchPartial(string const & str, vector<int> & queCnt, int const quAmount)
{
	if (str.length() == 0) return;
	if (queCnt.size() != quAmount) queCnt.resize(quAmount, 0);
	int index = 0;
	Node * node = root;
	while (index <= str.length())
	{
		auto it = node->pointers.find(CharToId(str[index]));
		if (it == node->pointers.end()) return;
		node = (*it).second;
		index++;
		for (auto it = node->quIndeces.begin(); it != node->quIndeces.end(); ++it)
		{
			queCnt[(*it)]++;
		}
	}
}

void Bor::PrintBor()
{
	PrintNode(root);
}

void Bor::PrintNode(Node * node)
{
	cout << endl << "node = " << node << ", letter = " << node->letter << endl;
	if (node)
	{
		cout << "children:" << endl;
		for (auto it = node->pointers.begin(); it != node->pointers.end(); ++it)
		{
			cout << (*it).first << " " << (*it).second << endl;
		}
		cout << "quIndeces:" << endl;
		for (auto it = node->quIndeces.begin(); it != node->quIndeces.end(); ++it)
		{
			cout << (*it) << endl;
		}
		for (auto it = node->pointers.begin(); it != node->pointers.end(); ++it)
		{
			PrintNode((*it).second);
		}
	}
}

