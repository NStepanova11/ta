#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const enum TOKEN_TYPES {
	KEYWORD,
	DELIMITER,
	OPERATOR
};

class Analisator {
private:
	vector<string> keywords;
	vector<char> delimiters;
	vector<char> operators;
	map<TOKEN_TYPES, string> tokenNames;
	vector<string> lexems;
public:
	Analisator();
	vector<string> initialKeywords();
	vector<char> initialDelimiters();
	vector<char> initialOperators();
	map<TOKEN_TYPES, string> initialTokenNames();
	void readFile();

	void testCase();
};