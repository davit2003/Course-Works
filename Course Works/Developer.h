#pragma once

#include <vector>
#include <string>
#include "Employee.h"

class Developer : Employee {
private:
	std::vector<std::string> FinishedProjects;
	std::vector<std::string> CurrentProjects;
	int AnsweredTickets;
	int CurrentTickets;
	int Bonus; //Bonus for each Project
public:
	void FinishProject();
	void NewProject(std::string p);
	void AnswerTicket();
	void AddTicket();
	void SetProjectBonus(int b);
};