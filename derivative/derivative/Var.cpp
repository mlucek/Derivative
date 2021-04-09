#include "Var.h"

std::string Var::counter(std::string exp)
{

	std::string result;
	if (exp == "x")
	{
		result = "1";
	}
	else
	{
		std::string str1 = "";
		std::string str2 = "";
		std::string str3 = "";

		int counter = 0;
		int brack = 0;
		for (int i = 0; i < exp.length(); i++) //* nie mo¿e byæ 1 znakiem
		{
			if (exp[i] != '^' || (exp[i] == '^' && brack !=0) )
			{
				str2 = str2 + exp[i];
			}
			else if (exp[i] == '^' && counter==0 && brack ==0)
			{
				counter += 1;
				str1 = str2;
				str2 = "";
			}
			if (exp[i] == '(')
			{
				brack += 1;
			}
			if (exp[i] == ')')
			{
				brack -= 1;
			}
		}
		int firstx = 0, secoundx = 0;
		for (int i = 0; i < str1.length(); i++)
		{
			if (str1[i] == 'x')
			{
				firstx += 1;
			}
		}
		for (int i = 0; i < str2.length(); i++)
		{
			if (str2[i] == 'x')
			{
				secoundx += 1;
			}
		}
		if (firstx > 0 && secoundx == 0)
		{
			Reader q;
			q.decoder(str1);
			str3 = "*(" + q.fexpression + ')';
			result = "(" + str2 + "*" + str1 + "^(" + str2 + "-1))" + str3;
		}
		else if(firstx == 0 && secoundx > 0)
		{
			if ((exp[0] == '(' && exp[1] == 'e' && exp[2] == ')' && exp[3] == '^') || (exp[0] == 'e' && exp[1]))
			{
				Reader q;
				q.decoder(str2);
				str3 = "*(" + q.fexpression + ')';
				result ="(" + exp + ")" + str3;
			}
			else
			{
				Reader q;
				q.decoder(str2);
				str3 = "*(" + q.fexpression + ')';
				result = "(" + exp + ")*ln(" + str1 + ")" + str3;
			}
		}
		else if (firstx > 0 && secoundx > 0)
		{
			result = "nie obslugiwany wyjatek x^x";
		}
	}

	return result;
}
