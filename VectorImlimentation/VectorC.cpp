#include "VectorC.h"

template<typename T>
void VectorC<T>::reallocate() {
    int old_size = size();
    int old_capacity = capacity();
    int new_capacity = (old_capacity == 0 ? 1 : old_capacity * 2);

    T* new_block = new T[new_capacity];

    for (int i = 0; i < old_size; i++) {
        new_block[i] = m_begin[i];
    }

    delete[] m_begin;

    m_begin = new_block;
    m_end   = new_block + old_size;
    m_capacity   = new_block + new_capacity;
}

template<typename T>
VectorC<T>::VectorC() : m_begin(nullptr), m_end(nullptr), m_capacity(nullptr) {}

template<typename T>
int VectorC<T>::size() const
{
    return m_end - m_begin;
}

template<typename T>
int VectorC<T>::capacity() const
{
    return m_capacity - m_begin;
}

template<typename T>
void VectorC<T>::push_back(const T &value)
{
    if (m_end == m_capacity)
    {
        reallocate();
    }
    *m_end = value;
    m_end++;
}

template<typename T>
VectorC<T>::~VectorC()
{
    std::cout << "distructer is called\n";
    delete[] m_begin;
}

template<typename T>
T *VectorC<T>::begin() const
{
    return m_begin;
}

template<typename T>
T *VectorC<T>::end() const
{
    return m_end;
}
template class VectorC<int>;
template class VectorC<float>;
template class VectorC<std::string>;

