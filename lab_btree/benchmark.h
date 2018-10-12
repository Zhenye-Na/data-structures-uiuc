/**
 * @file benchmark.h
 * Class for easy runtime benchmarks that can output to simple two column
 * csv files.
 *
 * @author Matt Joras
 * @date Winter 2013
 */
#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>

/**
 * Class which contains a collection of benchmark results.
 * @author Matt Joras
 * @date Winter 2013
 */
class Benchmark
{
  private:
    /**
     * Contains the actual results / benchmark parameter, uses std::chrono.
     */
    struct BenchmarkResult {
        unsigned int n;
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        BenchmarkResult(unsigned int n,
                        std::chrono::high_resolution_clock::time_point s,
                        std::chrono::high_resolution_clock::time_point e)
            : n(n), start_time(s), end_time(e)
        {
        }
    };

    std::vector<BenchmarkResult> results;
    std::string name;

  public:
    Benchmark(const std::string& name) : name(name)
    {
    }

    size_t add_point(unsigned int n)
    {
        auto min = std::chrono::high_resolution_clock::time_point::min();
        results.emplace_back(n, min, min);
        return results.size() - 1;
    }

    void start(size_t idx)
    {
        results[idx].start_time = std::chrono::high_resolution_clock::now();
    }

    void end(size_t idx)
    {
        results[idx].end_time = std::chrono::high_resolution_clock::now();
    }

    void write_to_file(std::string out_dir = "results")
    {
        using namespace std::chrono;
        std::string outname = out_dir + "/" + name + ".csv";
        std::ofstream out(outname);
        out << "n,elapsed_time (ms)" << std::endl;
        for (auto& result : results) {
            auto diff = result.end_time - result.start_time;
            out << result.n << ","
            << duration_cast<milliseconds>(diff).count()
            << std::endl;
        }
    }
};

#endif /* BENCHMARK_H */
