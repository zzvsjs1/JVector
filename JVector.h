#pragma once
#ifndef _JVECTOR_
#define _JVECTOR_

namespace JSTD 
{
	template<class T>
	class JVector
	{
	public:
		using size_type       = size_t;
		using difference_type = ptrdiff_t;
		using value_type      = T;

		JVector() = default;

		JVector(size_type count) 
		{
		
		}

		JVector(JVector&&) noexcept = default;


		~JVector() noexcept;

	private:

	};
}
#endif //_JVECTOR_