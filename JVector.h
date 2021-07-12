#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

#include <cassert>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <limits>

#include "jstd_core.h"

_JSTD_BEGIN

// JVector const iterator. This class manages a pointer to an JVector.
template <class MyVector>
class JVector_Const_Iterator
{
public:
	using iterator_category = _STD random_access_iterator_tag;
	using value_type        = typename MyVector::value_type;
	using difference_type   = typename MyVector::difference_type;
	using pointer           = typename MyVector::const_pointer;
	using reference         = const value_type&;
	
	using ptr_t             = typename MyVector::pointer;

	// A public member pointer, same design as MSVC STL
	ptr_t ptr;
	
	JVector_Const_Iterator() noexcept = default;

	JVector_Const_Iterator(ptr_t pointer) noexcept : ptr(pointer) {}

	JVector_Const_Iterator& operator=(const JVector_Const_Iterator&) noexcept = default;

	reference operator*() const noexcept
	{
		return *ptr;
	}

	pointer operator->() const noexcept
	{
		return ptr;
	}

	JVector_Const_Iterator& operator++() noexcept
	{
		++ptr;
		return *this;
	}

	JVector_Const_Iterator operator++(int) noexcept
	{
		JVector_Const_Iterator temp = *this;
		++*this;
		return temp;
	}

	JVector_Const_Iterator& operator--() noexcept
	{
		--ptr;
		return *this;
	}

	JVector_Const_Iterator operator--(int) noexcept
	{
		JVector_Const_Iterator temp = *this;
		--*this;
		return temp;
	}

	JVector_Const_Iterator& operator+=(const difference_type off) noexcept
	{
		ptr += off;
		return *this;
	}

	NODISCARD JVector_Const_Iterator operator+(const difference_type off) const noexcept
	{
		JVector_Const_Iterator temp = *this;
		temp += off;
		return temp;
	}

	NODISCARD JVector_Const_Iterator& operator-=(const difference_type off) noexcept
	{
		return *this += -off;
	}

	NODISCARD JVector_Const_Iterator operator-(const difference_type off) const noexcept
	{
		JVector_Const_Iterator temp = *this;
		temp -= off;
		return temp;
	}

	NODISCARD difference_type operator-(const JVector_Const_Iterator &right) const noexcept
	{
		return ptr - right.ptr;
	}

	NODISCARD reference operator[](const difference_type off) const noexcept
	{
		return *(*this + off);
	}

	NODISCARD bool operator==(const JVector_Const_Iterator &right) const noexcept
	{
		return ptr == right.ptr;
	}

	NODISCARD bool operator!=(const JVector_Const_Iterator &right) const noexcept
	{
		return !(*this == right);
	}

	NODISCARD bool operator<(const JVector_Const_Iterator &right) const noexcept
	{
		return ptr < right.ptr;
	}

	NODISCARD bool operator>(const JVector_Const_Iterator &right) const noexcept
	{
		return right < *this;
	}

	NODISCARD bool operator<=(const JVector_Const_Iterator &right) const noexcept
	{
		return !(right < *this);
	}

	NODISCARD bool operator>=(const JVector_Const_Iterator &right) const noexcept
	{
		return !(*this < right);
	}
};

// Iterator
template <class MyVector>
class JVector_Iterator : public JVector_Const_Iterator<MyVector>
{
public:
	using my_base           = JVector_Const_Iterator<MyVector>;

	using iterator_category = _STD random_access_iterator_tag;
	using value_type        = typename MyVector::value_type;
	using difference_type   = typename MyVector::difference_type;
	using pointer           = typename MyVector::pointer;
	using reference         = value_type&;

	using my_base::my_base;

	JVector_Iterator& operator=(const JVector_Iterator&) noexcept = default;

	NODISCARD reference operator*() const noexcept
	{
		return const_cast<reference>(my_base::operator*());
	}

	NODISCARD pointer operator->() const noexcept
	{
		return this->ptr;
	}

	JVector_Iterator& operator++() noexcept
	{
		my_base::operator++();
		return *this;
	}

	JVector_Iterator operator++(int) noexcept
	{
		JVector_Iterator temp = *this;
		my_base::operator++();
		return temp;
	}

	JVector_Iterator& operator--() noexcept
	{
		my_base::operator--();
		return *this;
	}

	JVector_Iterator operator--(int) noexcept
	{
		JVector_Iterator temp = *this;
		my_base::operator--();
		return temp;
	}

	JVector_Iterator& operator+=(const difference_type  off) noexcept
	{
		my_base::operator+=(off);
		return *this;
	}

	NODISCARD JVector_Iterator operator+(const difference_type off) const noexcept
	{
		JVector_Iterator temp = *this;
		temp += off;
		return temp;
	}

	JVector_Iterator& operator-=(const difference_type off) noexcept {
		static_cast<void>(my_base::operator-=(off));
		return *this;
	}

	using my_base::operator-;

	NODISCARD JVector_Iterator operator-(const difference_type off) const noexcept
	{
		JVector_Iterator temp = *this;
		temp -= off;
		return temp;
	}

	NODISCARD reference operator[](const difference_type off) const noexcept
	{
		return const_cast<reference>(my_base::operator[](off));
	}
};

template <class MyVector>
NODISCARD JVector_Iterator<MyVector> operator+(
	typename JVector_Iterator<MyVector>::difference_type off, JVector_Iterator<MyVector> next) noexcept
{
	return next += off;
}

// JVector is a class that provides mutable arrays. The allocator is not used.
template<class T, class Allocator = _STD allocator<T>>
class JVector
{
private:
	using alty                   = typename _STD allocator_traits<Allocator>::template rebind_alloc<T>;
	using alty_traits            = _STD allocator_traits<alty>;
	
public:
	using value_type             = T;
	using allocator_type         = Allocator;
	//using pointer                = typename alty_traits::pointer;
	using pointer                = T*;
	//using const_pointer          = typename alty_traits::const_pointer;
	using const_pointer          = const T*;
	using reference              = value_type&;
	using const_reference        = const value_type&;
	using size_type              = typename alty_traits::size_type;
	using difference_type        = typename alty_traits::difference_type;
	using iterator               = JVector_Iterator<JVector<T, Allocator>>;
	using const_iterator         = JVector_Const_Iterator<JVector<T, Allocator>>;
	using reverse_iterator       = _STD reverse_iterator<iterator>;
	using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

private:
	size_type m_capacity;
	size_type m_size;
	pointer m_data;

public:
	JVector() noexcept(_STD is_nothrow_default_constructible_v<alty>);

	explicit JVector(size_type count);

	JVector(size_type count, const T &value);

	JVector(const JVector &other);

	JVector(JVector &&other) noexcept;

	JVector(_STD initializer_list<T> init);

	~JVector() noexcept;

	void assign(size_type count, const T &value);

	template <class InputIt>
	void assign(InputIt first, InputIt last);

	void assign(_STD initializer_list<T> ilist);

	JVector& operator=(const JVector &other);

	JVector& operator=(JVector &&other) noexcept;

	JVector& operator=(_STD initializer_list<T> ilist);

	NODISCARD reference at(size_type pos);

	NODISCARD const_reference at(size_type pos) const;

	NODISCARD reference operator[](size_type pos);

	NODISCARD const_reference operator[](size_type pos) const;

	NODISCARD reference front() noexcept;
	
	NODISCARD reference front() const noexcept;

	NODISCARD reference back() noexcept;

	NODISCARD const_reference back() const noexcept;

	NODISCARD value_type* data() noexcept;

	NODISCARD const value_type* data() const noexcept;
	
	NODISCARD iterator begin() noexcept;

	NODISCARD const_iterator begin() const noexcept;

	NODISCARD iterator end() noexcept;

	NODISCARD const_iterator end() const noexcept;

	NODISCARD reverse_iterator rbegin() noexcept;

	NODISCARD const_reverse_iterator rbegin() const noexcept;

	NODISCARD reverse_iterator rend() noexcept;

	NODISCARD reverse_iterator rend() const noexcept;

	NODISCARD const_iterator cbegin() const noexcept;

	NODISCARD const_iterator cend() const noexcept;

	NODISCARD const_reverse_iterator crbegin() const noexcept;

	NODISCARD const_reverse_iterator crend() const noexcept;

	NODISCARD bool empty() const noexcept;

	NODISCARD size_type size() const noexcept;

	NODISCARD size_type max_size() const noexcept;

	void reserve(size_type new_cap);

	NODISCARD size_type capacity() const noexcept;

	void shrink_to_fit();

	void clear() noexcept;

	iterator insert(const_iterator pos, const T &value);

	iterator insert(const_iterator pos, T &&value);

	iterator insert(const_iterator pos, size_type count, const T &value);

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last);

	iterator insert(const_iterator pos, _STD initializer_list<T> ilist);

private:
	void destroy_range_and_reallocate_in_active(pointer first, pointer last);

	template <class Iter>
	void destroy_range(Iter first, Iter last) noexcept;
	
	template <class Iter>
	void assign_range(Iter first, Iter last);
	
	template <class... Args>
	decltype(auto) emplace_back_with_unused_capacity(Args&&... args);

	template <class... Args>
	pointer emplace_reallocate(const_iterator pos, Args&&... args);

	void change_array(pointer new_array, size_type new_capacity, size_type new_number_of_elements) noexcept;

public:
	template <class... Args>
	iterator emplace(const_iterator pos, Args&&... args);

	template <class... Args>
	reference emplace_back(Args&&... args);

	iterator erase(const_iterator pos) noexcept(_STD is_nothrow_move_assignable_v<value_type>);

	iterator erase(const_iterator first, const_iterator last) noexcept(_STD is_nothrow_move_assignable_v<value_type>);

	void push_back(const T &value);

	void push_back(T &&value);

	void pop_back() noexcept;
	
	void resize(size_type count);

	void resize(size_type count, const value_type &value);

	void swap(JVector &other) noexcept;

protected:
	void range_check(size_type n) const;

private:
	template <class Iter>
	void range_construct(Iter first, Iter last);
	
	static pointer allocate_memory(size_type size);

	void dellocate_and_reset_memeber() noexcept;
	
	NODISCARD size_type calculate_growth(size_type new_size) const;
	
	static void assign_copy_range(iterator from, iterator to, const_reference value);

	template <class Iter>
	static void copy_range(Iter from, Iter to, pointer dist);
	
	template <class Iter>
	static Iter move_range(Iter from, Iter to, pointer dist) noexcept;

	template <class Iter>
	static Iter rmove_range(Iter from, Iter to, pointer dist) noexcept;
	
};

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector() noexcept(::std::is_nothrow_default_constructible_v<alty>) :
	m_capacity(),
	m_size(),
	m_data()
{
	
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(size_type count) :
	m_capacity(count),
	m_size(count),
	m_data(allocate_memory(count))
{
	if (m_data)
	{
		for (auto start = m_data, end = m_data + m_size; start != end; start++)
		{
			::new(start) value_type();
		}
	}
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(size_type count, const T &value) :
	m_capacity(count),
	m_size(count),
	m_data(allocate_memory(count))
{
	if (m_data)
	{
		for (auto start = m_data, end = m_data + m_size; start != end; start++)
		{
			::new(start) value_type(value);
		}
	}
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(const JVector &other) :
	m_capacity(other.m_capacity),
	m_size(other.m_size),
	m_data(allocate_memory(other.m_capacity))
{
	// TODO: Do we need to use function try block?
	try
	{
		if (other.m_size != 0)
		{
			copy_range(other.cbegin(), other.cend(), m_data);
		}
	}
	catch (...)
	{
		delete[] m_data;
		throw;
	}
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(JVector &&other) noexcept :
	m_capacity(), 
	m_size(),
	m_data()
{
	dellocate_and_reset_memeber();
	swap(other);
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(_STD initializer_list<T> init) :
	m_capacity(),
	m_size(),
	m_data()
{
	range_construct(init.begin(), init.end());
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::~JVector() noexcept
{
	delete[] m_data;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::assign(size_type count, const T &value)
{
	if (count > m_size)
	{

	}
	else
	{

	}
}

template <class T, class Alloc>
template <class InputIt>
inline void 
JVector<T, Alloc>::assign(InputIt first, InputIt last)
{
	// TODO assign
}

template <class T, class Alloc>
template <class InputIt>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, InputIt first, InputIt last)
{
	// TODO assign
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::change_array(pointer new_data, size_type new_capacity, size_type new_size) noexcept
{
	delete[] m_data;
	m_data = new_data;
	m_capacity = new_capacity;
	m_size = new_size;
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::destroy_range_and_reallocate_in_active(pointer first, pointer last)
{
	// Destroy [first, last) using raw pointer.
	if (first != last && first != m_data + m_size)
	{
		size_type distance = last - first;
		size_type new_capacity = m_capacity - distance;
		pointer new_vector = allocate_memory(new_capacity);
		pointer second_half_start_point = new_vector + (first - m_data);

		move_range(m_data, first, new_vector);
		move_range(last, m_data + m_size, second_half_start_point);

		change_array(new_vector, new_capacity, m_size - distance);
	}
}

template <class T, class Allocator>
template <class Iter>
inline void
JVector<T, Allocator>::destroy_range(Iter first, Iter last) noexcept
{
	if constexpr (
		!_STD is_trivially_destructible_v<typename _STD iterator_traits<pointer>::value_type>)
	{
		for (; first != last; ++first)
		{
			first->~T();
		}
	}
}

template <class T, class Alloc>
template <class Iter>
inline void
JVector<T, Alloc>::assign_range(Iter first, Iter last)
{
	pointer my_next = m_data;
	pointer my_last = m_data + m_capacity;
		
	// Copy from source.
	for (; first != last && my_next != my_last; ++first, ++my_next)
	{
		*my_next = *first;
	}

	// Trim vector, if capacity > number of elements.
	destroy_range_and_reallocate_in_active(my_next, my_last);

	// Append to the end, if there are remaining elements.
	// Warning: Maybe poor performance.
	for (; first != last; ++first)
	{
		emplace_back(*first);
	}
}

template <class T, class Alloc>
template <class... Args>
inline decltype(auto)
JVector<T, Alloc>::emplace_back_with_unused_capacity(Args&&... value)
{
	::new(m_data + m_size) value_type(_STD forward<Args>(value)...);
	return *(m_data + m_size++);
}

template <class T, class Alloc>
template <class... Args>
typename JVector<T, Alloc>::pointer
JVector<T, Alloc>::emplace_reallocate(const_iterator pos, Args&&... value)
{
	if (m_capacity == max_size())
	{
		throw _STD logic_error("JVector too long");
	}

	const auto new_capacity = calculate_growth(m_capacity + 1);
	const auto added_pos = static_cast<size_type>(pos.ptr - m_data);
	const pointer new_vector = allocate_memory(new_capacity);

	try
	{
		::new(new_vector + added_pos) value_type(_STD forward<Args>(value)...);
	}
	catch (...)
	{
		delete[] new_vector;
		throw;
	}

	move_range(m_data, pos.ptr, new_vector);
	move_range(pos.ptr, m_data + m_size, new_vector + added_pos + 1);
	change_array(new_vector, new_capacity, m_size + 1);
	
	return new_vector + added_pos;
}

template <class T, class Alloc>
template <class ...Args>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::emplace(const_iterator pos, Args&&... args)
{
	pointer where_ptr = pos.ptr;

	// Check if vector have enough space to store a new object.
	if (m_size != m_capacity)
	{
		// If where pointer equal to the back + 1.
		if (where_ptr == m_data + m_size)
		{
			// Emplace to the back.
			emplace_back_with_unused_capacity(_STD forward<Args>(args)...);
		}
		else
		{
			rmove_range(m_data + m_size, where_ptr - 1, m_data + m_size + 1);
			new (where_ptr) value_type(_STD forward<Args>(args)...);
			++m_size;
		}

		return iterator(where_ptr);
	}

	// Reallocate vector and construct a new object to array.
	return iterator(emplace_reallocate(where_ptr, _STD forward<Args>(args)...));
}

template <class T, class Alloc>
template <class... Args>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::emplace_back(Args&&... args)
{
	// Check if vector have enough space to store a new object.
	if (m_size != m_capacity)
	{
		return emplace_back_with_unused_capacity(_STD forward<Args>(args)...);
	}
	
	// Otherwise, reallocate vector and construct a new object.
	return *emplace_reallocate(cend(), _STD forward<Args>(args)...);
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::assign(_STD initializer_list<T> ilist)
{
	assign_range(ilist.begin(), ilist.end());
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(const JVector &other)
{
	if (this != _STD addressof(other))
	{
		auto new_vector = allocate_memory(other.m_size);

		try
		{
			copy_range(other.cbegin(), other.cend(), m_data);
		}
		catch (...)
		{
			delete[] new_vector;
			throw;
		}

		dellocate_and_reset_memeber();
		change_array(new_vector, other.m_size, other.m_size);
	}

	return *this;
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(JVector &&other) noexcept
{
	if (this != _STD addressof(other))
	{
		dellocate_and_reset_memeber();
		swap(other);
	}
	
	return *this;
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(_STD initializer_list<T> ilist)
{
	assign_range(ilist.begin(), ilist.end());
	return *this;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::at(size_type pos)
{
	range_check(pos);
	return m_data[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::at(size_type pos) const
{
	range_check(pos);
	return m_data[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::operator[](size_type pos)
{	
	return m_data[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::operator[](size_type pos) const
{
	return m_data[pos];
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::front() noexcept
{
	return *m_data;
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::front() const noexcept
{
	return *m_data;
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::back() noexcept
{
	return m_data[m_size - 1];
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::back() const noexcept
{
	return m_data[m_size - 1];
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::value_type*
JVector<T, Alloc>::data() noexcept
{
	return m_data;
}

template <class T, class Alloc>
const typename JVector<T, Alloc>::value_type* 
JVector<T, Alloc>::data() const noexcept
{
	return m_data;
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::begin() noexcept
{
	return iterator(m_data);
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator
JVector<T, Alloc>::begin() const noexcept
{
	return const_iterator(m_data);
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::end() noexcept
{
	return iterator(m_data + m_size);
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator
JVector<T, Alloc>::end() const noexcept
{
	return const_iterator(m_data + m_size);
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reverse_iterator
JVector<T, Alloc>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_reverse_iterator
JVector<T, Alloc>::rbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reverse_iterator
JVector<T, Alloc>::rend() noexcept
{
	return reverse_iterator(begin());
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reverse_iterator
JVector<T, Alloc>::rend() const noexcept
{
	return const_reverse_iterator(begin());
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator
JVector<T, Alloc>::cbegin() const noexcept
{
	return begin();
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator
JVector<T, Alloc>::cend() const noexcept
{
	return end();
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_reverse_iterator
JVector<T, Alloc>::crbegin() const noexcept
{
	return rbegin();
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_reverse_iterator
JVector<T, Alloc>::crend() const noexcept
{
	return rend();
}
	
template <class T, class Alloc>
inline bool 
JVector<T, Alloc>::empty() const noexcept
{
	return m_size == 0;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::size() const noexcept
{
	return m_size;
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
	// Increase capacity to new_cap.
	if (new_cap > capacity())
	{
		if (new_cap > max_size())
		{
			// TODO: Think about which exception I should use.
			throw _STD runtime_error("New capacity is too large.");
		}

		auto new_vector = allocate_memory(new_cap);
		move_range(begin(), end(), new_vector);
		change_array(new_vector, new_cap, m_size);
	}
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::capacity() const noexcept
{
	return m_capacity;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::shrink_to_fit()
{
	// Reduce capacity to size.
	if (m_capacity != m_size)
	{
		auto new_vector = allocate_memory(m_size);
		move_range(m_data, m_data + m_size, new_vector);
		change_array(new_vector, m_size, m_size);
	}
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, const T &value)
{
	return emplace(pos, value);
}

template <class T, class Alloc>
typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, T &&value)
{
	return emplace(pos, _STD move(value));
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, const size_type count, const T &value)
{
	// TODO insert count * value at pos

	if (count == 0)
	{
		return begin();
	}

	// reallocate
	if (count > m_capacity - m_size)
	{
		
	}
	else if (count == 1 && pos.ptr == m_data + m_size)
	{
		emplace_back(value);
	}
	else
	{
		
	}

	return iterator();
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::insert(const_iterator pos, ::std::initializer_list<T> ilist)
{
	// TODO not finished
	return insert(pos, ilist.begin(), ilist.end());
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::erase(const_iterator pos) noexcept(_STD is_nothrow_move_assignable_v<value_type>)
{
	auto need_to_destruct = m_data + m_size - 1;
	move_range(pos.ptr + 1, m_data + m_size, pos.ptr);
	destroy_range(m_data + m_size - 1, m_data + m_size);
	--m_size;
	
	return iterator(pos.ptr);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::erase(const_iterator first, const_iterator last) noexcept(_STD is_nothrow_move_assignable_v<value_type>)
{
	if (first != last)
	{
		destroy_range(first.ptr, last.ptr);
		m_size -= last.ptr - first.ptr;
	}

	return iterator(first.ptr);
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::push_back(const T &value)
{
	// Insert element at end, provide strong guarantee.
	emplace_back(value);
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::push_back(T &&value)
{
	// Insert by moving into element at end, provide strong guarantee.
	emplace_back(_STD move(value));
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::pop_back() noexcept
{
	assert(!empty());
	data[m_size - 1].~value_type();
	--m_size;
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::resize(size_type count)
{
	// If an exception is thrown, this function has no effect, provide strong exception guarantee.

	// If count < size, trim the vector.
	if (count < m_size)
	{
		destroy_range(m_data + count, m_data + m_size);
		m_size = count;
	}
	// Ohterwise grow or append to the end.
	else if (count > m_size)
	{
		if (count <= m_capacity)
		{
			// new[] will call default constructor. But is there a problem with my approach?
			const auto need_to_add = count - m_size;
			auto temp_vector = allocate_memory(count);
			move_range(temp_vector, temp_vector + need_to_add, m_data + m_size);
			delete[] temp_vector;
		}
		else
		{
			if (count > max_size())
			{
				throw _STD runtime_error("Vector too long");
			}

			// Default initialization has been performed.
			auto new_vector = allocate_memory(count);
			move_range(m_data, m_data + m_size, new_vector);
			change_array(new_vector, count, count);
		}
	}
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::resize(size_type count, const value_type &value)
{
	// If count < size, trim the vector.
	if (count < m_size)
	{
		destroy_range(m_data + count, m_data + m_size);
		m_size = count;
	}
	// Ohterwise grow or append to the end.
	else if (count > m_size)
	{
		const auto need_to_add = count - m_size;
		if (count <= m_capacity)
		{
			auto temp_vector = allocate_memory(need_to_add);

			try
			{
				assign_copy_range(temp_vector, temp_vector + need_to_add, value);
			}
			catch (...)
			{
				delete[] temp_vector;
				throw;
			}

			move_range(temp_vector, temp_vector + need_to_add, m_data + m_size);
			delete[] temp_vector;
		}
		else
		{
			if (count > max_size())
			{
				throw _STD runtime_error("Vector too long");
			}

			auto new_vector = allocate_memory(count);

			try
			{
				assign_copy_range(new_vector + m_size, new_vector + count, value);
			}
			catch (...)
			{
				delete[] new_vector;
				throw;
			}

			move_range(m_data, m_data + m_size, new_vector);
			change_array(new_vector, count, count);
		}
	}
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::clear() noexcept
{	
	destroy_range(m_data, m_data + m_size);
	m_size = 0;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::swap(JVector &other) noexcept
{
	if (this != _STD addressof(other))
	{
		using _STD swap;
		swap(m_data, other.m_data);
		swap(m_size, other.m_size);
		swap(m_capacity, other.m_capacity);
	}
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::range_check(size_type index) const
{
	if (index >= m_size)
	{
		throw _STD out_of_range("JVector::range_check() : size n >= JVector.size()");
	}
}

template <class T, class Alloc>
template <class Iter>
inline void
JVector<T, Alloc>::range_construct(Iter first, Iter last)
{
	for (; first != last; ++first)
	{
		emplace_back(*first);
	}
}

template <class T, class Alloc> 
inline typename JVector<T, Alloc>::pointer
JVector<T, Alloc>::allocate_memory(const size_type size)
{
	return  size != 0 ? new value_type[size] : nullptr;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::dellocate_and_reset_memeber() noexcept
{
	// This code is robust in the sense that if the array is nullptr, then nothing happens by using delete[] on it.
	// If the value of the array is undefined, then there is no way to ensure that the deletion will behave reasonably.
	delete[] m_data;
	m_data = nullptr;
	m_capacity = 0;
	m_size = 0;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::calculate_growth(const size_type new_size) const
{	
	const size_type old_capacity = m_capacity;
	
	// Geometric growth would overflow
	const auto max = max_size();
	
	if (old_capacity > max - old_capacity / 2)
	{
		return max;
	}

	// Adding 1.5 times capacity
	const size_type geometric = old_capacity + old_capacity / 2;
	
	// Geometric growth would be insufficient
	if (geometric < new_size)
	{
		return new_size;
	}

	return geometric;
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::assign_copy_range(iterator from, iterator to, const_reference value)
{
	// Copy value n times to a range of array
	for (; from != to; ++from)
	{
		*from = value;
	}
}

template <class T, class Alloc>
template <class Iter>
inline void
JVector<T, Alloc>::copy_range(Iter from, Iter to, pointer dist)
{
	for (; from != to; ++from, ++dist)
	{
		*dist = *from;
	}
}

template <class T, class Alloc>
template <class Iter>
inline Iter
JVector<T, Alloc>::move_range(Iter from, Iter to, pointer dist) noexcept
{
	for (; from != to; ++from, ++dist)
	{
		*dist = _STD move(*from);
	}

	return Iter(dist);
}

template<class T, class Alloc>
template<class Iter>
inline Iter 
JVector<T, Alloc>::rmove_range(Iter from, Iter to, pointer dist) noexcept
{
	for (; from != to; --dist, --from)
	{
		*dist = _STD move(*from);
	}

	return Iter(dist);
}

// Operator overloading functions. Outside the class scope
template <class T, class Alloc>
NODISCARD bool
operator==(const JVector<T, Alloc> &lhs, const JVector<T, Alloc> &rhs)
{
	return lhs.size() == rhs.size() && _STD equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <class T, class Alloc>
NODISCARD bool
operator!=(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return !(left == right);
}

template <class T, class Alloc>
NODISCARD bool
operator<(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return _STD lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <class T, class Alloc>
NODISCARD bool
operator>(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return right < left;
}

template <class T, class Alloc>
NODISCARD bool
operator<=(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return !(right < left);
}

template <class T, class Alloc>
NODISCARD bool
operator>=(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return !(left < right);
}

template <class T, class Alloc>
void
swap(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right) noexcept
{
	left.swap(right);
}

_JSTD_END
#endif // !_JVECTOR_