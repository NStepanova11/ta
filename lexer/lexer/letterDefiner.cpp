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

vector <char>letterDefiner::initialBrackets(){
	vector<char> b;
	b.push_back('{');
	b.push_back('}');
	b.push_back('(');
	b.push_back(')');
	b.push_back('[');
	b.push_back(']');
	return b;
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

//[A-Z, a-z,0-9, _ ]
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
	k.push_back("then");
	k.push_back("else");
	k.push_back("println");
	k.push_back("while");
	return k;
}

map <TOKEN_STATUS, string> letterDefiner::defineTokenNames() {
	map <TOKEN_STATUS, string> tokenName = {
		{ TOKEN_STATUS::ERR, "ERR"},
		{ TOKEN_STATUS::NUM_2, "NUM_2" },
		{ TOKEN_STATUS::NUM_8, "NUM_8" },
		{ TOKEN_STATUS::NUM_10, "NUM_10" },
		{ TOKEN_STATUS::NUM_16, "NUM_16" },
		{ TOKEN_STATUS::NUM_F, "FLOAT"},
		{ TOKEN_STATUS::E, "EXP" },
		{ TOKEN_STATUS::ID, "ID" },
		{ TOKEN_STATUS::KEYWORD, "KEYWORD" },
		{ TOKEN_STATUS::DELIMITER, "DELIMITER" },
		{ TOKEN_STATUS::OPERATOR, "OPERATOR" },
		{ TOKEN_STATUS::BRACKET, "BRACKET" },
		{ TOKEN_STATUS::SINGLE_COMMENT, "SINGLE_COMMENT" },
		{ TOKEN_STATUS::MULTI_COMMENT, "MULTI_COMMENT" }
	};
	return tokenName;
}
