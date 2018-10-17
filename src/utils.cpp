#include "utils.hpp"
#include <iostream>

int CountWords(std::string strString)
{
	int nSpaces = 0;
	unsigned int i = 0;

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
	return nSpaces + 1;
}

std::string		mapToString(uint32_t **map, int dims) {
	std::string	ret;

	for (int i = 0; i < pow(dims, 2); i++) {
		ret.append(std::to_string(map[i / dims][i % dims]));
		ret.append(1, ' ');
	}
	return (ret.substr(0, ret.length() - 1));
}