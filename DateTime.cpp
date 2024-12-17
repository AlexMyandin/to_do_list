#include "DateTime.h"




DateTime::DateTime(int day, int month, int year, int hour, int min) :
	m_day(day), m_month(month), m_year(year), m_hour(hour), m_min(min) {};


// геттеры
int DateTime::getDay() { return m_day; };
int DateTime::getMonth() { return m_month; };
int DateTime::getYear() { return m_year; };
int DateTime::getHour() { return m_hour; };
int DateTime::getMin() { return m_min; };
// сеттеры
void DateTime::setDay(int day) { m_day = day; };
void DateTime::setMonth(int month) { m_month = month; };
void DateTime::setYear(int year) { m_year = year; };
void DateTime::setHour(int hour) { m_hour = hour; };
void DateTime::setMin(int min) { m_min = min; };

bool DateTime::operator>=(DateTime& date) {
	return true;
};

bool DateTime::operator<=(DateTime& date) {
	return true;
};

bool DateTime::operator==(DateTime& date) {
	return true;
};