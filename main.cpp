#include <iostream>
#include "skip_list.h"

int main()
{
	skip_list<int, std::string> sl(5);
	sl.insert(1, "asdf");
	sl.insert(1, "adsssf");


}
