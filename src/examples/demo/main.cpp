//
// Copyright (C) 2024 Patrick Rotsaert
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "cpputil/config.h"
#include "cpputil/logging/logging.h"

#ifdef CPPUTIL_USE_SPDLOG
#include <spdlog/spdlog.h>
#endif

namespace cpputil {
namespace demo {

} // namespace demo
} // namespace cpputil

int main()
{
#ifdef CPPUTIL_USE_SPDLOG
	spdlog::set_level(spdlog::level::trace);
	spdlog::set_pattern("%L [%Y-%m-%d %H:%M:%S.%f Δt=%iμs](%t) %^%v%$ [%s:%#]");
#endif

	culog(debug, "application started");

	using namespace cpputil::demo;

	try
	{
		// TODO...
	}
	catch (const std::exception& e)
	{
		culog(err, "{}", e.what());
		return 1;
	}
}
