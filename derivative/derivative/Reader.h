#pragma once
#include<string>
#include<iostream>
#include <queue>


class Reader
{
public:
	friend class Analizer;
	std::string fexpression = "";
	std::string exp;
	void writeexp();
	void decoder(std::string expression);
	


};

