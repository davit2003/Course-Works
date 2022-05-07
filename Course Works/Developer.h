#pragma once

#include <vector>
#include <memory>
#include "Employee.h"

class Developer : public Employee {
private:
	std::vector<std::string> finishedProjects;
	std::vector<std::string> currentProjects;
	int answeredTickets;
	int currentTickets;
	int bonus; //Bonus for each Project
public:
	Developer();

	Developer(std::string name, std::string surname, int salary, unsigned long long pid, Date expirationDate, Seniority seniority):
		Employee(name, surname, salary, pid, expirationDate, seniority) {}

	Developer(std::string name, std::string surname, int salary, unsigned long long pid, Date expirationDate, Seniority seniority, std::vector<std::string> finished_projects, std::vector<std::string> current_projects, int answered_tickets, int current_tickets, int bonus) :
		Employee(name, surname, salary, pid, expirationDate, seniority) {
		finishedProjects = finished_projects;
		currentProjects = current_projects;
		answeredTickets = answered_tickets;
		currentTickets = current_tickets;
		bonus = bonus;
	}

	std::string GetFinishedProjects();
	std::string GetCurrentProjects();
	int GetAnsweredTickets();
	int GetCurrentTickets();
	int GetBonus();

	std::unique_ptr<RequestResponse<void*>> FinishProject(int);
	std::unique_ptr<RequestResponse<void*>> NewProject(std::string);
	std::unique_ptr<RequestResponse<void*>> AnswerTicket();
	std::unique_ptr<RequestResponse<void*>> AddTicket();
	std::unique_ptr<RequestResponse<void*>> SetProjectBonus(int);

	float EvaluateWorkLoad() const override;
};