//
// Copyright (C) 2024 Patrick Rotsaert
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "cpputil/version.h"

#include <cassert>

namespace cpputil {

int version::number()
{
	return CPPUTIL_VERSION_NUMBER;
}

int version::major()
{
	return CPPUTIL_VERSION_MAJOR;
}

int version::minor()
{
	return CPPUTIL_VERSION_MINOR;
}

int version::patch()
{
	return CPPUTIL_VERSION_PATCH;
}

void version::check()
{
	assert(CPPUTIL_VERSION_NUMBER == number());
}

} // namespace cpputil
