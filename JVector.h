#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

#include <memory>
#include <iterator>

#include "jstd_core.h"

_JSTD_BEGIN
	// JVector common iterator




	// JVector const iterator




	// JVector insert iterator





	// JVector core
	template<class T, class Alloc = std::allocator<T>>
	class JVector
	{
	public:
		using value_type             = T;
		//using allocator_type         = Alloc;
		using size_type              = std::size_t;
		using difference_type        = std::ptrdiff_t;
		using reference              = T&;
		using const_reference        = const T&;
		using pointer                = std::allocator_traits<Alloc>::pointer;
		using const_pointer          = std::allocator_traits<Alloc>::const_pointer;
		//using reverse_iterator       = std::reverse_iterator<iterator>;
		//using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		JVector() = default;

		JVector(size_type count) 
		{

		}

		JVector(JVector&&) noexcept = default;


		~JVector() noexcept;

	private:






	};
_JSTD_END
#endif // !_JVECTOR_