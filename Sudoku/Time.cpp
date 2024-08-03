#include "Time.h"


Time::Time(const bool start) {
	Timer_started = start;
	if (Timer_started)
		m_start = std::chrono::high_resolution_clock::now();
	
}

void Time::Start() {
	Timer_started = true;
	m_start = std::chrono::high_resolution_clock::now();
}

void Time::Stop() {
	Timer_ended = true;
	m_end = std::chrono::high_resolution_clock::now();
}

void Time::Sleep(const unsigned short milisecond) {
	
	m_start = std::chrono::high_resolution_clock::now();
	
	while (true)
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_start) >= std::chrono::milliseconds(milisecond))
			break;
	return;
}

std::ostream &operator<<( std::ostream& out, const Time time) {

	if (time.Timer_started and time.Timer_ended) {
		std::chrono::duration<float> Duration = std::chrono::duration<float>(time.m_end - time.m_start);

		if (Duration < std::chrono::milliseconds(1))
			std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(Duration) << '\n';
		else
			out << "Time : " << Duration << '\n';
	}
	else
		out << "ERROR : Start timer is not setted\n\a";
	
	return out;
}


Time::~Time() {

}