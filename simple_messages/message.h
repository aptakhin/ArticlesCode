#pragma once
#include <string>

class Message
{
public:
	Message(unsigned code) : code(code) {}

	virtual ~Message() {}

	const unsigned code;
};

enum Code
{
	STRING = 1
};

class StringMessage : public Message
{
public:
	StringMessage(const std::string& msg) : Message(STRING), message(msg) {}

	const std::string message;
};

template <class Base, class Derived>
bool is_sliced(const Derived* der)
{
	return (void*) der != (const Base*) der;
}