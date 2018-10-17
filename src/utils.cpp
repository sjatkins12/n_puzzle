#include "utils.hpp"
#include <iostream>

int CountWords(std::string strString)
{
	auto nSpaces = 0;
	auto i = 0;

	// Skip over spaces at the beginning of the word
	while(isspace(strString.at(i)))
		i++;
	for(; i < strString.length(); i++)
	{
		if(isspace(strString.at(i)))
		{
			nSpaces++;
			// Skip over duplicate spaces & if a NULL character is found, we're at the end of the string
			while(isspace(strString.at(i)))
			{
				i++;
				if(i == strString.length())
					return (nSpaces);
			}
		}
	}
	// The number of words = the number of spaces + 1
	return (nSpaces + 1);
}
