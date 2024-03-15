#ifndef benchmark_hxx_
#define benchmark_hxx_

//=============================================================================

#include <atomic>
#include <chrono>

//=============================================================================

template <typename Clock = std::chrono::steady_clock>
class benchmark
{
public:
  using clock_type = Clock;

private:
  using tp_type = std::atomic<std::chrono::time_point<Clock>>;
  tp_type t0;

public:
  benchmark()
  {
    std::atomic_thread_fence(std::memory_order_acq_rel);
    t0.store(clock_type::now(), std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acq_rel);
  }

  double elapsed() const
  {
    std::atomic_thread_fence(std::memory_order_acq_rel);
    tp_type t1;
    t1.store(clock_type::now(), std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acq_rel);
    return 
      std::chrono::duration<double>(
        t1.load(std::memory_order_relaxed) - 
        t0.load(std::memory_order_relaxed)
      ).count()
    ;
  }
};

//=============================================================================

#endif // #ifndef benchmark_hxx_
