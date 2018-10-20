#ifndef PUZZEL_HPP

# define PUZZEL_HPP
# include <string>
# include <math.h>
# include <iostream>
# include <vector>
# include <stack>
# include <stdlib.h>

class Puzzle {
	std::string	_state_map;
	uint32_t	_size;
	std::pair<uint32_t, uint32_t> _emptyIndex;

public:
	Puzzle(Puzzle const &);
	Puzzle(Puzzle &&);
	Puzzle() {};
	~Puzzle() {};
	Puzzle(std::string state_map, uint32_t size);

	std::pair<uint32_t, uint32_t>	getEmptyIndex() const;
	void							setEmptyIndex(const std::pair<uint32_t, uint32_t> &);
	uint32_t						getSize() const;
	int								getCell(const uint32_t, const uint32_t) const;
	void							setCell(const std::pair<uint32_t, uint32_t> &, const int value);

	std::unique_ptr<std::vector<int> >	makeVector( void ) const;

	bool				canUpMove( void ) const;
	bool				canDownMove( void ) const;
	bool				canLeftMove( void ) const;
	bool				canRightMove( void ) const;

	Puzzle	&			upMove( Puzzle && cpyPuzzle ) const;
	Puzzle	&			downMove( Puzzle && cpyPuzzle ) const;
	Puzzle	&			leftMove( Puzzle && cpyPuzzle ) const;
	Puzzle	&			rightMove( Puzzle && cpyPuzzle ) const;	
	std::string			toString() const;
	bool				operator<( Puzzle const &rhs) const ;
	bool				operator==(Puzzle const &rhs) const ;
	Puzzle &			operator=(Puzzle const &rhs);
	Puzzle &			operator=(Puzzle &&rhs);
	
};

#endif
