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

const enum TOKEN_TYPES {
	KEYWORD,
	DELIMITER,
	OPERATOR,
	DEC_NUM
};

class Analisator {
private:
	vector<char> delimiters;
	vector<char> operators;
	vector<char> numbers;
	vector<char> letters;
	vector<string> keywords;

	letterDefiner letterDefiner;
	map<TOKEN_TYPES, string> tokenNamesMap;
	vector<string> lexemList;

public:
	Analisator();
	map<TOKEN_TYPES, string> initialTokenNames();
	void readFile();
	void parseLexems(string &fileLine);

	void testCase();
};