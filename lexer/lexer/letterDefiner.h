#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>

using namespace std;

const enum LETTER_TYPES {
	EMPTY,
	LETTER,
	NUM,
	DEL,
	OPERATION,
};

const enum TOKEN_STATUS {
	KEYWORD,
	DELIMITER,
	OPERATOR,
	NUMBER,
	ID,
	ERR
};

class letterDefiner {
private:
	//минимальные единицы (литеры)
	vector<char> delimiters;
	vector<char> operators;
	vector<char> numbers;
	vector<char> letters;

public:
	map <TOKEN_STATUS, vector<LETTER_TYPES>> lettersOfTokenMap;
	vector<string> initialKeywords();
	vector<char> initialDelimiters();
	vector<char> initialOperators();
	vector<char> initialNumbers();
	vector<char> initialLetters();
	map <TOKEN_STATUS, vector<LETTER_TYPES>> generateLettersOfTokenMap();
};