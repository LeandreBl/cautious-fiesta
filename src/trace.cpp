#include "trace.hpp"

int trace(const char string[]) noexcept
{
	return fputs(string, stderr);
}

int trace(bool isOk) noexcept
{
	const char *color;

	if (isOk == true)
		color = "[ " BOLDGREEN "OK" RESET " ] ";
	else
		color = "[ " BOLDRED "KO" RESET " ] ";
	return fputs(color, stderr);
}

int trace(bool isOk, const char string[]) noexcept
{
	int ret = trace(isOk);
	return ret + trace(string);
}