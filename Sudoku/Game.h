#pragma once

#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

#include "Random.h"
#include "Time.h"
#include "Screen.h"



#if __has_include (<iomanip>) or __has_include(<iostream>)
#include <iomanip>
#include <iostream>
#endif

using us = unsigned short;
using vector = std::vector<us>;
constexpr us Max_Size = 15;


enum Difficulty
{
	Easy = 10,
	Medium = 30,
	Hard = 50,
	extrimyHard = 100
};

enum Set_Difficulty {

	set_hard = 2,
	set_Medium,
	set_Easy
};

enum Player_Level {
	Professional = 3,
	intermidate = 5,
	beginner = 7
};

class Sudoku
{
public:
	
	//	set size and fill table with 0
	Sudoku(const size_t );

	Sudoku();

	[[noreturn]]~Sudoku();

	void Run();

private:

	//	generate table
	void Generate_vector();

	//	check for duplicate number
	bool is_duplicated(const us , const vector )const;

	//	convert column to row without 0 
	vector convertor(const size_t , const auto )const;

	//	return empty count
	us empty_spot(const auto);

	//	randomly erase spots
	void Erase_random_spots(const Set_Difficulty = Set_Difficulty::set_Easy);

	//	program solve table
	void Self_solve();

	void User_solve();

	void Show_Difficulty(const us ) const noexcept;

	Set_Difficulty Select_Difficulty();

	template <typename OutPut> OutPut Input(const auto, const size_t , const bool newLine = true);

	void Print();

	void Initialize_table(const size_t);


private:
	Screen screen;


	size_t m_size;
	us Attempts = 1;
	us Chance;

	std::vector<std::vector<us>> table;
	std::map<std::pair<us, us>, us> ans_map;
};

