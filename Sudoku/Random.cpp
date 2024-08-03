#include "Random.h"

//	maximum limite for the game is 100
Random::Random(const size_t limite){
	if (limite > 0 and limite < 100)_LIKELY
		m_Limite = limite;
	else
		Error("wrong Limite");
}


void Random::Error(const char* str)noexcept {

	std::cout << "[ERROR] : " << str << "\n\a";

	terminate();
}
void Random::Error(const std::string str)noexcept {
	std::cout << "[ERROR] : " << str << "\n\a";

	terminate();
}

	//	generate a number ni range 1 - max_size
unsigned short Random::Get_Random_Number()const {
		std::random_device random;

		std::mt19937 genrator(random());

		std::uniform_real_distribution<float> Limiter(1, m_Limite + 1.0);

		return static_cast<unsigned short> (Limiter(genrator));

}

