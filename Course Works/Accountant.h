#pragma once

#include "Employee.h"
#include "RequestResponse.h"
#include <memory>

class Accountant : public Employee {
private:
	int ReportsSubmited;
	int SuccessfulFFNum; //Successful Financial forecasting
	int FFnum; //Financial forecasting
	int ProfitIncrease;
public:
	Accountant() : Employee(), ReportsSubmited(0), SuccessfulFFNum(0), FFnum(0), ProfitIncrease(0){}
	
	Accountant(std::string name, std::string surname, int salary, unsigned long long pid, Date expirationDate, Seniority seniority):
		Employee(name, surname, salary, pid, expirationDate, seniority),
		ReportsSubmited(0), SuccessfulFFNum(0), FFnum(0), ProfitIncrease(0){}
	
	Accountant(std::string name, std::string surname, int salary, unsigned long long pid, Date expirationDate, Seniority seniority, int reportsSub, int succFF, int FF, int profitInc) :
		Employee(name, surname, salary, pid, expirationDate, seniority),
		ReportsSubmited(reportsSub), SuccessfulFFNum(succFF), FFnum(FF), ProfitIncrease(profitInc) {}

	int GetReportsSubmited();
	int GetSuccessfulFFNum();
	int GetFFnum();
	int GetProfitIncrease();

	std::unique_ptr<RequestResponse<void*>> SubmitReport();
	std::unique_ptr<RequestResponse<void*>> SubmitFF();
	std::unique_ptr<RequestResponse<void*>> FFSucceeded();
	std::unique_ptr<RequestResponse<void*>> IncreaseProfit(int p);

	float EvaluateWorkLoad() const override;
};