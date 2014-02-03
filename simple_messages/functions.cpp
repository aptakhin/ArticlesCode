
#include "functions.h"

int main()
{
	Messanger messanger;

	messanger.subscribe(STRING, [](const StringMessage& msg)
	{
		std::cout << "Received: " << msg.message << std::endl;
	});

	messanger.send(StringMessage("Hello, messages!"));
	return 0;
}

