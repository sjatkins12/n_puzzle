#ifndef AI_HPP

# define AI_HPP

#include <string>
#include <unordered_map>
#include "puzzle.hpp"
#include <queue>
#include <stack>
#include <iostream>

struct PuzzleState {
	Puzzle	p;
	std::shared_ptr<PuzzleState> parent;
	std::vector<PuzzleState> children;
	int	f;
	int	g;
	int	move;
};

class AI {
	std::unique_ptr<Puzzle> _start;
	std::unique_ptr<Puzzle> _finish;
	std::unordered_map<int32_t, std::pair<int32_t, int32_t> >	_finish_map;

	void					generate_children(PuzzleState &) const;
	int						heuristic(const Puzzle & current, const Puzzle & goal) const;
	int						getInvCount( void ) const ;
	std::unique_ptr<std::stack<std::string> >	retrace(PuzzleState p) const;

	AI();
	AI & operator=(const AI& src);
	AI(const AI& src);

public:
	AI(std::unique_ptr<Puzzle> && start, std::unique_ptr<Puzzle> && finish);
	~AI() {};
	
	std::unique_ptr<std::stack<std::string> >	solve() const ;
	bool										isSolvable( void ) const;
	
	const int upMove = 0;
	const int downMove = 1;
	const int rightMove = 2;
	const int leftMove = 3;	
};

#endif
