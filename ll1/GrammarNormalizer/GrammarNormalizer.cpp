// GrammarNormalizer.cpp : Defines the entry point for the console application.

// 1 - ���������� �������
// 2 - ������� ������������
// 3 - ������� ����� ��������
// 4 - �������� ��������� �������

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

