#ifndef NATIVE_ACTIVITY_MAPWRAPPER_H
#define NATIVE_ACTIVITY_MAPWRAPPER_H

#include <map>
#include "Iterator.h"

template<typename K, typename V>
class Map {
public:
    V *put(K key, V value);

    V *get(K key);

    bool contains(K key);

    bool remove(K key);

    std::map<K, V> *getPtr();

    Iterator<K, V> getIterator();

private:
    std::map<K, V> _map;
};

template<typename K, typename V>
Iterator<K, V> Map<K, V>::getIterator() {
    return Iterator<K, V>(&_map);
}

template<typename K, typename V>
V *Map<K, V>::put(K key, V value) {
    return &(_map.insert(std::pair<K, V>(key, value)).first->second);
}

template<typename K, typename V>
bool Map<K, V>::contains(K key) {
    return _map.find(key) != _map.end();
}

template<typename K, typename V>
bool Map<K, V>::remove(K key) {
    typename std::map<K, V>::iterator pos = _map.find(key);
    if (pos == _map.end()) {
        return false;
    }
    _map.erase(pos);
    return true;
}

template<typename K, typename V>
V *Map<K, V>::get(K key) {
    typename std::map<K, V>::iterator pos = _map.find(key);
    if (pos == _map.end()) {
        return NULL;
    }
    return &(pos->second);
}

template<typename K, typename V>
std::map<K, V> *Map<K, V>::getPtr() {
    return &_map;
};

#endif //NATIVE_ACTIVITY_MAPWRAPPER_H
