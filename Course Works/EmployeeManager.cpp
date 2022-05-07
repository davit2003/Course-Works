#include <iostream>
#include <string>
#include "EmployeeManager.h"
#include "Developer.h"
#include "Accountant.h"
#include "MarketingManager.h"

std::unique_ptr<RequestResponse<void*>> EmployeeManager::Create() {
	std::string name, surname, message;
	int salary, y, m, d, sen;
	unsigned long long pid;
	Date expDate;
	Seniority seniority;


	std::cout << "Input Name \n";
	std::cin >> name;
	
	std::cout << "Input Last Name \n";
	std::cin >> surname;

	std::cout << "Input Salary \n";
	std::cin >> salary;

	std::cout << "Input Personal ID \n";
	std::cin >> pid;

	std::cout << "Input Contract Expiration Date (format: year month day) \n";
	std::cin >> y >> m >> d;
	
	auto resp = expDate.SetDate(y, m, d);
	if (resp.get()->errorCode == ErrorCode::InvalidRequest) {
		message = resp.get()->errorMessage;
		goto ret;
	}

	std::cout << "Choose Seniority: \n 1. Intern \n 2. Junior \n 3. Middle \n 4. Senior \n";
	std::cin >> sen;

	switch (sen) {
	case 1:
		seniority = Seniority::Intern;
		break;
	case 2:
		seniority = Seniority::Junior;
		break;
	case 3:
		seniority = Seniority::Middle;
		break;
	case 4:
		seniority = Seniority::Senior;
		break;
	default:
		message = "Invalid Seniority Request";
		goto ret;
	}


	std::cout << "Choose Employee Type: \n 1. Developer \n 2. Accountant \n 3. Marketing Manager \n";
	int emptype;
	std::cin >> emptype;

	switch (emptype) {
	case 1:
		employees.push_back(new Developer(name, surname, salary, pid, expDate, seniority));
		break;
	case 2:
		employees.push_back(new Accountant(name, surname, salary, pid, expDate, seniority));
		break;
	case 3:
		employees.push_back(new MarketingManager(name, surname, salary, pid, expDate, seniority));
		break;
	default:
		return std::unique_ptr <RequestResponse <void*>> (new InvalidResponse<void*>("Invalid Request"));
		break;
	}
	
	ret:
		if(message != "")
			return std::unique_ptr <RequestResponse <void*>>(new InvalidResponse<void*>(message));
		return std::unique_ptr <RequestResponse <void*>>(new SuccessfulResponse<void*>());
}

std::unique_ptr<RequestResponse<void*>> EmployeeManager::Edit() {
	int ind;
	std::cout << "Input Employee Index You Want to Edit:\n";
	std::cin >> ind;
	ind--;

	if (ind >= 0 && ind < employees.size()) {
		std::cout << "Choose an Option: \n 1. Extend Contract \n 2. Cancel Contract \n 3. Set Salary \n 4. Promote \n";
		
		int opt, limit;
		std::string typ = typeid(*employees[ind]).name();
		typ = typ.substr(6);
		if (typ == "Developer") {
			std::cout << " 5. Finish Project \n 6. New Project \n 7. Answer Ticket \n 8. Add Ticket \n 9. Set Project Bonus \n";
			limit = 9;
		}
		else if (typ == "Accountant") {
			std::cout << " 5. Submit Report \n 6. Submit Financial Forecasting \n 7. Add Successful Financial Forecasting \n 8. Set Increased Profit \n";
			limit = 8;
		}
		else {
			std::cout << " 5. Make Strategy \n 6. Add Successful Strategy \n 7. Set Public Score \n";
			limit = 7;
		}

		std::cin >> opt;

		auto res = std::unique_ptr <RequestResponse <void*>>();
		if(opt < 1 || opt > limit)
			return std::unique_ptr <RequestResponse <void*>>(new InvalidResponse<void*>("Option"));
		else if (opt < 5) {
			if (opt == 1) {
				std::cout << "Input extension period format: (y, m, d)\n";
				int y, m, d;
				std::cin >> y >> m >> d;
				res = employees[ind]->ExtendContract(y, m, d);
			}
			else if (opt == 2)
				res = employees[ind]->CancelContract();
			else if (opt == 3) {
				std::cout << "Input new salary\n";
				int s;
				std::cin >> s;
				res = employees[ind]->SetSalary(s);
			}
			else 
				res = employees[ind]->Promote();
		}
		else if (typ == "Developer") {
			auto Dev = dynamic_cast<Developer*>(employees[ind]);
			if (opt == 5) {
				std::cout << "Which Project you want to finish\n";
				int s;
				std::cin >> s;
				res = Dev->FinishProject(s);
			}
			else if (opt == 6) {
				std::cout << "Input New Project Name\n";
				std::string p;
				std::cin >> p;
				res = Dev->NewProject(p);
			}
			else if (opt == 7)
				res = Dev->AddTicket();
			else if (opt == 8)
				res = Dev->AnswerTicket();
			else {
				std::cout << "Input Project Bonus\n";
				int s;
				std::cin >> s;
				res = Dev->SetProjectBonus(s);
			}
		}
		else if (typ == "Accountant") {
			auto Acc = dynamic_cast<Accountant*>(employees[ind]);
			if (opt == 5)
				res = Acc->SubmitReport();
			else if (opt == 6)
				res = Acc->SubmitFF();
			else if (opt == 7)
				res = Acc->FFSucceeded();
			else {
				std::cout << "Input Public Score\n";
				int s;
				std::cin >> s;
				res = Acc->IncreaseProfit(s);
			}
		}
		else {
			auto mm = dynamic_cast<MarketingManager*>(employees[ind]);
			if (opt == 5)
				res = mm->MakeStrategy();
			else if (opt == 6)
				res = mm->StrategySucceeded();
			else {
				std::cout << "Input Profit from Financial Forecast\n";
				int s;
				std::cin >> s;
				res = mm->SetPublicScore(s);
			}
		}
		return res;

	}
	return std::unique_ptr <RequestResponse <void*>>(new InvalidResponse<void*>("Index out of range"));
}

std::unique_ptr<RequestResponse<void*>> EmployeeManager::Remove() {
	int ind;
	std::cout << "Input Employee Index You Want to Fire:\n";
	std::cin >> ind;

	if (ind > 0 && ind <= employees.size()) {
		delete employees[ind - 1];
		employees.erase(employees.begin() + ind - 1);
		return std::unique_ptr <RequestResponse <void*>>(new SuccessfulResponse<void*>());
	}
	return std::unique_ptr <RequestResponse <void*>>(new InvalidResponse<void*>("Index out of range"));
}

void EmployeeManager::PrintList() {
	for (int i = 0; i < employees.size(); i++) {
		std::string Pos = typeid(*employees[i]).name();
		Pos = Pos.substr(6);

		std::cout << "(" << i + 1 << ") " << employees[i]->GetName() << " " << employees[i]->GetSurname() << std::endl;
		std::cout << "Personal ID: " << employees[i]->GetPID() << std::endl;
		std::cout << "Position: " << Pos << std::endl;
		std::cout << "Contract Expiration Date: " << employees[i]->GetExpirationDate().Format() << std::endl;
		std::cout << "Salary: " << employees[i]->GetSalary() << std::endl;
		
		std::cout << "Seniority: ";
		switch (employees[i]->GetSeniority()) {
		case Seniority::Intern: std::cout << "Intern" << std::endl; break;
		case Seniority::Junior: std::cout << "Junior" << std::endl; break;
		case Seniority::Middle: std::cout << "Middle" << std::endl; break;
		case Seniority::Senior: std::cout << "Senior" << std::endl; break;
		}

		if (Pos == "Developer") {
			auto Dev = dynamic_cast<Developer*>(employees[i]);
			std::cout << "Finished Projects: \n" << Dev->GetFinishedProjects() << std::endl;
			std::cout << "Current Projects: \n " << Dev->GetCurrentProjects() << std::endl;
			std::cout << "Answered Tickets: " << Dev->GetAnsweredTickets() << std::endl;;
			std::cout << "Current Tickets: " << Dev->GetCurrentTickets() << std::endl;
			std::cout << "Bonus from a Project: " << Dev->GetBonus() << std::endl;
		}
		else if (Pos == "Accountant") {
			auto Acc = dynamic_cast<Accountant*>(employees[i]);
			std::cout << "Reports Submited: " << Acc->GetReportsSubmited() << std::endl;
			std::cout << "Number of Financial Forecast Made: " << Acc->GetFFnum() << std::endl;
			std::cout << "Number of Successful Financial Forecast Made: " << Acc->GetSuccessfulFFNum() << std::endl;
			std::cout << "Profit Made by Company: " << Acc->GetProfitIncrease() << std::endl;
		}
		else {
			auto mm = dynamic_cast<MarketingManager*>(employees[i]);
			std::cout << "Number of Strategies Made: " << mm->GetStrategyNum() << std::endl;
			std::cout << "Number of Successful Strategies Made: " << mm->GetSuccessfulStrategyNum() << std::endl;
			std::cout << "Public Score: " << mm->GetPublicScore() << std::endl;
		}

		std::cout << "WorkLoad: " << employees[i]->EvaluateWorkLoad() << std::endl;
	}
}

EmployeeManager::~EmployeeManager() {
	for (auto obj : employees)
		delete obj;
}