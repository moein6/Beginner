#include <iostream>
#include <vector>
#include <iomanip>



enum situation {
	OFF,
	ON
};


constexpr bool debug = situation::OFF;

using vector = std::vector<std::vector<char>>;
using us = unsigned short;

constexpr char X = 'X';
constexpr char O = 'O';
constexpr us space = 2;


enum  Endgame
{
	Winner = true,
	Tie = false
};


class  Game
{
public:
	Game(const size_t newsize);

	Game();

	~Game();


	void Run();


private:
	bool Row_check();

	bool Column_check();

	bool Diameter();


	void Print()const;

	void Initialaze(const size_t newSize);

	void Solve(const us player);

	bool empty_spot();
private:

	vector m_Table;
	size_t m_Size;
	bool GameResul;
};
