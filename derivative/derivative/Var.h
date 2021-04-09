#pragma once
#include "Reader.h"
#include<string>
class Var :
	public Reader
{
	
public:
	friend class Analizer;
	std::string counter(std::string exp);


};

