#pragma once
#include <ios>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstring>
#include <random>
#include <array>
#include <memory>

std::mutex mtx;

//class template to implement node.
template<typename K, typename V>
class Node{
public:
	Node() = default;
	Node(K k, V v, int);
	~Node() = default;

	inline K get_key() const;
	inline V get_val() const;
	void set_val(V);

	//Array to hold pointers to next node of different level.
	std::shared_ptr<std::shared_ptr<Node>[]> next_node = nullptr;

private:
	K m_key;
	V m_val;
	int m_node_level = 0;
};