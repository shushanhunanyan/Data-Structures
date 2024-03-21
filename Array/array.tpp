#include <iostream>


template <typename T, std::size_t N>
array<T,N>::array()
{}


template <typename T, std::size_t N>
array<T,N>::array(std::initializer_list<T> list)
{
	if (list.size() > N) {
		throw std::out_of_range("error: to many arguments");
	}
	
 	std::size_t i = 0;
	for (const T& v : lists) {
		arr[i++] = v;
	}

}


template <typename T, std::size_t N>
array<T,N>::array(const array& oth) : arr[N]{}
{
	for (std::size_t i = 0; i < N; ++i) {
		arr[i] = oth.arr[i];
	}
}


/*
template <typename T, std::size_t N>
array<T,N>::array(array&& oth) : arr[N]{}
{
	for (std::size_t i = 0; i < N; ++i) {
		arr[i] = std::move(oth.arr[i]);
	}
}


template <typename T, std::size_t N>
array& array<T,N>::operator=(const array& oth)
{
	for (std::size_t i = 0; i < N; ++i) {
                arr[i] = oth.arr[i];
        }

	return *this;
}

template <typename T, std::size_t N>
array& array<T,N>::operator=(array&& oth)
{
}
*/


template <typename T, std::size_t N>
T& array<T,N>::operator[](std::size_t index)
{
	return arr[index];
}


template <typename T, std::size_t N>
bool array<T,N>::empty() const
{
	return N == 0;
}

template <typename T, std::size_t N>
std::size_t array<T,N>::size() const
{
        return N;
}


template <typename T, std::size_t N>
T& array<T,N>::at(std::size_t pos)
{
	if (pos >= N) {
		throw std::out_of_range("not valid index.");
	}
        return arr[pos];
}


template <typename T, std::size_t N>
T& array<T,N>::front()
{ 
        return arr[0];
}


template <typename T, std::size_t N>
T& array<T,N>::back()
{
        
        return arr[N - 1];
}


template <typename T, std::size_t N>
void array<T,N>::fill(const T& val)
{
        for (std::size_t i = 0; i < N; ++i) {
		arr[i] = val;
	}
}


template <typename T, std::size_t N>
void array<T,N>::swap(array& oth)
{
        for (std::size_t i = 0; i < N; ++i) {
		std::swap(arr[i], oth.arr[i]);
        }
}

