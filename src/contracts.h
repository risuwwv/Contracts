//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef CONDITIONS_H
#define CONDITIONS_H

//Documentation: 

//Define the macro CHECK_CONDITIONS to turn on the following macros:

//PRE_CONDITION(test) checks that its parameter is true at the point of call, aborts on failure
//POST_CONDITION(test) checks that its parameter is true at the end of the scope containing the call, aborts on failure
//VALIDITY_CHECK(obj) checks obj.is_valid() at the point of call, aborts on failure
//INVARIANT_CHECK(obj) checks obj.is_valid() at the point of call and at the end of the scope containing the call, aborts on failure

//Implementation:

#if !defined(CHECK_CONDITIONS)
#define PRE_CONDITION(x) ((void)(0))
#define POST_CONDITION(x) ((void)(0))
#define INVARIANT_CHECK(x) ((void)(0))
#define VALIDITY_CHECK(x) ((void)(0))
#else

#include <functional>

struct PostCondition
{
	PostCondition(const char* file, int line, const char* expr, const std::function<bool()>& f) : f_(f), file_(file), line_(line), expr_(expr)
	{}

	~PostCondition()
	{
		if (!f_())
		{
			fprintf(stderr, "POST_CONDITION \"%s\" is false \n(%s, line %d)\n", expr_, file_, line_);
			abort();
		}
	}

private:
	const std::function<bool()> f_;
	const char* const file_;
	const int line_;
	const char* const expr_;
};

#define POST_CONDITION_NAME(x) POSTCOND_##x

//without this, POST_CONDITION_NAME(__LINE__) is "POSTCOND___LINE__"
#define POST_CONDITION_VAR(x) POST_CONDITION_NAME(x)

#define INVARIANT_COND_NAME(x) INVARIANT_##x
#define INVARIANT_COND_VAR(x) INVARIANT_COND_NAME(x)

inline void preCondition(const char* file, int line, const char* expr, bool cond) noexcept
{
	if (!cond)
	{
		fprintf(stderr, "PRE_CONDITION \"%s\" is false \n(%s, Line %d)\n", expr, file, line);
		abort();
	}
}

inline void checkValidity(const char* file, int line, const char* expr, bool cond) noexcept
{
	if (!cond)
	{
		fprintf(stderr, "object \"%s\" is invalid \n(%s, Line %d)\n", expr, file, line);
		abort();
	}
}

template<typename T>
bool checkInvariant(const T& obj) noexcept
{
	return obj.is_valid();
}

//checks both at the point of construction and destruction
template<typename T>
struct CheckInvariant
{
	CheckInvariant(const char* file, int line, const char* expr, const T& obj) : file_(file), line_(line), expr_(expr), obj_(obj)
	{
		if (!checkInvariant<T>(obj_))
		{
			fprintf(stderr, "class invariant on object \"%s\" is false BEFORE operations\n(%s, Line %d)\n", expr_, file_, line_);
			abort();
		}
	}

	~CheckInvariant()
	{
		if (!checkInvariant<T>(obj_))
		{
			fprintf(stderr, "class invariant on object \"%s\" is false AFTER operations\n(%s, Line %d)\n", expr_, file_, line_);
			abort();
		}
	}

private:
	const char* const file_;
	const int line_;
	const char* const expr_;
	const T& obj_;
};

#define PRE_CONDITION(x) preCondition(__FILE__, __LINE__, #x, x)	

#define POST_CONDITION(x) PostCondition POST_CONDITION_VAR(__LINE__)(__FILE__, __LINE__, #x, [&]() { return (x); })

#define INVARIANT_CHECK(obj) CheckInvariant<decltype(obj)> INVARIANT_COND_VAR(__LINE__)(__FILE__, __LINE__, #obj, obj)

#define VALIDITY_CHECK(obj) checkValidity(__FILE__, __LINE__, #obj, checkInvariant<decltype(obj)>(obj))

#endif//CHECK_CONDITIONS

#endif//CONDITIONS_H
