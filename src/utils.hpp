#ifndef UTILS_H

# define UTILS_H

#include <string>
#include <math.h>
#include "puzzel.hpp"
#include <memory>

int 			CountWords(std::string strString);

std::string		mapToString(uint32_t **map, int dims);

std::unique_ptr<Puzzel> 	parser(const char *file);

#endif