// exceptions.h
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class Exception{
	std::string reason;
public:
	Exception();
	Exception(std::string reason);
	std::string why();
};
class InvalidTarget : public Exception{
public:
	InvalidTarget();
	InvalidTarget(std::string reason);
};

class NoEffect : public Exception{
public:
	NoEffect();
	NoEffect(std::string reason);
};

class InvalidMove : public Exception{
public:
	InvalidMove();
	InvalidMove(std::string reason);
};
#endif

