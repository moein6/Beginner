#pragma once
#include <random>

#if __has_include (<iostream>)
#include <iostream>
#endif // __has_include (<iostream>)


class Random
{
public:
	Random(const size_t);
	[[nodiscard]] unsigned short Get_Random_Number()const;


	template <typename Ty> friend Ty& operator<<(Ty& value, const Random& random) {
		value = random.Get_Random_Number();
		return value;
	}

private:

	[[noreturn]] void Error(const char* ) noexcept;
	[[noreturn]] void Error(const std::string ) noexcept;


	//	numbers will be in range 1-100
	size_t m_Limite ;


};

