#ifndef NATIVE_ACTIVITY_MAPWRAPPER_H
#define NATIVE_ACTIVITY_MAPWRAPPER_H

#include <map>

template<typename K, typename V> class MapWrapper {
public:
    V *put(K key, V value);

    V *get(K key);

    bool contains(K key);

    bool remove(K key);

private:
    std::map<K, V> _map;
};

template<typename K, typename V> V *MapWrapper<K, V>::put(K key, V value) {
    return &(_map.insert(std::pair<K, V>(key, value)).first->second);
}

template<typename K, typename V> bool MapWrapper<K, V>::contains(K key) {
    return _map.find(key) != _map.end();
}

template<typename K, typename V> bool MapWrapper<K, V>::remove(K key) {
    typename std::map<K, V>::iterator pos = _map.find(key);
    if (pos == _map.end()) {
        return false;
    }
    _map.erase(pos);
    return true;
}

template<typename K, typename V> V *MapWrapper<K, V>::get(K key) {
    typename std::map<K, V>::iterator pos = _map.find(key);
    if (pos == _map.end()) {
        return NULL;
    }
    return &(pos->second);
}

#endif //NATIVE_ACTIVITY_MAPWRAPPER_H
