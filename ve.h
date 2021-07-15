#pragma once
#ifndef VE
#define VE

#include <cassert>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <limits>
#include <exception>

template<class T, class Alloc = ::std::allocator<T>>
class vec
{
public:
private:
	using alty = typename ::std::allocator_traits<Alloc>::template rebind_alloc<T>;
	using alty_traits = ::std::allocator_traits<alty>;

public:
	using value_type = T;
	using allocator_type = Alloc;
	using pointer = T *;
	using const_pointer = const T *;
	using reference = value_type &;
	using const_reference = const value_type &;
	using size_type = typename alty_traits::size_type;
	using difference_type = typename alty_traits::difference_type;
	using iterator = T *;
	using const_iterator = const T*;
	using reverse_iterator = ::std::reverse_iterator<iterator>;
	using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

private:
	pointer m_first;
	pointer m_last;
	pointer m_end;

public:
	vec() noexcept
		: m_first(), m_last(), m_end()
	{}

private:
	pointer allocate_memory(size_type n)
	{
		if (alignof(T) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
		{
			::std:: align_val_t al = ::std:: align_val_t(alignof(T));
			return static_cast<pointer>(::operator new(n * sizeof(T), al));
		}

		return static_cast<pointer>(::operator new(n * sizeof(T)));
	}

	void deallocate(pointer ptr, size_type n) noexcept
	{
		if (alignof(T) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
		{
			::operator delete(ptr, n * sizeof(T), ::std::align_val_t(alignof(T)));
			return;
		}

		::operator delete(ptr, n * sizeof(T));
	}

	template <class... Args>
	void construct(pointer ptr, Args&&... args) noexcept(::std:: is_nothrow_constructible_v<pointer, Args...>)
	{
		::new(const_cast<void *>(static_cast<const volatile void*>(ptr))) value_type(::std::forward<Args>(args)...);
	}

	template <class Iter>
	void destroy(Iter& iter) noexcept(::std::is_nothrow_destructible_v<T>)
	{
		iter->~T();
	}

	template <class... Args>
	void construct_n_value(pointer ptr, size_type count, Args&&... args)
	{
		for (size_t i = 0; i < count; i++)
		{
			construct(ptr, ::std::forward<Args>(args)...);
		}
	}

	template <class Iter>
	void destroy_range(Iter first, Iter last) noexcept
	{
		if constexpr (!::std::is_trivially_destructible_v<typename ::std::iterator_traits<Iter>::value_type>)
		{
			for (; first != last; ++first)
			{
				destroy(first);
			}
		}
	}


public:
	vec(size_type count)
		: m_first(), m_last(), m_end()
	{
		if (count != count)
		{
			auto vector = allocate_memory(count);
			auto n = 0;
			try
			{
				for (size_t i = 0; i < count; i++, ++n)
				{
					construct(&vector[i]);
				}
			}
			catch (...)
			{
				destroy_range(vector, vector + n);
				deallocate(vector, n);
				throw
			}

			m_first = vector;
			m_last = vector + count;
			m_end = vector + count;
		}
	}

	vec(size_type count, const T &value)
		: m_first(), m_last(), m_end()
	{
		if (count != 0)
		{
			auto vector = allocate_memory(count);
			auto n = 0;
			try
			{
				for (size_t i = 0; i < count; i++, ++n)
				{
					construct(&vector[i], value);
				}
			}
			catch (...)
			{
				destroy_range(vector, vector + n);
				deallocate(vector, n);
				throw;
			}

			m_first = vector;
			m_last = vector + count;
			m_end = vector + count;
		}
	}

	vec(::std::initializer_list<T> init)
		: m_first(), m_last(), m_end()
	{
		if (init.size() != 0)
		{
			auto vector = allocate_memory(init.size());
			auto n = 0;
			try
			{
				for (auto start = init.begin(), stop = init.end(); start != stop; ++start, ++n)
				{
					construct(&vector[n], *start);
				}
			}
			catch (...)
			{
				destroy_range(vector, vector + n);
				deallocate(vector, n);
				throw;
			}

			m_first = vector;
			m_last = vector + init.size();
			m_end = vector + init.size();
		}
	}


	[[nodiscard]] reference operator[](const size_type pos)
	{
		return m_first[pos];
	}

	[[nodiscard]] const_reference operator[](const size_type pos) const
	{
		return m_first[pos];
	}

	[[nodiscard]] reference front() noexcept
	{
		return *m_first;
	}

	[[nodiscard]] reference front() const noexcept
	{
		return *m_first;
	}

	[[nodiscard]] reference back() noexcept 
	{
		return *(m_last - 1);
	}

	[[nodiscard]] const_reference back() const noexcept
	{
		return *(m_last - 1);
	}


	[[nodiscard]] pointer data() noexcept
	{
		return m_first;
	}

	[[nodiscard]] const_pointer data() const noexcept
	{
		return m_first;
	}

	[[nodiscard]] iterator begin() noexcept
	{
		return m_first;
	}

	[[nodiscard]] const_iterator begin() const noexcept
	{
		return m_first;
	}

	[[nodiscard]] iterator end() noexcept
	{
		return m_last;
	}

	[[nodiscard]] const_iterator end() const noexcept
	{
		return m_last;
	}


};

#endif // !VE
