//
// Copyright (C) 2024 Patrick Rotsaert
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "cpputil/logging/ibackend.h"
#include "cpputil/api.h"
#include "cpputil/config.h"

#include <fmt/format.h>
#include <boost/assert/source_location.hpp>

#include <memory>
#include <chrono>

namespace cpputil {
namespace logging {

class CPPUTIL_EXPORT logging
{
public:
	static std::unique_ptr<ibackend> backend;

	// Not thread safe
	static void set_backend(std::unique_ptr<ibackend>&& backend);
};

} // namespace logging
} // namespace cpputil

// Macro for logging using a fmtlib format string
#define culog(lvl, ...)                                                                                                                    \
	do                                                                                                                                     \
	{                                                                                                                                      \
		auto& backend = ::cpputil::logging::logging::backend;                                                                              \
		if (backend)                                                                                                                       \
		{                                                                                                                                  \
			backend->log_message(                                                                                                          \
			    std::chrono::system_clock::now(), BOOST_CURRENT_LOCATION, ::cpputil::logging::log_level::lvl, fmt::format(__VA_ARGS__));   \
		}                                                                                                                                  \
	} while (false)

// Macros for eliding logging code at compile time
#undef CPPUTIL_MIN_LOG
#define CPPUTIL_MIN_LOG(minlvl, lvl, ...)                                                                                                  \
	do                                                                                                                                     \
	{                                                                                                                                      \
		if constexpr (::cpputil::logging::log_level::lvl >= ::cpputil::logging::log_level::minlvl)                                         \
		{                                                                                                                                  \
			culog(lvl, __VA_ARGS__);                                                                                                       \
		}                                                                                                                                  \
	} while (false)

#undef CPPUTIL_LOG
#define CPPUTIL_LOG(lvl, ...) CPPUTIL_MIN_LOG(CPPUTIL_LOGGING_LEVEL, lvl, __VA_ARGS__)
