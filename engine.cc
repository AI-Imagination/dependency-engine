#include "engine.h"

#include <glog/logging.h>

namespace depeng {

struct Operation {
  using opr_t = std::function<void()>;

  Operation(opr_t &&opr) : opr(opr) {}

  void operator()() { opr(); }

  opr_t opr;
}; // struct Operation

void NaiveEngine::PushSyncTask(OptHandler opr) {
  CHECK_NOTNULL(opr);
  (*opr)();
}

} // namespace depeng
