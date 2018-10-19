#include "AI.hpp"

AI::AI(std::unique_ptr<Puzzle> && start, std::unique_ptr<Puzzle> && finish) {
	this->_start = std::move(start);
	this->_finish = std::move(finish);

	auto dim = this->_finish->getSize();
	for (auto i = 0; i < dim; i++) {
		for (auto j = 0; j < dim; j++) {
			_finish_map.insert(std::make_pair<int32_t, std::pair<int32_t, int32_t>>
			(this->_finish->getCell(i, j), std::make_pair<uint, uint>(i , j)));
		}
	}
}

std::unique_ptr<std::stack<std::string> >	AI::solve( void ) const {
	std::priority_queue<PuzzleState> open;
	std::unordered_map<std::string, bool> visited;
	PuzzleState	current;

	open.push(
		PuzzleState {*(this->_start), nullptr, std::vector<PuzzleState>(), 0, 0, -1}
	);

	while (!open.empty()) {
		current = open.top();
		visited.insert(std::make_pair<std::string, bool>(current.p.toString(), true));

		if (current.p == *_finish)
			break ;

		open.pop();

		generate_children(current);
		for (auto & child : current.children) {
			if (visited.count(child.p.toString()) == 0) {
				child.f = child.g + heuristic(child.p, *(this->_finish));
				open.push(child);
			}
		}
	}
	return (retrace(open.top()));
}


void		AI::generate_children(PuzzleState & parent) const {
	std::shared_ptr<PuzzleState> parentPtr = std::make_shared<PuzzleState>(parent);

	if (parent.p.canUpMove()) 
		parent.children.push_back(PuzzleState {parent.p.upMove(), parentPtr, std::vector<PuzzleState>(), 0, parent.g + 1, upMove});
	if (parent.p.canDownMove()) 
		parent.children.push_back(PuzzleState {parent.p.downMove(), parentPtr, std::vector<PuzzleState>(), 0, parent.g + 1, downMove});
	if (parent.p.canLeftMove()) 
		parent.children.push_back(PuzzleState {parent.p.leftMove(), parentPtr, std::vector<PuzzleState>(), 0, parent.g + 1, leftMove});
	if (parent.p.canRightMove()) 
		parent.children.push_back(PuzzleState {parent.p.rightMove(), parentPtr, std::vector<PuzzleState>(), 0, parent.g + 1, rightMove});
}

int			AI::heuristic(const Puzzle & current, const Puzzle & goal) const {
	auto h = 0;
	auto dim = current.getSize();

	for (auto i = 0; i < dim; i++) {
		for (auto j = 0; j < dim; j++) {
			auto goal_position = _finish_map.at(current.getCell(i, j));
			h += abs(goal_position.first - i) + abs(goal_position.second - j);
		}
	}
	return (h);
}

std::unique_ptr<std::stack<std::string> >	AI::retrace(PuzzleState p) const {
	std::unique_ptr<std::stack<std::string> > stk = std::make_unique<std::stack<std::string> >();

	stk->push(p.p.toString());
	while (p.move != -1) {
		p = *p.parent;
		stk->push(p.p.toString());
	}
	return (std::move(stk));
}

bool					AI::isSolvable( void ) const {
	auto	inv_count = getInvCount();

	return ((_start->getSize() == _finish->getSize()) && 
			( ((_start->getSize() % 2) && !(inv_count % 2) ) || 
			(!(_start->getSize() % 2) && ( ((_start->getEmptyIndex().first + 1) % 2) == !(inv_count % 2) )) ));
}

int			AI::getInvCount( void ) const {
	auto invCount = 0;
	auto size = _start->getSize();
	auto startVector = _start->makeVector();
	auto finishVector = _finish->makeVector();

	for (auto i = 0; i < size - 1; i++) {
		for (auto j = i + 1; j < size; j++) {
			if ((((*startVector)[i] - (*startVector)[j]) * ((*finishVector)[i] - (*finishVector)[j]) < 0))
				invCount++;
		}
	}
	return (invCount);
}

/* PuzzleState Operator Overload */
bool operator<(const PuzzleState &rhs, const PuzzleState &lhs) {
	return (lhs.f < rhs.f);
}
