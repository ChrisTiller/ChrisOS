#pragma once

#include <cstddef>
#include <string>

class Window;

template<class T>
class SharedWindowPtr
{
public:

	template<class T>
	SharedWindowPtr() :
		mWindowPtr( T() )
	{
	}

	template<class T>
	SharedWindowPtr(std::nullptr_t) :
		mWindowPtr( T() )
	{

	}
	SharedWindowPtr(Window &window, const std::string &windowName = "");
	SharedWindowPtr(const SharedWindowPtr<T> &copy);

	template<class U>
	SharedWindowPtr(const SharedWindowPtr<U> &copy);

	~SharedWindowPtr();


	template <class T>
	SharedWindowPtr<T>& operator=(const SharedWindowPtr<T>& copy)
	{
		if (this != &copy)
		{
			reset();

			if (copy.get() != nullptr)
			{
				m_WidgetPtr = copy.get();

				m_RefCount = copy.getRefCount();
				*m_RefCount += 1;
			}
			else
			{
				m_WidgetPtr = nullptr;
				m_RefCount = nullptr;
			}
		}

		return *this;
	}

	template <class U>
	SharedWindowPtr<T>& operator=(const SharedWindowPtr<U>& copy)
	{
		reset();

		if (copy.get() != nullptr)
		{
			m_WidgetPtr = static_cast<T*>(copy.get());

			m_RefCount = copy.getRefCount();
			*m_RefCount += 1;
		}
		else
		{
			m_WidgetPtr = nullptr;
			m_RefCount = nullptr;
		}

		return *this;
	}

	bool operator!() const;

	template<typename U>
	bool operator ==(const SharedWindowPtr<U> &right) const;

	bool operator ==(const SharedWindowPtr<T> &right) const;

	template<typename U>
	friend bool operator ==(const SharedWindowPtr<T> &left, const U *right)
	{
		return left.mWindowPtr == right;
	}

	friend bool operator ==(const SharedWindowPtr<T> &left, const T *right)
	{
		return left.mWindowPtr == right;
	}

	template <typename U>
	friend bool operator ==(const U *left, const SharedWindowPtr<T> &right)
	{
		return left == right.mWindowPtr;
	}

	friend bool operator==(const T* left, const SharedWindowPtr<T>& right)
	{
		return left == right.mWindowPtr;
	}

	template <typename U>
	bool operator !=(const SharedWindowPtr<U>& right) const;

	bool operator !=(const SharedWindowPtr<T>& right) const;

	template <typename U>
	friend bool operator !=(const SharedWindowPtr<T>& left, const U* right)
	{
		return left.mWindowPtr != right;
	}

	friend bool operator !=(const SharedWindowPtr<T>& left, const T* right)
	{
		return left.mWindowPtr != right;
	}

	template <typename U>
	friend bool operator !=(const U* left, const SharedWindowPtr<T>& right)
	{
		return left != right.mWindowPtr;
	}

	friend bool operator !=(const T* left, const SharedWindowPtr<T>& right)
	{
		return left != right.mWindowPtr;
	}

	void init();

	void reset();

	T& operator*() const;

	T* operator->() const;

	T* getWindow() const;

	SharedWindowPtr clone() const;

	unsigned int* getRefCount() const;

private:

	T* mWindowPtr;
	unsigned int* m_RefCount;
};

