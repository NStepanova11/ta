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
	readFile();
	getNumberLexemType("9");
	//generateTokensTable();
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
			lexemList.push_back(pair<string, string>(word, "number"));
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
	string type;
	if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
		type = tokenName.at(TOKEN_STATUS::KEYWORD); // "keyword";
	}
	else if (isalpha(word[0])) {
		type = tokenName.at(TOKEN_STATUS::ID); //"id";
	}
	else {
		type = "err";
	}
	return type;
}

string Analisator::getNumberLexemType(string word) {
	regex binPattern("^(0b)([0-1]+)$");
	regex octPattern("^(0o)([0-7]+)$");
	regex hexPattern("^(0x)([0-9a-fA-f]+)$");
	regex decPattern("^(0|([1-9])([0-9]*))$");
	cmatch result;
		cout << "--------------" << endl;

	if (regex_match(word.c_str(), result, decPattern))
	{
		for (size_t i = 0; i < result.size(); i++)
		{
			cout << result[i] << endl;
		}
	
	}
	else cout << "false" << endl;
	return "try";
}


void Analisator::generateTokensTable() {
	ofstream fout("output.txt");
	for (auto token : lexemList) {
		fout <<"token: "<< token.first << " value: " << token.second << endl;
	}
	fout.close();
}