#include "Benchmark.h"

#include <iostream>
#include <cassert>

void Benchmark::SingleAllocation(Allocator* allocator, const std::size_t size, const std::size_t alignment) {
    std::cout << "BENCHMARK: ALLOCATION" << std::endl;
    std::cout << "\tSize:     \t" << size << std::endl;
    std::cout << "\tAlignment\t" << alignment << std::endl;

    StartRound();

    allocator->Init();

    auto operations = 0u;

    while (operations < m_nOperations) {
        allocator->Allocate(size, alignment);
        ++operations;
    }
    
    FinishRound();

    BenchmarkResults results = buildResults(m_nOperations, std::move(TimeElapsed), allocator->m_peak);

    PrintResults(results);
}

void Benchmark::SingleFree(Allocator* allocator, const std::size_t size, const std::size_t alignment) {
    std::cout << "BENCHMARK: ALLOCATION/FREE" << std::endl;
    std::cout << "\tSize:     \t" << size << std::endl;
    std::cout << "\tAlignment\t" << alignment << std::endl;

    void* addresses[m_nOperations];

    StartRound();

    allocator->Init();

    auto operations = 0u;

    while (operations < m_nOperations) {
        addresses[operations] = allocator->Allocate(size, alignment);
        ++operations;
    }

    while (operations) {
        allocator->Free(addresses[--operations]);
    }

    FinishRound();

    BenchmarkResults results = buildResults(m_nOperations, std::move(TimeElapsed), allocator->m_peak);

    PrintResults(results);
}

void Benchmark::MultipleAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments) {
    assert(allocationSizes.size() == alignments.size() && "Allocation sizes and Alignments must have same length");

    for (auto i = 0u; i < allocationSizes.size(); ++i) {
        SingleAllocation(allocator, allocationSizes[i], alignments[i]);
    }
}

void Benchmark::MultipleFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments) {
    assert(allocationSizes.size() == alignments.size() && "Allocation sizes and Alignments must have same length");

    for (auto i = 0u; i < allocationSizes.size(); ++i) {
        SingleFree(allocator, allocationSizes[i], alignments[i]);
    }
}

void Benchmark::PrintResults(const BenchmarkResults& results) const {
    std::cout << "\tRESULTS:" << std::endl;
    std::cout << "\t\tOperations:    \t" << results.Operations << std::endl;
    std::cout << "\t\tTime elapsed: \t" << results.Milliseconds.count() << " ms" << std::endl;
    std::cout << "\t\tOp per sec:    \t" << results.OperationsPerSec << " ops/ms" << std::endl;
    std::cout << "\t\tTimer per op:  \t" << results.TimePerOperation << " ms/ops" << std::endl;
    std::cout << "\t\tMemory peak:   \t" << results.MemoryPeak << " bytes" << std::endl;

    std::cout << std::endl;
}

const BenchmarkResults Benchmark::buildResults(std::size_t nOperations, std::chrono::milliseconds&& elapsedTime, const std::size_t memoryPeak) const {
    BenchmarkResults results;

    results.Operations = nOperations;
    results.Milliseconds = std::move(elapsedTime);
    results.OperationsPerSec = results.Operations / static_cast<double>(results.Milliseconds.count());
    results.TimePerOperation = static_cast<double>(results.Milliseconds.count()) / static_cast<double>(results.Operations);
    results.MemoryPeak = memoryPeak;

    return results;
}

