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



#include <ATen/ops/cov_ops.h>

namespace at {


// aten::cov(Tensor self, *, int correction=1, Tensor? fweights=None, Tensor? aweights=None) -> Tensor
inline at::Tensor cov(const at::Tensor & self, int64_t correction=1, const ::std::optional<at::Tensor> & fweights={}, const ::std::optional<at::Tensor> & aweights={}) {
    return at::_ops::cov::call(self, correction, fweights, aweights);
}

}
