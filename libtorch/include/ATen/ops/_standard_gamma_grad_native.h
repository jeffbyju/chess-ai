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
TORCH_API at::Tensor & _standard_gamma_grad_out(const at::Tensor & self, const at::Tensor & output, at::Tensor & out);
TORCH_API at::Tensor _standard_gamma_grad_cpu(const at::Tensor & self, const at::Tensor & output);
TORCH_API at::Tensor _standard_gamma_grad_cuda(const at::Tensor & self, const at::Tensor & output);
} // namespace native
} // namespace at
