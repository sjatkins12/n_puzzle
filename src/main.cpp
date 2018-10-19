#include "puzzle.hpp"
#include "utils.hpp"
#include "AI.hpp"

void	print_map(std::string map, uint32_t size) {
	auto index = 0;

	for (auto i = 0; i < size; i++) {
		for (auto cellCount = 0; cellCount < size; cellCount++) {
			while (map[index] == ' ')
				index++;
			std::cout << atoi(&(map[index])) << " ";
			while (map[index] != ' ' && map[index] != '\0')
				index++;
			while (map[index] == ' ')
				index++;
		}
		std::cout << std::endl;
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
	print_map(start->toString(), 3);
	std::cout << std::endl;

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
