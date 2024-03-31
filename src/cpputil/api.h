//
// Copyright (C) 2024 Patrick Rotsaert
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

// clang-format off

#if defined _WIN32 || defined __CYGWIN__
  #define CPPUTIL_API_IMPORT __declspec(dllimport)
  #define CPPUTIL_API_EXPORT __declspec(dllexport)
  #define CPPUTIL_API_LOCAL
#else
  #if __GNUC__ >= 4 // TODO: clang?
    #define CPPUTIL_API_IMPORT __attribute__ ((visibility ("default")))
    #define CPPUTIL_API_EXPORT __attribute__ ((visibility ("default")))
    #define CPPUTIL_API_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define CPPUTIL_API_IMPORT
    #define CPPUTIL_API_EXPORT
    #define CPPUTIL_API_LOCAL
  #endif
#endif

#ifdef CPPUTIL_SHARED // compiled as a shared library
  #ifdef CPPUTIL_SHARED_EXPORTS // defined if we are building the shared library
    #define CPPUTIL_EXPORT CPPUTIL_API_EXPORT
  #else
    #define CPPUTIL_EXPORT CPPUTIL_API_IMPORT
  #endif // CPPUTIL_SHARED_EXPORTS
  #define CPPUTIL_LOCAL CPPUTIL_API_LOCAL
#else // compiled as a static library
  #define CPPUTIL_EXPORT
  #define CPPUTIL_LOCAL
#endif // CPPUTIL_SHARED
