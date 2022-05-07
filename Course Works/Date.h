#pragma once

#include <memory>
#include "RequestResponse.h"

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date();
	Date(int, int, int);
	std::unique_ptr<RequestResponse<void*>> SetDate(int, int, int);
	std::unique_ptr<RequestResponse<void*>> AddDate(int, int, int);
	std::string Format();
};