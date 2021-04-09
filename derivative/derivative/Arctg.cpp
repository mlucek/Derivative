#include "Arctg.h"
#include "Reader.h"


std::string Arctg::counter(std::string exp)
{
	std::string str2;
	std::string str3;
	std::string str = exp;
	if (str[0] == '(' && str[str.length() - 1] == ')')
	{
		for (int i = 1; i < (str.length() - 1); i++)
		{
			str2 += str[i];
		}
		Reader q;
		q.decoder(str2);
		str3 = "*(" + q.fexpression + ')';
	}
	else
	{
		str2 = str;
		Reader q;
		q.decoder(str2);
		str3 = "*(" + q.fexpression + ')';
	}
	return  "((1/(" + str + "^2)+1))" + str3;
}