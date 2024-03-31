//
// Copyright (C) 2024 Patrick Rotsaert
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include "cpputil/logging/ibackend.h"
#include "cpputil/api.h"

namespace cpputil {
namespace logging {

class CPPUTIL_EXPORT spdlog_backend : public ibackend
{
public:
	spdlog_backend();

	~spdlog_backend() override;

	void log_message(const std::chrono::system_clock::time_point& time,
	                 const boost::source_location&                location,
	                 log_level                                    level,
	                 const std::string_view&                      message) override;
};

} // namespace logging
} // namespace cpputil
