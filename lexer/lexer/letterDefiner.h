#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const enum LETTER_TYPES {
	LETTER,
	NUMBER,
	CHAR_DELIMITER,
	CHAR_OPERATOR
};

class letterDefiner {
private:
	//минимальные единицы (литеры)
	vector<char> delimiters;
	vector<char> operators;
	vector<char> numbers;
	vector<char> letters;

public:
	map <LETTER_TYPES, vector<char>> lettersMap;
	vector<string> initialKeywords();
	vector<char> initialDelimiters();
	vector<char> initialOperators();
	vector<char> initialNumbers();
	vector<char> initialLetters();
	//map <LETTER_TYPES, vector<char>> generateLettersMap();
};