#include <cstddef>


template <typename T>
struct Node
{
        T data;
        Node *next;
        Node *prev;
        Node *greater;
        Node *lesser;

        Node(const T&);
};


/*
class Iterator
{
public:
	Iterator();
	operator++();
	operator++(int);
	operator !=(const Iterator&);
	operator*();
	private:	
};
*/

template <typename T>
class FrankensteinList
{
public:
	//copy move ctors need to add
        FrankensteinList();
	~FrankensteinList();
public:
	void PushBack(const T&);
	void PushFront(const T&);
	void PopBack();
	void PopFront();
	void Insert(const T&, const std::size_t pos);
	void Print() const;
	void PrintRev() const;
	void PrintAsc() const;
	void PrintDesc() const;
	const T Get(const std::size_t pos);
private:
	void PutInSortedOrder(Node<T>*);
	void RemoveFromSorted(Node<T>*);
	void AdvanceNode(Node<T>*);
private:
        Node<T> *head;
        Node<T> *tail;
        Node<T> *asc_head;
        Node<T> *desc_head;
	std::size_t size;
};


#include "FrankensteinList.tpp"
