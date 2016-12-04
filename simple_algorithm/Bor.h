#pragma once
#include <map>
#include <vector>
#include <set>
using namespace std;

class Bor
{
public:
	Bor() : root(new Node('*')) {}
	void AddToBor(string const & str, int const quIndex, bool markAllLetters = false); // �������� � ��� ������
	set<int> const * const SearchInBor(string const & str); // ����� � ���� ������ � ������� set
	void SearchPartial(string const & str, vector<int> & queCnt, int const quAmount);
	void PrintBor();
private:	
	static int CharToId(char c);

	class Node
	{
	public:
		Node(char const c) : letter(Bor::CharToId(c)) {}
		int letter; // 0..32 + 33..58 - ����� �����
		set<int> quIndeces;  /*���� ��� ������������ �������,
								�� ����� �������� ����� �������, � �������� ����������� �����*/
		map<int, Node*> pointers; /*��������� �� ��������� �������*/
	};
	Node * root;
	void PrintNode(Node * node);
};