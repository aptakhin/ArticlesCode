
#include <functional>
#include <iostream>
#include <typeindex>
#include <vector>
#include "message.h"
#include "delegate.h"

class Messanger
{
private:
	typedef I_DELEGATE<void, const Message&> Receiver;

	struct Subscriber
	{
		int       code;
		void*     object;
		Receiver* method;

		const std::type_info& arg_type;

		Subscriber(int code, void* object, Receiver* method, const std::type_info& arg_type)
		:	code(code),
			object(object),
			method(method),
			arg_type(arg_type)
		{
		}
	};

	typedef std::vector<Subscriber> Subscribers;
	typedef std::vector<Subscriber>::const_iterator SubscribersCI;

public:

	Messanger() {}

	template <class T, class LikeMessage>
	void subscribe(int code, T* object, void (T::* method)(const LikeMessage&))
	{
		void (T::* sign)(const Message&) = (void (T::*)(const Message&))method; // Bdysh!
		const std::type_info& arg_type = typeid(const LikeMessage);
		subscribers_.push_back(Subscriber(code, object, NewDelegate(object, sign), arg_type));
	}

	void send(const Message& msg)
	{
		const std::type_info& arg_type = typeid(msg);
		for (SubscribersCI i = subscribers_.begin(); i != subscribers_.end(); ++i)
		{
			if (i->code == msg.code)
			{
				if (arg_type != i->arg_type)
					throw std::logic_error("Bad message cast");
				i->method->call(msg);
			}
		}
	}

private:

	Subscribers subscribers_;
};

class Printer
{
public:
	void print(const StringMessage& msg)
	{
		std::cout << "Printer received: " << msg.message << std::endl;
	}
};

int main()
{
	Messanger messanger;
	Printer print;
	messanger.subscribe(STRING, &print, &Printer::print);
	messanger.send(StringMessage("Hello, messages!"));
	return 0;
}

