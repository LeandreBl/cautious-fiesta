#ifndef _TRACE_HPP_
# define _TRACE_HPP_

#include <cstdio>

#include "colors.h"

int trace(const char string[]) noexcept;
int trace(bool isOk) noexcept;
int trace(bool isOk, const char string[]) noexcept;

template <typename... Args>
int trace(const char *format, Args... args) noexcept
{
	return fprintf(stderr, format, args ...);
}

template <typename... Args>
int trace(bool isOk, const char *format, Args... args) noexcept
{
	int ret;

	ret = trace(isOk);
	ret += fprintf(stderr, format, args ...);
	return ret;
}

#endif /* !_TRACE_HPP_ */