#include "game.h"

Game::Game(const size_t newsize) {
	GameResul = Endgame::Tie;

	Set_M_Size(size);
}

Game::Game() {
	size_t size;

	std::cout << "Set Game size : ";
	std::cin >> size;

	Set_M_Size(size);

	Initialize(m_Size);
}

Game::~Game() {
}

void Game::Run() {

	us turn = 1, choice;
	bool HasName = false;
	std::string playername;

	std::cout << "1 - Sign in \n2 - Ghost\n_> ";
	std::cin >> choice;

	
	if (choice == 1) {
		//	send to database and recive names (this code will be added in next update)
		//	HasName = true;
	}


	do {
		ClearScreen
		Print();
		
		playername = Get_PlayerName(turn, HasName);


		if (Row() or Column() or Diagonal()) {
			GameResul = Endgame::Winner;
			break;
		}
		

		Play(turn, playername.data());

		turn++;

		if (turn > 2)
			turn = 1;

		PauseScreen

	} while (empty_spot());

	if (GameResul == Endgame::Winner) {
		constexpr auto fmt = "Player : {:<10} Win\n";
		std::cout << std::format(fmt, playername);
	}
	else 
		std::cout << "TIE\n";
}

bool Game::Check_vector(const vector1D& vec) {

	return (std::all_of(vec.begin(), vec.end(), [](const char& ch) { return ch == O; })
		or
		std::all_of(vec.begin(), vec.end(), [](const char& ch) {return ch == X; }));
}

bool Game::Row() {

	for (auto r : m_Table) {
		
		if (Check_vector(r))
			return true;
	}//	end for

	return false;

}//	end function

bool Game::Column() {


	for (us row = 0; row < m_Size ; row++) {
		//	convert a column to a row vector than check the vector
		if (Check_vector(coltorow_Vector(row)))
			return true;
	}//	end for

	return false;
}//	function

bool Game::Diagonal() {
	
	vector1D vec ;

	for (auto i = 0; i < m_Size; i++)
		vec.push_back(m_Table.at(i).at(i));

	if (Check_vector(vec))
		return true;


	vec.clear();

	for (auto i = 0; i < m_Size; i++)
		vec.push_back(m_Table.at(i).at(m_Size - 1 - i));


	if (Check_vector(vec))
		return true;

	return false;

}

vector1D Game::coltorow_Vector(const us& col) {
	//	 this function copys a column from main table and makes it row vector

	vector1D vec;

	for (auto i = 0; i < m_Size; i++)
		vec.push_back(m_Table.at(i).at(col));

	return vec;
		
}

void Game::Print()const {

	constexpr auto fmt1 = "{:<3}";
	constexpr auto fmt2 = "{:>2}";
	constexpr auto fmt3 = "\n{:<3} ";
	constexpr auto fmt4 = "{:<2}|";
	constexpr auto fmt5 = "{:>2}";
	
	std::cout << std::format(fmt1, ' ');

	for (auto i = 0; i < m_Size; i++)
		std::cout << std::format(fmt2, i + 1);
		

	std::cout << std::format(fmt3, ' ');
	
	std::cout << std::string(m_Size * space, '-') << '\n';

	
	for (auto i = 0; i < m_Size; i++) {
		std::cout << std::format(fmt4, i + 1);
		

		for (auto elem : m_Table.at(i))
			std::cout << std::format(fmt5, elem);

		std::cout << '\n';

	}//	end for

	std::cout << '\n';

}//	END FUNCTION

void Game::Initialize(const size_t newSize) {
		
	m_Size = newSize;
	m_Table.resize(m_Size);

	for (us i = 0; i < m_Size; i++)
		m_Table.at(i) = std::move(vector1D(m_Size, '-'));

}//	end function

void Game::Play(const us &Turn,const std::string_view &PlayerName) {

	us row;
	us col;
	auto ch = (Trun == 1 ) ? O : X;

	std::cout << PlayerName << " : \n";

	std::cout << "Row : ";
	std::cin >> row;

	std::cout << "Col : ";
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


void Game::Set_M_Size(const size_t &newsize){
	if (newsize > 2 and newsize < 10)
		m_Size = size;
	else {
		std::cerr << "[ERROR] : Wrong size! set to 3\n\a";
		m_Size = 3;
	}
}

bool Game::empty_spot() {
	bool found = false;
	
	for (auto v : m_Table)
		if (std::any_of(v.begin(), v.end(), [](const char& ch) { return ch == '-'; })){
			found = true;
			break;
		}
			
	return found;
}

std::string_view Game::Get_PlayerName(const unsigned short& Turn, const bool &hasName)const {
	if (hasName)
		return playerNameArr.at(Turn - 1);
	else
		switch (Turn) {
		case 1:	return "One";
		case 2:	return "Two";
		}//	end switch

	return "ERR";
}
