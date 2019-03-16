#include "stdafx.h"
#include "Analisator.h"

Analisator::Analisator()
	:keywords(letterDefiner.initialKeywords())
	,letters(letterDefiner.initialLetters())
	,numbers(letterDefiner.initialNumbers())
	,operators(letterDefiner.initialOperators())
	,delimiters(letterDefiner.initialDelimiters())
	, lettersOfTokenMap(letterDefiner.generateLettersOfTokenMap())
{
}
/*
map<TOKEN_TYPES, string> Analisator::initialTokenNames() {
	map<TOKEN_TYPES, string> tNames = {
		{ TOKEN_TYPES::KEYWORD, "KEYWORD" },
		{ TOKEN_TYPES::DELIMITER, "DELIMITER" },
		{ TOKEN_TYPES::OPERATOR, "OPERATOR" }
	};
	return tNames;
}
*/
void Analisator::readFile() {
	ifstream fin("input.txt");
	string fileLine;
	while (getline(fin, fileLine))
	{
		checkLexemTypes(fileLine);
	}
	fin.close();
}

/*
void Analisator::parseLexems(string &fileLine) {
	string  lexem;
	char c;
	int i = 0;
	map<int, pair<LETTER_TYPES, string>> tokenTypesTable;
	while (i < fileLine.size())
	{
		stringstream ss;
		string letter;
		c = fileLine[i];
		LETTER_TYPES lt = getLetterType(c);
		ss << c;
		ss >> letter;
		int id = 1;
	
		if (lt == LETTER_TYPES::CHAR_DELIMITER){

			if (lexem.size() != 0) {
				lexemList.push_back(lexem);
				cout << "\'" << lexem << "\'" << endl;
			}
			lexemList.push_back(letter);
			cout << "\'" << letter << "\'" << endl;
			lexem.clear();
		}
		else {
			lexem+= letter;
		}
		i++;
	}

	if (lexem.size()!=0) {
		lexemList.push_back(lexem);
		cout << "\'" << lexem << "\'" << endl;
	}
}
*/

void Analisator::testCase() {
	readFile();
	generateTokensTable();
	/*
	for (auto el : lexemList) {
		cout << "\'"<<el << "\'" << endl;
	}*/
}

void Analisator::checkLexemTypes(string &fileLine) {
	LETTER_TYPES currType = LETTER_TYPES::EMPTY;

	string word;
	pair <string, string> lexemProps;
	int i = 0;

	while (i < fileLine.size())
	{
		stringstream ss;
		string ltr;
		char chr = fileLine[i];
		currType = getLetterType(chr);
		ss << chr;
		ss >> ltr;

		if (currType == LETTER_TYPES::LETTER) {
			do
			{
				word += chr;
				i++;
				chr = fileLine[i];
				currType = getLetterType(chr);
			} while ((currType == LETTER_TYPES::LETTER || currType == LETTER_TYPES::NUM ) && i < fileLine.size());
			//lexemProps.push_back(word);
			//lexemProps.push_back(getTextLexemType(word));
			lexemList.push_back(pair<string, string>(word, getTextLexemType(word)));
			cout << "\'" << word << "\'" << endl;
			word.clear();

		}
		else if (currType == LETTER_TYPES::NUM) {
			do
			{
				word += chr;
				i++;
				chr = fileLine[i];
				currType = getLetterType(chr);
			} while ((currType == LETTER_TYPES::NUM) && i < fileLine.size());
			//lexemProps.push_back(word);
			//lexemProps.push_back("num");
			lexemList.push_back(pair<string, string>(word, "num"));
			cout << "\'" << word << "\'" << endl;
			word.clear();
		}
		else if (currType == LETTER_TYPES::OPERATION) {
			do
			{
				word += chr;
				i++;
				chr = fileLine[i];
				currType = getLetterType(chr);
			} while ((currType == LETTER_TYPES::OPERATION) && i < fileLine.size());
			//lexemProps.push_back(word);
			//lexemProps.push_back("operator");
			lexemList.push_back(pair<string, string>(word, "operation"));
			cout << "\'" << word << "\'" << endl;
			word.clear();
		}
		else if (currType == LETTER_TYPES::DEL) {
			if (chr != ' ')
			{
				word = chr;
				lexemList.push_back(pair<string, string>(word, "delimiter"));
				word.clear();
			}
			i++;
		}
		else {
			i++;
		}
	}
}

LETTER_TYPES Analisator::getLetterType(char c) {
	LETTER_TYPES letterType;

	if (find(numbers.begin(), numbers.end(), c) != numbers.end()) {
		letterType = LETTER_TYPES::NUM;
	}
	else if (find(letters.begin(), letters.end(), c) != letters.end()) {
		letterType = LETTER_TYPES::LETTER;
	}
	else if (find(delimiters.begin(), delimiters.end(), c) != delimiters.end()) {
		letterType = LETTER_TYPES::DEL;
	}
	else if (find(operators.begin(), operators.end(), c) != operators.end()) {
		letterType = LETTER_TYPES::OPERATION;
	}
	else letterType = LETTER_TYPES::EMPTY;
	return letterType;
}

string Analisator::getTextLexemType(string word) {
	string type;
	if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
		type = "keyword";
	}
	else if (word[0] == '\"' && word[0] == word[word.size() - 1]) {
		type = "string";
	}
	else if (isalpha(word[0])) {
		type = "id";
	}
	else {
		type = "err";
	}
	return type;
}

void Analisator::generateTokensTable() {
	for (auto token : lexemList) {
		cout << token.first << "-" << token.second << endl;
	}
}