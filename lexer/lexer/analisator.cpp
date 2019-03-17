#include "stdafx.h"
#include "Analisator.h"

Analisator::Analisator()
	:keywords(letterDefiner.initialKeywords())
	,letters(letterDefiner.initialLetters())
	,numbers(letterDefiner.initialNumbers())
	,operators(letterDefiner.initialOperators())
	,delimiters(letterDefiner.initialDelimiters())
	,tokenName(letterDefiner.defineTokenNames())
{
}

void Analisator::readFile() {
	ifstream fin("input.txt");
	string fileLine;
	while (getline(fin, fileLine))
	{
		checkLexemTypes(fileLine);
	}
	fin.close();	
}

void Analisator::testCase() {
	//cout<< getNumberLexemType("11line");
	readFile();
	generateTokensTable();
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
			} while (currType!=LETTER_TYPES::DEL && currType != LETTER_TYPES::OPERATION && i < fileLine.size());
			//while ((currType == LETTER_TYPES::LETTER || currType == LETTER_TYPES::NUM ) && i < fileLine.size());
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
			} while (currType != LETTER_TYPES::DEL && currType != LETTER_TYPES::OPERATION && i < fileLine.size());
			//while ((currType == LETTER_TYPES::NUM) && i < fileLine.size());
			lexemList.push_back(pair<string, string>(word, getNumberLexemType(word)));
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

			lexemList.push_back(pair<string, string>(word, tokenName.at(TOKEN_STATUS::OPERATOR))); //"operation"));
			cout << "\'" << word << "\'" << endl;
			word.clear();
		}
		else if (currType == LETTER_TYPES::DEL) {
			if (chr != ' ')
			{
				word = chr;
				lexemList.push_back(pair<string, string>(word, tokenName.at(TOKEN_STATUS::DELIMITER))); //"delimiter"));
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
	regex idPattern("^([a-zA-z])([\\w]*)$");
	cmatch result;

	string type;
	if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
		type = tokenName.at(TOKEN_STATUS::KEYWORD); // "keyword";
	}
	else if (regex_match(word.c_str(), idPattern)) {
		type = tokenName.at(TOKEN_STATUS::ID); //"id";
	}
	else {
		type = TOKEN_STATUS::ERR;
	}
	return type;
}

string Analisator::getNumberLexemType(string word) {
	regex binPattern("^(0b)([0-1]+)$");
	regex octPattern("^(0o)([0-7]+)$");
	regex hexPattern("^(0x)([0-9a-fA-f]+)$");
	regex decPattern("^(0|([1-9])([0-9]*))$");
	regex floatPattern("^([0-9]+)(.)([1-9]+)");
	cmatch result;

	string type;
	if (regex_match(word.c_str(), result, binPattern)) {
		type = tokenName.at(TOKEN_STATUS::NUM_2);
	}
	else if (regex_match(word.c_str(), octPattern)) {
		type = tokenName.at(TOKEN_STATUS::NUM_8);
	}
	else if (regex_match(word.c_str(), decPattern)) {
		type = tokenName.at(TOKEN_STATUS::NUM_10);
	}
	else if (regex_match(word.c_str(), hexPattern)) {
		type = tokenName.at(TOKEN_STATUS::NUM_16);
	}
	else if (regex_match(word.c_str(), floatPattern)) {
		type = tokenName.at(TOKEN_STATUS::NUM_F);
	}
	else {
		type = tokenName.at(TOKEN_STATUS::ERR);
	}
	return type;
}


void Analisator::generateTokensTable() {
	ofstream fout("output.txt");
	for (auto token : lexemList) {
		fout <<"token: "<< token.first << " value: " << token.second << endl;
	}
	fout.close();
}