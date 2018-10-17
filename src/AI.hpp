#ifndef AI_HPP

# define AI_HPP

#include <string>
#include <unordered_map>
#include "puzzel.hpp"
#include <queue>
#include <stack>
#include <iostream>

struct PuzzleState {
	Puzzel	p;
	std::shared_ptr<PuzzleState> parent;
	std::vector<PuzzleState> children;
	int	f;
	int	g;
	int	move;
};

class AI {
	std::unique_ptr<Puzzel> start;
	std::unique_ptr<Puzzel> finish;

	void					generate_children(PuzzleState &) const;
	int						heuristic(const Puzzel & current, const Puzzel & goal) const;
	std::unordered_map<int32_t, std::pair<int32_t, int32_t> >	finish_map;
	std::unique_ptr<std::stack<std::string> >					retrace(PuzzleState p) const;
	int			getInvCount( void ) const ;

	AI();
	AI & operator=(const AI& src);
	AI(const AI& src);

public:
	AI(std::unique_ptr<Puzzel> && start, std::unique_ptr<Puzzel> && finish);
	~AI() {};
	std::unique_ptr<std::stack<std::string> >	solve() const ;
	bool				isSolvable( void ) const;
	
	const int upMove = 0;
	const int downMove = 1;
	const int rightMove = 2;
	const int leftMove = 3;	
};

#endif
