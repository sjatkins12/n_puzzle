#ifndef PARSER_H

# define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <math.h>
#include "puzzle.hpp"
#include <memory>

std::unique_ptr<Puzzle> 	parser(const char *file);

#endif
