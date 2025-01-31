#pragma once
// @generated by torchgen/gen.py from DispatchKeyFunction.h

// NB: The implementing C++ file is RegisterDispatchKey.cpp

// The only #includes we need are for custom classes that have defaults in the C++ API
#include <c10/core/MemoryFormat.h>
#include <c10/core/Scalar.h>
#include <ATen/core/Reduction.h>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {

namespace mps {

TORCH_API at::Tensor median(const at::Tensor & self);
TORCH_API ::std::tuple<at::Tensor &,at::Tensor &> median_out(at::Tensor & values, at::Tensor & indices, const at::Tensor & self, int64_t dim, bool keepdim=false);
TORCH_API ::std::tuple<at::Tensor &,at::Tensor &> median_outf(const at::Tensor & self, int64_t dim, bool keepdim, at::Tensor & values, at::Tensor & indices);

} // namespace mps
} // namespace at
