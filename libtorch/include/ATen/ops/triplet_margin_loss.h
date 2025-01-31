#pragma once

// @generated by torchgen/gen.py from Function.h

#include <ATen/Context.h>
#include <ATen/DeviceGuard.h>
#include <ATen/TensorUtils.h>
#include <ATen/TracerMode.h>
#include <ATen/core/Generator.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <optional>



#include <ATen/ops/triplet_margin_loss_ops.h>

namespace at {


// aten::triplet_margin_loss(Tensor anchor, Tensor positive, Tensor negative, float margin=1.0, float p=2, float eps=1e-06, bool swap=False, int reduction=Mean) -> Tensor
inline at::Tensor triplet_margin_loss(const at::Tensor & anchor, const at::Tensor & positive, const at::Tensor & negative, double margin=1.0, double p=2, double eps=1e-06, bool swap=false, int64_t reduction=at::Reduction::Mean) {
    return at::_ops::triplet_margin_loss::call(anchor, positive, negative, margin, p, eps, swap, reduction);
}

}
