#pragma once

#include "ErrorCode.h"
#include <string>

template <typename T>
class RequestResponse {
public:
	ErrorCode errorCode;
	std::string errorMessage;
	T response;
	RequestResponse() {}
};

template <typename T>
class SuccessfulResponse : public RequestResponse<T> {
public:
	SuccessfulResponse() {
		this->errorCode = ErrorCode::SuccessfulRequest;
	}
	SuccessfulResponse(T data) {
		this->errorCode = ErrorCode::SuccessfulRequest;
		this->response = data;
	}
};

template <typename T>
class InvalidResponse : public RequestResponse<T> {
public:
	InvalidResponse() {
		this->errorCode = ErrorCode::InvalidRequest;
	}
	InvalidResponse(std::string message) {
		this->errorCode = ErrorCode::InvalidRequest;
		this->errorMessage = message;
	}
};