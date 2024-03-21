#include "vector.h"


#include <iostream>
#include <utility>


template <typename T>
void swap(vector<T>& first, vector<T>& second) noexcept
{
        first.swap(second);
}

template <typename T>
vector<T>::vector() 
	: m_data{nullptr}
	, m_size{}
	, m_cap{}
{}

template <typename T>
vector<T>::vector(std::size_t count, const T& value) 
	: m_data{new T[count]}
        , m_size{count}
        , m_cap{count}
{
	for (std::size_t i = 0; i < m_size; ++i) {
		m_data[i] = value;
	}
}

template <typename T>
vector<T>::vector(const vector& oth) 
	: m_size{oth.m_size}
       	, m_cap{oth.m_cap}    
{
	if (0 == m_cap) {
		m_data = nullptr;
	} else {
		m_data = new T[m_cap];
		for (std::size_t i = 0; i < m_size; ++i) {
			m_data[i] = oth.m_data[i];
		}
	}
}

template <typename T>
vector<T>::vector(vector&& oth) noexcept
{
	m_data = std::exchange(oth.m_data, nullptr);
	m_size = std::exchange(oth.m_size, 0);
        m_cap = std::exchange(oth.m_cap, 0);
}

template <typename T>
vector<T>::vector(std::initializer_list<T> init)
	: m_data{new T[init.size()]}
	, m_size{}
	, m_cap(init.size())
{
       m_data.reserve(init.size());
	for (const auto& v : init) {
		m_data.push_back(v);
	}
}

template <typename T>
template <class InputIt>
vector<T>::vector(InputIt first, InputIt last)	
{
	std::size_t count = std::distance(first, last);
	
	m_data = new T[count];
        m_size = count;
        m_cap = count;

	InputIt it = first;
	for (std::size_t i = 0; it != last; ++i, ++it) {
		m_data[i] = *it;
    	}
}


template <typename T>
vector<T>& vector<T>::operator=(const vector& oth)
{
	vector tmp = oth;
	swap(tmp);
	return *this;
}

template <typename T>
void vector<T>::swap(vector& oth) noexcept
{
	std::swap(m_data, oth.m_data);
        std::swap(m_size, oth.m_size);
        std::swap(m_cap, oth.m_cap);
}

template <typename T>
vector<T>::~vector()
{
    delete[] m_data;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& oth)
{
        swap(oth);
        return *this;
}

template <typename T>
void vector<T>::assign(std::size_t count, const T& value)
{
	delete[] m_data;

	m_data = new T[count];
	m_size = count;
	m_cap = count;

	for (std::size_t i = 0; i < m_size; ++i) {
		m_data[i] = value;
	}
}

template <typename T>
T& vector<T>::at(std::size_t pos)
{
       if (pos >= m_size) {
	       throw std::out_of_range("Invalid inex");
       } 
       return m_data[pos];
}

template <typename T>
T& vector<T>::operator[](std::size_t pos)
{ 
       return m_data[pos];
}

template <typename T>
T& vector<T>::front() const
{
       return m_data[0];
}

template <typename T>
T& vector<T>::back() const
{
       return m_data[m_size - 1];
}

template <typename T>
bool vector<T>::empty()
{
       return 0 == m_size;
}

template <typename T>
std::size_t vector<T>::size()
{
       return m_size;
}

template <typename T>
std::size_t vector<T>::capacity()
{
       return m_cap;
}

template <typename T>
void vector<T>::reserve(std::size_t new_cap)
{
       if (new_cap <= m_cap) {
	       return;
       }

       T* new_data = new T[new_cap];
       for (std::size_t i = 0; i < m_size; ++i) {
	       new_data[i] = m_data[i];
       }
       delete[] m_data;
       m_data = new_data;
       m_cap = new_cap;
}

template <typename T>
void vector<T>::push_back(T value)
{
	if (m_size >= m_cap) {
		if (m_cap == 0) {
			m_cap = 1;
		} else {
			m_cap *= 2;
		}

		T *new_data = new T[m_cap];
		for (std::size_t i = 0; i < m_size; ++i) {
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
	}
	m_data[m_size++] = value;
}

template <typename T>
void vector<T>::pop_back()
{
	--m_size;
}

//no exception throw bc. implemented like STL
template <typename T>
void vector<T>::insert(std::size_t pos, T value)
{
	if (m_size >= m_cap) {
		m_cap == 0 ? m_cap = 1 : m_cap *= m_cap;

                T *new_data = new T[m_cap];
		for (std::size_t i = 0; i < pos; ++i) {
			new_data[i] = m_data[i];
		}
		new_data[pos] = value;
		++m_size;
		for (std::size_t i = pos; i < m_size; ++i) {
                        new_data[i + 1] = m_data[i];
                }
		delete[] m_data;
		m_data = new_data;
	} else {
		for (std::size_t i = m_size; i >= pos; --i) {
			m_data[i] = m_data[i - 1];
		}
		m_data[pos]  = value;
		++m_size;
	}
}


