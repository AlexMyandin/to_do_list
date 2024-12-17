#pragma once
#include <string>
using namespace std;
class DateTime
{
public:

	DateTime(int day,int month, int year, int hour, int min);
	// геттеры
	int getDay();
	int getMonth();
	int getYear();
	int getHour();
	int getMin();
	// сеттеры
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	void setHour(int hour);
	void setMin(int min);

	bool operator>=(DateTime& date);

	bool operator<=(DateTime& date);

	bool operator==(DateTime& date);

private:
	int m_day;
	int m_month;
	int m_year;
	int m_hour;
	int m_min;
};

