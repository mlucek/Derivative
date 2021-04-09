#include "Reader.h"
#include"Sin.h"
#include <iostream>


//std::string ffexpression = "12";
int main()
{
	Reader alfa;
	alfa.writeexp();
	alfa.decoder(alfa.exp);
	std::cout << "Wynik:" << std::endl;
	std::cout << alfa.fexpression;
}