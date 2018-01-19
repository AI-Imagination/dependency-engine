#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>

namespace resengine {

struct Resource;
struct Operation;
using ResHandler = Resource *;
using OptHandler = Operation *;

// Base class for engines.
class Engine {
public:
  // Callback that will be triggered after the option completes.
  using OptCallback = std::function<void(OptHandler)>;
  using OptCallbackP = std::shared_ptr<OptCallback>;

  // Push an asynchronuous task, which is an operation `opt`, it will waits to
  // read the resources `read_res`, and waits to write `write_res`.
  //
  // Usage:
  //
  //   ResHandler a, b;
  //   Operation opt([args...]{
  //      ...
  //   });
  //   some_engine.PushAsyncTask(opt, {a}, {b}, some_callback);
  //
  virtual void PushAsyncTask(OptHandler opt, std::vector<ResHandler> read_res,
                             std::vector<ResHandler> write_res,
                             const OptCallbackP &callback) = 0;

  // Push a synchronuous task `opt`, it will be executed immediately.
  virtual void PushSyncTask(OptHandler opt) = 0;

  // Number of tasks in the engine.
  virtual size_t num_tasks() const = 0;
};

} // namespace resengine

#endif // ENGINE_H_
