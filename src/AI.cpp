#include "AI.hpp"

AI::AI(std::unique_ptr<Puzzle> && start, std::unique_ptr<Puzzle> && finish) {
	this->_start = std::move(start);
	this->_finish = std::move(finish);
	auto	tempVect = this->_finish->makeVector();

	auto dim = this->_finish->getSize();
	for (auto i = 0; i < dim; i++) {
		for (auto j = 0; j < dim; j++) {
			this->_finish_map.insert(std::make_pair<uint32_t, std::pair<uint32_t, uint32_t> >(tempVect->at((i * dim) + j), std::make_pair<uint, uint>(i , j)));
		}
	}
}

PuzzleState::PuzzleState(Puzzle && p, std::shared_ptr<PuzzleState> parent, std::vector<std::shared_ptr<PuzzleState> > children, int f, int g) {
	this->p = std::move(p);
	this->parent = parent;
	this->children = children;
	this->f = f;
	this->g = g;
}

std::unique_ptr<std::stack<std::string> >	AI::solve( void ) const {
	std::priority_queue<std::shared_ptr<PuzzleState> > open;
	std::unordered_map<std::string, bool> visited;
	std::shared_ptr<PuzzleState>	current;

	open.push(
		std::make_shared<PuzzleState>(std::move(*_start), nullptr, std::vector<std::shared_ptr<PuzzleState> >(), 0, 0)
	);

	while (!open.empty()) {
		current = open.top();
		visited.insert(std::make_pair<std::string, bool>(current->p.toString(), true));

		if (current->p == *_finish)
			break ;

		open.pop();

		generate_children(current);
		for (auto & child : current->children) {
			if (visited.count(child->p.toString()) == 0) {
				child->f = child->g + heuristic(child->p);
				open.push(child);
			}
		}
	}
	return (retrace(open.top()));
}


void		AI::generate_children(std::shared_ptr<PuzzleState> const parentPtr) const {
	if (parentPtr->p.canUpMove()) {
		parentPtr->children.push_back(
			std::make_shared<PuzzleState>(std::move(parentPtr->p.upMove(Puzzle(parentPtr->p))), parentPtr, std::vector<std::shared_ptr<PuzzleState> >(), 0, parentPtr->g + 1)
			);
	}
	if (parentPtr->p.canDownMove()) {
		parentPtr->children.push_back(
			std::make_shared<PuzzleState>(std::move(parentPtr->p.downMove(Puzzle(parentPtr->p))), parentPtr, std::vector<std::shared_ptr<PuzzleState> >(), 0, parentPtr->g + 1)
			);
	}
	if (parentPtr->p.canLeftMove()) {
		parentPtr->children.push_back(
			std::make_shared<PuzzleState>(std::move(parentPtr->p.leftMove(Puzzle(parentPtr->p))), parentPtr, std::vector<std::shared_ptr<PuzzleState> >(), 0, parentPtr->g + 1)
			);
	}
	if (parentPtr->p.canRightMove()) {
		parentPtr->children.push_back(
			std::make_shared<PuzzleState>(std::move(parentPtr->p.rightMove(Puzzle(parentPtr->p))), parentPtr, std::vector<std::shared_ptr<PuzzleState> >(), 0, parentPtr->g + 1)
			);
	}
}

/* Manhatten Distance */
int			AI::heuristic(const Puzzle & current) const {
	auto h = 0;
	auto dim = current.getSize();
	auto mapVect = current.makeVector();

	for (auto i = 0; i < dim; i++) {
		for (auto j = 0; j < dim; j++) {
			auto goal_position = _finish_map.at(mapVect->at((i * dim) + j));
			h += abs(goal_position.first - i) + abs(goal_position.second - j);
		}
	}
	return (h);
}

std::unique_ptr<std::stack<std::string> >	AI::retrace(std::shared_ptr<PuzzleState> ptr) const {
	auto 	stk = std::make_unique<std::stack<std::string> >();

	stk->push(ptr->p.toString());
	while (ptr->parent != nullptr) {
		ptr = ptr->parent;
		stk->push(ptr->p.toString());
	}
	return (std::move(stk));
}

bool					AI::isSolvable( void ) const {
	auto	inv_count = getInvCount();

	std::cout << "INV: " << inv_count << std::endl;
 	return ((_start->getSize() == _finish->getSize()) && 
			( ((_start->getSize() % 2) && !(inv_count % 2) ) || 
			(!(_start->getSize() % 2) && ( ((_start->getEmptyIndex().first + 1) % 2) == !(inv_count % 2) )) ));
}

int			AI::getInvCount( void ) const {
	auto invCount = 0;
	auto size = _start->getSize();
	auto startVector = _start->makeVector();
	auto finishVector = _finish->makeVector();

	for (auto i = 0; i < (size * size) - 1; i++) {
		for (auto j = i + 1; j < size * size; j++) {
			if (startVector->at(i) != 0 && startVector->at(j) != 0) {
				auto i_final = (_finish_map.at(startVector->at(i)).first * size) + _finish_map.at(startVector->at(i)).second;
				auto j_final = (_finish_map.at(startVector->at(j)).first * size) + _finish_map.at(startVector->at(j)).second;
				if (i_final > j_final)
					invCount++;
			}
		}
	}
	return (invCount);
}

/* PuzzleState Pointer Operator Overload */
bool operator<(const std::shared_ptr<PuzzleState> & rhs, const std::shared_ptr<PuzzleState> & lhs) {
	return (lhs->f < rhs->f);
}

