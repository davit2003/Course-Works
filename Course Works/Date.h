#pragma once


class Date {
private:
	int year;
	int month;
	int day;
public:
	Date(int y, int m, int d) : year(y), month(m), day(d) {};
	void SetDate(int y, int m, int d);
	void AddDate(int y, int m, int d);
};