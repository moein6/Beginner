#include "Game.h"

//	set size and fill table with 0
Sudoku::Sudoku(const size_t new_size) {
	Initialize_table(new_size);
	Select_PlayerLevel();
}

Sudoku::Sudoku() {

	size_t size = Input<us>("Enter size ", Max_Size, false);
	
	Initialize_table(size);
	Select_PlayerLevel();
}

Sudoku::~Sudoku() {
	//	show end of the game
	if (empty_spot(table) == 0)
		std::cout << "Table is compelite well Done!\n\n";
	else
		std::cout << "May next time you be better\n";
}

void Sudoku::Run() {
	//	generated table
	Generate_vector();

	Erase_random_spots(Select_Difficulty());

	Print();

	Solve();
}

void Sudoku::Print() {
	
	
	constexpr auto space = "{:<3} ";
	constexpr auto H_Header = "{:>3}";
	constexpr auto V_Header = "{:<3}|";

	std::cout << std::format(space, ' ');

	for (auto i = 0; i < m_size; i++)
		std::cout << std::format(H_Header, i + 1);


	std::cout << '\n' << std::format(space, ' ');
	std::cout << std::string(m_size * 3, '-') << '\n';


	for (auto i = 0; i < m_size; i++) {

		std::cout << std::format(V_Header, i + 1);

		for (auto elem : table.at(i))
			std::cout << std::format(H_Header, elem);

		std::cout << '\n';

	}//	end for

	std::cout << '\n';


}

//	generate table
void Sudoku::Generate_vector() {
	//	fill all vector with unique numbers

	Random random(m_size);
	short attempts = 0;

	// lambda fixed: takes table by reference and clears it
	auto clearTable = [](auto& Table) {
		for (auto& row : Table)
			std::fill(row.begin(), row.end(), 0);
		};

	while (attempts++ < 100) {

		clearTable(table);  // correctly clears
		bool stop = false;

		for (size_t row = 0; row < m_size && !stop; row++) {

			for (size_t column = 0; column < m_size; column++) {

				bool filled = false;
				short counter = 0;

				while (!filled && counter++ < 100) {

					us number = random.Get_Random_Number();

					if (is_duplicated(number, table[row])) continue;
					if (is_duplicated(number, convertor(column, table))) continue;

					table[row][column] = number;
					filled = true;
				}

				if (!filled) {
					stop = true;
					break;
				}
			}
		}

		if (!stop) {
			// Success!
			break;
		}
	}

	if (attempts >= 100) {
		// failed to generate a full valid board after 100 attempts
		std::cerr << "Failed to generate table.\n";
		endGame();
	}
}//	end function

//	check for duplicate number
bool Sudoku::is_duplicated(const us value, const vector1D vec)const  {
	
	return (std::any_of(vec.begin(), vec.end(), [value](int y) { return value == y; }));

}

//	convert column to row without 0 
vector1D Sudoku::convertor(const size_t column, const auto &base_vec)const {
	vector1D res;

	for (size_t i = 0; i < m_size; i++)
		if (base_vec.at(i).at(column) != 0)
			res.push_back(base_vec.at(i).at(column));

	return res;
}//	end function

us Sudoku::empty_spot(const auto& vec) {
	us sum = 0;

	for (auto v : vec)
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
	us Value = Input<us>("Num ", m_size, false);


	for(auto [spot , ansvalue] : ans_map)
		if (spot.first == X and spot.second == Y and ansvalue == Value) {
			table.at(X).at(Y) = std::move(Value);
			return;
		}


	if (--Chance < 1) {
		std::cout <<  "[ERROR] : You ran-out of Attempt you had";

		endGame();

	}
	std::cout << "[Message] : Spot is already filled or value is out of rane";
	std::cout << "You have " << Chance << " Attempts left\n";
	

}

void Sudoku::Show_Difficulty() noexcept {

	std::string dif;
	const us BlankSpots = empty_spot(table);

	if (BlankSpots <= Difficulty::Easy)
		dif = "Easy";
	else if (BlankSpots <= Difficulty::Medium and BlankSpots > Difficulty::Easy)
		dif = "Medium";
	else if (BlankSpots <= Difficulty::Hard and BlankSpots > Difficulty::Medium)
		dif = "Hard";
	else if (BlankSpots <= Difficulty::extrimyHard and BlankSpots > Difficulty::Hard)
		dif = "Extreamly hard";
	else
		dif = "Can not be solve by user";

	std::cout << "Table Difficulty : " << dif << '\n';

}

Set_Difficulty Sudoku::Select_Difficulty() {

	std::cout << "\nGame difficulty\n";
	us choose = Input<us>("1 - Easy \n2 - Medium\n3 - Hard", 3);

	switch (choose) {
	case 1: return Set_Difficulty::set_Easy;
	case 2: return Set_Difficulty::set_Medium;
	case 3: return Set_Difficulty::set_hard;
	default:return Set_Difficulty::set_hard;
	}//	end switch

}//	end func

//	limite from 1 - (user limites) 
template <typename OutPut> OutPut Sudoku::Input(const auto options, size_t limit, bool newLine ) {
	static_assert(std::is_arithmetic_v<OutPut>,
		"Input only supports numeric types.");

	OutPut choose{};
	while (true) {
		std::cout << options
			<< (newLine ? "\nEnter selection: " : " : ");

		if (std::cin >> choose) {
			if (choose >= 0 && static_cast<size_t>(choose) <= limit) {
				return choose; // valid input
			}
			else {
				std::cout << "Please enter a value between 0 and " << limit << ".\n";
			}
		}
		else {
			// clear error state and discard bad input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, please enter a number.\n";
		}
	}
}

void Sudoku::Initialize_table(const size_t new_size) {
	if (new_size > 2 and new_size < 50) [[likely]]
		m_size = new_size;
	else								[[unlikely]]
		m_size = 2;


		table.resize(m_size);

		for (size_t i = 0; i < m_size; i++) {
			vector1D temp(m_size, 0);
			table.at(i) = temp;
		}
}


void Sudoku::endGame() {
	throw std::runtime_error("Game Stoped!\n");
}


void Sudoku::Solve() {

	Time timer;


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
	default: std::cout << "[ERROR] wrong choose\n";
	}//	end switch

	Print();
	std::cout << "[TIME] : " << timer << '\n';

}


void Sudoku::Select_PlayerLevel() {
	std::cout << "\nEnter your level\n";

	char level = Input<char>("1 - Beginner\n2 - Intermidate\n3 - professional", '3');

	switch (level)
	{
	case '1': Chance = Player_Level::beginner;		break;
	case '2': Chance = Player_Level::intermidate;	break;
	case '3': Chance = Player_Level::Professional;	break;
	}//	end switch

}
