#include "Accountant.h"

int Accountant::GetReportsSubmited() {
	return ReportsSubmited;
}

int Accountant::GetSuccessfulFFNum() {
	return SuccessfulFFNum;
}

int Accountant::GetFFnum() {
	return FFnum;
}

int Accountant::GetProfitIncrease() {
	return ProfitIncrease;
}

std::unique_ptr<RequestResponse<void*>> Accountant::SubmitReport() {
	std::unique_ptr <RequestResponse <void*>> res;

	if (ReportsSubmited == INT_MAX)
		res.reset(new InvalidResponse<void*>("Reports limit reached"));
	else {
		ReportsSubmited++;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

std::unique_ptr<RequestResponse<void*>> Accountant::SubmitFF() {
	std::unique_ptr <RequestResponse <void*>> res;

	if (FFnum == INT_MAX)
		res.reset(new InvalidResponse<void*>("Financial forecasting limit reached"));
	else {
		FFnum++;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

std::unique_ptr<RequestResponse<void*>> Accountant::FFSucceeded() {
	std::unique_ptr <RequestResponse <void*>> res;

	if (SuccessfulFFNum == INT_MAX)
		res.reset(new InvalidResponse<void*>("Successful Financial forecasting limit reached"));
	else {
		SuccessfulFFNum++;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

std::unique_ptr<RequestResponse<void*>> Accountant::IncreaseProfit(int p) {
	ProfitIncrease += p;
	return std::unique_ptr <RequestResponse <void*>>(new SuccessfulResponse<void*>());
}

float Accountant::EvaluateWorkLoad() const{
	if (SuccessfulFFNum == 0)
		return 0;

	return (float)SuccessfulFFNum / FFnum;
}