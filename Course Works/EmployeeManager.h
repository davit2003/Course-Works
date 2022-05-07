#pragma once

#include "Employee.h"
#include <vector>
#include <memory>

class EmployeeManager {
private:
	std::vector<Employee*> employees;
public:
	EmployeeManager() {};

	std::unique_ptr<RequestResponse<void*>> Create();
	std::unique_ptr<RequestResponse<void*>> Edit();
	std::unique_ptr<RequestResponse<void*>> Remove();
	void PrintList();
	
	~EmployeeManager();
};