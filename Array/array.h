#include <initializer_list>
#include <cstddef>

/*
	bool operator==(const array&);
        bool operator!=(const array&);
        bool operator<(const array&);
        bool operator>(const array&);
        bool operator>=(const array&);
        bool operator<=(const array&);
*/


template <typename T, std::size_t N>
struct array
{
	array(); //undefined values on stl
	array(std::initializer_list<T>);
	array(const array&);
        array(array&&);
	array& operator=(const array&);
	array& operator=(array&&);
//	~array();



	bool empty() const;
	std::size_t size() const;
	T& operator[](std::size_t);

	T& at(std::size_t);
	T& front();
	T& back();
	T* data();
	void fill(const T&);
	void swap(array&);

	T arr[N];
};

#include "array.tpp"
