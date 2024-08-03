#pragma once
#if __has_include (<iostream>)
#include <iostream>
#endif // __has_Include (<iostream>)

#define CLEAN std::system("cls")
#define PAUSE std::cin.get() , std::cin.get();

class Screen
{
public:

	//	using << for show Massages
	template <typename Type>	friend Screen& operator << (Screen& screen, const Type& text) {
		std::cout << "[MASSAGE] : " << text;
		return screen;
	}

	//	using || for show Error
	template <typename Type>	friend Screen& operator || (Screen& screen, const Type& Text) {
		std::cerr << "[ERROR]: " << Text << "\a\n";
		return screen;
	}

	template <typename Ty>		friend Screen& operator == (Screen& screan, const Ty& text) {
		std::cout << text;
		return screan;
	}

};
