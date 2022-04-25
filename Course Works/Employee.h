#pragma once
#include <string>
#include "SeniorityEnum.h"
#include "Date.h"

class Employee{
private:
	std::string name;
	std::string surname;
	int salary;
	char pid[11]; //Personal ID
	Date expirationDate; // Contract Expiration Date
	float satisfactionScore; // Companies Satisfaction by current employee
	Seniority seniority;

public:
	void ExtendContract(int y, int m, int d);
	void SetSalary(int s);
	void Promote();
	virtual float EvalateSetisfaction() = 0;
	virtual float EvalateSuccessRate() = 0;
};
