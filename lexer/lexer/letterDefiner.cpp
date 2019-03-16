#include "stdafx.h"
#include "letterDefiner.h"

vector<char> letterDefiner::initialDelimiters() {
	vector<char> d;
	d.push_back(' ');
	d.push_back(';');
	d.push_back(',');
	return d;
}

vector<char> letterDefiner::initialOperators() {
	vector<char> o;
	o.push_back('+');
	o.push_back('-');
	o.push_back('*');
	o.push_back('/');
	o.push_back('%');
	o.push_back('=');
	o.push_back('+=');
	o.push_back('-=');
	o.push_back('*=');
	o.push_back('/=');
	o.push_back('%=');
	o.push_back('==');
	o.push_back('++');
	o.push_back('--');
	return o;
}

vector <char> letterDefiner::initialNumbers() {
	vector<char> n;
	char num = '0';
	while (num<='9')
	{
		n.push_back(num);
		num++;
	}
	n.push_back('.');
	return n;
}

vector <char> letterDefiner::initialLetters() {
	vector<char> l;
	char letter = 'a';
	while (letter<='z')
	{
		l.push_back(letter);
		letter++;
	}

	letter = 'A';
	while (letter<='Z')
	{
		l.push_back(letter);
		letter++;
	}

	letter = '0';	
	while (letter <= '9')
	{
		l.push_back(letter);
		letter++;
	}

	l.push_back('_');
	return l;
}

vector<string> letterDefiner::initialKeywords() {
	vector<string> k;
	k.push_back("for");
	k.push_back("break");
	k.push_back("if");
	k.push_back("else");
	k.push_back("println");
	k.push_back("while");
	return k;
}

map <TOKEN_STATUS, vector<LETTER_TYPES>> letterDefiner::generateLettersOfTokenMap(){
	lettersOfTokenMap = {
		{ TOKEN_STATUS::KEYWORD, {LETTER_TYPES::LETTER}},
		{ TOKEN_STATUS::NUMBER,{ LETTER_TYPES::NUM }},
		{ TOKEN_STATUS::DELIMITER, {LETTER_TYPES::DEL}},
		{ TOKEN_STATUS::OPERATOR, {LETTER_TYPES::OPERATION}},
		{ TOKEN_STATUS::ID, {LETTER_TYPES::LETTER, LETTER_TYPES::NUM}}
	};
	return lettersOfTokenMap;
}