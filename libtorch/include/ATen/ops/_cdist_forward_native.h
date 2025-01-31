#pragma once

// @generated by torchgen/gen.py from NativeFunction.h

#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <optional>
#include <c10/core/QScheme.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <tuple>
#include <vector>


namespace at {
namespace native {
TORCH_API at::Tensor & _cdist_forward_out(const at::Tensor & x1, const at::Tensor & x2, double p, ::std::optional<int64_t> compute_mode, at::Tensor & out);
TORCH_API at::Tensor _cdist_forward(const at::Tensor & x1, const at::Tensor & x2, double p, ::std::optional<int64_t> compute_mode);
TORCH_API at::Tensor _cdist_forward_mps(const at::Tensor & x1, const at::Tensor & x2, double p, ::std::optional<int64_t> compute_mode);
} // namespace native
} // namespace at
