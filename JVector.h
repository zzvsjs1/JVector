#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

#include <algorithm>
#include <iterator>
#include <memory>

#include "jstd_core.h"

_JSTD_BEGIN
// JVector const iterator
/*
template <class MyVector>
class JVector_Const_Iterator
{
public:
	using iterator_category = _STD random_access_iterator_tag;
	using value_type        = typename MyVector::value_type;
	using difference_type   = typename MyVector::difference_type;
	using pointer           = typename MyVector::const_pointer;
	using reference         = const value_type&;

	using ptr = typename MyVector::pointer;

	JVector_Const_Iterator() noexcept : ptr() {}

	reference operator*() const noexcept
	{
		return *ptr;
	}


private:

};
*/



// JVector core, allocator is not used.
template<class T, class Alloc = _STD allocator<T>>
class JVector
{
private:
	using alty                   = typename _STD allocator_traits<Alloc>::template rebind_alloc<T>;
	using alty_traits            = _STD allocator_traits<alty>;
	
public:
	using value_type             = T;
	using allocator_type         = Alloc;
	//using pointer                = typename alty_traits::pointer;
	using pointer                = T*;
	using const_pointer          = typename alty_traits::const_pointer;
	using size_type              = typename alty_traits::size_type;
	using difference_type        = typename alty_traits::difference_type;
	using reference              = T&;
	using const_reference        = const T&;
	using iterator               = T*;
	using const_iterator         = const T*;
	using reverse_iterator       = _STD reverse_iterator<iterator>;
	using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

private:
	size_type m_data_capacity;
	size_type m_number_of_elements;
	value_type *m_data_array;

public:
	JVector() noexcept(_STD is_nothrow_default_constructible_v<alty>) = default;

	explicit JVector(size_type count);

	JVector(size_type count, const T &value);

	JVector(const JVector &other);

	JVector(JVector &&other) noexcept;

	JVector(_STD initializer_list<T> init);

	~JVector() noexcept;

	void assign(size_type count, const T &value);

	template< class InputIt >
	void assign(InputIt first, InputIt last);

	void assign(_STD initializer_list<T> ilist);

	JVector& operator=(const JVector &other);

	JVector& operator=(JVector &&other) noexcept;

	JVector& operator=(_STD initializer_list<T> ilist);

	_NODISCARD reference at(size_type pos);

	_NODISCARD const_reference at(size_type pos) const;

	_NODISCARD reference operator[](size_type pos);

	_NODISCARD const_reference operator[](size_type pos) const;

	_NODISCARD reference front() noexcept
	{
		return *m_data_array; 
	}

	_NODISCARD reference front() const noexcept
	{ 
		return *m_data_array;
	}

	_NODISCARD reference back() noexcept
	{ 
		return m_data_array[m_number_of_elements - 1]; 
	}

	_NODISCARD const_reference back() const noexcept
	{ 
		return m_data_array[m_number_of_elements - 1]; 
	}

	_NODISCARD value_type* data() noexcept
	{ 
		return m_data_array; 
	}

	_NODISCARD const value_type* data() const noexcept
	{ 
		return m_data_array; 
	}

	// Iterators
	_NODISCARD iterator begin() noexcept
	{
		return m_data_array;
	}

	_NODISCARD const_iterator begin() const noexcept
	{
		return const_iterator(m_data_array);
	}

	_NODISCARD iterator end() noexcept
	{
		return  m_data_array + m_number_of_elements;
	}

	_NODISCARD const_iterator end() const noexcept
	{
		return const_iterator(m_data_array + m_number_of_elements);
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
	_NODISCARD bool empty() const noexcept;

	_NODISCARD size_type size() const noexcept;

	_NODISCARD size_type max_size() const noexcept;

	void reserve(size_type new_cap);

	_NODISCARD size_type capacity() const noexcept;

	void shrink_to_fit();

	// Modifiers
	void clear() noexcept;

	iterator insert(const_iterator pos, const T &value);

	iterator insert(const_iterator pos, T &&value);

	iterator insert(const_iterator pos, size_type count, const T &value);

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last);

	iterator insert(const_iterator pos, _STD initializer_list<T> ilist);

	template< class... Args >
	iterator emplace(const_iterator pos, Args&&... args);

	iterator erase(const_iterator pos) noexcept(_STD is_nothrow_move_assignable_v<value_type>);

	iterator erase(const_iterator first, const_iterator last) noexcept(_STD is_nothrow_move_assignable_v<value_type>);

	void push_back(const T &value);

	void push_back(T &&value);

	template<class... Args>
	reference emplace_back(Args&&... args);

	void pop_back();

	void resize(size_type count);

	void resize(size_type count, const value_type &value);

	void swap(JVector &other) noexcept;


	/*
	bool operator<(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator<=(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator>(const JVector<T> &lhs, const JVector<T> &rhs);
	bool operator>=(const JVector<T> &lhs, const JVector<T> &rhs);
	*/

private:
	void allocate_new_capacity(const size_type new_capacity);
	value_type* allocate_memory(const size_type size);
	void fill_n_to_array(pointer dest, const size_type count, const T& value);
	void destroy() noexcept;
	_NODISCARD size_type calculate_growth(const size_type new_size) const;
	static void assign_range(iterator from, iterator to, value_type value);
	static void copy_range(const_iterator from, const_iterator to, pointer dist) noexcept;
	static void move_range(iterator from, iterator to, pointer dist) noexcept;

};

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(size_type count) : m_data_capacity(count),
m_number_of_elements(count),
m_data_array(nullptr)
{
	if (count != 0)
		m_data_array = allocate_memory(count);
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(size_type count, const T &value) :
	m_data_capacity(count),
	m_number_of_elements(count),
	m_data_array(nullptr)
{
	if (count != 0)
	{
		m_data_array = allocate_memory(count);
		assign_range(begin(), end(), value);
	}
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(const JVector &other) :
	m_data_capacity(other.m_data_capacity),
	m_number_of_elements(other.m_number_of_elements),
	m_data_array(nullptr)
{
	if (other.m_number_of_elements != 0)
	{
		m_data_array = allocate_memory(other.m_data_capacity);
		copy_range(other.cbegin(), other.cend(), m_data_array);
	}
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(JVector &&other) noexcept :
	m_data_capacity(other.m_data_capacity), 
	m_number_of_elements(other.m_number_of_elements),
	m_data_array(other.m_data_array)
{
	other.m_data_capacity = 0;
	other.m_number_of_elements = 0;
	other.m_data_array = nullptr;
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(_STD initializer_list<T> init) :
	m_data_capacity(init.size()),
	m_number_of_elements(init.size()),
	m_data_array(nullptr)
{
	if (init.size() != 0)
	{
		m_data_array = allocate_memory(init.size());
		copy_range(init.begin(), init.end(), m_data_array);
	}
}

template <class T, class Alloc>
inline JVector<T, Alloc>::~JVector() noexcept
{
	destroy();
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::assign(size_type count, const T &value)
{
}

template <class T, class Alloc>
template<class InputIt>
inline void 
JVector<T, Alloc>::assign(InputIt first, InputIt last)
{

}

template <class T, class Alloc>
template<class InputIt>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, InputIt first, InputIt last)
{
	
}

template <class T, class Alloc>
template<class ...Args>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::emplace(const_iterator pos, Args &&...args)
{
	
}

template <class T, class Alloc>
template<class ...Args>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::emplace_back(Args &&...args)
{
	return reference();
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::assign(_STD initializer_list<T> ilist)
{
	
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(const JVector &other)
{
	if (this != _STD addressof(other))
	{
		destroy();
		copy_range(other.cbegin(), other.cend(), begin());
	}

	return *this;
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(JVector &&other) noexcept
{
	if (this != _STD addressof(other))
	{
		destroy();

		m_data_capacity = other.m_data_capacity;
		m_number_of_elements = other.m_number_of_elements;
		m_data_array = other.m_data_array;

		other.m_data_capacity = 0;
		other.m_number_of_elements = 0;
		other.m_data_array = nullptr;
	}

	return *this;
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(_STD initializer_list<T> ilist)
{
	// TODO: insert return statement here
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::at(size_type pos)
{
	if (size() <= pos)
		throw _STD out_of_range("JVector's index out of range.");

	return m_data_array[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::at(size_type pos) const
{
	if (size() <= pos)
		throw _STD out_of_range("JVector's index out of range.");

	return m_data_array[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::operator[](size_type pos)
{
#ifdef JSTL_DEBUG
	assert(("Index out of bound.", pos < size()));
#endif // JSTL_DEBUG
	
	return m_data_array[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::operator[](size_type pos) const
{
	return m_data_array[pos];
}

template <class T, class Alloc>
inline bool 
JVector<T, Alloc>::empty() const noexcept
{
	return m_number_of_elements == 0;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::size() const noexcept
{
	return m_number_of_elements;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::max_size() const noexcept
{
	return (_STD min)(
		static_cast<size_type>((_STD numeric_limits<difference_type>::max)()),
			static_cast<size_type>(-1) / sizeof(value_type));
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::reserve(size_type new_cap)
{
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::capacity() const noexcept
{
	return m_data_capacity;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::shrink_to_fit()
{
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, const T& value)
{
	
}

template <class T, class Alloc>
typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, T&& value)
{
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, size_type count, const T & value)
{
	
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, ::std::initializer_list<T> ilist)
{
	return iterator();
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::erase(const_iterator pos) noexcept(::std::is_nothrow_move_assignable_v<value_type>)
{
	return iterator();
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::erase(const_iterator first, const_iterator last) noexcept(::std::is_nothrow_move_assignable_v<value_type>)
{
	
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::push_back(const T & value)
{
	// insert element at end, provide strong guarantee.
	emplace_back(value);
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::push_back(T && value)
{
	// insert by moving into element at end, provide strong guarantee.
	emplace_back(_STD move(value));
}


template <class T, class Alloc>
inline void 
JVector<T, Alloc>::clear() noexcept
{
	destroy();
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::swap(JVector & other) noexcept
{
	if (this != _STD addressof(other))
	{
		using _STD swap;
		swap(m_data_array, other.m_data_array);
		swap(m_number_of_elements, other.m_number_of_elements);
		swap(m_data_capacity, other.m_data_capacity);
	}
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::allocate_new_capacity(const size_type new_capacity)
{
	auto new_array = allocate_memory();
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::value_type*
JVector<T, Alloc>::allocate_memory(const size_type size)
{
	return new value_type[size];
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::destroy() noexcept
{
	if (m_data_array)
	{
		m_data_capacity = 0;
		m_number_of_elements = 0;
		delete[] m_data_array;
		m_data_array = nullptr;
	}
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::calculate_growth(const size_type new_size) const
{
	const size_type old_capacity = capacity();

	// geometric growth would overflow
	if (const auto max = max_size(); old_capacity > max - old_capacity / 2) {
		return max;
	}

	// 1.5 times capacity
	const size_type geometric = old_capacity + old_capacity / 2;
	
	// geometric growth would be insufficient
	if (geometric < new_size) {
		return new_size;
	}

	return geometric;
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::assign_range(iterator from, iterator to, value_type value)
{
	for (; from != to; ++from)
		*from = value;
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::copy_range(const_iterator from, const_iterator to, pointer dist) noexcept
{
	for (size_type i = 0; from != to; ++from, ++i)
		dist[i] = *from;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::move_range(iterator from, iterator to, pointer dist) noexcept
{
	for (size_type i = 0; from != to; ++from, ++i)
		dist[i] = _STD move(*from);
}




// op overloaded. If no cxx20
template <class T, class Alloc>
_NODISCARD bool operator==(const JVector<T, Alloc> &lhs, const JVector<T, Alloc> &rhs)
{
	return lhs.size() != rhs.size() && _STD equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <class T, class Alloc>
_NODISCARD bool operator!=(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return !(left == right);
}


_JSTD_END
#endif // !_JVECTOR_