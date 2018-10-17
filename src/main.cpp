#include "puzzel.hpp"
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
	std::unique_ptr<Puzzel> start;
	std::unique_ptr<Puzzel> end;
	std::unique_ptr<std::stack<std::string> > move_stk;

	if (argc != 3) {
		std::cout << "Usage: ./npuzzle start_map end_map" << std::endl;
		return (EXIT_FAILURE);
	}

	start = parser(argv[1]);
	end = parser(argv[2]);

	auto size = start->getSize();
	AI solver(std::move(start), std::move(end));

	if (solver.isSolvable()) {
		std::cout << "IS SOLVABLE!" << std::endl;
		move_stk = solver.solve();
		std::cout << "START" << std::endl << "-----" << std::endl;
		while (!move_stk->empty()) {
			auto top = move_stk->top();
			move_stk->pop();
			print_map(top, size);

			std::cout << std::endl;
		}
	}


	return 0;
}