/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_COMPILER_PLUGIN_POPLAR_DRIVER_PASSES_HOST_COMPUTE_SCHEDULE_OPTIMIZER_H_
#define TENSORFLOW_COMPILER_PLUGIN_POPLAR_DRIVER_PASSES_HOST_COMPUTE_SCHEDULE_OPTIMIZER_H_

#include "tensorflow/compiler/xla/service/hlo_pass_interface.h"

namespace xla {

class HloModule;

namespace poplarplugin {

/*
 * This pass makes sure that the sends and recvs are scheduled in the same
 * order with respect to the shards. This can allow for more overlap of the
 * operations on the host and the stream copies between the host and the IPUs.
 */
class HostComputeScheduleOptimizer : public HloModulePass {
 public:
  absl::string_view name() const override {
    return "host-compute-schedule-optimizer";
  }

  using HloPassInterface::Run;
  StatusOr<bool> Run(
      HloModule* module,
      const absl::flat_hash_set<absl::string_view>& execution_threads) override;
};

}  // namespace poplarplugin
}  // namespace xla

#endif  // TENSORFLOW_COMPILER_PLUGIN_POPLAR_DRIVER_PASSES_HOST_COMPUTE_SCHEDULE_OPTIMIZER_H_
