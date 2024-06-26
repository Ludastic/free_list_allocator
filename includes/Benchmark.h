#pragma once

#include <ctime>
#include <cstddef>
#include <chrono>
#include <ratio>
#include <vector>

#include "Allocator.h" // base class allocator


struct BenchmarkResults
{
	std::size_t Operations;
	std::chrono::milliseconds Milliseconds;
	double OperationsPerSec;
	double TimePerOperation;
    std::size_t MemoryPeak;
};

class Benchmark {
public:
    Benchmark() = delete;

    Benchmark(const unsigned int nOperations) : m_nOperations { nOperations } { }

	void SingleAllocation(Allocator* allocator, const std::size_t size, const std::size_t alignment);
	void SingleFree(Allocator* allocator, const std::size_t size, const std::size_t alignment);

	void MultipleAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments);
	void MultipleFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments);

private:
	void PrintResults(const BenchmarkResults& results) const;

	const BenchmarkResults buildResults(std::size_t nOperations, std::chrono::milliseconds&& ellapsedTime, std::size_t memoryUsed) const;
    
    void SetStartTime() noexcept { Start = std::chrono::high_resolution_clock::now(); }

    void SetFinishTime() noexcept { Finish = std::chrono::high_resolution_clock::now(); }

    void SetElapsedTime() noexcept { TimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Finish - Start); }

    void StartRound() noexcept { SetStartTime(); }

    void FinishRound() noexcept
    {
        SetFinishTime();
        SetElapsedTime();
    }

private:
	std::size_t m_nOperations;

    std::chrono::time_point<std::chrono::high_resolution_clock> Start;
    std::chrono::time_point<std::chrono::high_resolution_clock> Finish;

    std::chrono::milliseconds TimeElapsed{};
};
