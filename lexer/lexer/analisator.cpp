#include "stdafx.h"
#include "Analisator.h"

Analisator::Analisator()
	:keywords(letterDefiner.initialKeywords())
	,letters(letterDefiner.initialLetters())
	,numbers(letterDefiner.initialNumbers())
	,operators(letterDefiner.initialOperators())
	,delimiters(letterDefiner.initialDelimiters())
{
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
	while (getline(fin, fileLine))
	{
		parseLexems(fileLine);
	}
	fin.close();
}

void Analisator::parseLexems(string &fileLine) {
	string  lexem;
	char letter;
	int i = 0;
	
	while (i < fileLine.size())
	{
		stringstream ss;
		string s;
		letter = fileLine[i];
		ss << letter;
		ss >> s;

		if (find(delimiters.begin(), delimiters.end(), letter) != delimiters.end()) {

			if (lexem.size() != 0) {
				lexemList.push_back(lexem);
				cout << "\'" << lexem << "\'" << endl;
			}
			lexemList.push_back(s);
			cout << "\'" << s << "\'" << endl;
			lexem.clear();
		}
		else {
			lexem+=s;
		}
		i++;
	}

	if (lexem.size()!=0) {
		lexemList.push_back(lexem);
		cout << "\'" << lexem << "\'" << endl;
	}
}

void Analisator::testCase() {
	readFile();
	/*
	for (auto el : lexemList) {
		cout << "\'"<<el << "\'" << endl;
	}*/
}


/*
for (size_t i = 0; i <fileLine.size(); i++)
{
if (find(delimiters.begin(), delimiters.end(), fileLine[i]) == delimiters.end()) {
lexem += fileLine[i];
}
else if (find(delimiters.begin(), delimiters.end(), fileLine[i]) != delimiters.end()) {
lexemList.push_back(lexem);
lexemList.push_back(lexem = fileLine[i]);
lexem = "";
}
}
if (lexem.size() != 0) {
lexemList.push_back(lexem);
lexem = "";
}*/