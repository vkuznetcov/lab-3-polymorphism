#pragma once 

template<typename T>

class UniquePtr {

	T* ptr;

	UniquePtr(UniquePtr<T>& ptr) = delete;

	UniquePtr<T> operator=(const UniquePtr<T>& ptr) = delete;

public:

	////constructors


	UniquePtr<T>() : ptr(nullptr) { std::cout << "creating empty UniquePtr" << std::endl << std::endl; }

	explicit UniquePtr<T>(T* ptr) :ptr(ptr) { std::cout << "creating UniquePtr with parameter" << std::endl << std::endl; }

	UniquePtr(UniquePtr<T>&& ptr): ptr(ptr.ptr) noexcept {	
		std::cout << "move_ctor" << std::endl << std::endl;
		ptr.ptr = nullptr;
	}

	~UniquePtr(){
		//checking for allocated memory
		reset();
		std::cout << "removing UniquePtr" << std::endl << std::endl;
	}

	UniquePtr<T>(std::nullptr_t nullp) : ptr(nullptr) { std::cout << "creating null UniquePtr" << std::endl << std::endl; }

	////assigment operators

	UniquePtr<T>& operator=(UniquePtr<T>&& tmp) {
		if (*this == tmp)
			return *this;

		if (tmp.ptr) {
			ptr = tmp.ptr;
			tmp.ptr = nullptr;
		}
		else
			reset();

		return *this;
	}

	UniquePtr<T>& operator=(std::nullptr_t nullp) noexcept {
		reset();
		return *this;
	}

	////modificators

	void swap(UniquePtr& pointer) noexcept {
		T* tmp = this->ptr;
		this->ptr = pointer.ptr;
		pointer.ptr = T* tmp;
	}

	UniquePtr<T> release() {
		if (ptr) {
			UniquePtr<T> copyPtr(this->ptr);
			delete ptr;
			ptr = nullptr;
			return copyPtr;
		}
		return nullptr;
	}

	void reset() {
		if (ptr)
			delete ptr;
		ptr = nullptr;
	}

	////spectators methods

	explicit operator bool() const noexcept {
		if (ptr)
			return true;
		return false;
	}

	T* get() const {
		if (ptr)
			return ptr;
		return nullptr;
	}

	////access operators

	T& operator*() {
		return *ptr;
	}

	T& operator*() const {
		return *ptr;
	}

	T* operator->() const noexcept {
		return get();
	}

	

};

template <typename T>
bool operator==(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return lhs.get() == rhs.get();
}

template <typename T>
bool operator==(std::nullptr_t nullp, const UniquePtr<T>& obj) {
	return !obj.get();
}

template <typename T>
bool operator==(const UniquePtr<T>& obj, std::nullptr_t nullp) {
	return !obj.get();
}

template <typename T>
bool operator!=(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return rhs.get() != lhs.get();
}

template <typename T>
bool operator!=(std::nullptr_t nullp, const UniquePtr<T>& obj)noexcept {
	return (bool)obj;
}

template <typename T>
bool operator!=(const UniquePtr<T>& obj, std::nullptr_t nullp)noexcept {
	return (bool)obj;
}

template <typename T>
bool operator<(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return lhs.get() < rhs.get();
}

template <typename T>
bool operator>(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return lhs.get() > rhs.get();
}

template <typename T>
bool operator<=(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return lhs.get() <= rhs.get();
}

template <typename T>
bool operator>=(const UniquePtr<T>& lhs, const UniquePtr<T>& rhs) {
	return lhs.get() >= rhs.get();
}