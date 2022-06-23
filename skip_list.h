#pragma once
#include <ios>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstring>
#include <random>

std::mutex mtx;

//class template to implement node.
template<typename K, typename V>
class Node{
public:
	Node() = default;
	Node(K k, V v, int);
	~Node();

	inline K get_key() const;
	inline V get_val() const;
	void set_val(V);

	//Array to hold pointers to next node of different level.
	Node<K, V> **next_node;

private:
	K key;
	V val;
	int _node_level;
};

template<typename K, typename V>
inline K Node<K, V>::get_key() const
{
	return key;
}

template<typename K, typename V>
inline V Node<K, V>::get_val() const
{
	return val;
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

	this->next_node = new Node<K, V> *[_node_level + 1];
	memset(this->next_node, 0, sizeof(Node<K, V>*) * (_node_level + 1));
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
	int erase(K);
	int search(K) const;
	int _get_random_level();
	inline unsigned int size() const;
	inline unsigned int get_level() const;
	void dump_file();

private:
	int _element_count;
	int _max_level;
	int _cur_level;

	std::ofstream _file_writer;
	std::ifstream _file_reader;

	Node<K, V> *_header;
};

//insert element to the skip list.
//if insert successfully, return 0.
//if element exists, return 1.
template<typename K, typename V>
int skip_list<K, V>::insert(const K key, const V val)
{
	mtx.lock();
	Node<K, V> *cur = _header;

	//"update" is the array which put nodes that need to change of different level.
	Node<K, V> *update[_max_level + 1];
	memset(update, 0, sizeof(Node<K, V> *) * (_max_level + 1));

	//from top to bottom
	for (int i = _cur_level; i >= 0; i--)
	{
		while (cur->next_node[i] && cur->next_node[i]->get_key() < key)
		{
			cur = cur->next_node[i];
		}
		update[i] = cur;
	}

	cur = cur->next_node[0];

	//if the key value already exists.
	if (cur && cur->get_key() == key)
	{
		std::cout << "Fail to insert! key:" << key << " exists." << std::endl;
		mtx.unlock();
		return 1;
	}

	if (!cur || cur->get_key() != key)
	{
		int random_level = _get_random_level();

		if (random_level > _cur_level)
		{
			for (int i = _cur_level + 1; i <= random_level; i++)
			{
				update[i] = _header;
			}
			_cur_level = random_level;
		}

		auto insert_node = new Node<K, V>(key, val, _cur_level);

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

//erase element from the skip list.
//if erase successfully, return 0.
//if element does not exists, return 1.
template<typename K, typename V>
int skip_list<K, V>::erase(K key)
{
	mtx.lock();
	Node<K, V> *cur = _header;
	Node<K, V> *update[_max_level + 1];
	memset(update, 0, sizeof(Node<K, V> *) * (_max_level + 1));

	for (int i = _cur_level; i >= 0; i--)
	{
		while (cur->next_node[i] != nullptr && cur->next_node[i]->get_key() < key)
		{
			cur = cur->next_node[i];
		}
		update[i] = cur;
	}

	cur = cur->next_node[0];
	if (cur == nullptr || cur->get_key() != key)
	{
		std::cout << "Fail to erase! key:" << key << " does not exist." << std::endl;
		mtx.unlock();
		return 1;
	}
	else if (cur->get_key() == key)
	{
		for (int i = 0; i <= _cur_level; i++)
		{
			if (update[i]->next_node[i] != cur)
				break;
			update[i]->next_node[i] = cur->next_node[i];
		}

		while (_cur_level > 0 && _header->next_node[_cur_level] == nullptr)
		{
			_cur_level--;
		}

		std::cout << "Successfully erase key:" << key << std::endl;
		_element_count--;
	}

	mtx.unlock();
	return 0;
}

//get val of key.
//if search successfully, return 0.
//if key does not exist, return 1.
template<typename K, typename V>
int skip_list<K, V>::search(K key) const
{
	Node<K, V> *cur = _header;

	for (int i = _cur_level; i >= 0; i--)
	{
		while (cur->next_node[i] && cur->next_node[i]->get_key() < key)
		{
			cur = cur->next_node[i];
		}
	}

	cur = cur->next_node[0];

	if (!cur || cur->get_key() != key)
	{
		std::cout << "Key does not exist!" << std::endl;
		return 1;
	}

	std::cout << "Found key:" << key << ", val:" << cur->get_val() << std::endl;
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
inline unsigned int skip_list<K, V>::size() const
{
	return this->_element_count;
}

template<typename K, typename V>
inline unsigned int skip_list<K, V>::get_level() const
{
	return this->_cur_level;
}

template<typename K, typename V>
void skip_list<K, V>::dump_file()
{
	std::fstream fs;
	fs.open("./test.txt", std::fstream::trunc);

}

template<typename K, typename V>
skip_list<K, V>::skip_list(int max_level)
{
	this->_max_level = max_level;
	this->_cur_level = 0;
	this->_element_count = 0;

	K k;
	V v;
	this->_header = new Node<K, V>(k, v, _max_level);
}

template<typename K, typename V>
skip_list<K, V>::~skip_list()
{
	delete _header;
}