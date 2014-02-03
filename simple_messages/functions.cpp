
#include "functions.h"

int main()
{
	Messanger messanger;

	messanger.subscribe(STRING, [](const StringMessage& msg)
	{
		std::cout << "Received (1): " << msg.message << std::endl;
	});

	std::function<void (const StringMessage& msg)> func = [](const StringMessage& msg)
	{
		std::cout << "Received (2): " << msg.message << std::endl;
	};
	messanger.subscribe(STRING, func);

	messanger.send(StringMessage("Hello, messages!"));
	return 0;
}

