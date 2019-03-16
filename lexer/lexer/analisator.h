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

using namespace std;

class Analisator {
private:
	vector<char> delimiters;
	vector<char> operators;
	vector<char> numbers;
	vector<char> letters;
	vector<string> keywords;

	letterDefiner letterDefiner;
	map <TOKEN_STATUS, vector<LETTER_TYPES>> lettersOfTokenMap;
	//map<TOKEN_TYPES, string> tokenNamesMap;
	vector<pair<string, string>> lexemList;

public:
	Analisator();
	//map<TOKEN_TYPES, string> initialTokenNames();
	void readFile();
	void parseLexems(string &fileLine);
	void checkLexemTypes(string &fileLine);
	LETTER_TYPES getLetterType(char c);
	void generateTokensTable();
	string getTextLexemType(string word);
	void testCase();
};