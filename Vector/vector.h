#include <initializer_list>
#include <cstddef>

template <typename T>
class vector;

template <typename T>
void swap(vector<T>&, vector<T>&) noexcept;

//STL impl- + std::allocator<T> as def
template <typename T>
class vector
{
public:
	vector();
	vector(std::size_t, const T& value = T()); //count, value	
	vector(const vector&);
	vector(vector&&) noexcept;
	vector(std::initializer_list<T>);
	template <class InputIt>
	vector(InputIt, InputIt);
	~vector();

	vector& operator=(const vector&);
        vector& operator=(vector&&);
	void swap(vector&) noexcept;
	void assign(std::size_t, const T&);
        void assign(std::initializer_list<T>);
        
//-----element access
	T& at(std::size_t pos);
        T& operator[](std::size_t pos);
	T& front() const;
        T& back() const;

//------capacity
	bool empty();
	std::size_t size();
	std::size_t capacity();
	void reserve(std::size_t);

//------modifiers
	void clear();
	void insert(std::size_t, T); // first argument should be iterator position
	void push_back(T);
	void pop_back();
	void resize();
public:
	T* m_data;
	std::size_t m_size;
	std::size_t m_cap;
};

#include "vector.tpp"
