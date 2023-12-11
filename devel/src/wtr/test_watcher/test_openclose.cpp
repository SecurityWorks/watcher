#include "snitch/snitch.hpp"
#include "test_watcher/test_watcher.hpp"
#include <stdio.h>

// clang-format off

TEST_CASE("Rapid Open and Close", "[concurrent][openclose][perf]")
{
  using namespace wtr::test_watcher;

  printf("Rapid Open and Close\n");

  auto res = vec_cat(
    perf_range<RangePair{
        .watcher_range=  { .start=1,  .stop=80,  .step=1 },
        .event_range=    { .start=10, .stop=10,  .step=0 }}>(),
    perf_range<RangePair{
        .watcher_range=  { .start=1,   .stop=30,   .step=1 },
        .event_range=    { .start=100, .stop=100,  .step=0 }}>()
  );

  show_results(res);

  for (auto r : res)
    CHECK(r.time_taken_watch < r.time_taken_fsops);
};

// clang-format on
