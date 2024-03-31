#pragma once

#include "cpputil/config.h"

#ifdef CPPUTIL_HAVE_BOOST
#include <boost/throw_exception.hpp>
#define CPPUTIL_THROW_EXCEPTION(x) BOOST_THROW_EXCEPTION(x)
#else
#define CPPUTIL_THROW_EXCEPTION(x) throw(x)
#endif
