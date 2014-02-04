
#include "functions.h"

int main()
{
	Messenger messenger;

	messenger.subscribe(STRING, [](const StringMessage& msg)
	{
		std::cout << "Received (1): " << msg.message << std::endl;
	});

	std::function<void (const StringMessage& msg)> func = [](const StringMessage& msg)
	{
		std::cout << "Received (2): " << msg.message << std::endl;
	};
	messenger.subscribe(STRING, func);

	messenger.send(StringMessage("Hello, messages!"));
	return 0;
}

