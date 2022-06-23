#include <iostream>
#include <chrono>
#include "skip_list.h"

skip_list<int, std::string> SkipList(18);

std::chrono::duration<double> stress_test(skip_list<int, std::string> &list, int test_count)
{
	auto start_time = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < test_count; i++)
	{
		list.insert(rand() % test_count, "aaa");
	}

	auto finish_time = std::chrono::high_resolution_clock::now();
	auto elapsed = finish_time - start_time;

	return elapsed;
}

int main()
{
	std::cout << stress_test(SkipList, 100000).count() << std::endl;
}
