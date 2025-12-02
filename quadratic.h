#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
    unsigned int (*func) (const Key);
    unsigned int size;
    unsigned int count;

    Key *keys;
    Key initialValue;
    Value *values;

    long indexOf(const Key) const;

public:
    Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
    ~Quadratic();
    bool full() const;
    bool put(Key, Value);
    bool contains(const Key) const;
    Value get(const Key) ;
    void clear();
    std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
    size = sze;
    count = 0;
    initialValue = init;
    func = f;
    keys = new Key[size];
    values = new Value[size];

    for (unsigned int i = 0; i < size; i++) {
        keys[i] = initialValue;
    }

    for (unsigned int i = 0; i < size; i++) {
        values[i] = 0;
    }
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
    delete [] keys;
    delete [] values;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
    return (count >= size);
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
    unsigned int start = func(k) % size;
    unsigned int i = 0;

    while (i < size) {
        unsigned int idx = (start + i * i) % size;

        if (keys[idx] == initialValue) {
            return -1;
        }
        if (keys[idx] == k) {
            return idx;
        }
        ++i;
    }
    return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
    long pos = indexOf(k);
    if (pos != -1) {
        values[pos] = v;
        return true;
    }

    if (full()) {
        return false;
    }

    unsigned int start = func(k) % size;
    unsigned int i = 0;

    while (i < size) {
        unsigned int idx = (start + i * i) % size;
        if (keys[idx] == initialValue) {
            keys[idx] = k;
            values[idx] = v;
            ++count;
            return true;
        }
        ++i;
    }

    return false;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
    long pos = indexOf(k);
    return (pos != -1);
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
    long pos = indexOf(k);
    if (pos != -1) {
        return values[pos];
    }

    return pos;
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
    count = 0;
    for (unsigned int i = 0; i < size; i++) {
        keys[i] = initialValue;
    }
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
    std::stringstream aux;

    for (unsigned int i = 0; i < size; i++) {
        if (keys[i] != initialValue) {
            aux << "(" << i << " " << keys[i]
                << " : " << values[i] << ") ";
        }
    }
    return aux.str();
}

#endif /* HASH_H_ */
