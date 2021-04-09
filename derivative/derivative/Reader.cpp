#include "Reader.h"
#include"Sin.h"
#include"Var.h"
#include"Cos.h"
#include"Ln.h"
#include"Ctg.h"
#include"Tg.h"
#include"Arccos.h"
#include"Arcsin.h"
#include"Arcctg.h"
#include"Arctg.h"
#include <cctype>


void Reader::writeexp() 
{
	std::string expression;
	std::cout << "wprowadz pochdna do policzenia:" << std::endl;
	std::cin >> expression;
	Reader::exp = expression;
}

void Reader::decoder(std::string expression)
{
	std::string exp = expression;
	std::string singleexp = "";
	std::string charr = "";
	std::queue<std::string> singleexpression;
	std::queue<std::string> chars;
	int bracket = 0;
	std::string finishexp = "";
	

	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] == '(')
		{
			bracket = bracket + 1;
			singleexp += exp[i];
		}
		else if (exp[i] == ')')
		{
			bracket = bracket - 1;
			singleexp += exp[i];
		}
		else if ((exp[i] == '+' || exp[i] == '-') && (bracket == 0))
		{
			if (singleexpression.empty() && singleexp=="" )
			{
				charr = exp[i];
				chars.emplace(charr);
				charr = "";
			}
			else
			{
				charr = exp[i];
				chars.emplace(charr);
				charr = "";
				singleexpression.emplace(singleexp);
				singleexp = "";
			}
		}
		else
		{
			singleexp += exp[i];
		}
	}
	if (singleexp != "")
	{
		singleexpression.emplace(singleexp);
		singleexp = "";
	}
	do 
	{
		if (chars.size() == singleexpression.size())
		{
			fexpression = fexpression + chars.front();
			chars.pop();
		}
		fexpression += '(';
		std::string analizer = singleexpression.front();		//sprawdzanie czy istnieje element w kolejce 
		singleexpression.pop();			
		int mult = 0; //mnozenie
		int divi = 0; // dzielenie
		std::string str1 = "";
		std::string str2 = "";
		std::string str3 = "";
		for (int i = 0; i < analizer.length(); i++) //* nie mo¿e byæ 1 znakiem
		{
			if (analizer[i] != '*' && analizer[i]!='/')
			{
				str2 = str2 + analizer[i];
			}
			else if (analizer[i]=='*' && bracket == 0 && mult == 0 && divi ==0)
			{
				mult += 1;
				str1 = str2;
				str2 = "";
			}
			else if (analizer[i] == '/' && bracket == 0 && mult == 0 && divi == 0)
			{
				divi += 1;
				str3 = str2;
				str2 = "";
			}

			else if ((analizer[i] == '*'|| analizer[i] == '/') && (mult != 0 || divi !=0))   // && bracket == 0
			{
				str2 = str2 + analizer[i];
			}
			else if ((analizer[i] == '*' || analizer[i] == '/') && bracket != 0)
			{
				str2 = str2 + analizer[i];
			}
			if (analizer[i] == '(')
			{
				bracket += 1;
			}
			if (analizer[i] == ')')
			{
				bracket -= 1;
			}
		}
		if (analizer.length() == str2.length())
		{
			if (analizer[0] == '(' && analizer[analizer.length() - 1] == ')')			// ten warunek mo¿e generowaæ b³edy np w postaci takiej pochondej (x+1)^(x-2)
			{
				int brack = 1;
				int ttttrue = 0;				//zmienna do warunku sprawdzajacego czy to glowny nawias
				std::string newanalizer = "";
				for (int i = 1; i < analizer.length() - 1; i++)
				{
					newanalizer = newanalizer + analizer[i];
					if (analizer[i] == '(')
					{
						brack += 1;
					}
					else if (analizer[i] == ')')
					{
						brack -= 1;
					}
					if (brack == 0)
					{
						ttttrue += 1;
					}
				}
				if (ttttrue == 0)
				{
					analizer = newanalizer;
					Reader q1;
					q1.decoder(analizer);
					fexpression = fexpression + "(" + q1.fexpression + ")";
				}
				else
				{
					for (int i = 0; i < analizer.length(); i++)
					{
						if (analizer[i] == '^')           // warunek z nawiasami jest konieczny ?
						{
							Var q;
							std::string test = q.counter(analizer);
							fexpression = fexpression + test;
							analizer = "";				//potencjalnie niebezpieczne
						}
					}
				}
			}
			else if(analizer.size()>0)
			{
				int brack = 0;
				for (int i = 0; i < analizer.length(); i++)
				{
					if (analizer[i] == '(')
					{
						brack += 1;
					}
					else if (analizer[i] == ')')
					{
						brack -= 1;
					}

					else if (analizer[i] == '^' && brack ==0)           // warunek z nawiasami jest konieczny ?
					{
						Var q;
						std::string test = q.counter(analizer);
						fexpression = fexpression + test;
						analizer = "";				//potencjalnie niebezpieczne
					}
				}
				int digit=0;
				for (int i = 0; i < analizer.length(); i++)
				{
					if (isdigit(analizer[i]) || analizer[i]=='.')
					{
						digit += 1;
					}
				}
				if (analizer.length() == digit)
				{
					fexpression = fexpression + '0';
				}
				else if (analizer[0] == 's' && analizer[1] == 'i' && analizer[2] == 'n') 
				{
					std::string sin="";
					for (int i = 3; i < analizer.length(); i++)
					{
						sin += analizer[i];
					}
					Sin q;
					std::string test = q.counter(sin);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'c' && analizer[1] == 'o' && analizer[2] == 's') 
				{
					std::string cos="";
					for (int i = 3; i < analizer.length(); i++)
					{
						cos += analizer[i];
					}
					Cos q;
					std::string test = q.counter(cos);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'c' && analizer[1] == 't' && analizer[2] == 'g') 
				{
					std::string ctg="";
					for (int i = 3; i < analizer.length(); i++)
					{
						ctg += analizer[i];
					}
					Ctg q;
					std::string test = q.counter(ctg);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 't' && analizer[1] == 'g' ) 
				{
					std::string tg="";
					for (int i = 2; i < analizer.length(); i++)
					{
						tg += analizer[i];
					}
					Tg q;
					std::string test = q.counter(tg);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'l' && analizer[1] == 'n')
				{
					std::string ln="";
					for (int i = 2; i < analizer.length(); i++)
					{
						ln += analizer[i];
					}
					Ln q;
					std::string test = q.counter(ln);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'a' && analizer[1] == 'r' && analizer[2] == 'c' && analizer[3] == 's' && analizer[4] == 'i' && analizer[5] == 'n')
				{
					std::string arcsin="";
					for (int i = 6; i < analizer.length(); i++)
					{
						arcsin += analizer[i];
					}
					Arcsin q;
					std::string test = q.counter(arcsin);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'a' && analizer[1] == 'r' && analizer[2] == 'c' && analizer[3] == 'c' && analizer[4] == 'o' && analizer[5] == 's')
				{
					std::string arccos="";
					for (int i = 6; i < analizer.length(); i++)
					{
						arccos += analizer[i];
					}
					Arccos q;
					std::string test = q.counter(arccos);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'a' && analizer[1] == 'r' && analizer[2] == 'c' && analizer[3] == 'c' && analizer[4] == 't' && analizer[5] == 'g')
				{
					std::string arcctg="";
					for (int i = 6; i < analizer.length(); i++)
					{
						arcctg += analizer[i];
					}
					Arcctg q;
					std::string test = q.counter(arcctg);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'a' && analizer[1] == 'r' && analizer[2] == 'c' && analizer[3] == 't' && analizer[4] == 'g' )
				{
					std::string arctg="";
					for (int i = 5; i < analizer.length(); i++)
					{
						arctg += analizer[i];
					}
					Arctg q;
					std::string test = q.counter(arctg);
					fexpression = fexpression + test;
				}
				else if (analizer[0] == 'x')
				{
					Var q;
					std::string test = q.counter("x");
					fexpression = fexpression + test;
				}
			}	
		}
		else
		{
			if (str1.size() > 0)
			{
				Reader q1, q2;
				q1.decoder(str1);
				q2.decoder(str2);
				fexpression = fexpression + "((" + q1.fexpression + ")*(" + str2 + ")+(" + str1 + ")*(" + q2.fexpression + "))";
			}
			else if (str3.size() > 0)
			{
				Reader q2, q3;
				q2.decoder(str2);
				q3.decoder(str3);
				fexpression = fexpression + "(((" + q2.fexpression + ")*(" + str3 + ")-(" + str2 + ")*(" + q3.fexpression + "))/(" + str3 + ")^2)";
			}
		}
		fexpression += ')';
		if (chars.size() != 0)
		{
			std::string charr;
			charr = chars.front();
			fexpression = fexpression + charr;
			chars.pop();
		}
	} while (singleexpression.size() > 0);	
}