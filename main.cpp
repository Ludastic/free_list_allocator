#include <iostream>
#include <vector>

#include "Benchmark.h"
#include "Allocator.h"
#include "FreeListAllocator.h"

int main()
{
    const auto B = static_cast<std::size_t>(900'000'000);

    const std::vector<std::size_t> ALLOCATION_SIZES {262'144*102};
    const std::vector<std::size_t> ALIGNMENTS {8};
    Allocator * freeListAllocator = new FreeListAllocator(B, FreeListAllocator::PlacementPolicy::FIND_FIRST);

    Benchmark benchmark(10);

    benchmark.MultipleAllocation(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.MultipleFree(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);

}




