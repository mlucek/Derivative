#include "Ctg.h"
#include "Reader.h"

std::string Ctg::counter(std::string expression)
{
	std::string str2;
	std::string str3;
	std::string str = expression;
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
	return  "(-1/(sin" + str+ "^2))" + str3;
}