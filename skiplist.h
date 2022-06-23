#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstring>

#define STORE_DIR "./store/dumpfile"

std::mutex mtx;

//class template to implement node.
template<typename K, typename V>
class Node{
public:
	Node() {};
	Node(K k, V v, int lv);
	~Node();

	K get_key() const;
	V get_val() const;
	void set_val(V);

	//Array to hold pointers to next node of different level.
	Node<K, V> **next_node;

private:
	K key;
	V val;
	int _node_level;
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
	this->_node_level = level;

	this->next_node = new Node<K, V> *[level + 1];
	memset(next_node, 0, sizeof(Node<K, V>*) * (level + 1));
}

template<typename K, typename V>
Node<K, V>::~Node()
{
	delete []next_node;
}

//class template for skip list.
template<typename K, typename V>
class skiplist{
public:
	explicit skiplist(int);
	~skiplist();

	int insert(K, V);

private:
	int _max_level;
	int _cur_level;

	int _get_random_level();

	Node<K, V> *_header;
	Node<K, V> *create_node(K, V);
};

template<typename K, typename V>
int skiplist<K, V>::insert(const K key, const V val)
{
	mtx.lock();
	Node<K, V> *cur = this->_header;

	//update is the array which put nodes that need to change of different level.
	Node<K, V> *update[this->_max_level];
	memset(update, 0, sizeof(Node<K, V> *) * (_max_level + 1));

	//from top to bottom
	for (int i = _cur_level; i >= 0; i--)
	{
		while (cur->next_node[i] != nullptr && cur->next_node[i]->get_ket() < key)
		{
			cur = cur->next_node[i];
		}
		update[i] = cur;
	}

	cur = cur->next_node[0];

	//if the key value already exists.
	if (cur != nullptr && cur->get_key() == key)
	{
		std::cout << "Fail to insert! key:" << key << " exists." << std::endl;
		mtx.unlock();
		return 1;
	}

	if (cur == nullptr || cur->get_key() != key)
	{
		int random_level = _get_random_level();

		if (random_level > _cur_level)
		{
			for (int i = _cur_level + 1; i <= random_level; i++)
			{
				update[i] = _header;
			}
		}
		_cur_level = random_level;

		Node<K, V>* insert_node = create_node(key, val);
	}
}

template<typename K, typename V>
int skiplist<K, V>::_get_random_level()
{
	int lv = 1;
	while (rand() % 2) {
		lv++;
	}
	lv = std::min(lv, _max_level);
	return lv;
}

template<typename K, typename V>
skiplist<K, V>::skiplist(int max_level)
{
	this->_max_level = max_level;
	this->_cur_level = 0;

	K k = nullptr;
	V v = nullptr;
	this->_header = new Node<K, V>(k, v, _max_level);
}

template<typename K, typename V>
skiplist<K, V>::~skiplist()
{
	delete _header;
}