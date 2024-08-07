#include "Game.h"


//	set size and fill table with 0
Sudoku::Sudoku(const size_t new_size) {
	Initialize_table(new_size);
}

Sudoku::Sudoku() {

	size_t size = Input<us>("Enter size ", Max_Size, false);
	
	std::cout << "\nEnter your level\n";
	
	char level = Input<char>("1 - Beginner\n2 - Intermidate\n3 - professional", '3');

	switch (level)
	{
	case '1': Chance = Player_Level::beginner;		break;
	case '2': Chance = Player_Level::intermidate;	break;
	case '3': Chance = Player_Level::Professional;	break;
	}//	end switch

	Initialize_table(size);



}

Sudoku::~Sudoku() {
	//	show end of the game
	if (empty_spot(table) == 0)
		screen << "Table is compelite well Done!\n\n";
	else
		screen << "May next time you be better\n";

	exit(true);
}



void Sudoku::Run() {

	Time timer;

	//	generated table
	Generate_vector();

	Erase_random_spots(Select_Difficulty());

	Print();

	Show_Difficulty(empty_spot(table));

	us choose = Input<us>("1 - We solve it\n2 - You solve it", 2);

	CLEAN;
	
	switch (choose)
	{
	case 1: {

		timer.Start();

		Self_solve();

		timer.Stop();

	}		break;
	case 2: {
		timer.Start();

		while (empty_spot(table)) {


			Print();

			User_solve();

			PAUSE;
			CLEAN;

		}//	end while

		timer.Stop();

	}		break;
	default: screen || "wrong choose\n";
	}//	end switch

	Print();
	screen == timer;


}

void Sudoku::Print() {
	std::cout << std::setw(3) << std::left << ' ';

	for (auto i = 0; i < m_size; i++)
		std::cout << std::setw(3) << std::right << i + 1;


	std::cout << '\n' << std::setw(3) << std::left << ' ';

	for (unsigned short i = 0; i < m_size * 3; i++)
		std::cout << '-';

	std::cout << '\n';

	for (auto i = 0; i < m_size; i++) {

		std::cout << std::setw(2) << std::left << i + 1 << '|';

		for (auto elem : table.at(i))
			std::cout << std::setw(3) << std::right << elem;

		std::cout << '\n';

	}//	end for

	std::cout << '\n';


}



//	generate table
void Sudoku::Generate_vector() {
	//	fill all vector with unique numbers

	Random random(m_size);

Re_process:

	auto temp = table;

	for (size_t row = 0; row < m_size; row++) {

		short counter = 0;

		for (size_t column = 0; column < m_size ; column++) {

			Again:
			us number = std::move(random.Get_Random_Number());

			/*
   			us number;
      			number << random;
   
   			*/
			
			//	if it is duplicated goto again and generate new number
			if (empty_spot(temp) and (is_duplicated(number, temp.at(row)) or is_duplicated(number, convertor(column, temp)))) {

				counter++;
				//	if infinit loop than stop and re-process.
				if (counter >= m_size * 100) {

					if (Attempts > 500)
					{
						screen || "Can not Generate a table for this size at the moment";
						screen << "Please re-start program and try again";
						PAUSE;
						exit(true);
					}
					else
						screen == "Atempt number " == ++Attempts == '\n';

					CLEAN;
					goto Re_process;

				}

			goto Again;


			}//	end if

			temp.at(row).at(column) = std::move(number);

		}//	end for

	}//	end first for

	//	temp is filled now copy it to table.
	table = std::move(temp);

}//	end function

//	check for duplicate number
bool Sudoku::is_duplicated(const us value, const vector vec)const {
	if (std::any_of(vec.begin(), vec.end(), [value](int y) { return value == y; }))
		return true;

	return false;

}

//	convert column to row without 0 
vector Sudoku::convertor(const size_t column, const auto base_vec)const {
	vector res;

	for (size_t i = 0; i < m_size; i++)
		if (base_vec.at(i).at(column) != 0)
			res.push_back(base_vec.at(i).at(column));

	return res;
}//	end function

us Sudoku::empty_spot(const auto vec) {
	us sum = 0;

	for (auto v : table)
		sum += static_cast<us>(std::count(v.cbegin(), v.cend(), 0));
			
	return sum;

}

void Sudoku::Erase_random_spots(const Set_Difficulty diff) {
	Random random(m_size);

	for (size_t f1 = 0; f1 < m_size; f1++)
		for (size_t size = 0; size < m_size / diff; size++)
		{
			//	to fit in vector size
			auto row = random.Get_Random_Number() - 1;
			auto col = random.Get_Random_Number() - 1;

			if (table.at(row).at(col) != 0) {
				ans_map[std::make_pair(row, col)] = table.at(row).at(col);
				table.at(row).at(col) = 0;
			}
			else
				size--;
		}

}//	end function

void Sudoku::Self_solve() {

	for (auto [loc, value] : ans_map)
		table.at(loc.first).at(loc.second) = std::move(value);

}

//	we can comapre user slove inputs with answers we have 

void Sudoku::User_solve() {

	us X = Input<us>("row ", m_size + 1, false) - 1;
	us Y = Input<us>("Col ", m_size + 1, false) - 1;
	us Value = Input<us>("row ", m_size, false);


	for(auto [spot , ansvalue] : ans_map)
		if (spot.first == X and spot.second == Y and ansvalue == Value) {
			table.at(X).at(Y) = std::move(Value);
			return;
		}


	if (--Chance < 1) {
		screen || "You ran-out of Attempt you had";
		this->~Sudoku();
	}
	screen || "Spot is already filled or value is out of rane";
	screen << "You have " == Chance == " Attempts left\n";

}

void Sudoku::Show_Difficulty(const us BlankSpots) const noexcept {

	std::cout << "Table Difficulty : ";

	if (BlankSpots <= Difficulty::Easy)
		std::cout << "Easy\n";
	else if (BlankSpots <= Difficulty::Medium and BlankSpots > Difficulty::Easy)
		std::cout << "Medium\n";
	else if (BlankSpots <= Difficulty::Hard and BlankSpots > Difficulty::Medium)
		std::cout << "Hard\n";
	else if (BlankSpots <= Difficulty::extrimyHard and BlankSpots > Difficulty::Hard)
		std::cout << "Extreamly hard\n";
	else
		std::cout << "Can not be solve by user\n";


}

Set_Difficulty Sudoku::Select_Difficulty() {

	std::cout << "\nEnter your preferred game Difficulty\n";
	us choose = Input<us>("1 - Easy \n2 - Medium\n3 - Hard", 3);

	switch (choose)
	{
	case 1: return Set_Difficulty::set_Easy;
	case 2: return Set_Difficulty::set_Medium;
	case 3: return Set_Difficulty::set_hard;
	default :
		screen || "Wrong input choose between 1-3\n";
		screen << "Default is : \"hard\"\n";
		return Set_Difficulty::set_hard;
	}

}

//	limite from 1 - (user limites) 
template <typename OutPut> OutPut Sudoku::Input(const auto options, const size_t Limite , const bool NewLine) {
		
	OutPut choose;
	
	do {
		std::cout << options;

		if (NewLine)
			std::cout << "\nEnter selection : ";
		else
			std::cout << " : ";
		

		if (std::cin >> choose and std::cin.fail())
		{
			std::cin.clear();
			std::cin.setf(std::ios::goodbit);

		}

	} while (choose > Limite or choose < 0);

	return choose;
}

void Sudoku::Initialize_table(const size_t new_size) {
	if (new_size > 2 and new_size < 50) [[likely]]
		m_size = new_size;
	else [[unlikely]]
		m_size = 2;


		table.resize(m_size);

		for (size_t i = 0; i < m_size; i++)
		{
			vector temp(m_size, 0);
			table.at(i) = temp;
		}
}
