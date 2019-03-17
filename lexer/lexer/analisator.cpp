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

void Analisator::testCase() {
	readFile();
	generateTokensTable();
	//cout << getDivisionLexemType("/*multi comment*/") << endl;
}


void Analisator::readFile() {
	ifstream fin("input.txt");
	string fileLine;
	char ch;
	while ((ch = fin.get()) != EOF) {
		fileLine += ch;
	}
	//f << fileLine << endl;
	checkLexemTypes(fileLine);

	/*
	while (getline(fin, fileLine))
	{
		checkLexemTypes(fileLine);
	}*/
	fin.close();
}

void Analisator::checkLexemTypes(string &fileLine) {
	LETTER_TYPES currType = LETTER_TYPES::EMPTY;
	string word;
	pair <string, string> lexemProps;
	int i = 0;

	while (i < fileLine.size())
	{
		char chr = fileLine[i];
		currType = getLetterType(chr);

			if (currType == LETTER_TYPES::LETTER) {
				do
				{
					word += chr;
					i++;
					chr = fileLine[i];
					currType = getLetterType(chr);
				} while ((currType == LETTER_TYPES::LETTER || currType == LETTER_TYPES::NUM) && i < fileLine.size());
				lexemList.push_back(pair<string, string>(word, getTextLexemType(word)));
			}
			else if (currType == LETTER_TYPES::NUM) {
				do
				{
					word += chr;
					i++;
					chr = fileLine[i];
					currType = getLetterType(chr);
				} while ((currType == LETTER_TYPES::LETTER || currType == LETTER_TYPES::NUM) && i < fileLine.size());
				lexemList.push_back(pair<string, string>(word, getNumberLexemType(word)));
			}
			else if (currType == LETTER_TYPES::OPERATION) {
				word = chr;
				i++;

				if (chr == '\/' && fileLine[i] == chr) {
					bool eol = false;
					do
					{
						if (fileLine[i] != '\n')
							word += fileLine[i];
						else
							eol = true;
						i++;

					} while (!eol && i<fileLine.size());
				}
				else if (chr == '\/' && fileLine[i] == '*')
				{
					do
					{
						if (fileLine[i] == '\n')
							word += ' ';
						else
							word += fileLine[i];
						i++;
					} while (i < fileLine.size() && !(word[word.size() - 1] == '\/' && word[word.size() - 2] == '*'));
				}
				lexemList.push_back(pair<string, string>(word, getDivisionLexemType(word)));
			}
			else if (currType == LETTER_TYPES::DEL) {
				if (chr != ' ')
				{
					word = chr;
					lexemList.push_back(pair<string, string>(word, tokenName.at(TOKEN_STATUS::DELIMITER)));
				}
				i++;
			}
			else {
				i++;
			}
			word.clear();
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
	regex floatPattern("^([0-9]+)(.)([1-9]+)$");
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

string Analisator::getDivisionLexemType(string word) {
	regex singleComPattern("(\/\/)(.+?)");
	regex multiComPattern("^(\/.*)([\\w]*)(.*\/)$");
	cmatch result;

	string type;
	if (regex_match(word.c_str(), result, singleComPattern)) {
		type = tokenName.at(TOKEN_STATUS::SINGLE_COMMENT);
	}
	else if (regex_match(word.c_str(), multiComPattern)) {
		type = tokenName.at(TOKEN_STATUS::MULTI_COMMENT);
	}
	else if (word == "\/") {
		type = tokenName.at(TOKEN_STATUS::DELIMITER);
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