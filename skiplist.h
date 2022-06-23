#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mutex>

#define STORE_DIR "./store/dumpfile"

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

