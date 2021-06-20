#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

#include <memory>
#include <iterator>
#include <algorithm>

#include "jstd_core.h"

_JSTD_BEGIN
// JVector const iterator

template <class MyVector>
class JVector_Const_Iterator
{
public:
	using iterator_category = random_access_iterator_tag;
	using value_type = typename MyVector::value_type;
	using difference_type = typename MyVector::difference_type;
	//using pointer = typename MyVector::const_pointer;
	using reference = const value_type&;


private:

};



// JVector insert iterator


// JVector core
template<class T>
class JVector
{
public:
	using value_type             = T;
	using size_type              = std::size_t;
	using difference_type        = std::ptrdiff_t;
	//using pointer = typename _Alty_traits::pointer;
	//using const_pointer = typename _Alty_traits::const_pointer;
	using reference              = T&;
	using const_reference        = const T&;
	using iterator               = T*;
	using const_iterator         = const T*;
	using reverse_iterator       = _STD reverse_iterator<iterator>;
	using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

private:
	size_type data_capacity;
	size_type number_of_elements;
	value_type *data_array;

public:
	JVector() = default;

	explicit JVector(size_type count);

	JVector(size_type count, const T &value);

	JVector(const JVector &other);

	JVector(JVector &&other) noexcept;

	JVector(std::initializer_list<T> init)
	{
		// todo modify me once emplaceback() is implemented
	}

	~JVector() noexcept 
	{ 
		delete[] data_array; 
	}

	void assign(size_type count, const T &value);

	template< class InputIt >
	void assign(InputIt first, InputIt last);

	void assign(std::initializer_list<T> ilist);

	JVector& operator=(const JVector &other)
	{
		if (this == _STD addressof(other))
			return *this;
		
		auto new_data_array = new value_type[other.capacity()];

		if (data_array)
			delete[] data_array;

		data_array = new_data_array;
		std::copy(other.cbegin(), other.cend(), data_array);
		data_capacity = other.data_capacity;
		number_of_elements = other.number_of_elements;
		return *this;
	}

	// Incomplete!
	JVector& operator=(JVector &&other) noexcept
	{
		if (this == _STD addressof(other))
			return *this;

		// Move and assign
		return *this;
	}

	// Incomplete!
	JVector& operator=(std::initializer_list<T> ilist)
	{
		// Resize and copy
		return *this;
	}

	// Element access
	_NODISCARD reference at(size_type pos)
	{ 
		// todo check.
		return data_array[pos]; 
	}

	_NODISCARD const_reference at(size_type pos) const 
	{ 
		// todo check.
		return data_array[pos]; 
	}

	_NODISCARD reference operator[](size_type pos) 
	{ 
		return data_array[pos];
	}

	_NODISCARD const_reference operator[](size_type pos) const
	{ 
		return data_array[pos];
	}

	_NODISCARD reference front() noexcept
	{ 
		return *data_array; 
	}

	_NODISCARD reference front() const noexcept
	{ 
		return *data_array;
	}

	_NODISCARD reference back() noexcept
	{ 
		return data_array[number_of_elements - 1]; 
	}

	_NODISCARD const_reference back() const noexcept
	{ 
		return data_array[number_of_elements - 1]; 
	}

	value_type* data() noexcept 
	{ 
		return data_array; 
	}

	const value_type* data() const noexcept 
	{ 
		return data_array; 
	}

	// Iterators
	_NODISCARD iterator begin() noexcept
	{
		return data_array;
	}

	_NODISCARD const_iterator begin() const noexcept
	{
		return const_iterator(data_array);
	}

	_NODISCARD iterator end() noexcept
	{
		return data_array + number_of_elements;
	}

	_NODISCARD const_iterator end() const noexcept
	{
		return const_iterator(data_array + number_of_elements);
	}

	_NODISCARD reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(end());
	}

	_NODISCARD const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(end());
	}

	_NODISCARD reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin());
	}

	_NODISCARD reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(begin());
	}

	_NODISCARD const_iterator cbegin() const noexcept
	{ 
		return begin(); 
	}

	_NODISCARD const_iterator cend() const noexcept
	{ 
		return end(); 
	}

	_NODISCARD const_reverse_iterator crbegin() const noexcept
	{ 
		return rbegin(); 
	}

	_NODISCARD const_reverse_iterator crend() const noexcept 
	{
		return rend();
	}

	// Capacity
	_NODISCARD bool empty() const noexcept
	{ 
		return number_of_elements == 0; 
	}

	_NODISCARD size_type size() const noexcept
	{ 
		return number_of_elements;
	}

	_NODISCARD size_type max_size() const noexcept;

	void reserve(size_type new_cap);

	_NODISCARD size_type capacity() const noexcept
	{ 
		return data_capacity; 
	}

	void shrink_to_fit();

	// Modifiers
	void clear() noexcept;

	iterator insert(const_iterator pos, const T &value);

	iterator insert(const_iterator pos, T &&value);

	iterator insert(const_iterator pos, size_type count, const T &value);

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last);

	iterator insert(const_iterator pos, std::initializer_list<T> ilist);

	template< class... Args >
	iterator emplace(const_iterator pos, Args&&... args);

	iterator erase(const_iterator pos) noexcept(std::is_nothrow_move_assignable_v<value_type>);

	iterator erase(const_iterator first, const_iterator last) noexcept(std::is_nothrow_move_assignable_v<value_type>);

	void push_back(const T &value)
	{
		// insert element at end, provide strong guarantee.
		emplace_back(value);
	}

	void push_back(T &&value)
	{
		// insert by moving into element at end, provide strong guarantee.
		emplace_back(_STD move(value));
	}

	// todo read placment new
	template<class... Args>
	reference emplace_back(Args&&... args);

	void pop_back();

	void resize(size_type count);

	void resize(size_type count, const value_type &value);

	void swap(JVector &other) noexcept
	{
		if (this != _STD addressof(other))
		{
			using _STD swap;
			swap(data_array, other.data_array);
			swap(number_of_elements, other.number_of_elements);
			swap(data_capacity, other.data_capacity);
		}
	}

	// operator
	/*
	bool operator==(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator!=(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator<(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator<=(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator>(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator>=(const JVector<T> &lhs, const JVector<T> &rhs);
	*/

private:

};

template<class T>
inline JVector<T>::JVector(size_type count)
{
	
}

template<class T>
inline JVector<T>::JVector(size_type count, const T &value)
{
}

template<class T>
inline JVector<T>::JVector(const JVector &other)
{
}

template<class T>
inline JVector<T>::JVector(JVector &&other) noexcept
{
}

template<class T>
inline typename JVector<T>::size_type JVector<T>::max_size() const noexcept
{
	return (_STD min)(
		static_cast<size_type>((_STD numeric_limits<difference_type>::max)()), static_cast<size_type>(-1) / sizeof(value_type));
}


_JSTD_END
#endif // !_JVECTOR_