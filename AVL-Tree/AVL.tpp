#include "AVL.h"

#include <algorithm>
#include <iostream>



template <typename T>
Node<T>::Node(T& val)
        : key{val}
        ,left{}
        ,right{}
{}


template <typename T>
AVL<T>::AVL()
        : root{}
{}


template <typename T>
AVL<T>::AVL(T val)
        : root{ new Node<T>(val) }
{}

/*
template <typename T>
AVL<T>::~AVL()
{
        DeleterHelper(root);
}*/


// -------------INSERTION--------------

template <typename T>
Node<T>* AVL<T>::Insert(T val)
{
	return _InsertHelper(root, val);
}



template <typename T>
Node<T>* AVL<T>::_InsertHelper(Node<T> *node, T val)
{
        if (!node) {
		return new Node<T>(val);
	}

	if (node->key >= val) {
		node->left = _InsertHelper(node->left, val);

	}
	if (node->key < val) {
                node->right = _InsertHelper(node->right, val);
        } 

	int bf = _GetBalanceFactor(node);

	if (bf < -1 && val < node->right->key) {
		node->right = _RightRotate(node->right);
		return _LeftRotate(node);

	}
	if (bf < -1 && val >= node->right->key) {
		return _LeftRotate(node);
	}

	if (bf > 1 && val < node->left->key) {
                return _RightRotate(node);

        }
        if (bf > 1 && val >= node->left->key) {
		node->left = _LeftRotate(node->left);
                return _RightRotate(node);
        }
	
	return node;
}


template <typename T>
int AVL<T>::_GetBalanceFactor(Node<T> *node)
{
	if (!node) {
		return 0;
	}

	int lh = _GetHeight(node->left);
	int rh = _GetHeight(node->right);

	return lh - rh;
}


template <typename T>
int AVL<T>::_GetHeight(Node<T>* node) const
{
        if (!node) {
                return -1;
        }

        return 1 + std::max(_GetHeight(node->left), _GetHeight(node->right));
}

// ---------------ROTATIONS----------

template <typename T>
Node<T>* AVL<T>::_LeftRotate(Node<T> *z)
{
        Node<T> *y = z->right;
        z->right = y->left;
        y->left = z;

        return y;
}


template <typename T>
Node<T>* AVL<T>::_RightRotate(Node<T> *z)
{
        Node<T> *y = z->left;
        z->left = y->right;
        y->right = z;

        return y;
}

//-----------REMOVE-------------

template <typename T>
Node<T>* AVL<T>::Remove(const T& val)
{
	return _Remove(root, val);
}


template <typename T>
Node<T>* AVL<T>::_Remove(Node<T> *node, const T& val)
{
        if (!node) {
		return nullptr;
	}

	if (node->key > val) {
		node->left = _Remove(node->left, val);
	} else if (node->key < val) {
		node->right = _Remove(node->right, val);

	} else {
		Node<T> *tmp = nullptr;

		if (!node->right) {
			tmp = node->left;
			delete node;
			return tmp;
		}
		if (!node->left) {
			tmp = node->right;
			delete node;
			return tmp;

		} else {
			tmp = GetMax(node->left);
			node->key = tmp->key;
			node->left = _Remove(node->left, tmp->key);
		}
	}
	int bf = _GetBalanceFactor(node);

	if (bf > 1 && _GetBalanceFactor(node->left) >= 0) {
		return _RightRotate(node);
	}
	if (bf > 1 && _GetBalanceFactor(node->left) < 0) {
                node->left = _LeftRotate(node->left);
		return _RightRotate(node);
        }
	if (bf < -1 && _GetBalanceFactor(node->right) <= 0) {
                return _LeftRotate(node);
        }
	if (bf < -1 && _GetBalanceFactor(node->right) > 0) {
		node->right = _RightRotate(node->right);
                return _LeftRotate(node);
        }
	
	return node;
}


//------------TRAVERSE-----------

template <typename T>
void AVL<T>::_InorderTraversal(Node<T>* node, std::function<void(const T&)> visit) const
{
        if (!node) { return; }

        _InorderTraversal(node->left, visit);
        visit(node->key);
        _InorderTraversal(node->right, visit);
}


template <typename T>
void AVL<T>::Traverse() const
{
        _InorderTraversal(root, [](const int& val) { std::cout << val << " "; });
}


//-------------GET MIN MAX------------

template <typename T>
Node<T>* AVL<T>::_GetMin(Node<T>* node) const
{
        if (!node) {
                return nullptr;
        }
        while (node->left) {
                node = node->left;
        }
        return node;
}


template <typename T>
Node<T>* AVL<T>::_GetMax(Node<T>* node) const
{
        if (!node) {
                return nullptr;
        }
        while (node->right) {
                node = node->right;
        }
        return node;
}


//-----------SUCCESSOR PREDECESSOR-------


template <typename T>
Node<T>* AVL<T>::GetSuccessor(const T& val)
{
	return _GetSuccessor(Search(val));
	
}

template <typename T>
Node<T>* AVL<T>::GetPredecessor(const T& val)
{
        return _GetPredecessor(Search(val));

}

template <typename T>
Node<T>* AVL<T>::_GetSuccessor(Node<T>* node)
{
        if (!node) {
                return nullptr;
        }

        if (node->right) {
                return _GetMin(node->right);
        }
        Node<T> *successor = nullptr;
        Node<T> *ancestor = root;

        while (ancestor != node) {
                if (ancestor->key > node->key) {
                        successor = ancestor;
                        ancestor = ancestor->left;
                } else {
                        ancestor = ancestor->right;
                }
        }

        return successor;
}


template <typename T>
Node<T>* AVL<T>::_GetPredecessor(Node<T>* node)
{
        if (!root) {
                return nullptr;
        }

        if (node->left != nullptr) {
                return _GetMax(node->left);

        }

        Node<T>* predecessor = nullptr;
        Node<T>* ancestor = root;

        while (ancestor != node) {
                if (ancestor->key < node->key) {
                        predecessor = ancestor;
                        ancestor = ancestor->right;
                } else {
                        ancestor = ancestor->left;
                }
        }

        return predecessor;
}


template <typename T>
Node<T>* AVL<T>::Search(const T& val) const
{
        return _Search(root, val);
}


template <typename T>
Node<T>* AVL<T>::_Search(Node<T>* node, const T& val) const
{
        if (!node) {
                return nullptr;
        }

        if (val == node->key) {
            return node;
        }
        if (val > node->key) {
            return _Search(node->right, val);
        }
        else {
            return _Search(node->left, val);
        }
}


