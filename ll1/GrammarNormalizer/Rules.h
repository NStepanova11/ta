#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

class Rules
{
private:
	unordered_map<string, vector<vector<string>>> m_alternatives; //���� -> ����� �����, �������� -> ������ ������ ������, ������� ������ ����� - ���������� �������
	vector<string> m_rules;
	bool factorizIsFound;
	bool leftRecIsFound;
public:
	void ReadRulesFromFile();
	void GetRulesAlternatives();
	void ShowAllAlternativesMap();
	void FindFactorization();
	void AddNewRule();
};

