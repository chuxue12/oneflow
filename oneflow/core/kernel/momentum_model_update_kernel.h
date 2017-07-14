#ifndef ONEFLOW_CORE_KERNEL_MOMENTUM_MODEL_UPDATE_KERNEL_H_
#define ONEFLOW_CORE_KERNEL_MOMENTUM_MODEL_UPDATE_KERNEL_H_

#include "oneflow/core/kernel/kernel_manager.h"

namespace oneflow {

template<DeviceType device_type, typename FloatingPointType>
class MomentumMdUpdateKernel final : public Kernel {
 public:
  OF_DISALLOW_COPY_AND_MOVE(MomentumMdUpdateKernel);
  MomentumMdUpdateKernel() = default;
  ~MomentumMdUpdateKernel() = default;

  void Forward(const KernelCtx&,
               std::function<Blob*(const std::string&)>) const override;

  void Backward(const KernelCtx&,
                std::function<Blob*(const std::string&)>) const override {
    UNEXPECTED_RUN();
  }

 private:
};

}  // namespace oneflow

#endif  // ONEFLOW_CORE_KERNEL_MOMENTUM_MODEL_UPDATE_KERNEL_H_
