#include "puzzle.hpp"
#include "utils.hpp"
#include <sstream>

Puzzle::Puzzle(std::string state_map, uint32_t size) {
	this->_state_map = state_map;
	this->_size = size;

	for (auto i = 0; i < _size; i++) {
		for (auto j = 0; j < _size; j++) {
			if (getCell(i, j) == 0) {
				this->_emptyIndex = std::make_pair<uint32_t, uint32_t>(i, j);	
				i = _size;
				break ;
			}
		}
	}
}

int		Puzzle::getCell(const uint32_t row, const uint32_t col) const {
	auto strStream = std::istringstream(_state_map);
	int indexValue;

	for (auto i = 0; i <= (row * _size) + col; i++) {
		strStream >> indexValue;
	}
	return (indexValue);
}

void		Puzzle::setCell(const std::pair<uint32_t, uint32_t>& cell, const int value) {
	auto index = 0;
	auto i = 0;

	for (; i < cell.first; i++) {
		for (auto cellCount = 0; cellCount < _size; cellCount++) {
			while (_state_map[index] == ' ')
				index++;
			while (_state_map[index] != ' ' && _state_map[index] != '\0')
				index++;
			while (_state_map[index] == ' ')
				index++;
		}
	}
	for (auto j = 0; j < cell.second; j++) {
		while (_state_map[index] == ' ')
			index++;
		while (_state_map[index] != ' ' && _state_map[index] != '\0')
			index++;
		while (_state_map[index] == ' ')
			index++;
	}
	auto skip = index;
	while (_state_map[skip] != ' ' && _state_map[skip] != '\0')
		skip++;
	_state_map = _state_map.substr(0, index) + std::to_string(value) + _state_map.substr(skip);
}


Puzzle	Puzzle::upMove() const {
	Puzzle cpyPuzzle = Puzzle(*this);

	cpyPuzzle.setCell(std::make_pair<int, int>(_emptyIndex.first - 1, _emptyIndex.second), 0);
	cpyPuzzle.setCell(_emptyIndex, getCell(_emptyIndex.first - 1, _emptyIndex.second));
	cpyPuzzle.setEmptyIndex(std::make_pair<int, int>(_emptyIndex.first - 1, _emptyIndex.second));
	
	return (cpyPuzzle);
}

Puzzle	Puzzle::downMove() const {
	Puzzle cpyPuzzle = Puzzle(*this);

	cpyPuzzle.setCell(std::make_pair<int, int>(_emptyIndex.first + 1, _emptyIndex.second), 0);
	cpyPuzzle.setCell(_emptyIndex, getCell(_emptyIndex.first + 1, _emptyIndex.second));
	cpyPuzzle.setEmptyIndex(std::make_pair<int, int>(_emptyIndex.first + 1, _emptyIndex.second));
	
	return (cpyPuzzle);
}

Puzzle	Puzzle::leftMove() const {
	Puzzle cpyPuzzle = Puzzle(*this);

	cpyPuzzle.setCell(std::make_pair<int, int>(_emptyIndex.first, _emptyIndex.second - 1), 0);
	cpyPuzzle.setCell(_emptyIndex, getCell(_emptyIndex.first, _emptyIndex.second - 1));
	cpyPuzzle.setEmptyIndex(std::make_pair<int, int>(_emptyIndex.first, _emptyIndex.second - 1));

	return (cpyPuzzle);
}

Puzzle	Puzzle::rightMove() const {
	Puzzle cpyPuzzle = Puzzle(*this);

	cpyPuzzle.setCell(std::make_pair<int, int>(_emptyIndex.first, _emptyIndex.second + 1), 0);
	cpyPuzzle.setCell(_emptyIndex, getCell(_emptyIndex.first, _emptyIndex.second + 1));
	cpyPuzzle.setEmptyIndex(std::make_pair<int, int>(_emptyIndex.first, _emptyIndex.second + 1));
	
	return (cpyPuzzle);
}

std::pair<uint32_t, uint32_t>		Puzzle::getEmptyIndex() const {
	return (_emptyIndex);
}

void	Puzzle::setEmptyIndex(const std::pair<uint32_t, uint32_t> & index) {
	this->_emptyIndex = index;
}

bool	Puzzle::canUpMove() const {
	return (_emptyIndex.first > 0);
}

bool	Puzzle::canDownMove() const {
	return (_emptyIndex.first < _size - 1);
}

bool	Puzzle::canLeftMove() const {
	return (_emptyIndex.second > 0);
}

bool	Puzzle::canRightMove() const {
	return (_emptyIndex.second < _size - 1);
}


uint32_t	Puzzle::getSize() const {
	return (_size);
}

std::unique_ptr<std::vector<int> >	Puzzle::makeVector( void ) const {
	auto	flatVectorPtr = std::make_unique<std::vector<int> >();
	auto	strStream = std::istringstream(_state_map);
	int		tempNum;

	for (auto i = 0; i < _size * _size; i++) {
		strStream >> tempNum;
		flatVectorPtr->push_back(tempNum);
	}
	return (std::move(flatVectorPtr));
}

bool	Puzzle::operator==( Puzzle const &rhs ) const {
	return (rhs._state_map == this->_state_map);
}

std::string Puzzle::toString( void ) const {
	return (_state_map);
}
