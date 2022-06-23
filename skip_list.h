#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstring>
#include <random>

#define STORE_DIR "./store/dumpfile"

std::mutex mtx;

//class template to implement node.
template<typename K, typename V>
class Node{
public:
	Node(K, V, int);
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
	key = k;
	val = v;
	_node_level = level;

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
class skip_list{
public:
	explicit skip_list(int);
	~skip_list();

	int insert(K, V);
	unsigned int size();

private:
	int _element_count;
	int _max_level;
	int _cur_level;

	int _get_random_level();

	Node<K, V> *_header;
};

template<typename K, typename V>
int skip_list<K, V>::insert(const K key, const V val)
{
	mtx.lock();
	Node<K, V> *cur = this->_header;

	//update is the array which put nodes that need to change of different level.
	Node<K, V> *update[this->_max_level];
	memset(update, 0, sizeof(Node<K, V> *) * (_max_level + 1));

	//from top to bottom
	for (int i = _cur_level; i >= 0; i--)
	{
		while (cur->next_node[i] != nullptr && cur->next_node[i]->get_key() < key)
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

		auto insert_node = new Node<K, V>(key, val, random_level);

		for (int i = 0; i <= random_level; i++)
		{
			insert_node->next_node[i] = update[i]->next_node[i];
			update[i]->next_node[i] = insert_node;
		}

		std::cout << "Successfully inserted key:" << key << ", val:" << val << std::endl;
		_element_count++;
	}
	mtx.unlock();
	return 0;
}

template<typename K, typename V>
int skip_list<K, V>::_get_random_level()
{
	int lv = 1;
	while (rand() % 2) {
		lv++;
	}
	lv = std::min(lv, _max_level);
	return lv;
}

template<typename K, typename V>
unsigned int skip_list<K, V>::size()
{
	return this->_element_count;
}

template<typename K, typename V>
skip_list<K, V>::skip_list(int max_level)
{
	_max_level = max_level;
	_cur_level = 0;
	_element_count = 0;

	K k;
	V v;
	this->_header = new Node<K, V>(k, v, _max_level);
}

template<typename K, typename V>
skip_list<K, V>::~skip_list()
{
	delete _header;
}