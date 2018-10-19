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

	Puzzle				upMove( void ) const;
	Puzzle				downMove( void ) const;
	Puzzle				leftMove( void ) const;
	Puzzle				rightMove( void ) const;	
	std::string			toString() const;
	bool				operator<( Puzzle const &rhs) const ;
	bool				operator==(Puzzle const &rhs) const ;
};

#endif
