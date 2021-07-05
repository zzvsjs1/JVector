#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

#include <iterator>
#include <memory>
#include <initializer_list>

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

	_NODISCARD JVector_Const_Iterator operator+(const difference_type off) const noexcept
	{
		JVector_Const_Iterator temp = *this;
		temp += off;
		return temp;
	}

	_NODISCARD JVector_Const_Iterator& operator-=(const difference_type off) noexcept
	{
		return *this += -off;
	}

	_NODISCARD JVector_Const_Iterator operator-(const difference_type off) const noexcept
	{
		JVector_Const_Iterator temp = *this;
		temp -= off;
		return temp;
	}

	_NODISCARD difference_type operator-(const JVector_Const_Iterator &right) const noexcept
	{
		return ptr - right.ptr;
	}

	_NODISCARD reference operator[](const difference_type off) const noexcept
	{
		return *(*this + off);
	}

	_NODISCARD bool operator==(const JVector_Const_Iterator &right) const noexcept
	{
		return ptr == right.ptr;
	}

	_NODISCARD bool operator!=(const JVector_Const_Iterator &right) const noexcept
	{
		return !(*this == right);
	}

	_NODISCARD bool operator<(const JVector_Const_Iterator &right) const noexcept
	{
		return ptr < right.ptr;
	}

	_NODISCARD bool operator>(const JVector_Const_Iterator &right) const noexcept
	{
		return right < *this;
	}

	_NODISCARD bool operator<=(const JVector_Const_Iterator &right) const noexcept
	{
		return !(right < *this);
	}

	_NODISCARD bool operator>=(const JVector_Const_Iterator &right) const noexcept
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

	_NODISCARD reference operator*() const noexcept
	{
		return const_cast<reference>(my_base::operator*());
	}

	_NODISCARD pointer operator->() const noexcept
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

	_NODISCARD JVector_Iterator operator+(const difference_type off) const noexcept
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

	_NODISCARD JVector_Iterator operator-(const difference_type off) const noexcept
	{
		JVector_Iterator temp = *this;
		temp -= off;
		return temp;
	}

	_NODISCARD reference operator[](const difference_type off) const noexcept
	{
		return const_cast<reference>(my_base::operator[](off));
	}
};

template <class MyVector>
_NODISCARD JVector_Iterator<MyVector> operator+(
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
	using reference              = value_type&;
	using const_reference        = const value_type&;
	using const_pointer          = const T*;
	using size_type              = typename alty_traits::size_type;
	using difference_type        = typename alty_traits::difference_type;
	using iterator               = JVector_Iterator<JVector<T, Allocator>>;
	using const_iterator         = JVector_Const_Iterator<JVector<T, Allocator>>;
	using reverse_iterator       = _STD reverse_iterator<iterator>;
	using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

private:
	size_type m_data_capacity;
	size_type m_number_of_elements;
	value_type *m_data_array;

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

	_NODISCARD reference at(size_type pos);

	_NODISCARD const_reference at(size_type pos) const;

	_NODISCARD reference operator[](size_type pos);

	_NODISCARD const_reference operator[](size_type pos) const;

	_NODISCARD reference front() noexcept;
	
	_NODISCARD reference front() const noexcept;

	_NODISCARD reference back() noexcept;

	_NODISCARD const_reference back() const noexcept;

	_NODISCARD value_type* data() noexcept;

	_NODISCARD const value_type* data() const noexcept;
	
	_NODISCARD iterator begin() noexcept;

	_NODISCARD const_iterator begin() const noexcept;

	_NODISCARD iterator end() noexcept;

	_NODISCARD const_iterator end() const noexcept;

	_NODISCARD reverse_iterator rbegin() noexcept;

	_NODISCARD const_reverse_iterator rbegin() const noexcept;

	_NODISCARD reverse_iterator rend() noexcept;

	_NODISCARD reverse_iterator rend() const noexcept;

	_NODISCARD const_iterator cbegin() const noexcept;

	_NODISCARD const_iterator cend() const noexcept;

	_NODISCARD const_reverse_iterator crbegin() const noexcept;

	_NODISCARD const_reverse_iterator crend() const noexcept;

	_NODISCARD bool empty() const noexcept;

	_NODISCARD size_type size() const noexcept;

	_NODISCARD size_type max_size() const noexcept;

	void reserve(size_type new_cap);

	_NODISCARD size_type capacity() const noexcept;

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
	void assign_range(Iter first, Iter last);
	
	template <class... Valty>
	decltype(auto) emplace_back_with_unused_capacity(Valty&&... value);

	template <class... Valty>
	pointer emplace_reallocate(const_iterator pos, Valty&&... value);

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

	void destroy() noexcept;
	
	_NODISCARD size_type calculate_growth(size_type new_size) const;
	
	static void assign_copy_range(iterator from, iterator to, const_reference value);

	template <class Iter>
	static void copy_range(Iter from, Iter to, pointer dist) noexcept;
	
	template <class Iter>
	static Iter move_range(Iter from, Iter to, pointer dist) noexcept;

	template <class Iter>
	static Iter rmove_range(Iter from, Iter to, pointer dist) noexcept;

	static value_type* resize_and_move(size_type new_size, iterator from, iterator to);
	
};

template<class T, class Alloc>
inline
JVector<T, Alloc>::JVector() noexcept(::std::is_nothrow_default_constructible_v<alty>) :
	m_data_capacity(0),
	m_number_of_elements(0),
	m_data_array(nullptr)
{
	
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(size_type count) :
	m_data_capacity(count),
	m_number_of_elements(count),
	m_data_array(nullptr)
{
	if (count != 0)
	{
		m_data_array = allocate_memory(count);
	}
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
		assign_copy_range(begin(), end(), value);
	}
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(const JVector &other) :
	m_data_capacity(other.m_data_capacity),
	m_number_of_elements(other.m_number_of_elements),
	m_data_array(nullptr)
{
	if (m_data_capacity != 0)
	{
		m_data_array = allocate_memory(other.m_data_capacity);
	}

	if (other.m_number_of_elements != 0)
	{
		copy_range(other.cbegin(), other.cend(), m_data_array);
	}
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(JVector &&other) noexcept :
	m_data_capacity(0), 
	m_number_of_elements(0),
	m_data_array(nullptr)
{
	destroy();
	swap(other);
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::JVector(_STD initializer_list<T> init) :
	m_data_capacity(0),
	m_number_of_elements(0),
	m_data_array(nullptr)
{
	range_construct(init.begin(), init.end());
}

template <class T, class Alloc>
inline
JVector<T, Alloc>::~JVector() noexcept
{
	// The reason for not using JVector::destroy() is that there is no need to modify the values of other members.
	delete[] m_data_array;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::assign(size_type count, const T &value)
{
	// TODO assign
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

template<class T, class Alloc>
inline void
JVector<T, Alloc>::change_array(pointer new_array, size_type new_capacity, size_type new_number_of_elements) noexcept
{
	delete[] m_data_array;
	m_data_array = new_array;
	m_data_capacity = new_capacity;
	m_number_of_elements = new_number_of_elements;
}

template <class T, class Alloc>
inline void
JVector<T, Alloc>::destroy_range_and_reallocate_in_active(pointer first, pointer last)
{
	// Destroy [first, last) using raw pointer.
	if (first != last && first != m_data_array + m_number_of_elements)
	{
		size_type distance = last - first;
		size_type new_capacity = m_data_capacity - distance;
		pointer new_vector = allocate_memory(new_capacity);
		pointer second_half_start_point = new_vector + (first - m_data_array);

		move_range(m_data_array, first, new_vector);
		move_range(last, m_data_array + m_number_of_elements, second_half_start_point);

		change_array(new_vector, new_capacity, m_number_of_elements - distance);
	}
}

template <class T, class Alloc>
template <class Iter>
inline void
JVector<T, Alloc>::assign_range(Iter first, Iter last)
{
	pointer my_next = m_data_array;
	pointer my_last = m_data_array + m_data_capacity;

	// Exhausted only the source from arguments: Trim the vector and append does nothing.
	// Exhausted only the vector: Trim does nothing, then append to the back.
	// Exhausted source and vector: Trim and append does nothing.
		
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
template <class... Valty>
inline decltype(auto)
JVector<T, Alloc>::emplace_back_with_unused_capacity(Valty&&... value)
{
	new (m_data_array + m_number_of_elements) value_type(_STD forward<Valty>(value)...);
	return *(m_data_array + m_number_of_elements++);
}

template <class T, class Alloc>
template <class... Valty>
typename JVector<T, Alloc>::pointer
JVector<T, Alloc>::emplace_reallocate(const_iterator pos, Valty&&... value)
{
	if (m_data_capacity == max_size())
		throw _STD exception("JVector too long");

	const auto new_capacity = calculate_growth(m_data_capacity + 1);
	const auto added_pos = static_cast<size_type>(pos.ptr - m_data_array);

	const pointer new_vector = allocate_memory(new_capacity);
	
	new (new_vector + added_pos) value_type(_STD forward<Valty>(value)...);

	move_range(m_data_array, pos.ptr, new_vector);

	move_range(pos.ptr, m_data_array + m_number_of_elements, new_vector + added_pos + 1);

	change_array(new_vector, new_capacity, m_number_of_elements + 1);
	
	// Return the current value's reference to the caller.
	return new_vector + added_pos;
}

template <class T, class Alloc>
template <class ...Args>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::emplace(const_iterator pos, Args&&... args)
{
	pointer where_ptr = pos.ptr;

	// Check if vector have enough space to store a new object.
	if (m_number_of_elements != m_data_capacity)
	{
		// If where pointer equal to the back + 1.
		if (where_ptr == m_data_array + m_number_of_elements)
		{
			// Emplace to the back.
			emplace_back_with_unused_capacity(_STD forward<Args>(args)...);
		}
		else
		{
			rmove_range(m_data_array + m_number_of_elements, where_ptr - 1, m_data_array + m_number_of_elements + 1);
			new (where_ptr) value_type(_STD forward<Args>(args)...);
			++m_number_of_elements;
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
	if (m_number_of_elements != m_data_capacity)
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
		// Firstly, allocate a new vector, if throw a exception, this object will not change.
		auto new_vector = allocate_memory(other.m_number_of_elements);

		// Then, copy all the elements from other JVector. This function does not throw an exception.
		copy_range(other.cbegin(), other.cend(), m_data_array);

		// Finally, destroy all the members.
		destroy();
		change_array(new_vector, other.m_number_of_elements, other.m_number_of_elements);
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
	return m_data_array[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::at(size_type pos) const
{
	range_check(pos);
	return m_data_array[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::operator[](size_type pos)
{	
	return m_data_array[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::operator[](size_type pos) const
{
	return m_data_array[pos];
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::front() noexcept
{
	return *m_data_array;
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::front() const noexcept
{
	return *m_data_array;
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::reference
JVector<T, Alloc>::back() noexcept
{
	return m_data_array[m_number_of_elements - 1];
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::back() const noexcept
{
	return m_data_array[m_number_of_elements - 1];
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::value_type*
JVector<T, Alloc>::data() noexcept
{
	return m_data_array;
}

template <class T, class Alloc>
const typename JVector<T, Alloc>::value_type* 
JVector<T, Alloc>::data() const noexcept
{
	return m_data_array;
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::begin() noexcept
{
	return iterator(m_data_array);
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator
JVector<T, Alloc>::begin() const noexcept
{
	return const_iterator(m_data_array);
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::end() noexcept
{
	return iterator(m_data_array + m_number_of_elements);
}

template<class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator
JVector<T, Alloc>::end() const noexcept
{
	return const_iterator(m_data_array + m_number_of_elements);
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
	// Increase capacity to new_cap (without geometric growth), provide strong guarantee.
	if (new_cap > capacity())
	{
		if (new_cap > max_size())
		{
			throw _STD exception("New capacity is too large.");
		}

		auto new_vector = allocate_memory(new_cap);
		move_range(begin(), end(), new_vector);
		change_array(new_vector, new_cap, m_number_of_elements);
	}
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
	// Reduce capacity to size.
	if (m_data_capacity != m_number_of_elements)
	{
		
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
	if (count > m_data_capacity - m_number_of_elements)
	{
		
	}
	else if (count == 1 && pos.ptr == m_data_array + m_number_of_elements)
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
	pointer where = pos.ptr;
	move_range(iterator(where + 1), end(), where);
	--m_number_of_elements;

	return iterator(pos.ptr);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator
JVector<T, Alloc>::erase(const_iterator first, const_iterator last) noexcept(_STD is_nothrow_move_assignable_v<value_type>)
{
	if (first != last)
	{
		destroy_range_and_reallocate_in_active(first.ptr, last.ptr);
	}

	// TODO add iter.
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
	// TODO

	--m_number_of_elements;
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::resize(size_type count)
{
	
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::resize(size_type count, const value_type &value)
{
	
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::clear() noexcept
{
	if (_STD is_arithmetic_v<T>)
	{
		
	}
	
	for (iterator start = begin(), last = end(); start != last; ++start)
	{
		;
	}

	m_number_of_elements = 0;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::swap(JVector &other) noexcept
{
	if (this != _STD addressof(other))
	{
		using _STD swap;
		swap(m_data_array, other.m_data_array);
		swap(m_number_of_elements, other.m_number_of_elements);
		swap(m_data_capacity, other.m_data_capacity);
	}
}

template<class T, class Alloc>
inline void
JVector<T, Alloc>::range_check(size_type n) const
{
	if (n > m_number_of_elements)
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


	return new value_type[size];
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::destroy() noexcept
{
	// This code is robust in the sense that if the array is nullptr, then nothing happens by using delete[] on it.
	// If the value of the array is undefined, then there is no way to ensure that the deletion will behave reasonably.
	delete[] m_data_array;
	m_data_array = nullptr;
	m_data_capacity = 0;
	m_number_of_elements = 0;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type
JVector<T, Alloc>::calculate_growth(const size_type new_size) const
{	
	const size_type old_capacity = m_data_capacity;
	
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
JVector<T, Alloc>::copy_range(Iter from, Iter to, pointer dist) noexcept
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

template<class T, class Alloc>
inline typename JVector<T, Alloc>::value_type* 
JVector<T, Alloc>::resize_and_move(size_type new_size, iterator from, iterator to)
{
	// TODO unused, consider remove this function
	auto new_array = allocate_memory(new_size);
	move_range(from, to, new_array);
	return new_array;
}

// Operator overloading functions. Outside the class scope
template <class T, class Alloc>
_NODISCARD bool
operator==(const JVector<T, Alloc> &lhs, const JVector<T, Alloc> &rhs)
{
	return lhs.size() == rhs.size() && _STD equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <class T, class Alloc>
_NODISCARD bool
operator!=(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return !(left == right);
}

template <class T, class Alloc>
_NODISCARD bool
operator<(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return _STD lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <class T, class Alloc>
_NODISCARD bool
operator>(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return right < left;
}

template <class T, class Alloc>
_NODISCARD bool
operator<=(const JVector<T, Alloc> &left, const JVector<T, Alloc> &right)
{
	return !(right < left);
}

template <class T, class Alloc>
_NODISCARD bool
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