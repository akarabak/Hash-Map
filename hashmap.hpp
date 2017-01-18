// ICS/CSE 46 Summer 2015
// Project 2
//
// This file is where you will implement your hash map. Do not
// change the public function headers. Your hash map must dynamically
// resize and must use separate chaining. You may not use any data
// structures from the standard library in this file.
//
#ifndef __HASHMAP_HPP__
#define __HASHMAP_HPP__
#define INITIAL_CAPACITY 10
#include <iostream>
#include <functional>

// A simple node struct for your separate chaining
// You may change this if you want
template <class K,class V>
struct KVNode
{
    K key;
    V value;
    KVNode<K,V>* next;
};

template <class K, class V>
class HashMap {
    public:
        // Default constructor: creates an empty hash map
        HashMap();
        // Constructor setting the default value for our map
        HashMap(V value);
        // Destructor: deallocates all memory associated
        // with the hash map
        ~HashMap();
        // size() returns the number of elements currently
        // stored in the hash map.
        unsigned int size() const;
        // set() inserts the given key value pair into the
        // hash map.  If the key is already in the map, then
        // the value for that key is overwritten.
        void set(const K& key, const V& value);
        // get() returns the value associated with the key.
        // If the key is not in the hash map, the default
        // value should be returned.
        V get(const K& key) const;
    private:
        // You are allowed to add any private variables you 
        // need to implement the functionality of a hash map
        // It is also okay to add addional public or private
        // methods you need, but you may not change the 
        // already existing method signatures.

        // You may find these private members useful, but you are
        // not required to use them.
        KVNode<K,V>** map;
        // To use this hash map with your own key type,
        // you may need to provide a specialization of std::hash.
        std::hash<K> hash;
        // This is the default value to return if a key is not
        // in the hash map
        V default_value;


        int sizeOfMap; //number of different elements on hash map + nodes
        int capacity; //capacity of current hash map
        const double loadFactor = 0.75;
};

template <class K, class V>
HashMap<K, V>::HashMap() : default_value()
{
	//TODO: Implement this method
	capacity = INITIAL_CAPACITY;
	sizeOfMap = 0;
	map = new KVNode<K, V>*[capacity]{};
}

template <class K, class V>
HashMap<K, V>::HashMap(V value)
{
	//TODO: Implement this method
	capacity = INITIAL_CAPACITY;
	sizeOfMap = 0;
	map = new KVNode<K, V>*[capacity]{};
	default_value = value;

}

template <class K, class V>
HashMap<K, V>::~HashMap()
{
	//TODO: Implement this method
	for (int i = 0; i < capacity; i++)
	{
		KVNode<K, V>* pointer = map[i];
		KVNode<K, V>* temp;
		while (pointer != nullptr)
		{
			temp = pointer->next;
			delete pointer;
			pointer = temp;
		}
	}
	delete [] map;
}

template <class K, class V>
unsigned int HashMap<K, V>::size() const
{
	//TODO: Implement this method
	return sizeOfMap;
}

template <class K, class V>
void HashMap<K, V>::set(const K& key, const V& value)
{
	//TODO: Implement this method
	if (((double)sizeOfMap / capacity) >= loadFactor)
	{
		KVNode<K, V>** temp = new KVNode<K, V>*[capacity*2]{};
		for (int i = 0; i < capacity; i++)
		{
			KVNode<K, V>* pointer = map[i];
			KVNode<K, V>* tempPointer;
			while (pointer != nullptr)
			{
				tempPointer = pointer->next;
				int hashValue = hash(pointer->key) % (capacity * 2);
				temp[hashValue] = new KVNode<K, V>{pointer->key, pointer->value, temp[hashValue] };
				delete pointer;
				pointer = tempPointer;
			}
		}
		capacity *= 2;
		delete [] map;
		map = temp;
	}

	int hashValue = hash(key) % capacity;
	bool wasNotKey = true;
	KVNode<K, V>* pointer = map[hashValue];
	while (pointer != nullptr)
	{
		if (pointer->key == key)
		{
			pointer->value = value;
			wasNotKey = false;
			break;
		}
		pointer = pointer->next;
	}
	if (wasNotKey)
	{
		map[hashValue] = new KVNode<K, V>{ key, value, map[hashValue] };
		sizeOfMap++;
	}
	
}


template <class K, class V>
V HashMap<K, V>::get(const K& key) const
{
	//TODO: Implement this method
	int hashValue = hash(key) % capacity;
	KVNode<K,V>* pointer = map[hashValue];
	while(pointer != nullptr)
	{
		if(pointer->key == key)
			return pointer->value;
		pointer = pointer->next;
	}
	return default_value;
}



#endif // __HASHMAP_HPP__
