#include "Employee.h"


Employee::Employee(std::string n, std::string s, int sal, unsigned long long p, Date exp, Seniority sen) {
	name = n;
	surname = s;
	salary = sal;
	pid = p;
	expirationDate = exp;
	seniority = sen;
}
std::string Employee::GetName() {
	return name;
}

std::string Employee::GetSurname() {
	return surname;
}

unsigned int Employee::GetSalary() {
	return salary;
}

unsigned long long Employee::GetPID() {
	return pid;
}

Date Employee::GetExpirationDate() {
	return expirationDate;
}

Seniority Employee::GetSeniority() {
	return seniority;
}

/////////////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<RequestResponse<void*>> Employee::CancelContract() {
	expirationDate.SetDate(0, 0, 0);
	return std::unique_ptr <RequestResponse <void*>> (new SuccessfulResponse<void*>());
}

std::unique_ptr<RequestResponse<void*>> Employee::ExtendContract(int y, int m, int d) {
	std::unique_ptr<RequestResponse<void*>> res;
	RequestResponse<void*> x = *expirationDate.AddDate(y, m, d).get();

	if (x.errorCode == ErrorCode::SuccessfulRequest)
		res.reset(new SuccessfulResponse<void*>());
	else
		res.reset(new InvalidResponse<void*>(x.errorMessage));

	return res;
}

std::unique_ptr<RequestResponse<void*>> Employee::SetSalary(int s) {
	salary = s;
	return std::unique_ptr <RequestResponse <void*>>(new SuccessfulResponse<void*>());
}

std::unique_ptr<RequestResponse<void*>> Employee::Promote() {
	std::unique_ptr<RequestResponse<void*>> res;
	
	if (seniority == Seniority::Senior)
		res.reset(new InvalidResponse<void*>("Employee reached maximum potential"));
	else {
		int curr = static_cast<std::underlying_type<Seniority>::type>(seniority);
		seniority = static_cast<Seniority>(curr + 1);
		res.reset(new SuccessfulResponse<void*>());
	}
	return res;
}

