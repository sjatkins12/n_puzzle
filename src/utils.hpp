#ifndef UTILS_H

# define UTILS_H

#include <string>
#include <math.h>
#include "puzzle.hpp"
#include <memory>

int 			CountWords(std::string strString);


std::unique_ptr<Puzzle> 	parser(const char *file);

#endif
