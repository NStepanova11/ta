#include "stdafx.h"
#include "Analisator.h"

Analisator::Analisator()
	:keywords(initialKeywords())
	,delimiters(initialDelimiters())
	,operators(initialOperators())
	,tokenNames(initialTokenNames())
{
}

vector<string> Analisator::initialKeywords(){
	vector<string> k;
	k.push_back("for");
	k.push_back("break");
	k.push_back("if");
	k.push_back("else");
	k.push_back("println");
	k.push_back("while");
	return k;
}

vector<char> Analisator::initialDelimiters() {
	vector<char> d;
	d.push_back(' ');
	d.push_back(';');
	d.push_back(',');
	return d;
}

vector<char> Analisator::initialOperators() {
	vector<char> o;
	o.push_back('+');
	o.push_back('-');
	o.push_back('*');
	o.push_back('/');
	o.push_back('%');
	o.push_back('=');
	return o;
}

map<TOKEN_TYPES, string> Analisator::initialTokenNames() {
	map<TOKEN_TYPES, string> tNames = {
		{ TOKEN_TYPES::KEYWORD, "KEYWORD" },
		{ TOKEN_TYPES::DELIMITER, "DELIMITER" },
		{ TOKEN_TYPES::OPERATOR, "OPERATOR" }
	};
	return tNames;
}

void Analisator::readFile() {
	ifstream fin("input.txt");
	string fileLine;
	string lexem;
	while (getline(fin, fileLine))
	{
		for (size_t i = 0; i <fileLine.size(); i++)
		{
			if (find(delimiters.begin(), delimiters.end(), fileLine[i])==delimiters.end()) {
				lexem += fileLine[i];
			}
			else if (find(delimiters.begin(), delimiters.end(), fileLine[i]) != delimiters.end()){
				lexems.push_back(lexem);
				lexems.push_back(lexem = fileLine[i]);
				lexem = "";
			}
		}
		if (lexem.size() != 0) {
			lexems.push_back(lexem);
			lexem = "";
		}
	}
	fin.close();
}

void Analisator::testCase() {
	readFile();
	for (auto el : lexems) {
		cout << "\'"<<el << "\'" << endl;
	}
}