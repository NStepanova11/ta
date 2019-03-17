#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <regex>

using namespace std;

const enum LETTER_TYPES {
	EMPTY,
	LETTER,
	NUM,
	DEL,
	OPERATION,
};

const enum TOKEN_STATUS {
	ERR,
	NUM_2,
	NUM_8,
	NUM_10,
	NUM_16,
	NUM_F,
	ID,
	KEYWORD,
	DELIMITER,
	OPERATOR,
	SINGLE_COMMENT,
	MULTI_COMMENT
};

class letterDefiner {
private:
	//минимальные единицы (литеры)
	vector<char> delimiters;
	vector<char> operators;
	vector<char> numbers;
	vector<char> letters;

public:
	vector<string> initialKeywords();
	vector<char> initialDelimiters();
	vector<char> initialOperators();
	vector<char> initialNumbers();
	vector<char> initialLetters();
	map <TOKEN_STATUS, string> defineTokenNames();
};