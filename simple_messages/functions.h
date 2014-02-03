#pragma once

#include <functional>
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include "message.h"

// [http://meh.schizofreni.co/programming/magic/2013/01/23/function-pointer-from-lambda.html]
template <typename Function>
struct function_traits
	: public function_traits<decltype(&Function::operator())>
{};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
{
	typedef ReturnType(*pointer)(Args...);
	typedef std::function<ReturnType(Args...)> function;
};

template <typename ReturnType, typename... Args>
struct function_traits<std::function<ReturnType(Args...)> const>
{
	typedef ReturnType(*pointer)(Args...);
	typedef std::function<ReturnType(Args...)> function;
};

template <typename Function>
typename function_traits<Function>::pointer
to_function_pointer(Function& lambda)
{
	return static_cast<typename function_traits<Function>::pointer>(lambda);
}

class Messanger
{
private:
	typedef std::function<void(const Message&)> Receiver;

	struct Subscriber
	{
		int      code;
		void*    object;
		Receiver call;

		const std::type_index arg_type;

		Subscriber(int code, void* object, Receiver recv, std::type_index arg_type)
		:	code(code),
			object(object),
			call(recv),
			arg_type(arg_type) {}
	};

public:

	Messanger() {}

	template <typename F>
	void subscribe(int code, F func)
	{
		typedef typename function_traits<F>::function FType;
		auto& arg_type = typeid(typename FType::argument_type);
		auto pass = (void(*) (const Message&)) to_function_pointer(func); // Bdysh!
		subscribers_.emplace_back(Subscriber(code, nullptr, pass, arg_type));
	}

	void send(const Message& msg)
	{
		const std::type_index arg_type = typeid(msg);
		for (auto& i: subscribers_)
		{
			if (i.code == msg.code)
			{
				if (arg_type != i.arg_type)
					throw std::logic_error("Bad message cast");
				i.call(msg);
			}
		}
	}

private:
	std::vector<Subscriber> subscribers_;
};
