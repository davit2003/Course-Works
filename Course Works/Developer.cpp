#include "Developer.h"
#include "RequestResponse.h"

Developer :: Developer() : Employee() {
	answeredTickets = 0;
	currentTickets = 0;
	bonus = 0;
}

std::string Developer::GetFinishedProjects() {
	std::string res;
	for (int i = 0; i < finishedProjects.size(); i++)
		res += finishedProjects[i] + "\n";
	return res;
}

std::string Developer::GetCurrentProjects() {
	std::string res;
	for (int i = 0; i < currentProjects.size(); i++)
		res += currentProjects[i] + "\n";
	return res;
}

int Developer::GetAnsweredTickets() {
	return answeredTickets;
}

int Developer::GetBonus() {
	return bonus;
}

int Developer::GetCurrentTickets() {
	return currentTickets;
}


std::unique_ptr<RequestResponse<void*>> Developer::FinishProject(int index) {
	std::unique_ptr <RequestResponse <void*>> res;

	if (index < 0 || index > currentProjects.size())
		res.reset(new InvalidResponse<void*>("Index is out of bounds"));
	else {
		finishedProjects.push_back(currentProjects[index]);
		currentProjects.erase(currentProjects.begin() + index);

		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

std::unique_ptr<RequestResponse<void*>> Developer::NewProject(std::string project) {
	std::unique_ptr <RequestResponse <void*>> res;
	if (currentProjects.size() == currentProjects.max_size())
		res.reset(new InvalidResponse<void*>("Vector is full"));
	else {
		currentProjects.push_back(project);
		res.reset(new SuccessfulResponse<void*>());
	}
	return res;
}

std::unique_ptr<RequestResponse<void*>> Developer::AnswerTicket() {
	std::unique_ptr <RequestResponse <void*>> res;

	if (currentTickets == 0)
		res.reset(new InvalidResponse<void*>("No Tickets"));
	else {
		answeredTickets++;
		currentTickets--;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

std::unique_ptr<RequestResponse<void*>> Developer::AddTicket() {
	std::unique_ptr <RequestResponse <void*>> res;

	if (currentTickets == INT_MAX)
		res.reset(new InvalidResponse<void*>("Tickets limit reached"));
	else {
		currentTickets++;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

std::unique_ptr<RequestResponse<void*>> Developer::SetProjectBonus(int bonus) {
	std::unique_ptr <RequestResponse <void*>> res;

	if (bonus < 0)
		res.reset(new InvalidResponse<void*>("Amount Invalid"));
	else {
		bonus = bonus;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}
float Developer::EvaluateWorkLoad() const{
	float finp = finishedProjects.size(), currp = currentProjects.size();
	
	if (finp == 0 || answeredTickets == 0)
		return 0;

	return (float)answeredTickets / (currentTickets + answeredTickets) + finp / (finp + currp);
}