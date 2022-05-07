#include "MarketingManager.h"


int MarketingManager::GetSuccessfulStrategyNum() {
	return successfulStrategyNum;
}
int MarketingManager::GetStrategyNum() {
	return strategyNum;
}
double MarketingManager::GetPublicScore() {
	return publicScore;
}

std::unique_ptr<RequestResponse<void*>> MarketingManager::MakeStrategy() {
	std::unique_ptr <RequestResponse <void*>> res;
	if (strategyNum == INT_MAX)
		res.reset(new InvalidResponse<void*>("Strategy limit reached"));
	else {
		strategyNum++;
		res.reset(new SuccessfulResponse<void*>());
	}
	return res;
}

std::unique_ptr<RequestResponse<void*>> MarketingManager::StrategySucceeded() {
	std::unique_ptr <RequestResponse <void*>> res;

	if (strategyNum == 0)
		res.reset(new InvalidResponse<void*>("No strategies"));
	else {
		successfulStrategyNum++;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

std::unique_ptr<RequestResponse<void*>> MarketingManager::SetPublicScore(double pubScore) {
	std::unique_ptr <RequestResponse <void*>> res;

	if (pubScore < 0 || pubScore > 10)
		res.reset(new InvalidResponse<void*>("Score is out of range"));
	else {
		publicScore = pubScore;
		res.reset(new SuccessfulResponse<void*>());
	}

	return res;
}

float MarketingManager::EvaluateWorkLoad() const{
	if (strategyNum == 0)
		return 0;
	return (float)successfulStrategyNum / (float)strategyNum;
}