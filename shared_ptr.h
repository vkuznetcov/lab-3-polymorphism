#pragma once

template <typename T>
class SharedPtr {
	T* ptr;
	size_t* count;
	
public:
	////constructors
	SharedPtr<T>() : ptr(nullptr), count(new size_t(0)) { std::cout << "creating empty SharedPtr" << std::endl << std::endl; }

	explicit SharedPtr<T>(T* ptr) : ptr(ptr), count(new size_t(1)) { std::cout << "creating SharedPtr with parameter" << std::endl << std::endl; }

	SharedPtr<T>(const SharedPtr<T>& obj) {
		std::cout << "copy-ctor" << std::endl << std::endl;
		count = obj.count;
		++(*count);
		ptr = obj.ptr;
	}

	SharedPtr(SharedPtr<T>&& obj) : ptr(obj.ptr), count(obj.count) {
		std::cout << "move-ctor" << std::endl << std::endl;
		obj.ptr = nullptr;
	}

	SharedPtr<T>(std::nullptr_t nullp) : ptr(nullptr), count(new size_t(0)) { std::cout << "creating null SharedPtr" << std::endl << std::endl; }

	~SharedPtr() {
		reset();
	}

	////assigment operators
	SharedPtr<T>& operator=(SharedPtr<T>&& obj) noexcept {
		SharedPtr<T>(std::move(obj)).swap(*this);
		return *this;
	}

	SharedPtr<T>& operator=(std::nullptr_t nullp) noexcept {
		reset();
		return *this;
	}

	SharedPtr<T>& operator=(const SharedPtr<T>& obj) noexcept {
		SharedPtr<T>(obj).swap(*this);
		return *this;
	}

	////modificators
	void swap(SharedPtr& obj) noexcept {
		auto tmp = this->ptr;
		this->ptr = obj.ptr;
		obj.ptr = tmp;

		auto count = this->count;
		this->count = obj.count;
		obj.count = count;
	}

	void reset() {
		std::cout << "process: removing SharedPtr" << std::endl << std::endl;
		if ((*count) == 1) {
			std::cout << "process: destroying SharedPtr object(you should see a message about destroying the object)" << std::endl << std::endl;
			delete ptr;
		}

		ptr = nullptr;
		--(*count);
	}

	////spectators
	long use_count() const {
		return *count;
	}

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
		return ptr;
	}
};

template <typename T>
bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return lhs.get() == rhs.get();
}

template <typename T>
bool operator==(const SharedPtr<T>& obj, std::nullptr_t nullp) {
	return !obj.get();
}

template <typename T>
bool operator==(std::nullptr_t nullp, const SharedPtr<T>& obj) {
	return !obj.get();
}

template <typename T>
bool operator!=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return lhs.get() != rhs.get();
}

template <typename T>
bool operator!=(const SharedPtr<T>& obj, std::nullptr_t nullp) {
	return (bool)obj;
}

template <typename T>
bool operator!=(std::nullptr_t nullp, const SharedPtr<T>& obj) {
	return (bool)obj;
}

template <typename T>
bool operator>(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return lhs.get() > rhs.get();
}

template <typename T>
bool operator>=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return lhs.get() >= rhs.get();
}

template <typename T>
bool operator<(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return lhs.get() < rhs.get();
}

template <typename T>
bool operator<=(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs) {
	return lhs.get() <= rhs.get();
}