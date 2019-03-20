#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "letterDefiner.h"
#include <iomanip>

using namespace std;

class Analisator {
private:
	vector<char> delimiters;
	vector<char> operators;
	vector<char> numbers;
	vector<char> letters;
	vector<string> keywords;
	string multiComment;

	letterDefiner letterDefiner;
	map <TOKEN_STATUS, vector<LETTER_TYPES>> lettersOfTokenMap;
	map <TOKEN_STATUS, string> tokenName;
	vector<pair<string, string >> lexemList;

public:
	Analisator();
	void readFile();
	void checkLexemTypes(string &fileLine);
	LETTER_TYPES getLetterType(char c);
	void generateTokensTable();
	string getTextLexemType(string word);
	string getNumberLexemType(string word);
	string getDivisionLexemType(string word);

	void testCase();
};