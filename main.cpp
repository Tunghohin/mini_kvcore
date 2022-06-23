#include <iostream>
#include <chrono>
#include <fstream>
#include "skip_list.h"

std::chrono::duration<double> stress_test(skip_list<int, std::string> &list, int test_count)
{
	auto start_time = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < test_count; i++)
	{
		list.insert(rand() % test_count, "aaa");
	}

	for (int i = 0; i < test_count; i++)
	{
		list.search(rand() % test_count);
	}

	auto finish_time = std::chrono::high_resolution_clock::now();
	auto elapsed = finish_time - start_time;

	return elapsed;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	skip_list<int, std::string> l(8);
	const int case_cnt = 10000;
	stress_test(l, case_cnt);
	l.dump_file();
}
