#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstring>

#define STORE_DIR "./store/dumpfile"

//class template to implement node
template<typename K, typename V>
class Node {
public:
	Node() {};

	Node(K k, V v, int lv);

	~Node();

	K get_key() const;

	V get_val() const;

	void set_val(V);

	Node<K, V> **next_node;

	int node_level;

private:
	K key;
	V val;
};

template<typename K, typename V>
K Node<K, V>::get_key() const
{
	return this->key;
}

template<typename K, typename V>
V Node<K, V>::get_val() const
{
	return this->val;
}

template<typename K, typename V>
void Node<K, V>::set_val(V cur_val)
{
	this->val = cur_val;
}

template<typename K, typename V>
Node<K, V>::Node(const K k, const V v, int level)
{
	this->key = k;
	this->val = v;
	this->node_level = level;

	this->next_node = new Node<K, V> *[level + 1];
	memset(next_node, 0, sizeof(Node<K, V>*) * (level + 1));
}

template<typename K, typename V>
Node<K, V>::~Node()
{
	delete []next_node;
}
