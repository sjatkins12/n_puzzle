#ifndef PUZZEL_HPP

# define PUZZEL_HPP
# include <string>
# include <math.h>
# include <iostream>
# include <vector>
# include <stack>
# include <stdlib.h>

# define UP_MOVE 1
# define DOWN_MOVE 2
# define LEFT_MOVE 3
# define RIGHT_MOVE 4


class Puzzel {
	std::string	state_map;
	uint32_t	size;

	uint32_t	heuristic( void );

public:
	uint8_t		move_to_parent;

	~Puzzel() {};
	Puzzel() {};
	Puzzel(std::string state_map, uint32_t g_score, uint8_t move_to_parent);
	Puzzel(std::string state_map, uint32_t size);

	std::pair<uint32_t, uint32_t>	getEmptyIndex() const;
	int							getInvCount(const std::string) const;
	uint32_t					getSize() const;
	int							getCell(const uint32_t, const uint32_t) const;
	std::string					setCell(const std::pair<uint32_t, uint32_t> &, const int value);

	std::unique_ptr<std::vector<int> >	makeVector( void ) const;

	bool				canUpMove( void ) const;
	bool				canDownMove( void ) const;
	bool				canLeftMove( void ) const;
	bool				canRightMove( void ) const;

	Puzzel				upMove( void ) const;
	Puzzel				downMove( void ) const;
	Puzzel				leftMove( void ) const;
	Puzzel				rightMove( void ) const;	
	std::string			toString() const;
	bool				operator<( Puzzel const &rhs) const ;
	bool				operator==(Puzzel const &rhs) const ;
};

// struct	compareFScore {
// 	bool operator()(Puzzel  & p1, Puzzel  & p2) {
// 		return (p1.get_f_score() < p2.get_f_score());
// 	}
// };

#endif