#include <type_traits>
#include <iostream>
#include <chrono>
#include <math.h>
using namespace std;


// Non-Void version
template <class Fn, class... Args>
auto timer(Fn fn, Args && ... args)
    -> typename std::enable_if<
        !std::is_same< decltype( fn( std::forward<Args>(args) ... )), void >::value,
        std::pair<double, decltype(fn(args...))> >::type
{
  static_assert(!std::is_void<decltype(fn(args...))>::value,
                "Call timer_void if return type is void!");
  auto start = std::chrono::high_resolution_clock::now();
  auto ret = fn(args...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  return { elapsed_seconds.count(), ret };
}

// Void version
template <class Fn, class ... Args>
auto timer(Fn fn, Args && ... args) -> typename std::enable_if<
        std::is_same< decltype( fn( std::forward<Args>(args) ... )), void >::value,
        double>::type
{
  static_assert(std::is_void<decltype(fn(args...))>::value,
                "Call timer for non void return type");
  auto start = std::chrono::high_resolution_clock::now();
  fn(args...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  return elapsed_seconds.count();
}

double arbitrary_code(double x, double y) {
    return x * y;
}

int main () {
    std::cout << timer(arbitrary_code,1,2).first << std::endl;
}