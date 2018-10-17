#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "utils.hpp"
#include "puzzel.hpp"
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
	// std::cout << line + " Counting Words... " << std::flush;
	int words = CountWords(line);
	// std::cout << words << std::endl;

	if (words != dim)
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
		// std::cout << line << std::endl << std::flush;
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

std::unique_ptr<Puzzel> 	parser(const char *file) {
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
	return (std::make_unique<Puzzel>(combined, dim));
}

// int main(int argc, char ** argv) {

// 	if (argc != 2)
// 	{
// 		std::cout << "Usage: ./parser Puzzle File" << std::endl;
// 		exit(0);
// 	}
// 	std::string	from_p = parser(argv[1]);
// 	printf("Num Words: %d\nfrom p: %s\n",CountWords(from_p), from_p.c_str());

// 	Puzzel p = Puzzel(from_p, 1, 0);
// 	p.print_board();
// 	std::cout << "_________________________" << std::endl;
// 	std::cout << std::endl;

// 	AI ai = AI(from_p);
// 	std::stack<Puzzel> stk = ai.solve();
// 	std::cout << "Printing moves" << std::endl;
// 	while (!stk.empty()) {
// 		p = stk.top();
// 		stk.pop();
// 		p.print_board();
// 		std::cout << "_________________________" << std::endl;	
// 	}
// 	exit(0);
// 	std::vector<Puzzel> c;
// 	c = p.generate_children();
// 	std::priority_queue<Puzzel, std::vector<Puzzel>> q;
// 	for (int i = 0; i < c.size(); i++) {
// 		c[i].print_board();
// 		std::cout << "FSCORE: " << c[i].get_f_score() << std::endl;
// 		q.push(c[i]);
// 		std::cout << std::endl;
// 	}
// 	p = q.top();
// 	p.print_board();
// }