#include <iostream>
#include <chrono>
#include <fstream>
#include "skip_list.h"

template<typename K, typename V>
std::chrono::duration<double> stress_test(skip_list<K, V> &list, int test_count)
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

template<typename K, typename V>
double get_QPS(skip_list<K, V> &list, int test_count)
{
	return (double)test_count * 2.0 / stress_test(list, test_count).count();
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	skip_list<int, std::string> l(10);
	const int case_cnt = 1000000;
	std::cout << get_QPS(l, case_cnt) << std::endl;

	l.dump_file();
}
