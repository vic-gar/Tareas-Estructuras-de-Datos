/*
 *  bst.h
 *
 *  Created on: 10/10/2025
 *      Author: Víctor A. García Galván
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

	TreeNode<T>* predecesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
    bool find(T) const;
	void remove(T);
	void removeChilds();
    int height() const;
    bool ancestors(T, std::vector<T>&) const;
    int whatlevelamI(T)const;

    void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const;

	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) {
	value = val;
	left = 0;
	right = 0;
}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) {
	value = val;
	left = le;
	right = ri;
}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
bool TreeNode<T>::find(T val) const {
	if (val == value){
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
    return false;
}

template <class T>
TreeNode<T>* TreeNode<T>::predecesor() {
	TreeNode<T> *le, *ri;

	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	TreeNode<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void TreeNode<T>::remove(T val) {
	TreeNode<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				succ = left->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
void TreeNode<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
int TreeNode<T>::height() const {
    int le = (left  != 0) ? left->height()  : 0;
    int ri = (right != 0) ? right->height() : 0;
    return 1 + (le > ri ? le : ri);
}

template <class T>
bool TreeNode<T>::ancestors(T val, std::vector<T> &vec) const {
    if (val == value) {
        return true;
    }

    bool found = false;
    if (val < value && left != 0) {
        found = left->ancestors(val, vec);
    } 
    else if (val > value && right != 0) {
        found = right->ancestors(val, vec);
    }

    if (found) {
        vec.push_back(value); 
        return true;
    }

    return false;
}

template <class T>
int TreeNode<T>::whatlevelamI(T val) const {
    if (val == value) {
        return 1;
    } 
    else if (val < value && left != 0) {
        int level = left->whatlevelamI(val);
        if (level != 0) {
            return level + 1;
        }
    } 
    else if (val > value && right != 0) {
        int level = right->whatlevelamI(val);
        if (level != 0) {
            return level + 1;
        }
    }
    return 0; 
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != std::streampos(1)) {
		aux << " ";
	}
	aux << value;
}

template <class T>
class BST {
private:
	TreeNode<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
    int height() const;
    std::string ancestors(T)const;
    int whatlevelamI(T) const;

    std::string inorder() const;
	std::string preorder() const;
    std::string postorder() const;
    std::string levelByLevel() const;
    std::string visit() const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	}else{
		root = new TreeNode<T>(val);
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			TreeNode<T> *succ = root->predecesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
	if(root != 0){
		return root->find(val);
	}else{
		return false;
	}
}

template <class T>
int BST<T>::height() const {
    if (root == 0){
        return 0;
    }
    return root->height();
}
template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
    aux << "[";
    if (root != 0 && root->find(val)) {
        std::vector<T> ancestors_vec;
        root->ancestors(val, ancestors_vec); 
        std::reverse(ancestors_vec.begin(), ancestors_vec.end());

        for (size_t i = 0; i < ancestors_vec.size(); ++i) {
            if (i > 0) {
                aux << " ";
            }
            aux << ancestors_vec[i];
        }
    }
    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    if (root == 0) {
        return 0;
    }
    return root->whatlevelamI(val);
}


template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::levelByLevel() const {
	std::stringstream aux;
	aux << "[";
	if (!empty()) {
		std::queue<TreeNode<T>*> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode<T>* cur = q.front(); q.pop();
			if (aux.tellp() != std::streampos(1)) {
				aux << " ";
			}
			aux << cur->value;
			if (cur->left  != 0) q.push(cur->left);
			if (cur->right != 0) q.push(cur->right);
		}
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux;
	aux << preorder() << "\n"
	    << inorder()  << "\n"
	    << postorder() << "\n"
	    << levelByLevel();
	return aux.str();
}

#endif /* BST_H_ */
