#include "oneflow/core/kernel/broadcast_like_kernel.h"
#include "oneflow/core/ndarray/ndarray_util.h"

namespace oneflow {

template<DeviceType device_type, typename T>
void BroadcastLikeKernel<device_type, T>::ForwardDataContent(
    const KernelCtx& ctx, std::function<Blob*(const std::string&)> BnInOp2Blob) const {
  const Blob* x_blob = BnInOp2Blob("x");
  const Blob* like_blob = BnInOp2Blob("like");
  Blob* y_blob = BnInOp2Blob("y");
  const int64_t num_axes = y_blob->shape().NumAxes();
  const BroadcastLikeOpConf& conf = this->op_conf().broadcast_like_conf();
  const Shape& reduced_shape = like_blob->shape().CreateReducedShapeOrOnesShape(
      {conf.reduced_axis().begin(), conf.reduced_axis().end()});
  NdarrayUtil<device_type, T>::BroadcastTo(
      ctx.device_ctx, XpuVarNdarray<T>(y_blob, num_axes),
      XpuVarNdarray<const T>(reduced_shape, x_blob->dptr<T>()));
}

template<DeviceType device_type, typename T>
void BroadcastLikeKernel<device_type, T>::ForwardDim0ValidNum(
    const KernelCtx& ctx, std::function<Blob*(const std::string&)> BnInOp2Blob) const {
  BnInOp2Blob("y")->CopyDim0ValidNumFrom(ctx.device_ctx, BnInOp2Blob("like"));
}

REGISTER_KERNEL_HELPER_GPU_FLOATING(OperatorConf::kBroadcastLikeConf, BroadcastLikeKernel);

}  // namespace oneflow
