/*
 * list.h
 *
 *  	Created on: 28/09/2025
 *      Author: Víctor A. García 
 */

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;

//Clase Link
template <class T>
class Link {
    private:
        Link(T);
        Link(T, Link<T>*);
        Link(const Link<T>&);

        T	    value;
        Link<T> *next;

        friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}


//Clase List
template <class T>
class List {
    public:
        List();
        ~List();

        bool empty() const;
        void clear();
        void insertion(T);
        void insertionFirst(T);
        int search(T) const;
        void update(int, T);
        T deleteFirst();
        void deleteAt(int);

        std::string toString() const;

    private:
        Link<T> *head;
        int 	size;
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T>
void List<T>::insertionFirst(T val)  {
	Link<T> *newLink;

	newLink = new Link<T>(val);

	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::insertion(T val)  {
	Link<T> *newLink, *ptr;

    if (empty()) {
		insertionFirst(val);
		return;
	}

	ptr = head;
	while (ptr->next != 0) {
		ptr = ptr->next;
	}

    newLink = new Link<T>(val);
	newLink->next = 0;
	ptr->next = newLink;
	size++;
}

template <class T>
int List<T>::search(T val) const{
    Link<T> *ptr;

    ptr = head;
    int pos = 0;

    while (ptr != 0) {
        if (ptr->value == val){
            return pos;
        }
        
        ptr = ptr->next;
        pos++;
    }
    return -1;
}

template <class T>
void List<T>::update(int indx, T val){
    Link<T> *ptr;

    ptr = head;
    int pos = 0;

    while (pos < indx) {
        ptr = ptr->next;
        pos++;
    }
    ptr->value = val;
}

template <class T>
T List<T>::deleteFirst(){
	T val;
	Link<T> *ptr;

	ptr = head;

	head = ptr->next;
	val = ptr->value;

	delete ptr;
	size--;

	return val;
}

template <class T>
void List<T>::deleteAt(int indx){
    if (indx == 0) {
        deleteFirst();
        return;
    }
    Link<T>* ptr;

    ptr = head;
    int pos = 0;
    while (pos < indx - 1) {
        ptr = ptr->next;
        pos++;
    }
    Link<T>* targ = ptr->next;
    ptr->next = targ->next;

    delete targ;
    size--;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

#endif