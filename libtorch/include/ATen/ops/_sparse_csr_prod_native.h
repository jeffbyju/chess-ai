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
TORCH_API at::Tensor & _sparse_csr_prod_dim_dtype_out(const at::Tensor & self, at::IntArrayRef dim, bool keepdim, ::std::optional<at::ScalarType> dtype, at::Tensor & out);
TORCH_API at::Tensor _sparse_csr_prod_cpu(const at::Tensor & self, at::IntArrayRef dim, bool keepdim=false, ::std::optional<at::ScalarType> dtype=::std::nullopt);
TORCH_API at::Tensor _sparse_csr_prod_cuda(const at::Tensor & self, at::IntArrayRef dim, bool keepdim=false, ::std::optional<at::ScalarType> dtype=::std::nullopt);
} // namespace native
} // namespace at
