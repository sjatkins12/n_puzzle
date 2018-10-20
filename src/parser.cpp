#include "parser.hpp"
#include "puzzle.hpp"
#include "AI.hpp"

int		check_line(std::string line) {
	for (auto &c : line) {
		if (!isdigit(c) && !isblank(c))
		{
			std::cout << "Bad Puzzle" << std::endl;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int		check_digits(std::string line, int dim) {
	auto strStream = std::istringstream(line);
	int	indexValue;
	auto	count = 0;

	while (strStream >> indexValue) {
		count++;
	}

	if (count != dim)
	{
		std::cout << "Bad Puzzle" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

std::string		strip_spaces(std::string str) {
	auto	i = 0;
	std::string	ret;

	ret = "";

	while (isspace(str.at(i)))
		i++;
	for (; i < str.length(); i++) {
		if (isspace(str.at(i))) {
			while(i + 1 < str.length() && isspace(str.at(i + 1)))
				i++;
			if (i + 1 < str.length())
				ret += ' ';
		}
		else
			ret += str.at(i);
	}
	return (ret);	
}

int			get_dimmension(std::ifstream & f_stream) {
	std::string		line;
	int				dim;

	dim = 0;
	while (!dim && std::getline(f_stream, line))
	{
		line = line.substr(0, line.find('#'));
		if (check_line(line) == EXIT_FAILURE) {
			std::cout << "Error: cannot get dimmension!" << std::endl;
			f_stream.close();
			exit(0);
		}
		if (line.length())
			dim = std::stoi(line);
	}
	return (dim);
}

std::unique_ptr<Puzzle> 	parser(const char *file) {
	std::ifstream	f_stream(file);
	std::string		line, combined;
	int				dim;

	if (f_stream) {
		combined = "";
		dim = 0;
		dim = get_dimmension(f_stream);
		while (std::getline(f_stream, line)) {
			line = line.substr(0, line.find('#'));
			if (check_line(line) == EXIT_FAILURE ||
				check_digits(line, dim) == EXIT_FAILURE) {
					f_stream.close();
					exit(0);
				}
			combined += " " + line;
		}
		f_stream.close();
		combined = strip_spaces(combined);
	}
	else
		std::cout << "Bad File" << std::endl;
	return (std::make_unique<Puzzle>(combined, dim));
}
