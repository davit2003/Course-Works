#pragma once
#include "SeniorityEnum.h"
#include "Date.h"
#include "RequestResponse.h"

class Employee{
private:
	std::string name;
	std::string surname;
	unsigned int salary;
	unsigned long long pid; //Personal ID
	Date expirationDate; // Contract Expiration Date
	Seniority seniority;

public:
	Employee();
	Employee(std::string, std::string, int, unsigned long long, Date, Seniority);

	std::string GetName();
	std::string GetSurname();
	unsigned int GetSalary();
	unsigned long long GetPID();
	Date GetExpirationDate();
	Seniority GetSeniority();

	std::unique_ptr<RequestResponse<void*>> ExtendContract(int, int, int);
	std::unique_ptr<RequestResponse<void*>> CancelContract();
	std::unique_ptr<RequestResponse<void*>> SetSalary(int);
	std::unique_ptr<RequestResponse<void*>> Promote();

	virtual float EvaluateWorkLoad() const = 0;
	
	bool operator>(const Employee&) const;
	bool operator<(const Employee&) const;
};
