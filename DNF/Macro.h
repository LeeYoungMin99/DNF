#pragma once

// ------------------------------------------
// CRASH
// -----------------------------------------

#define CRASH(cause)						\
{											\
	UINT32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)							\
{													\
	if (!(expr))									\
	{												\
		CRASH("ASSERT_CRASH");						\
		__analysis_assume(expr);					\
	}												\
}

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif