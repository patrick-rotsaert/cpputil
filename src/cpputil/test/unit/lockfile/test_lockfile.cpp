//
// Copyright (C) 2024 Patrick Rotsaert
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <gtest/gtest.h>
#include <cpputil/lockfile/lockfile.h>
#include <filesystem>

namespace cpputil {
namespace lockfile {

namespace {
const auto LOCKFILE = std::filesystem::temp_directory_path() / "_test_lockfile_.LOCK";
}

TEST(LockfileTests, TestSuccess)
{
	EXPECT_NO_THROW(lockfile{ LOCKFILE });
}

TEST(LockfileTests, TestFailure)
{
	{
		auto l = lockfile{ LOCKFILE };
		EXPECT_ANY_THROW(lockfile{ LOCKFILE });
	}
	EXPECT_NO_THROW(lockfile{ LOCKFILE });
}

} // namespace lockfile
} // namespace cpputil
