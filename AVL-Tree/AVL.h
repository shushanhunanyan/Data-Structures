#include <cstddef>
#include <functional>

template <typename T>
struct Node
{
        T key;
        Node *left;
        Node *right;
        Node(T&);
};

template <typename T>
class AVL
{

public:
        AVL();
        AVL(T);
        //ctor implementations
       // ~AVL();
public:

	Node<T> *Insert(T);
	Node<T> *Remove(const T&);
	void Traverse() const;
	Node<T>* GetSuccessor(const T&);
	Node<T>* GetPredecessor(const T&);
	Node<T>* Search(const T&) const;

private:
        Node<T> *root;

private:
	Node<T>* _InsertHelper(Node<T>*, T);
	Node<T>* _Remove(Node<T>*, const T&);
	Node<T>* _LeftRotate(Node<T>*);
        Node<T>* _RightRotate(Node<T>*);
	Node<T>* _GetMin(Node<T>*) const;
        Node<T>* _GetMax(Node<T>*) const;
	Node<T>* _GetSuccessor(Node<T>*);
        Node<T>* _GetPredecessor(Node<T>*);
	int _GetBalanceFactor(Node<T>*);
        int _GetHeight(Node<T>*) const;
	void _InorderTraversal(Node<T>*, std::function<void(const T&)>) const;
        Node<T>* _Search(Node<T>*, const T&) const;
};

#include "AVL.tpp"

