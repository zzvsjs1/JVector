#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

#include <iterator>
#include <memory>
#include <initializer_list>
#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>

// NAMESPACE
#define _JSTD_BEGIN namespace JSTD {
#define _JSTD_END   }
#define _STD       ::std::

// Useful Macro
#define NODISCARD [[nodiscard]]

// JVector const iterator.
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
template <class T, class Alloc = _STD allocator<T>>
class JVector
{
private:
	using alty                   = typename _STD allocator_traits<Alloc>::template rebind_alloc<T>;
	using alty_traits            = _STD allocator_traits<alty>;
	
public:
	using value_type             = T;
	using allocator_type         = Alloc;
	using pointer                = T*;
	using const_pointer          = const T*;
	using reference              = value_type&;
	using const_reference        = const value_type&;
	using size_type              = typename alty_traits::size_type;
	using difference_type        = typename alty_traits::difference_type;
	using iterator               = JVector_Iterator<JVector<T, Alloc>>;
	using const_iterator         = JVector_Const_Iterator<JVector<T, Alloc>>;
	using reverse_iterator       = _STD reverse_iterator<iterator>;
	using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

private:
	size_type m_size;
	size_type m_capacity;
	pointer   m_data;

public:
	JVector() noexcept(_STD is_nothrow_default_constructible_v<alty>);

private:
	template <class Iter, class DestT>
	void copy_range(Iter from, Iter to, DestT destination);

	template <class Iter>
	void assign_copy_range(Iter from, Iter to, const value_type &value);

public:
	explicit JVector(size_type count);

	JVector(size_type count, const T &value);

private:
	template <class Iter>
	void range_construct(Iter from, Iter to);

public:
	JVector(_STD initializer_list<T> init);

	JVector(const JVector &other);

	JVector(JVector &&other) noexcept;

	~JVector() noexcept;

private:
	template <class Iter>
	void destroy_range(Iter first, Iter last);
	
public:
	void assign(size_type count, const T &value);

	JVector& operator=(const JVector &other);

private:
	void destroy_all_members() noexcept;

public:
	JVector& operator=(JVector &&other) noexcept;

	JVector& operator=(_STD initializer_list<T> ilist);

protected:
	void check_range(size_type n) const;

public:
	NODISCARD reference at(const size_type pos);

	NODISCARD const_reference at(const size_type pos) const;

	NODISCARD reference operator[](const size_type pos);

	NODISCARD const_reference operator[](const size_type pos) const;

	NODISCARD reference front() noexcept;
	
	NODISCARD reference front() const noexcept;

	NODISCARD reference back() noexcept;

	NODISCARD const_reference back() const noexcept;

	NODISCARD pointer data() noexcept;

	NODISCARD const pointer data() const noexcept;
	
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

private:
	void change_vector_capacity_to(const size_type new_capacity);

	void change_vector(pointer new_vector, size_type new_size, size_type new_capacity);

public:
	void reserve(const size_type new_cap);

	NODISCARD size_type capacity() const noexcept;

	void shrink_to_fit();

	void clear() noexcept;

	iterator insert(const_iterator pos, const T &value);

	iterator insert(const_iterator pos, T &&value);

private:
	size_type calculate_growth(size_type new_size);

	pointer move_range(pointer first, pointer last, pointer dest);

	template <class Iter>
	void rmove(Iter first, Iter last, pointer dest);

public:
	iterator insert(const_iterator pos, size_type count, const T &value);

private:
	template <class... Args>
	decltype(auto) emplace_rellocate(const pointer pos, Args&&... args);

	template <class... Args>
	decltype(auto) emplace_back_with_unused_capacity(Args&&... args);

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
};

template <class T, class Alloc>
inline 
JVector<T, Alloc>::JVector() noexcept(_STD is_nothrow_default_constructible_v<alty>) 
	: m_size(), 
	  m_capacity(), 
	  m_data()
	{}

template <class T, class Alloc>
template <class Iter, class DestT>
inline 
void JVector<T, Alloc>::copy_range(Iter from, Iter to, DestT dest)
{
	for (; from != to; ++from, ++dest)
	{
		*dest = *from;
	}
}

template <class T, class Alloc>
template <class Iter>
inline void 
JVector<T, Alloc>::assign_copy_range(Iter from, Iter to, const value_type &value)
{
	for (; from != to; ++from)
	{
		*from = value;
	}
}

template <class T, class Alloc>
inline 
JVector<T, Alloc>::JVector(size_type count)
	: m_size(count),
	m_capacity(count),
	m_data()
{
	// Constructs a vector with n default-inserted elements using the specified allocator.
	if (count != 0)
	{
		m_data = new value_type[count]{};
	}
}

template <class T, class Alloc>
inline 
JVector<T, Alloc>::JVector(size_type count, const T &value)
	: m_size(count),
	m_capacity(count),
	m_data()
{
	if (count != 0)
	{
		if (count > max_size())
		{
			throw _STD runtime_error("Vector too long.");
		}

		auto vector = new value_type[count]{};

		try
		{
			assign_copy_range(vector, vector + count, value);
		}
		catch (...)
		{
			delete[] vector;
			throw;
		}

		m_data = vector;
	}
}

template <class T, class Alloc>
template <class Iter>
inline void JVector<T, Alloc>::range_construct(Iter from, Iter to)
{
	const auto size = static_cast<size_type>(_STD distance(from, to));
	if (size > max_size())
	{
		throw _STD runtime_error("Vector too long");
	}

	if (size != 0)
	{
		auto new_vector = new value_type[size]{};
		
		try
		{
			for (auto vector_start = new_vector; from != to; ++from, ++vector_start)
			{
				*vector_start = *from;
			}
		}
		catch (...)
		{
			delete[] new_vector;
			throw;
		}

		change_vector(new_vector, size, size);
	}
}

template <class T, class Alloc>
inline JVector<T, Alloc>::JVector(::std::initializer_list<T> init)
	: m_size(),
	m_capacity(),
	m_data()
{
	range_construct(init.begin(), init.end());
}

template <class T, class Alloc>
inline 
JVector<T, Alloc>::JVector(const JVector &other)
	: m_size(other.m_size),
	m_capacity(other.m_size),
	m_data()
{
	if (other.m_size != 0)
	{
		auto vector = new value_type[other.m_size]{};
		
		try
		{
			copy_range(other.m_data, other.data + other.m_size, vector);
		}
		catch (...)
		{
			delete[] vector;
			throw;
		}

		m_data = vector;
	}
}

template <class T, class Alloc>
inline 
JVector<T, Alloc>::JVector(JVector &&other) noexcept
	: m_size(),
	m_capacity(),
	m_data()
{
	swap(other);
}

template <class T, class Alloc>
inline 
JVector<T, Alloc>::~JVector() noexcept
{
	delete[] m_data;
}

template <class T, class Alloc>
template <class Iter>
inline void 
JVector<T, Alloc>::destroy_range(Iter first, Iter last)
{
	if constexpr (
		!_STD is_trivially_destructible_v<typename std::iterator_traits<Iter>::value_type>)
	{
		for (; first != last; ++first)
		{
			first->~value_type();
		}
	}
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::assign(size_type count, const T &value)
{
	// Greater than size
	if (count > m_size)
	{
		// If we have enough memory.
		if (count <= m_capacity)
		{
			const auto end_of_count = m_data + count;

			// If throw an exception in assign_copy_range(), size will not be changed.
			assign_copy_range(m_data, end_of_count, value);
			destroy_range(end_of_count, m_data + m_size);
			m_size = count;
		}
		// Reallocate
		else
		{
			auto new_vector = new value_type[count]{};
			try
			{
				assign_copy_range(new_vector, new_vector + count, value);
			}
			catch (...)
			{
				delete[] new_vector;
				throw;
			}
			
			change_vector(new_vector, count, count);
		}
	}
	// No capacity modification, only trim.
	else
	{
		assign_copy_range(m_data, m_data + count, value);
		destroy_range(m_data + count, m_data + m_size);
		m_size = count;
	}
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(const JVector &other)
{
	if (this != _STD addressof(other))
	{
		pointer start           = m_data;
		const pointer end       = m_data + m_size;
		pointer other_start     = other.m_data;
		const pointer other_end = other.m_data + other.m_size;

		for (; start != end && other_start != other_end; ++start, ++other_start)
		{
			*start = *other_start;
		}

		destroy_range(start, end);
		m_size = start - m_data;

		for (; other_start != other_end; ++other_start)
		{
			emplace_back(*other_start);
		}
	}

	return *this;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::destroy_all_members() noexcept
{
	delete[] m_data;
	m_data     = nullptr;
	m_capacity = 0;
	m_size     = 0;
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(JVector &&other) noexcept
{
	if (this != _STD addressof(other))
	{
		destroy_all_members();
		swap(other);
	}

	return *this;
}

template <class T, class Alloc>
inline JVector<T, Alloc>&
JVector<T, Alloc>::operator=(_STD initializer_list<T> ilist)
{	
	if (ilist.size() != 0)
	{
		if (ilist.size() > m_capacity)
		{
			if (ilist.size() > max_size())
			{
				throw _STD runtime_error("Vector too long");
			}

			destroy_all_members();
			range_construct(ilist.begin(), ilist.end());
		}
		else
		{
			if (ilist.size() > m_size)
			{
				pointer start          = m_data;
				pointer end            = m_data + m_size;

				auto ilist_start       = ilist.begin();

				for (; start != end; ++start)
				{
					*start = *ilist_start;
				}

				for (const pointer list_length_end = m_data + ilist.size(); 
					start != list_length_end; 
					++start, ++ilist_start)
				{
					::new (static_cast<void*>(start)) value_type(*ilist_start);
					++m_size;
				}
			}
			else
			{
				pointer start = m_data;
				pointer end   = m_data + m_size;

				for (auto &obj : ilist)
				{
					*start = obj;
					++start;
				}

				destroy_range(start, end);
				m_size = ilist.size();
			}
		}
	}

	return *this;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::check_range(size_type n) const
{
	if (n >= m_size)
	{
		throw _STD out_of_range("JVector::check_range: Bounds-checked failed.");
	}
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference 
JVector<T, Alloc>::at(const size_type pos)
{
	check_range(pos);
	return m_data[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference
JVector<T, Alloc>::at(const size_type pos) const
{
	check_range(pos);
	return m_data[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference 
JVector<T, Alloc>::operator[](const size_type pos)
{
	assert(pos < m_size);
	return m_data[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference 
JVector<T, Alloc>::operator[](const size_type pos) const
{
	assert(pos < m_size);
	return m_data[pos];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference 
JVector<T, Alloc>::front() noexcept
{
	assert(m_size != 0);
	return *m_data;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference 
JVector<T, Alloc>::front() const noexcept
{
	assert(m_size != 0);
	return *m_data;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reference 
JVector<T, Alloc>::back() noexcept
{
	assert(m_size != 0);
	return m_data[m_size - 1];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reference 
JVector<T, Alloc>::back() const noexcept
{
	assert(m_size != 0);
	return m_data[m_size - 1];
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::pointer
JVector<T, Alloc>::data() noexcept
{
	return m_data;
}

template <class T, class Alloc>
inline const typename JVector<T, Alloc>::pointer
JVector<T, Alloc>::data() const noexcept
{
	return m_data;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::begin() noexcept
{
	return iterator(m_data);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator 
JVector<T, Alloc>::begin() const noexcept
{
	return const_iterator(m_data);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::end() noexcept
{
	return iterator(m_data + m_size);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator 
JVector<T, Alloc>::end() const noexcept
{
	return const_iterator(m_data + m_size);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reverse_iterator 
JVector<T, Alloc>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reverse_iterator 
JVector<T, Alloc>::rbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reverse_iterator 
JVector<T, Alloc>::rend() noexcept
{
	return reverse_iterator(begin());
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::reverse_iterator 
JVector<T, Alloc>::rend() const noexcept
{
	return const_reverse_iterator(begin());
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator 
JVector<T, Alloc>::cbegin() const noexcept
{
	return begin();
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_iterator 
JVector<T, Alloc>::cend() const noexcept
{
	return end();
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reverse_iterator 
JVector<T, Alloc>::crbegin() const noexcept
{
	return rbegin();
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::const_reverse_iterator 
JVector<T, Alloc>::crend() const noexcept
{
	return rend();
}

template <class T, class Alloc>
inline bool JVector<T, Alloc>::empty() const noexcept
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
	// Copy from MSVC STL.
	return (_STD min)(
		static_cast<size_type>((_STD numeric_limits<difference_type>::max)()), static_cast<size_type>(-1) / sizeof(value_type));
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::change_vector_capacity_to(const size_type new_capacity)
{
	auto new_vector = new value_type[new_capacity]{};
	move_range(m_data, m_data + m_size, new_vector);
	change_vector(new_vector, m_size, new_capacity);
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::change_vector(pointer new_vector, size_type new_size, size_type new_capacity)
{
	delete[] m_data;
	m_data     = new_vector;
	m_size     = new_size;
	m_capacity = new_capacity;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::reserve(const size_type new_cap)
{
	// Throws: length_error if n > max_size().
	// After reserve(), capacity() is greater or equal to the argument of reserve if reallocation happens.
	if (new_cap > m_capacity)
	{
		if (new_cap > max_size())
		{
			throw _STD runtime_error("Vector too long.");
		}

		change_vector_capacity_to(new_cap);
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
	// shrink_to_fit is a non-binding request to reduce capacity() to size().
	// It does not increase capacity(), but may reduce capacity() by causing reallocation.
	if (m_capacity != m_size)
	{
		if (m_size == 0)
		{
			destroy_all_members();
		}
		else
		{
			change_vector_capacity_to(m_size);
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
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::insert(const_iterator pos, const T &value)
{
	return emplace(pos, value);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::insert(const_iterator pos, T &&value)
{
	return emplace(pos, _STD move(value));
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::size_type 
JVector<T, Alloc>::calculate_growth(size_type new_size)
{
	// Copy from MSVC STL.
	const auto max = max_size();

	if (m_capacity > max - m_capacity / 2) 
	{
		return max;
	}

	const size_type geometric = m_capacity + m_capacity / 2;

	if (geometric < new_size)
	{
		return new_size;
	}

	return geometric;
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::pointer
JVector<T, Alloc>::move_range(pointer first, pointer last, pointer dest)
{
	for (; first != last; ++first, ++dest)
	{
		*dest = _STD move(*first);
	}

	return dest;
}

template <class T, class Alloc>
template <class Iter>
inline void 
JVector<T, Alloc>::rmove(Iter first, Iter last, pointer dest)
{
	for (; first != last; --last, --dest)
	{
		*dest = _STD move(*last);
	}
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::insert(const_iterator pos, size_type count, const T &value)
{
	pointer add_pos_ptr = pos.ptr;

	// If count == 0, skip.
	if (count == 0)
	{
		return iterator(pos.ptr);
	}
	// If just add one to back, using emplace_back_with_unused_capacity.
	else if (pos.ptr == m_data + m_size && count == 1)
	{
		emplace_back_with_unused_capacity(value);
		return iterator(add_pos_ptr);
	}
	// If no enough space to store the value.
	else if (count > m_capacity - m_size)
	{
		if (count > max_size() - m_size)
		{
			throw _STD runtime_error("Vector too long.");
		}

		// Provide store guarantee.
		const pointer start                = m_data;
		const size_type insert_pos_index   = pos.ptr - start;
		const size_type new_size           = m_size + count;
		const size_type new_capacity       = calculate_growth(new_size);
		auto new_vector                    = new value_type[new_capacity]{};

		try
		{
			assign_copy_range(new_vector + insert_pos_index, new_vector + insert_pos_index + count, value);
		}
		catch (...)
		{
			delete[] new_vector;
			throw;
		}

		move_range(m_data, add_pos_ptr, new_vector);
		move_range(add_pos_ptr, m_data + m_size, new_vector + insert_pos_index + count);
		change_vector(new_vector, new_size, new_capacity);

		return iterator(new_vector + insert_pos_index);
	}
	// If we have enough space to store the elementes.
	else
	{
		const auto old_size = m_size;

		for (size_t i = 0; i < count; i++)
		{
			emplace_back_with_unused_capacity(value);
		}

		_STD rotate(pos.ptr, m_data + old_size, m_data + m_size);
		return iterator(pos.ptr);
	}
}

template <class T, class Alloc>
template <class ...Args>
inline decltype(auto)
JVector<T, Alloc>::emplace_rellocate(const pointer pos, Args&&... args)
{
	if (m_size == max_size())
	{
		throw _STD runtime_error("Vector too long.");
	}

	const auto new_size      = m_size + 1;
	const auto new_capacity  = calculate_growth(new_size);
	const auto add_pos_index = pos - m_data;

	auto new_vector = new value_type[new_capacity]{};
	try
	{
		::new (static_cast<void*>(&new_vector[add_pos_index])) value_type(_STD forward<Args>(args)...);
	}
	catch (...)
	{
		delete[] new_vector;
		throw;
	}

	move_range(m_data, pos, new_vector);
	move_range(pos, m_data + m_size, new_vector + add_pos_index);
	change_vector(new_vector, new_size, new_capacity);

	return new_vector + add_pos_index;
}

template <class T, class Alloc>
template <class ...Args>
inline decltype(auto) 
JVector<T, Alloc>::emplace_back_with_unused_capacity(Args&&... args)
{
	::new (static_cast<void*>(&m_data[m_size])) value_type(_STD forward<Args>(args)...);
	++m_size;
	return m_data[m_size - 1];
}

template <class T, class Alloc>
template <class ...Args>
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::emplace(const_iterator pos, Args&&... args)
{
	const pointer pos_ptr = pos.ptr;

	if (m_size != m_capacity)
	{
		if (pos.ptr == m_data + m_size)
		{
			emplace_back_with_unused_capacity(_STD forward<Args>(args)...);
			return iterator(pos_ptr);
		}
		else
		{
			value_type new_obj        = value_type(_STD forward<Args>(args)...);
			const pointer rmove_start = pos_ptr - 1;
			const pointer rmove_end   = m_data + m_size - 1;
			const pointer rmove_dest  = m_data + m_size;

			rmove(rmove_start, rmove_end, rmove_dest);
			*pos_ptr = _STD move(new_obj);
			++m_size;

			return iterator(pos_ptr);
		}
	}

	return iterator(emplace_rellocate(pos_ptr, _STD forward<Args>(args)...));
}

template <class T, class Alloc>
template <class ...Args>
inline typename JVector<T, Alloc>::reference 
JVector<T, Alloc>::emplace_back(Args&& ...args)
{
	if (m_size != m_capacity)
	{
		return emplace_back_with_unused_capacity(_STD forward<Args>(args)...);
	}
	
	return *emplace_rellocate(m_data + m_size, _STD forward<Args>(args)...);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::erase(const_iterator pos) noexcept(_STD is_nothrow_move_assignable_v<value_type>)
{
	const pointer where_ptr = pos.ptr;
	move_range(where_ptr + 1, m_data + m_size, where_ptr);
	destroy_range(m_data + m_size - 1, m_data + m_size);

	return iterator(where_ptr);
}

template <class T, class Alloc>
inline typename JVector<T, Alloc>::iterator 
JVector<T, Alloc>::erase(const_iterator first, const_iterator last) noexcept(_STD is_nothrow_move_assignable_v<value_type>)
{
	if (first != last)
	{
		const pointer first_ptr      = first.ptr;
		const pointer last_ptr       = last.ptr;
		const size_type num_of_earse = last_ptr - first_ptr;
		const auto need_to_destroy = move_range(last_ptr, m_data + m_size, first_ptr);
		
		destroy_range(need_to_destroy, m_data + m_size);
		m_size -= num_of_earse;
	}

	return iterator(first.ptr);
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::push_back(const T &value)
{
	emplace_back(value);
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::push_back(T &&value)
{
	emplace_back(_STD move(value));
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::pop_back() noexcept
{
	destroy_range(m_data + m_size - 1, m_data + m_size);
	--m_size;
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::resize(size_type count)
{
	resize(count, value_type());
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::resize(size_type count, const value_type &value)
{
	if (count < m_size)
	{
		destroy_range(m_data + count, m_data + m_size);
		m_size = count;
	}
	else if (count > m_size)
	{
		// Reallocate
		if (count > m_capacity)
		{
			if (count > max_size())
			{
				throw _STD runtime_error("Vector too long");
			}

			pointer new_vector = new value_type[count]{};

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
			change_vector(new_vector, count, count);
		}
		else
		{
			for (size_type i = 0, need_to_append = count - m_size; i < need_to_append; ++i)
			{
				emplace_back_with_unused_capacity(value);
			}
		}
	}
}

template <class T, class Alloc>
inline void 
JVector<T, Alloc>::swap(JVector &other) noexcept
{
	if (this != _STD addressof(other))
	{
		using _STD swap;
		swap(m_data, other.m_data);
		swap(m_capacity, other.m_capacity);
		swap(m_size, other.m_size);
	}
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
#endif // !_JVECTOR_