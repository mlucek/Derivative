#pragma once
#include <string>
#include "Reader.h"

class Sin :
	public Reader
{
public:
	std::string counter(std::string exp);
};
