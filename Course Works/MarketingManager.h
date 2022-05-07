#pragma once

#include <memory>
#include "RequestResponse.h"
#include "Employee.h"

class MarketingManager : public Employee {
private:
	int successfulStrategyNum;
	int strategyNum;
	double publicScore;
public:
	MarketingManager() : Employee(), successfulStrategyNum(0), strategyNum(0), publicScore(0) {}
	MarketingManager(std::string name, std::string surname, int salary, unsigned long long pid, Date expirationDate, Seniority seniority)
		: Employee(name, surname, salary, pid, expirationDate, seniority) {}
	MarketingManager(std::string name, std::string surname, int salary, unsigned long long pid, Date expirationDate, Seniority seniority, int successful_strategy_num, int strategy_num, int public_score)
		: Employee(name, surname, salary, pid, expirationDate, seniority), successfulStrategyNum(successful_strategy_num), strategyNum(strategy_num), publicScore(public_score) {}

	int GetSuccessfulStrategyNum();
	int GetStrategyNum();
	double GetPublicScore();

	std::unique_ptr<RequestResponse<void*>> MakeStrategy();
	std::unique_ptr<RequestResponse<void*>> StrategySucceeded();
	std::unique_ptr<RequestResponse<void*>> SetPublicScore(double);


	float EvaluateWorkLoad() const override;
};
