#include <iostream>
#include <vector>
#include <iomanip>
#include <format>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>
#include <array>


#define ClearScreen std::system("cls");
#define PauseScreen std::system("pause");


using us = unsigned short;
using vector1D = std::vector<char>;
using vector2D = std::vector<std::vector<char>>;

constexpr char X = 'X';
constexpr char O = 'O';
constexpr us space = 2;
constexpr std::string_view FileName = "Players.bin";

constexpr enum Endgame { Tie = false, Winner = true };

class  Game
{
public:
	Game(const size_t newsize);
	
	Game();

	~Game();


	void Run();


private:
	bool Diagonal();

	bool Row();

	bool Check_vector(const vector1D& vec);

	void Print()const;

	bool empty_spot();

	vector1D coltorow_Vector(const us &);

	bool Column();

	void Play(const us&, const std::string_view & );
	
	void Initialize(const size_t newSize);

	std::string_view Get_PlayerName(const unsigned short & , const bool &hasName = false)const;

protected:
	std::array<std::string, 2> playerNameArr;

private:

	vector2D m_Table;
	size_t m_Size = 0;
	bool GameResul = false;


};


