#pragma once
#ifndef _JSTD_CORE_
#define _JSTD_CORE_

#include <cassert>

#ifdef _DEBUG
#define JSTL_DEBUG
#endif


// NAMESPACE
#define _JSTD_BEGIN namespace JSTD {
#define _JSTD_END   }
#define _STD       ::std::
#define _CHRONO    ::std::chrono::
#define _RANGES    ::std::ranges::

// 
#define JSTL_VERIFY(cond)                                     \
	assert(cond)


#endif // !_JSTD_CORE__