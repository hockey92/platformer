//
// Created by qwerty on 25.09.16.
//

#ifndef PLATFORMER_ITERATOR_H
#define PLATFORMER_ITERATOR_H

#include <map>

template<typename K, typename V>
class Iterator {
public:
    Iterator(std::map<K, V> *_map) : _map(_map), it(_map->begin()) { }

    std::pair<const K, V> *next() { return &(*(it++)); }

    bool hasNext() { return it != _map->end(); }

private:
    typename std::map<K, V>::iterator it;
    std::map<K, V> *_map;
};

#endif //PLATFORMER_ITERATOR_H
