#pragma once
#include <exception>
#include <string>

class endOfFile : public std::exception {
public:
	const char * what() const override {
		return "End of file found\n";
	}
};

class unknownColor : public std::exception {
private:
	std::string s; 
public:
	unknownColor(const std::string & name) :
		s{ std::string{ "unknown color [" } + name + "]" }
	{}
	
	const char * what() const override {
		return s.c_str();
	}
};

class unknownName : public std::exception {
private:
	std::string s;
public:
	unknownName(const std::string & name) :
		s{ std::string{ "unknown name [" } +name + "]" }
	{}

	const char * what() const override {
		return s.c_str();
	}
};

class unknownShape : public std::exception {
private:
	std::string s;
public:
	unknownShape(const std::string & shape) :
		s{ std::string{ "unknown shape [" } +shape + "]" }
	{}

	const char * what() const override {
		return s.c_str();
	}
};

class wrongCoordinate : public std::exception {
private:
	std::string s;
public:
	wrongCoordinate(const std::string & coordinate) :
		s{ std::string{ "Wrong coordinate [" } +coordinate + "]" }
	{}

	const char * what() const override {
		return s.c_str();
	}
};

class wrongCharacter : public std::exception {
private:
	std::string s;
public:
	wrongCharacter(const char & character) :
		s{ std::string{ "Wrong character [" } + character + "]" }
	{}

	const char * what() const override {
		return s.c_str();
	}
};

class notAFloat : public std::exception {
private:
	std::string s;
public:
	notAFloat(const char & character) :
		s{ std::string{ "Not a float: [" } +character + "]" }
	{}

	const char * what() const override {
		return s.c_str();
	}
};

class incorrectPicture : public std::exception {
private:
	std::string s;
public:
	incorrectPicture(std::string & picture) :
		s{ std::string{ "Incorrect picture file: [" } +picture + "]" }
	{}

	const char * what() const override {
		return s.c_str();
	}
};
