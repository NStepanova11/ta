// GrammarNormalizer.cpp : Defines the entry point for the console application.

// 1 - Распарсить правило
// 2 - Удалить факторизацию
// 3 - Удалить левую рекурсию
// 4 - выделить начальные символы

#include "stdafx.h"
#include "Rules.h"


int main()
{
	Rules rules;
	rules.ReadRulesFromFile();
	rules.GetRulesAlternatives();
	rules.FindFactorization();
	rules.ShowAllAlternativesMap();
    return 0;
}

