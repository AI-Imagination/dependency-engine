#ifndef DEPENG_ENGINE_H_
#define DEPENG_ENGINE_H_

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace depeng {

struct Resource;
struct Operation;
using ResHandler = Resource *;
using OptHandler = Operation *;

/*
 * Base class for engines.
 * There are several basic features of an engine:
 *   - an engine never holds any resource, but the handlers
 *   - engine helpes to schedule the execution of operations, and release them
 *   to underlying computing resource.
 */
class Engine {
public:
  // Callback that will be triggered after the option completes.
  using OptCallback = std::function<void(OptHandler)>;
  using OptCallbackP = std::shared_ptr<OptCallback>;

  /*
   * Push an asynchronuous task, which is an operation `opt`, it will waits to
   * read the resources `read_res`, and waits to write `write_res`.
   *
   * Usage:
   *
   *   ResHandler a, b;
   *   Operation opt([args...]{
   *      ...
   *   });
   *   some_engine.PushAsyncTask(opt, {a}, {b}, some_callback);
   */
  virtual void PushAsyncTask(OptHandler opt, std::vector<ResHandler> read_res,
                             std::vector<ResHandler> write_res,
                             const OptCallbackP &callback) = 0;

  // Push a synchronuous task `opt`, it will be executed immediately.
  virtual void PushSyncTask(OptHandler opt) = 0;

  // Number of tasks in the engine.
  virtual size_t num_oprs() const = 0;
};

// An engine without concurrency support, any new application can take this as
// the first step to test.
class NaiveEngine : public Engine {
public:
  virtual void PushAsyncTask(OptHandler opt, std::vector<ResHandler> read_res,
                             std::vector<ResHandler> write_res,
                             const OptCallbackP &callback) override {}

  virtual void PushSyncTask(OptHandler opt) override;

  virtual size_t num_oprs() const override { return 0; };
};

// An engine that handles dependency.
class DependencyEngine : public Engine {
public:
  virtual void PushAsyncTask(OptHandler opt, std::vector<ResHandler> read_res,
                             std::vector<ResHandler> write_res,
                             const OptCallbackP &callback) override;

  virtual void PushSyncTask(OptHandler opt) override;

  virtual size_t num_oprs() const override;

private:
  std::vector<OptHandler> ops_;
  std::map<ResHandler, std::vector<OptHandler>> res_;
};

} // namespace depeng

#endif // DEPENG_ENGINE_H_
