#ifndef VECTORC_H
#define VECTORC_H

#include <iostream>

template <typename T>
class VectorC
{

public:
    VectorC();

    int size() const;

    int capacity() const;

    void push_back(const T& value);

    ~VectorC();
    T *begin() const;
    T *end() const;

private:
    T* m_begin;
    T* m_end;
    T* m_capacity;

    void reallocate();
};

#endif
