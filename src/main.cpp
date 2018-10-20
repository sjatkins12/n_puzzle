#include "puzzle.hpp"
#include "utils.hpp"
#include "AI.hpp"
#include <sstream>

void	print_map(std::string map, uint32_t size) {
	auto index = 0;
	auto tempNum = 0;
	auto strStream = std::istringstream(map);

	while (strStream >> tempNum) {
		std::cout << tempNum << " ";
		index++;
		if (index % size == 0) {
			std::cout << std::endl;
		}
	}
}

int	main(int argc, char const *argv[])
{
	std::unique_ptr<Puzzle> start;
	std::unique_ptr<Puzzle> end;
	std::unique_ptr<std::stack<std::string> > move_stk;

	if (argc != 3) {
		std::cout << "Usage: ./npuzzle start_puzzle end_puzzle" << std::endl;
		return (EXIT_FAILURE);
	}

	start = parser(argv[1]);
	end = parser(argv[2]);
	auto size = start->getSize();

	AI solver(std::move(start), std::move(end));

	if (solver.isSolvable()) {
		move_stk = solver.solve();

	
		std::cout << "START" << std::endl << "-----" << std::endl;
		while (!move_stk->empty()) {
			auto top = move_stk->top();
			move_stk->pop();
			print_map(top, size);
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "Not Solvable Sorry!" << std::endl;
	}
	return 0;
}
