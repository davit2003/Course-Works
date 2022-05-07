#include "Date.h"
#include "RequestResponse.h"
#include <iomanip>

Date::Date() : year(0), month(0), day(0) {};

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {};

std::unique_ptr<RequestResponse<void*>> Date::AddDate(int y, int m, int d) {
	std::unique_ptr<RequestResponse<void*>> res;
	if (y < 0 || (m < 0 || m > 12) || (d < 0 || d > 30))
		res.reset(new InvalidResponse<void*>("The date is invalid"));
	else {
		day += d;
		day %= 30;
		month += m + day / 30;
		month %= 12;
		year += y + month / 12;
		res.reset(new SuccessfulResponse<void*>());
	}
	return res;
}

std::unique_ptr<RequestResponse<void*>> Date::SetDate(int y, int m, int d) {
	std::unique_ptr<RequestResponse<void*>> res;
	if (y < 0 || (m < 0 || m > 12) || (d < 0 || d > 30))
		res.reset(new InvalidResponse<void*>("The date is invalid"));
	else {
		year = y;
		month = m;
		day = d;
		res.reset(new SuccessfulResponse<void*>());
	}
	return res;
}

std::string Date::Format() {
	std::string formatedDate;
	char buffer[15];
	sprintf_s(buffer, "%02d/%02d/%04d", day, month, year);
	formatedDate = buffer;
	
	return formatedDate;
}