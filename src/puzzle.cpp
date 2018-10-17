#include "puzzel.hpp"
#include "utils.hpp"

// Puzzel::Puzzel(std::string state_map, uint32_t g_score, uint8_t move_to_parent) {
// 	this->state_map = state_map;
// 	this->f_score = this->heuristic() + g_score;
// 	this->g_score = g_score;
// 	this->move_to_parent = move_to_parent;
// }

Puzzel::Puzzel(std::string state_map, uint32_t size) {
	this->state_map = state_map;
	this->size = size;
}

int		Puzzel::getCell(const uint32_t row, const uint32_t col) const {
	auto index = 0;
	auto i = 0;
	for (; i < row; i++) {
		for (auto cellCount = 0; cellCount < size; cellCount++) {
			while (state_map[index] == ' ')
				index++;
			while (state_map[index] != ' ' && state_map[index] != '\0')
				index++;
			while (state_map[index] == ' ')
				index++;
		}
	}
	for (auto j = 0; j < col; j++) {
		while (state_map[index] == ' ')
			index++;
		while (state_map[index] != ' ' && state_map[index] != '\0')
			index++;
		while (state_map[index] == ' ')
			index++;
	}
	return (atoi(&(state_map[index])));
}

std::string		Puzzel::setCell(const std::pair<uint32_t, uint32_t>& cell, const int value) {
	auto index = 0;
	auto i = 0;
	for (; i < cell.first; i++) {
		for (auto cellCount = 0; cellCount < size; cellCount++) {
			while (state_map[index] == ' ')
				index++;
			while (state_map[index] != ' ' && state_map[index] != '\0')
				index++;
			while (state_map[index] == ' ')
				index++;
		}
	}
	for (auto j = 0; j < cell.second; j++) {
		while (state_map[index] == ' ')
			index++;
		while (state_map[index] != ' ' && state_map[index] != '\0')
			index++;
		while (state_map[index] == ' ')
			index++;
	}
	auto skip = index;
	while (state_map[skip] != ' ' && state_map[skip] != '\0')
		skip++;
	state_map = state_map.substr(0, index) + std::to_string(value) + state_map.substr(skip);	

	return (state_map);
}

bool	Puzzel::operator==( Puzzel const &rhs ) const {
	return (rhs.state_map == this->state_map);
}

std::string Puzzel::toString( void ) const {
	return (state_map);
}

Puzzel	Puzzel::upMove() const {
	Puzzel cpyPuzzel = Puzzel(*this);

	auto emptyIndex = getEmptyIndex();
	cpyPuzzel.setCell(std::make_pair<int, int>(emptyIndex.first - 1, emptyIndex.second), 0);
	cpyPuzzel.setCell(emptyIndex, getCell(emptyIndex.first - 1, emptyIndex.second));

	return (cpyPuzzel);
}

Puzzel	Puzzel::downMove() const {
	Puzzel cpyPuzzel = Puzzel(*this);

	auto emptyIndex = getEmptyIndex();
	cpyPuzzel.setCell(std::make_pair<int, int>(emptyIndex.first + 1, emptyIndex.second), 0);
	cpyPuzzel.setCell(emptyIndex, getCell(emptyIndex.first + 1, emptyIndex.second));

	return (cpyPuzzel);
}

Puzzel	Puzzel::leftMove() const {
	Puzzel cpyPuzzel = Puzzel(*this);

	auto emptyIndex = getEmptyIndex();
	cpyPuzzel.setCell(std::make_pair<int, int>(emptyIndex.first, emptyIndex.second - 1), 0);
	cpyPuzzel.setCell(emptyIndex, getCell(emptyIndex.first, emptyIndex.second - 1));

	return (cpyPuzzel);
}

Puzzel	Puzzel::rightMove() const {
	Puzzel cpyPuzzel = Puzzel(*this);

	auto emptyIndex = getEmptyIndex();
	cpyPuzzel.setCell(std::make_pair<int, int>(emptyIndex.first, emptyIndex.second + 1), 0);
	cpyPuzzel.setCell(emptyIndex, getCell(emptyIndex.first, emptyIndex.second + 1));

	return (cpyPuzzel);
}

std::pair<uint32_t, uint32_t>		Puzzel::getEmptyIndex() const {
	for (auto i = 0; i < getSize(); i++) {
		for (auto j = 0; j < getSize(); j++) {
			if (getCell(i, j) == 0)
				return (std::make_pair<uint32_t, uint32_t>(i, j));		
		}
	}
	return (std::make_pair<int, int>(-1, -1));
}

bool	Puzzel::canUpMove() const {
	auto emptyIndex = getEmptyIndex();

	return (emptyIndex.first > 0);
}

bool	Puzzel::canDownMove() const {
	auto emptyIndex = getEmptyIndex();

	return (emptyIndex.first < getSize() - 1);
}

bool	Puzzel::canLeftMove() const {
	auto emptyIndex = getEmptyIndex();

	return (emptyIndex.second > 0);
}

bool	Puzzel::canRightMove() const {
	auto emptyIndex = getEmptyIndex();

	return (emptyIndex.second < getSize() - 1);
}


uint32_t	Puzzel::getSize() const {
	return (size);
}

std::unique_ptr<std::vector<int> >	Puzzel::makeVector( void ) const {
	auto index = 0;
	std::unique_ptr<std::vector<int> > flatVector = std::make_unique<std::vector<int> >();

	for (auto i = 0; i < getSize(); i++) {
		for (auto cellCount = 0; cellCount < size; cellCount++) {
			while (state_map[index] == ' ')
				index++;
			flatVector->push_back(atoi(&(state_map[index])));
			while (state_map[index] != ' ' && state_map[index] != '\0')
				index++;
			while (state_map[index] == ' ')
				index++;
		}
	}
	return (std::move(flatVector));
}