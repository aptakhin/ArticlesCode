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