#pragma once

#include <cstddef>
#include <string>

class Window;

template<class T>
class SharedWindowPtr
{
public:

	SharedWindowPtr();

	SharedWindowPtr(std::nullptr_t) :
		mWindowPtr( T() )
	{

	}
	
	SharedWindowPtr(Window &window, const std::string &windowName = "")
	{
		window.addChildWindow(*this, windowName);
	}

	SharedWindowPtr(const SharedWindowPtr<T>& copy)
	{
		if (copy.get() != nullptr)
		{
			mWindowPtr = copy.get();

			m_RefCount = copy.getRefCount();
			*m_RefCount += 1;
		}
		else
		{
			mWindowPtr = nullptr;
			m_RefCount = nullptr;
		}
	}

	template <class U>
	SharedWindowPtr(const SharedWindowPtr<U>& copy)
	{
		if (copy.get() != nullptr)
		{
			mWindowPtr = static_cast<T*>(copy.get());

			m_RefCount = copy.getRefCount();
			*m_RefCount += 1;
		}
		else
		{
			mWindowPtr = nullptr;
			m_RefCount = nullptr;
		}
	}

	~SharedWindowPtr()
	{
		reset();
	}

	SharedWindowPtr<T>& operator=(const SharedWindowPtr<T>& copy)
	{
		if (this != &copy)
		{
			reset();

			if (copy.get() != nullptr)
			{
				mWindowPtr = copy.get();

				m_RefCount = copy.getRefCount();
				*m_RefCount += 1;
			}
			else
			{
				mWindowPtr = nullptr;
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
			mWindowPtr = static_cast<T*>(copy.get());

			m_RefCount = copy.getRefCount();
			*m_RefCount += 1;
		}
		else
		{
			mWindowPtr = nullptr;
			m_RefCount = nullptr;
		}

		return *this;
	}

	bool operator!() const
	{
		return mWindowPtr == nullptr;
	}

	template <class U>
	bool operator ==(const SharedWindowPtr<U>& right) const
	{
		return mWindowPtr == right.get();
	}

	bool operator ==(const SharedWindowPtr<T>& right) const
	{
		return mWindowPtr == right.mWindowPtr;
	}

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
	bool operator !=(const SharedWindowPtr<U>& right) const
	{
		return mWindowPtr != right.get();
	}

	bool operator !=(const SharedWindowPtr<T>& right) const
	{
		return mWindowPtr != right.mWindowPtr;
	}

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

	void init()
	{
		reset();

		m_RefCount = new unsigned int;
		*m_RefCount = 1;

		mWindowPtr = new T();
		mWindowPtr->m_Callback.widget = get();
	}

	void reset()
	{
		if (mWindowPtr != nullptr)
		{
			if (*m_RefCount == 1)
			{
				delete mWindowPtr;
				delete m_RefCount;

				mWindowPtr = nullptr;
				m_RefCount = nullptr;
			}
			else
				*m_RefCount -= 1;
		}
	}

	T& operator*() const
	{
		assert(mWindowPtr != nullptr);
		return *mWindowPtr;
	}

	T* operator->() const
	{
		assert(mWindowPtr != nullptr);
		return mWindowPtr;
	}

	T* get() const
	{
		return mWindowPtr;
	}

	SharedWindowPtr<T> clone() const
	{
		if (mWindowPtr != nullptr)
		{
			SharedWindowPtr<T> pointer = nullptr;

			pointer.m_RefCount = new unsigned int;
			*pointer.m_RefCount = 1;

			pointer.mWindowPtr = mWindowPtr->clone();
			pointer.mWindowPtr->m_Callback.widget = pointer.get();
			return pointer;
		}
		else
			return nullptr;
	}

	
	unsigned int* getRefCount() const
	{
		return m_RefCount;
	}

private:

	T* mWindowPtr;
	unsigned int* m_RefCount;
};

template <class T>
SharedWindowPtr<T>::SharedWindowPtr() :
mWindowPtr()
{
}