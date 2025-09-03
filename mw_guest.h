#pragma once

#include <kernel/function.h>
#include <kernel/memory.h>
#include <ppc/ppc_recomp_shared.h>
#include <os/logger.h>

namespace mw {

// Simple shim helpers to call MW05 guest code if a mapping is available.

inline void* guest_alloc(size_t size)
{
#if defined(sub_822C0988)
    return GuestToHostFunction<void*>(sub_822C0988, (uint32_t)size);
#else
    LOGF_UTILITY("mw::guest_alloc fallback malloc({})", size);
    return ::malloc(size);
#endif
}

inline void guest_free(void* p)
{
#if defined(sub_822C0270)
    GuestToHostFunction<void>(sub_822C0270, p);
#else
    LOGF_UTILITY("mw::guest_free fallback free({})", (void*)p);
    ::free(p);
#endif
}

} // namespace mw
