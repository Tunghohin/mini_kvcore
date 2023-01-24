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

namespace mini 
{

std::mutex mtx;

//class template to implement node.
template<typename K, typename V>
class Node
{
public:
	Node() = default;
	Node(K const, V const, int);
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

template<typename K, typename V>
Node<K, V>::Node(K const key, V const val, int level)
{
	this->m_key = key;
	this->m_val = val;
	this->m_node_level = level;
	
	this->next_node = std::make_shared<Node>(new std::shared_ptr<Node>[m_node_level + 1]);
	for (int i = 0; i < m_node_level + 1; i++)
	{
		this->next_node[i] = std::make_shared<Node>();
	}
}

template<typename K, typename V>
inline K Node<K, V>::get_key() const
{
	return this->m_key;
}

template<typename K, typename V>
inline V Node<K, V>::get_val() const
{
	return this->m_val;
}

template<typename K, typename V>
void Node<K, V>::set_val(V cur_val)
{
	this->m_val = cur_val;
}

//class template for skip list.
template<typename K, typename V>
class skip_list
{

};

}
