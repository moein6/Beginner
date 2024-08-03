#pragma once
#include <chrono>

#if __has_include (<iostream>)
#include <iostream>
#endif


class Time {
public:
	Time(const bool = false) ;

	~Time();

	void Start();

	void Stop();
	
	void Sleep(const unsigned short milisecond);

	friend std::ostream& operator<<(std::ostream& out, const Time time);	

private:
	std::chrono::high_resolution_clock::time_point m_start , m_end;

	bool Timer_started , Timer_ended;
};
