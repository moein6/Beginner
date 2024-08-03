#include "game.h"

Game::Game(const size_t newsize) {
	GameResul = Endgame::Tie;

	if (newsize > 2 and newsize < 10) [[likely]]
		Initialaze(newsize);
	else {
		std::cerr << "[ERROR] : Wrong size size is setted to 3\n\a";
		m_Size = 3;
	}
}

Game::Game() {
	size_t size;
	std::cout << "Enter Table size : ";

	std::cin >> size;

	if (size > 2 and size < 10)
		m_Size = size;
	else {
		std::cerr << "[ERROR] : Wrong size! size is setted as 3\n\a";
		m_Size = 3;
	}

	Initialaze(m_Size);
}

Game::~Game() {
	if (GameResul)
		std::cout << "Game Ended well\n";
	else
		std::cout << "Game did not ended\n";
}



void Game::Run() {

	us player = 0;

	do {

		Print();


		if (Row_check() or Column_check() or Diameter()) {
			GameResul = Endgame::Winner;
			break;
		}

		Solve(++player);

		std::system("pause");
		std::system("cls");

	} while (empty_spot());

	if (Endgame::Winner)
		std::cout << "Player" << (player % 2 ? " two " : " one ") << " is WINNER\n";
	else
		std::cout << "TIE\n";


	Print();


}


bool Game::Row_check() {

	bool foundinner = true;

	for (auto v : m_Table) {

		char prev = v.at(0);

		for (auto ch : v)
			if (ch == '-' or prev != ch)
				foundinner = false;
			else
				prev = ch;



		if (foundinner)
			return true;
	}//	end for

	return false;
}

bool Game::Column_check() {


	for (us row = 0; row < m_Size ; row++) {

		bool found = true;

		for (us col = 0; col < m_Size - 1; col++)
			if (m_Table.at(col).at(row) != m_Table.at(col + 1).at(row) or m_Table.at(col).at(row) == '-')
				found = false;

		if (found)
			return found;
	}

	return false;
}

bool Game::Diameter() {
	bool good = true;

	for (us i = 0; i < m_Size - 1; i++)
		if (m_Table.at(i).at(i) != m_Table.at(i + 1).at(i + 1) or m_Table.at(i).at(i) == '-')
			good = false;

	if (good)
		return good;

	//	the other Diameter of table
	for (us i = 0; i < m_Size - 1; i++)
		for (short j = m_Size - 1; j >= 0; j--)
			if (m_Table.at(i).at(j) == '-' or m_Table.at(i).at(j) != m_Table.at(i + 1).at(j))
				good = false;

	return good;
}


void Game::Print()const {

	std::cout << std::setw(space + 1) << std::left << ' ';
	for (auto i = 0; i < m_Size; i++)
		std::cout << std::setw(space) << std::right << i + 1;

	std::cout << '\n' << std::setw(space + 1) << std::left << ' ';
	for (unsigned short i = 0; i < m_Size * space; i++)
		std::cout << '=';
	std::cout << '\n';




	for (auto i = 0; i < m_Size; i++) {

		std::cout << std::setw(2) << std::left << i + 1 << '|';

		for (auto elem : m_Table.at(i))
			std::cout << std::setw(space) << std::right << elem;

		std::cout << '\n';

	}//	end for

	std::cout << '\n';




}

void Game::Initialaze(const size_t newSize) {

	m_Size = newSize;
	m_Table.resize(m_Size);

	for (us i = 0; i < m_Size; i++) {

		std::vector<char> temp(m_Size, '-');
		m_Table.at(i) = std::move(temp);

	}//	end for




}//	end function

void Game::Solve(const us player) {

	us row;
	us col;


	auto p = (player % 2 == 0);
	char ch = p ? X : O;

	std::cout << "Player " << (p ? " two " : " one ") << '\n';

	std::cout << "Enter row : ";
	std::cin >> row;

	std::cout << "col : ";
	std::cin >> col;

	if (row > m_Size or col > m_Size) {
		std::cerr << "wrong input\n";
		return;
	}

	row--;
	col--;

	if (m_Table.at(row).at(col) == '-')
		m_Table.at(row).at(col) = ch;
	else
		std::cerr << "This spot is already filled\n";

}

bool Game::empty_spot() {
	for (auto v : m_Table)
		for (auto ch : v)
			if (ch == '-')
				return true;

	return false;
}