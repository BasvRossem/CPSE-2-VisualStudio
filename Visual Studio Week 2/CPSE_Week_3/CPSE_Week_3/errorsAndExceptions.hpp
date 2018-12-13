#pragma once
#include <iostream>
#include <string>

class errorLogger {
private:
	std::ofstream myLog;
public:
	errorLogger(std::string errorFile) {
		myLog.open(errorFile);
	}
};

