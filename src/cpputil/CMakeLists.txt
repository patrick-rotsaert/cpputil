#
# Copyright (C) 2024 Patrick Rotsaert
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#

cmake_minimum_required(VERSION 3.19)

set(EXTRA_SOURCES)
set(EXTRA_PUBLIC_LIBRARIES)
set(EXTRA_PUBLIC_HEADERS)

if(${PROJECT_NAME_UC}_INSTALL)
	# When install rules are included, then the fmt and spdlog packages must be pre-installed.
	# If not, then they will be fetched from github (see included fmtlib.cmake and spdlog.cmake)
	# and then their install targets would be included, which is probably not what you want.
	project_find_package(fmt REQUIRED)
	if(${PROJECT_NAME_UC}_USE_SPDLOG)
		project_find_package(spdlog REQUIRED)
	endif()
endif()

# {fmtlib}
include(${PROJECT_SOURCE_DIR}/cmake/common/fmtlib.cmake)

# spdlog
if(${PROJECT_NAME_UC}_USE_SPDLOG)
	include(${PROJECT_SOURCE_DIR}/cmake/common/spdlog.cmake)
	list(APPEND EXTRA_PUBLIC_LIBRARIES spdlog::spdlog)
	list(APPEND EXTRA_SOURCES logging/spdlog_backend.cpp logging/spdlog_backend.h)
	if(${PROJECT_NAME_UC}_INSTALL)
		list(APPEND EXTRA_PUBLIC_HEADERS logging/spdlog_backend.h)
	endif()
endif()

# Threads
if(${PROJECT_NAME_UC}_THREAD_SAFE)
	project_find_package(Threads REQUIRED)
	list(APPEND EXTRA_PUBLIC_LIBRARIES Threads::Threads)
endif()

# Boost
find_package(Boost QUIET COMPONENTS date_time system filesystem)
if(Boost_FOUND)
	set(CPPUTIL_HAVE_BOOST 1)
	list(APPEND EXTRA_PUBLIC_LIBRARIES Boost::boost)
endif()
if(Boost_SYSTEM_FOUND)
	set(CPPUTIL_HAVE_BOOST_SYSTEM 1)
	list(APPEND EXTRA_PUBLIC_LIBRARIES Boost::system)
endif()
if(Boost_DATE_TIME_FOUND)
	set(CPPUTIL_HAVE_BOOST_DATE_TIME 1)
	list(APPEND EXTRA_PUBLIC_LIBRARIES Boost::date_time)
endif()
if(Boost_FILESYSTEM_FOUND)
	set(CPPUTIL_HAVE_BOOST_FILESYSTEM 1)
	list(APPEND EXTRA_PUBLIC_LIBRARIES Boost::filesystem)
endif()

add_project_library(${PROJECT_NAME}
	SOURCES
		conversion/conversion.cpp
		lockfile/lockfile.cpp
		lockfile/lockfile_impl_posix.hpp
		logging/ibackend.cpp
		logging/logging.cpp
		misc/demangle.cpp
		version.cpp
		version.h.in
		config.h.in
		${EXTRA_SOURCES}

	PUBLIC_HEADERS
		api.h
		conversion/conversion.h
		lockfile/lockfile.h
		logging/ibackend.h
		logging/logging.h
		logging/log_level.h
		misc/formatters.hpp
		misc/lock_types.hpp
		misc/sync_queue.hpp
		misc/always_false.hpp
		misc/demangle.h
		misc/demangled_type_name.hpp
		misc/is_optional.hpp
		misc/is_scoped_enum.hpp
		misc/throw_exception.h
		${EXTRA_PUBLIC_HEADERS}

	PUBLIC_LIBRARIES
		fmt::fmt
		${EXTRA_PUBLIC_LIBRARIES}

	UNIT_TEST_SOURCES
		test/unit/conversion/test_conversion.cpp
		test/unit/lockfile/test_lockfile.cpp

	PUBLIC_INCLUDE_DIRS
		${CMAKE_CURRENT_BINARY_DIR}/.. # for configured headers, see below
)

#
# Build time logging levels

# Values are as in log_level.h
set(LOGGING_LEVELS trace debug info warn err critical off)

if(${PROJECT_NAME_UC}_DEBUG_BUILD)
	set(DEFAULT_LOGGING_LEVEL trace)
else()
	set(DEFAULT_LOGGING_LEVEL warn)
endif()

# Logging verbosity of the library
set(${PROJECT_NAME_UC}_LOGGING_LEVEL ${DEFAULT_LOGGING_LEVEL} CACHE STRING "Logging verbosity of the ${PROJECT_NAME} library")
set_property(CACHE ${PROJECT_NAME_UC}_LOGGING_LEVEL PROPERTY STRINGS ${LOGGING_LEVELS})

configure_file(
	version.h.in
	${CMAKE_CURRENT_BINARY_DIR}/version.h
)

configure_file(
	config.h.in
	${CMAKE_CURRENT_BINARY_DIR}/config.h
)

if(${PROJECT_NAME_UC}_INSTALL)
	install_project_header(${CMAKE_CURRENT_BINARY_DIR}/version.h ${CMAKE_CURRENT_BINARY_DIR}/..)
	install_project_header(${CMAKE_CURRENT_BINARY_DIR}/config.h ${CMAKE_CURRENT_BINARY_DIR}/..)
endif()
