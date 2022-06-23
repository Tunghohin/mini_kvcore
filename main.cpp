#include <iostream>
#include "skip_list.h"

int main()
{
	skip_list<int, std::string> list(5);

	for (int i = 1; i <= 100; i++)
	{
		int key = 1 + (rand() % 97);
		std::string val = "asdfasdf";

		list.insert(key, val);
	}
	for (int i = 1; i <= 20; i++)
	{
		int key = 1 + (rand() % 97);

		list.erase(key);
	}
}
