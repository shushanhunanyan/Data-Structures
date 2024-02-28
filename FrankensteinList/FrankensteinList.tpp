#include "FrankensteinList.h"

#include <iostream>

template <typename T>
Node<T>::Node(const T& v) : data{v}, next{}, prev{}, greater{}, lesser{}
{}


template <typename T>
FrankensteinList<T>::FrankensteinList() : head{}, tail{}, asc_head{}, desc_head{}, size{}
{}

template <typename T>
FrankensteinList<T>::~FrankensteinList() 
{
	Node<T> *tmp = nullptr;
	while (head) {
		tmp = head;
		head = head->next;
		delete tmp;
	}

}


template <typename T>
void FrankensteinList<T>::PutInSortedOrder(Node<T>* node)
{
	if (!asc_head) {
		asc_head = node;
		desc_head = node;

	} else {
		Node<T> *curr = asc_head;
		while (curr->greater && curr->data < node->data) {
			curr = curr->greater;
		}
		if (curr->data > node->data) {
			if (asc_head == curr) {
				asc_head = node;
			} else {
				curr->lesser->greater = node;
				node->lesser = curr->lesser;
			}
			node->greater = curr;
			curr->lesser = node;
		} else {
			if (!curr->greater) {
				desc_head = node;
			}
			node->greater = curr->greater;
			node->lesser = curr;
			curr->greater = node;
		}
	}		
}


template <typename T>
void FrankensteinList<T>::PushBack(const T& val)
{
	Node<T> *node = new Node<T>(val);
	if (!head) {
		head = node;
	} else {
		tail->next = node;
		node->prev = tail;
	}

	tail = node;
	++size;
	PutInSortedOrder(node);
}


template <typename T>
void FrankensteinList<T>::PushFront(const T& val)
{
        Node<T> *node = new Node<T>(val);
        if (!head) {
		tail = node;
        } else {
		head->prev = node;
	}
	node->next = head;
	head = node;
	++size;
	PutInSortedOrder(node);
}


template <typename T>
void FrankensteinList<T>::PopFront()
{
	if (!head) {
		return;	
	}
	
	RemoveFromSorted(head);
	if (head->next) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	} else {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	--size;
}


template <typename T>
void FrankensteinList<T>::PopBack()
{
        if (!head) {
                return;
        }

        RemoveFromSorted(tail);
        if (tail->prev) {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
        } else {
                delete tail;
                head = nullptr;
                tail = nullptr;
        }
	--size;
}


template <typename T>
void FrankensteinList<T>::RemoveFromSorted(Node<T> *node)
{
	if (asc_head == desc_head) {
		asc_head = nullptr;
		desc_head = nullptr;
		return;
	}

	if (node->greater) {
		node->greater->lesser = node->lesser;
			
	} else {
		desc_head = node->lesser;
	}

	if (node->lesser) {
		node->lesser->greater = node->greater;
	} else {
		asc_head = node->greater;
	}
        
}


template <typename T>
void FrankensteinList<T>::Insert(const T& val, const std::size_t pos)
{
	if (0 == pos) {
		PushFront(val);
		return;
	}
	if (pos >= size) {
		PushBack(val);
		return;
	}

	Node<T> *node = new Node(val);
	Node<T> *curr = head;
	std::size_t count = 0;

	while (count != pos) {
		curr = curr->next;
		++count;
	}

	curr->prev->next = node;
	node->prev = curr->prev;
	curr->prev = node;
	node->next = curr;
	++size;

	PutInSortedOrder(node);
}


template <typename T>
const T FrankensteinList<T>::Get(const std::size_t pos)
{
	if (pos >= size) {
		throw std::out_of_range("No such position");
	}

	Node<T> *curr = head;
	std::size_t count = 0;

	while (count != pos) {
		curr = curr->next;
		++count;
	}
	
	AdvanceNode(curr);
	return curr->data;
}


template <typename T>
void FrankensteinList<T>::AdvanceNode(Node<T>* node)
{
	if (node == head) {
		return;
	}

	Node<T>* prevNode = node->prev;
    	Node<T>* nextNode = node->next;
	
	prevNode->next = nextNode;
    	if (nextNode) {
        	nextNode->prev = prevNode;
    	} else {
		tail = prevNode;
    	}
	
	if (prevNode->prev) {
        	prevNode->prev->next = node;
        	node->prev = prevNode->prev;
    	} else {
        	head = node;
        	node->prev = nullptr;
    	}

    	node->next = prevNode;
    	prevNode->prev = node;
}


template <typename T>
void FrankensteinList<T>::Print() const
{
	Node<T> *curr = head;
	while (curr) {
		std::cout << curr->data << " ";
		curr = curr->next;
	} 
	std::cout << std::endl;

}


template <typename T>
void FrankensteinList<T>::PrintRev() const
{
        Node<T> *curr = tail;
        while (curr) {
                std::cout << curr->data << " ";
                curr = curr->prev;
        }
        std::cout << std::endl;

}


template <typename T>
void FrankensteinList<T>::PrintAsc() const
{
        Node<T> *curr = asc_head;
        while (curr) {
                std::cout << curr->data << " ";
                curr = curr->greater;
        } 
        std::cout << std::endl;

}



template <typename T>
void FrankensteinList<T>::PrintDesc() const
{
        Node<T> *curr = desc_head;
        while (curr) {
                std::cout << curr->data << " ";
                curr = curr->lesser;
        }
        std::cout << std::endl;

}


