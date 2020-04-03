#pragma once
#include <vector>

//iterator for vector
template <typename T>
class IteratorV final {
	T* node;

public:
	////constructors
	IteratorV(): node(nullptr) {}

	IteratorV(T* const node): node(node) {}

	////operators overloads
	IteratorV<T>& operator++() {
		++node;
		return *this;
	}

	IteratorV<T>& operator++(int) {
		IteratorV<T> copy(*this);
		++node;
		return copy;
	}

	IteratorV<T>& operator--() {
		--node;
		return *this;
	}

	IteratorV<T>& operator--(int) {
		IteratorV<T> copy(*this);
		--node;
		return copy;
	}

	T& operator*() const {
		return *node;
	}

	bool operator==(const IteratorV<T>& obj) {
		return node == obj.node;
	}

	bool operator==(std::nullptr_t nullp) {
		return node == nullp;
	}

	bool operator!=(const IteratorV<T>& obj) {
		return node != obj.node;
	}

	bool operator!=(std::nullptr_t nullp) {
		return node != nullp;
	}

	bool operator<(const IteratorV<T>& obj) {
		return node < obj.node;
	}

	bool operator>(const IteratorV<T>& obj) {
		return node > obj.node;
	}
};

template <typename T>
IteratorV<T> operator+(IteratorV<T>& obj, const int num) {

	if (obj == nullptr)
		return obj;

	IteratorV<T> res(obj);

	for (auto i = 0; i < num; ++i)
		++res;

	return res;
}

template <typename T>
IteratorV<T> operator+=(IteratorV<T>& obj, const int num) {
	if (obj == nullptr)
		return obj;

	for (auto i = 0; i < num; ++i)
		++obj;

	return obj;
}

template <typename T>
class Vector {
	T* ptr;
	size_t size;

public:
	////constructors
	Vector<T>(): ptr(nullptr), size(0) {}//empty ctor(default)

	Vector<T>(T* newPtr, size_t size): ptr(newPtr), size(size) {}//ctor with pointer to new array and size of this array

	Vector<T>(size_t size): ptr(new T[size]), size(size) {}//ctor withount pointer, only wih size

	Vector<T>(const Vector<T>& obj) : ptr(new T[obj.size]), size(obj.size) {//copy ctor
		for (auto i = 0; i < size; ++i)
			ptr[i] = obj.ptr[i];
	}

	Vector<T>(Vector<T>&& obj) noexcept : ptr(obj.ptr), size(obj.size) {//move ctor
		obj.ptr = nullptr;
		obj.size = 0;
	}

	~Vector() {
		std::cout << "deleting collection" << std::endl << std::endl;
		delete[] ptr;
		ptr = nullptr;
		size = 0;
	}

	////assigment  operators
	Vector<T>& operator=(const Vector<T>& obj) {//copy assigment
		if (this == obj)
			return *this;

		delete[] ptr;
		ptr = new T[obj.size];
		size = obj.size;

		for (auto i = 0; i < size; ++i) {
			ptr[i] = obj.ptr[i];
		}

		return *this;
	}

	Vector<T>& operator=(Vector<T>&& obj) {
		if (this == obj) {
			obj.ptr = nullptr;
			obj.size = 0;
			return *this;
		}

		delete[] ptr;
		ptr = obj.ptr;
		size = obj.ptr;
		obj.ptr = nullptr;
		obj.size = 0;

		return *this;
	}

	////access to elements
	T& at(size_t index) {//with checking index
		if (size > 0) {
			if ((index < 1) || (index > (size - 1)))
				throw "Invalid index: out of range";
			return ptr[index];
		}
		else throw "Current vector is empty";
	}

	T& at(size_t index) const {//with checking index(const)
		if (size > 0) {
			if ((index < 1) || (index > (size - 1)))
				throw "Invalid index: out of range";
			return ptr[index];
		}
		else throw "Current vector is empty";
	}

	T& operator[](size_t index) {//without checking index
		return ptr[index];
	}

	const T& operator[](size_t index) const {//without checking index(const)
		return ptr[index];
	}

	T& front() {//access to the first element of vector
		return at(0);
	}

	const T& front() const {//access(const) to the first element of vector
		return at(0);
	}

	T& back() {//access to last element of vector
		return at(size - 1);
	}

	const T& back() const {//access(const) to last element of vector
		return at(size - 1);
	}

	T* data() const {//access to data of vector;
		if (ptr)
			return &front();
		throw "the vector is empty";
	}

	////iterators
	IteratorV<T> begin() const {//return iterator to the first element
		if (ptr)
			return IteratorV<T>(ptr);
		return end();
	}

	IteratorV<T> end() const {//return iterator to the last element
		if (ptr == nullptr)
			return nullptr;
		return IteratorV<T>(ptr + size);
	}

	////capacity
	bool empty() const noexcept {//checking vector for emptiness
		return begin() == end();
	}

	size_t sizer() const noexcept {
		if (empty())
			return 0;
		return begin() - end();
	}

	/*void reserve(size_t size) {
		if (size < 0 || size>1000)
			throw "size if out of range";
		Vector<T>::size = size;
	}*/

	////modifiers
	void clear() noexcept {//destroy vector
		delete ptr;
		ptr = nullptr;
		size = 0;
	}

	IteratorV<T> insert(IteratorV<T>& pos, const T& value) {//paste element before iterator
		Vector<T> copy(new T[size + 1], size + 1);
		IteratorV<T> counter = begin();

		int index = 0;

		for (int i; counter != pos; ++i) {
			++counter;
			++index;
		}

		int counterInt = 0;

		for (auto i = 0; i < size + 1; ++i) {
			if (i != index) {
				copy[i] = ptr[counterint];
				++counterInt;
			}
			else
				copy[i] = value;
		}

		*this = copy;

		pos = begin() += index;
		return pos;
	}

	IteratorV<T> erase(IteratorV<T>& pos) {//remove element in iterator
		if (empty())
			throw "ERROR: vector is empty";

		//creating new vector
		Vector<T> copy(new T[size - 1], size - 1);

		//using for search index
		IteratorV<T> counter = begin();

		int index = 0;
		for (int i = 0; counter != pos; ++i) {
			++counter;
			++index;
		}

		// WE FOUNDED INDEX OF ELEMENT BEFORE THEN WE WILL PASTE "VALUE"

		int counterInt = 0;

		for (auto i = 0; i < size - 1; ++i) {
			if (counterInt != index) {
				copy[i] = ptr[counterInt];
				++counterInt;
			}
			else {
				++counterInt;
				--i;
			}
		}

		*this = copy;

		if ((begin() += index) < end())
			pos = (begin() += index);
		else pos = --(end());

		return pos;
	}
};

template <typename T>
bool operator==(const Vector<T>& v1, const Vector<T>& v2) noexcept {
	if (v1.sizer() == 0 && v2.sizer() == 0)
		return true;

	if (v1.sizer() == v2.sizer()) {
		for (auto i = 0; i < v2.size; ++i)
			if (v1[i] != v2[i])
				return false;
		return true;
	}

	return false;
}

template <typename T>
bool operator!=(const Vector<T>& v1, const Vector<T>& v2) noexcept {
	return !(v1 == v2);	
}

template <typename T>
bool operator<(const Vector<T>& v1, const Vector<T>& v2) noexcept {
	if (v1.sizer() == v2.sizer()) {
		for (auto i = 0; i < v1.sizer(); ++i) {
			if (v1[i] < v2[i])
				return true;
			else if (v1[i] > v2[i])
				return false;
		}
		return false;
	}
	else return (v1.sizer() < v2.sizer());
}

template <typename T>
bool operator>(const Vector<T>& v1, const Vector<T>& v2) {
	if (v1.sizer() == v2.sizer()) {
		for (auto i = 0; i < v1.sizer(); ++i) {
			if (v1[i] > v2[i])
				return true;
			else if (v1[i] < v2[i])
				return false;
		}
		return false;
	}
	else return (v1.sizer()>v2.sizer())
}

template <typename T>
bool operator<=(const Vector<T>& v1, const Vector<T>& v2) {
	return !(v1 > v2);
}

template <typename T>
bool operator>=(const Vector<T>& v1, const Vector<T>& v2) {
	return !(v1 < v2);
}

template <typename T>
int operator-(const IteratorV<T>& obj1, const IteratorV<T>& obj2) {
	IteratorV<T> copy = obj1;
	auto i = 0;
	for (i = 0; copy != obj2; ++i) {
		copy++;
	}
	return i;
}