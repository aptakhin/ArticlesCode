#include <string>
#include <functional>
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <chrono>
#include "functions.h"

class StringMessenger
{
private:
	typedef std::function<void(const StringMessage&)> Receiver;

	struct Subscriber
	{
		int      code;
		Receiver recv;

		Subscriber(int code, Receiver recv)
		:	code(code),
			recv(recv)
		{
		}
	};

	typedef std::vector<Subscriber> Subscribers;

public:

	StringMessenger() {}

	void subscribe(int code, Receiver& recv)
	{
		subscribers_.emplace_back(Subscriber(code, recv));
	}

	void send(const StringMessage& msg)
	{
		for (auto& i: subscribers_)
		{
			if (i.code == msg.code)
				i.recv(msg);
		}
	}

private:
	Subscribers subscribers_;
};

int main()
{
	Messenger messanger;
	std::function<void(const StringMessage&)> func = [](const StringMessage& msg){};
	messanger.subscribe(STRING, [](const StringMessage& msg){});

	StringMessenger str_messanger;
	str_messanger.subscribe(STRING, func);

	double ratio_avg = 0;
	double ratio_sum = 0;
	int    ratio_num = 0;

	const int Tests = 5000000;

	StringMessage test_message("Hello, messages!");

	while (true)
	{
		using std::chrono::duration_cast;
		using std::chrono::milliseconds;
		using std::chrono::steady_clock;

		auto start1 = steady_clock::now();
		for (int i = 0; i < Tests; ++i)
			messanger.send(test_message);
		auto end1   = std::chrono::steady_clock::now();

		auto time1  = duration_cast<milliseconds>(end1 - start1).count();
		std::printf("Msg: %5d ms\n", time1);

		auto start2 = steady_clock::now();
		for (int i = 0; i < Tests; ++i)
			str_messanger.send(test_message);
		auto end2   = std::chrono::steady_clock::now();
		auto time2  = duration_cast<milliseconds>(end2 - start2).count();
		std::printf("Str: %5d ms\n", time2);
				
		double ratio = double(time1) / time2;
		std::printf("Ratio: %.1lf\n", ratio);
		ratio_sum += ratio;
		++ratio_num;
		ratio_avg = ratio_sum / ratio_num;
		std::printf("Ratio avg: %.1lf (%d)\n", ratio_avg, ratio_num);
	}

	return 0;
}
