#ifndef MAP_HPP
# define MAP_HPP

# include /* header */

class map
{
private:
	/* data */
public:
	map();
	map(const map &from);
	~map();
	map	&operator=(const map &rvalue);
};

#endif