// This program demonstrates how to implement while-loop control flow
// using condition tasks.
#include <taskflow/taskflow.hpp>

int main() {

  tf::Executor executor;
  tf::Taskflow taskflow;

  int i;

  auto [init, cond, body, back, done] = taskflow.emplace(
    [&](){ std::cout << "i=0\n"; i=0; },
    [&](){ std::cout << "while i<10 \n"; return i < 10 ? 0 : 1; },
    [&](){ std::cout << "Here i is incremented by 2....,i+=2 = " << i+=2 << '\n'; },
    [&](){ std::cout << "back\n"; return 0; },
    [&](){ std::cout << "done\n"; }
  );

  init.name("init");
  cond.name("while i < 10 ");
  body.name("i+=2");
  back.name("back");
  done.name("done");

  init.precede(cond);
  cond.precede(body, done);
  body.precede(back);
  back.precede(cond);

  taskflow.dump(std::cout);

  executor.run(taskflow).wait();

  return 0;
}

