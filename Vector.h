#pragma once
#ifndef _VECTOR_
#define _VECTOR_
#include <cassert>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <limits>

template<typename T, typename Alloc>
struct Vector_base
{
	using T_alloc_type = typename std::allocator_traits<Alloc>::template rebind<T>::other;
	using pointer      = typename std::allocator_traits<T_alloc_type>::pointer;

	struct Vector_impl_data
	{
		pointer m_start;
		pointer m_finish;
		pointer m_end_of_storage;

		Vector_impl_data() noexcept
			: m_start(), m_finish(), m_end_of_storage()
		{}

		Vector_impl_data(Vector_impl_data&& right) noexcept
			: m_start(right.m_start), m_finish(right.m_finish),
			m_end_of_storage(other.end_of_storage)
		{
			right.m_start = right.m_finish = right.m_end_of_storage = pointer();
		}

		void _M_copy_data(Vector_impl_data const &x) noexcept
		{
			m_start = x.m_start;
			m_finish = x.m_finish;
			m_end_of_storage = x.m_end_of_storage;
		}

		void _M_swap_data(Vector_impl_data const &x) noexcept
		{
			Vector_impl_data temp;
			temp._M_copy_data(*this);
			_M_copy_data(x);
			x._M_copy_data(temp);
		}
	};

	struct Vector_impl : public T_alloc_type, public Vector_impl_data
	{
		Vector_impl() noexcept(std::is_nothrow_default_constructible<T_alloc_type>::value)
			: T_alloc_type()
		{}

		Vector_impl(T_alloc_type const& a) noexcept
			: T_alloc_type(a)
		{}


	};
};









#endif //_VECTOR_
