#include <iostream>
#include <chrono>
#include "skip_list.h"
#include <map>

skip_list<int, std::string> SkipList(8);

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
	int T = 100;
	std::map<int, int> num_cnt;
	while (T--)
	{
		num_cnt[SkipList._get_random_level()]++;
	}

	for (auto i : num_cnt)
	{
		std::cout << "NUM: " << i.first << " cnt: " << i.second << '\n';
	}
}
