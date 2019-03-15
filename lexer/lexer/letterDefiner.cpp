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

/*
map <LETTER_TYPES, vector<char>> letterDefiner::generateLettersMap(){
	lettersMap = {
		{ LETTER_TYPES::LETTER, initialLetters()},
		{ LETTER_TYPES::NUMBER, initialNumbers()},
		{ LETTER_TYPES::CHAR_DELIMITER, initialDelimiters()},
		{LETTER_TYPES::CHAR_OPERATOR, initialOperators()}
	};
	return lettersMap;
}*/