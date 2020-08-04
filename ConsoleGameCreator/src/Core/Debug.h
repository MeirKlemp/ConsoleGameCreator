#pragma once

#ifdef CGC_DEBUG
  #if defined(CGC_WINDOWS)
    #define CGC_DEBUGBREAK() __debugbreak()
  #elif defined(CGC_LINUX)
    #include <signal.h>
    #define CGC_DEBUGBREAK() raise(SIGTRAP)
  #else
    #error "Platform doesn't support debugbreak yet!"
  #endif
  #define CGC_ENABLE_ASSERTS
#else
  #define CGC_DEBUGBREAK()
#endif

#ifdef CGC_ENABLE_ASSERTS
  // TODO: Add logging.
  #define CGC_ASSERT(x, ...) { if(!(x)) { CGC_DEBUGBREAK(); } }
#else
  #define CGC_ASSERT(x, ...)
#endif
