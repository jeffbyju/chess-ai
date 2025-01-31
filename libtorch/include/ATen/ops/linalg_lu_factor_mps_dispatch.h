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

TORCH_API ::std::tuple<at::Tensor,at::Tensor> linalg_lu_factor(const at::Tensor & A, bool pivot=true);
TORCH_API ::std::tuple<at::Tensor &,at::Tensor &> linalg_lu_factor_out(at::Tensor & LU, at::Tensor & pivots, const at::Tensor & A, bool pivot=true);
TORCH_API ::std::tuple<at::Tensor &,at::Tensor &> linalg_lu_factor_outf(const at::Tensor & A, bool pivot, at::Tensor & LU, at::Tensor & pivots);

} // namespace mps
} // namespace at
