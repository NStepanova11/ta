#include "stdafx.h"
#include "Rules.h"

void Rules::ReadRulesFromFile()
{
	ifstream fin("rules.txt");
	string rule;

	while (getline(fin,rule))
	{
		m_rules.push_back(rule);
	}
}

void Rules::GetRulesAlternatives()
{
	for (string rule : m_rules)
	{
		stringstream ss(rule);
		string token;

		int i = 0;
		string leftSide;
		vector<string> rightSide = {};
		vector<vector<string>> allRightSides = {};

		while (ss >> token)
		{
			if (i == 0)
			{
				leftSide = token;
				m_alternatives.insert(pair<string, vector<vector<string>>>(leftSide, {}));
			}
			else
			{
				if (token != "::=" && token != "|")
				{
					rightSide.push_back(token);
				}
				else if (token == "|")
				{
					allRightSides.push_back(rightSide);
					rightSide.clear();
				}
			}
			i++;
		}
		allRightSides.push_back(rightSide);
		m_alternatives.at(leftSide) = allRightSides;
	}
}

void Rules::ShowAllAlternativesMap()
{
	for (auto rule : m_alternatives)
	{
		cout << rule.first << " -> ";
		for (auto rightProds : rule.second)
		{
			for (size_t i = 0; i < rightProds.size(); i++)
			{
				cout<< rightProds[i]<<" ";
			}
			cout << " | ";
		}
		cout << endl;
	}
	cout << "----------------" << endl;
}

void Rules::FindFactorization()
{
	//находит и заменяет одинаковые правила
	//следующий шаг - удалить дубликаты правил в правой части
	unordered_map<string, vector<vector<string>>> newRules;
	for (auto &production : m_alternatives)
	{
		string leftSide = production.first;
		string newNoTerminal = "";

		vector<vector<string>> rightSideAlternatives = production.second;
		for (size_t i = 0; i < rightSideAlternatives.size()-1; i++)
		{
			int j = i + 1;
			bool haveFactor = false;
			vector<vector<string>> factorRules = {};

			while (j<rightSideAlternatives.size())
			{
				if (rightSideAlternatives[i][0] == rightSideAlternatives[j][0])
				{
					vector<string> newRule = {};
					newRule.push_back(rightSideAlternatives[j][1]);
					factorRules.push_back(newRule);
					newNoTerminal = leftSide + to_string(i + 1);
					rightSideAlternatives[j][1] = newNoTerminal;
					haveFactor = true;
				}
				j++;
			}
			if (haveFactor)
			{
				vector<string> newRule = {};
				newRule.push_back(rightSideAlternatives[i][1]);
				factorRules.push_back(newRule);
				rightSideAlternatives[i][1] = newNoTerminal;
				newRules.insert(pair<string, vector<vector<string>>>(newNoTerminal, factorRules));
			}
		}
		m_alternatives.at(leftSide) = rightSideAlternatives;
	}

	for (auto rule : newRules)
		m_alternatives.insert(rule);
}


/*
void Rules::FindFactorization()
{
	for (auto rule : m_alternatives)
	{
		int ruleFactorCounter = 1;
		vector<vector<string>> factorizationParts = {};
		bool haveFactor = false;
		for (int i = 0; i < rule.second.size()-1; i++)
		{
			factorizationParts.clear();
			vector<string> factorRule = {}; //новый массив для правой продукции (только один терминал)
			for (int j = i + 1; j < rule.second.size(); j++)
			{
				cout << "i=" << i << " j=" << j << endl;
				cout << rule.second[i][0] << rule.second[i][1] << "==" << rule.second[j][0] << rule.second[j][1]<<endl;
				if (rule.second[i][0] == rule.second[j][0])
				{
					factorRule.clear();
					haveFactor = true;
					factorRule.push_back(rule.second[j][1]);
					factorizationParts.push_back(factorRule); //помещаем в список альтернатив факторизации
					rule.second[j][1] = rule.first + to_string(ruleFactorCounter); //замена на другой нетерминал
				}				
			}
			if (haveFactor)
			{
				ruleFactorCounter++;
				factorizationParts.push_back(factorRule);
				cout << rule.first + to_string(ruleFactorCounter) << " --> ";
				for (size_t i = 0; i < factorizationParts.size(); i++)
				{
					for (auto item : factorizationParts[i])
					{
						cout << item << "| ";
					}
				}
				cout << endl;
				//m_alternatives.insert(pair<string, vector<vector<string>>>(rule.first + to_string(ruleFactorCounter), factorizationParts));
			}
		}
		
	}
}
*/

void Rules::AddNewRule()
{
}
