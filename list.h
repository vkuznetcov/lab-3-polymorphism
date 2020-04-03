#pragma once

template <typename T>
struct Node final {
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node(const T data): data(data), next(nullptr), prev(nullptr) {}
	Node(Node<T>* obj) { this = obj; }
};

////iterator for list
template <typename T>
class IteratorL final {
	Node<T>* node;

public:
	////constructors
	IteratorL() : node(nullptr) {}

	IteratorL(Node<T>* const node) : node(node) {}

	////operators overloads
	IteratorL<T>& operator++() {
		node = node->next;
		return *this;
	}

	IteratorL<T>& operator--() {
		node = node->prev;
		return *this;
	}

	IteratorL<T>& operator++(int) {
		IteratorL<T> copy(*this);
		node = node->next;
		return copy;
	}

	IteratorL<T>& operator--(int) {
		IteratorL<T> copy(*this);
		node = node->prev;
		return copy;
	}

	T& operator*() const {
		return node->data;
	}

	Node<T>* operator&() const {
		return node;
	}

	bool operator==(std::nullptr_t nullp) const {
		return node == nullp;
	}

	bool operator==(const IteratorL<T>& obj) const {
		return node == obj.node;
	}

	bool operator!=(std::nullptr_t nullp) const {
		return node != nullp;
	}

	bool operator!=(const IteratorL<T>& obj) const {
		return node != obj.node;
	}

	bool operator<(const IteratorL<T>& obj) const {
		return node < obj.node;
	}

	bool operator>(const IteratorL<T>& obj) const {
		return node > obj.node;
	}
};

template <typename T>
IteratorL<T> operator+(const IteratorL<T>& obj, const int num) {
	if (obj == nullptr)
		return obj;

	IteratorL<T> res(obj);

	for (auto i = 0; i < num; ++i)
		++res;

	return res;
}

template <typename T>
IteratorL<T> operator+=(IteratorL<T>& obj, const int num) {
	if (obj == nullptr)
		return obj;

	for (auto i = 0; i < num; ++i)
		++obj;

	return obj;
}

template <typename T>
class List {
	Node<T>* ptr;
	size_t size;

public:
	////constructors
	List<T>(): ptr(nullptr), size(0) {}//default ctor

	List<T>(Node<T>* newPtr, size_t size) : size(size){//with pointer to list and size of this list
		if (newPtr == nullptr) {
			ptr = nullptr;
			Vector::size = 0;
		}
		else {
			while (newPtr->prev)
				newPtr = newPtr->prev;

			ptr = new Node<T>;
			ptr->prev = nullptr;

			ptr->data = newPtr->data;
			newPtr = newPtr->next;
			Node<T>* tmp = ptr;
			while (newPtr) {
				ptr->next = new Node<T>;
				ptr = ptr->next;
				ptr->prev = tmp;
				ptr->data = newPtr->data;
				newPtr = newPtr->next;
				tmp = ptr;
			}
			pre->next = nullptr;
		}
	}

	List<T>(std::nullptr_t nullp): ptr(nullp), size(0) {}//without parameters(null)

	List<T>(const List<T>& obj): size(obj.size) {//copy ctor
		IteratorL<T> it = obj.begin();

		if (obj.size > 1) {
			ptr = new Node<T>(*it);

			ptr->prev = nullptr;

			Node<T>* tmp = nullptr;

			++it;

			for (; it != obj.end(); ++it) {
				tmp = ptr;
				ptr->next = new Node<T>(*it);
				ptr = ptr->next;
				ptr->prev = tmp;
			}
			ptr->next = nullptr;
		}
		else {
			if (obj.size == 1) {
				ptr = new Node<T>(*it);
				ptr->prev = nullptr;
				ptr->next = nullptr;
			}
			else ptr = nullptr;
		}
	}

	List<T>(List<T>&& obj) noexcept : ptr(&(obj.begin())), size(obj.size) {//move ctor
		obj.ptr = nullptr;
		obj.size = 0;
	}

	~List() {//dtor
		std::cout << "removing collection" << std::endl << std::endl;
		clear();
	}

	////assigment operators

	List<T>& operator=(const List<T>& obj) {//copy assigment
		if (*this == obj)
			return *this;

		clear();//deleting old list

		if (obj.size >= 1) {
			IteratorL<T> it = obj.begin();

			ptr = new Node<T>(*it);
			ptr->prev = nullptr;

			Node<T>* tmp = nullptr;
			++it;
			for (; it != obj.end(); ++it) {
				tmp = ptr;
				ptr->next = new Node<T>;
				ptr = ptr->next;
				ptr->data = *it;
				ptr->prev = tmp;
			}
			ptr->next = nullptr;
		}
		else ptr = nullptr;

		size = obj.size;
		return *this;
	}

	List<T>& operator=(List<T>&& obj) {//move assigment
		if (*this == obj) {
			obj.ptr = nullptr;
			obj.size = 0;
			return *this;
		}

		clear();
		ptr = &(obj.begin());
		size = obj.size;

		obj.ptr = nullptr;
		obj.size = 0;

		return *this;
	}

	////access to elements
	T& front() {//access to the first element of list
		if (ptr)
			return *(begin());
		else throw "List is empty";
	}

	T& back() {//access to last element of list
		if (ptr) {
			List<T> tmp(*this);
			while (tmp.ptr->next != nullptr)
				tmp.ptr = tmp.ptr->next;

			return tmp.ptr->data;
		}
		else throw "List is empty";
	}

	T& front() const {//access(const) to the first element of list
		if (ptr)
			return *(begin());
		else throw "List if empty";
	}

	T& back() const {//access(const) to last element of list
		if (ptr) {
			List<T> tmp(*this);
			while (tmp->next != nullptr)
				tmp.ptr = tmp.ptr->next;

			return tmp.ptr->data;
		}
		else throw "List is empty";
	}

	////iterators
	IteratorL<T> begin() const noexcept {//return iterator to the first element
		if (ptr) {
			Node<T>* tmp = ptr;

			if (size > 1) {
				while (tmp->prev != nullptr)
					tmp = tmp->prev;

				return IteratorL<T>(tmp);
			}
			else return IteratorL<T>(tmp);
		}
		else return end();
	}

	IteratorL<T> end() const noexcept {
		if (!ptr)
			return nullptr;

		Node<T>* tmp = ptr;

		//return to place after last element
		while (tmp != nullptr)
			tmp = tmp->next;

		return IteratorL<T>(tmp);
	}

	////capacity
	bool empty() const noexcept {
		return end() == begin();
	}

	size_t sizer() const noexcept {
		if (empty())
			return 0;

		return begin() - end();
	}

	////modificators
	void clear() {//destroy list
		//if there are no items
		if (!ptr)
			return;

		//if there is one item
		if (size == 1) {
			delete ptr;
			ptr = nullptr;
			size = 0;
			return;
		}

		//in other situations
		while (ptr->prev != nullptr)//return to the first element
			ptr = ptr->prev;

		Node<T>* tmp;

		while (ptr) {
			tmp = ptr->next;
			delete ptr;
			ptr = tmp;
		}
		ptr = nullptr;
		size = 0;
	}

	//paste element before iterator
	IteratorL<T> insert(IteratorL<T>& pos, const T& val) {
		//increment size of list
		++size;

		//if list do not exist -> creating first node
		if (!ptr) {
			ptr = new Node<T>(val);
			ptr->prev = nullptr;
			ptr->next = nullptr;

			pos = begin();
			return pos;
		}

		//if another situation
		else {
			//if only one node exists
			if (size == 1) {
				Node<T>* tmp = ptr;

				if (pos == begin()) {
					//create new node before current node
					ptr->prev = new Node<T>(val);

					//return to new node
					ptr = ptr->prev;

					//make connections with new node;
					ptr->next = tmp;

					//because insert item before the first element
					ptr->prev = nullptr;

					//return pos to second node
					pos = ++begin();
				}
				else {
					//create node after current node
					ptr->next = new Node<T>(val);

					//make connections with new node
					ptr = ptr->next;
					ptr->prev = tmp;

					//because we insert an element before end
					ptr->next = nullptr;

					//return pos to second node
					pos = end();
				}
				return pos;
			}

			//if not only one item exists

			//if we want to paste in the end
			if (pos == end()) {
				while (ptr->next)
					ptr = ptr->next;

				ptr->next = new Node<T>(val);
				ptr->next->next = nullptr;

				ptr->next->prev = ptr;
				return end();
			}

			//another situations

			//return to the first node
			while (ptr->prev)
				ptr = ptr->prev;

			//index of insert element
			auto index = begin() - pos;

			//moving in pos
			ptr = &pos;

			//use bucket
			Node<T>* tmp;

			//if element isn't first
			if (ptr->prev != nullptr) {
				tmp = ptr->prev;
				tmp->next = new Node<T>(val);
				ptr->prev = tmp->next;
				tmp->next->next = ptr;
				tmp->next->prev = tmp;
			}

			//if element if first
			else {
				tmp = new Node<T>(val);
				ptr->prev = tmp;
				tmp->prev = nullptr;
				tmp->next = ptr;
				ptr->prev = tmp;
				++index;
			}

			//placing pos in new place(after inserted element)
			pos = begin();
			for (auto i = 0; i < index; ++i)
				++pos;
		}

		return pos;
	}

	//remove element in iterator
	IteratorL<T> erase(IteratorL<T>& pos) {
		//if list if empty
		if (empty())
			throw "ERROR: list if empty";

		//return to the first element
		while (ptr->prev != nullptr)
			ptr = ptr->prev;

		//to pos node
		ptr = &pos;

		//if only one element(with exit from method)
		if (ptr->next == nullptr && ptr->prev == nullptr) {
			delete ptr;
			ptr = nullptr;
			--size;
			return end();
		}

		//if element isn't first and isn't last
		if (ptr->next != nullptr && ptr->prev != nullptr) {
			//save previous node
			Node<T>* before = ptr->prev;

			//save next node
			Node<T>* after = ptr->next;

			//delete node between after and before
			delete ptr;

			//connect after and before
			before->next = after;
			after->prev = before;

			ptr = after;
		}
		else
			//if pos - node is last node
			if (ptr->next == nullptr) {
				//save previous node
				Node<T>* before = ptr->prev;

				before->next = nullptr;

				//delete last node
				delete ptr;
				ptr = before;
			}
			//if pos - node if the first node
			else {
				//save next node
				Node<T>* after = ptr->next;

				after->prev = nullptr;

				//delete first node
				delete ptr;
				ptr = after;
			}
		//decrement size of list
		--size;

		//reinitialize pos for return it iterator in the future
		pos = begin();

		//for placing iterator pos in new position(after erased node)
		Node<T>* tmp;

		//return to first node of this list
		tmp = &(begin());

		//plase iterator pos in position after pasted node
		while (tmp != ptr) {
			tmp = tmp->next;
			++pos;
		}

		return pos;
	}
};

template<typename T>
bool operator==(const List<T>& l1, const List<T>& l2) {
	IteratorL<T> tmp1 = l1.begin();
	IteratorL<T> tmp2 = l2.begin();

	//compare sizes of lists
	if (l1.sizer() == l2.sizer()) {
		//comparing pointers
		while (tmp1 != l1.end()) {
			if (tmp1 = tmp2) {
				++tmp1;
				++tmp2;
			}
			else return false;
		}
		return true;
	}
	else return false;
}

template<typename T>
bool operator!=(const List<T>& l1, const List<T>& l2) {
	return !(l1 == l2);
}

template<typename T>
bool operator<(const List<T>& l1, const List<T>& l2) {
	if (l1.sizer() == l2.sizer()) {
		IteratorL<T> tmp1 = l1.begin();
		IteratorL<T> tmp2 = l2.begin();
		for (auto i = 0; i < l1.sizer(); ++i) {
			if (tmp1 < tmp2)
				return true;
			else if (tmp2 > tmp1)
				return false;
		}
		return false;
	}
	else return (l1.sizer() < l2.sizer());
}

template<typename T>
bool operator>(const List<T>& l1, const List<T>& l2) {
	if (l1.sizer() == l2.sizer()) {
		IteratorL<T> tmp1 = l1.begin();
		IteratorL<T> tmp2 = l2.begin();
		for (auto i = 0; i < l1.sizer(); ++i) {
			if (tmp1 > tmp2)
				return true;
			else if (tmp2 < tmp1)
				return false;
		}
		return false;
	}
	else return (l1.sizer() > l2.sizer());
}

template<typename T>
bool operator<=(const List<T>& l1, const List<T>& l2) {
	return !(l1 > l2);
}

template<typename T>
bool operator>=(const List<T>& l1, const List<T>& l2) {
	return !(l1 < l2);
}

template<typename T>
int operator-(const IteratorL<T>& it1, const IteratorL<T>& it2) {
	IteratorL<T> copy = it1;
	auto i = 0;
	for (i = 0; copy != it2; ++i)
		copy++;

	return i;
}