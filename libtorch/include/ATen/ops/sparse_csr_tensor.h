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



#include <ATen/ops/sparse_csr_tensor_ops.h>

namespace at {


// aten::sparse_csr_tensor.crow_col_value_size(Tensor crow_indices, Tensor col_indices, Tensor values, int[] size, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=False) -> Tensor
inline at::Tensor sparse_csr_tensor(const at::Tensor & crow_indices, const at::Tensor & col_indices, const at::Tensor & values, at::IntArrayRef size, at::TensorOptions options) {
    return at::_ops::sparse_csr_tensor_crow_col_value_size::call(crow_indices, col_indices, values, size, c10::optTypeMetaToScalarType(options.dtype_opt()), options.layout_opt(), options.device_opt(), options.pinned_memory_opt());
}
// aten::sparse_csr_tensor.crow_col_value_size(Tensor crow_indices, Tensor col_indices, Tensor values, int[] size, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=False) -> Tensor
inline at::Tensor sparse_csr_tensor(const at::Tensor & crow_indices, const at::Tensor & col_indices, const at::Tensor & values, at::IntArrayRef size, ::std::optional<at::ScalarType> dtype, ::std::optional<at::Layout> layout, ::std::optional<at::Device> device, ::std::optional<bool> pin_memory) {
    return at::_ops::sparse_csr_tensor_crow_col_value_size::call(crow_indices, col_indices, values, size, dtype, layout, device, pin_memory);
}

// aten::sparse_csr_tensor.crow_col_value(Tensor crow_indices, Tensor col_indices, Tensor values, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=False) -> Tensor
inline at::Tensor sparse_csr_tensor(const at::Tensor & crow_indices, const at::Tensor & col_indices, const at::Tensor & values, at::TensorOptions options) {
    return at::_ops::sparse_csr_tensor_crow_col_value::call(crow_indices, col_indices, values, c10::optTypeMetaToScalarType(options.dtype_opt()), options.layout_opt(), options.device_opt(), options.pinned_memory_opt());
}
// aten::sparse_csr_tensor.crow_col_value(Tensor crow_indices, Tensor col_indices, Tensor values, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=False) -> Tensor
inline at::Tensor sparse_csr_tensor(const at::Tensor & crow_indices, const at::Tensor & col_indices, const at::Tensor & values, ::std::optional<at::ScalarType> dtype, ::std::optional<at::Layout> layout, ::std::optional<at::Device> device, ::std::optional<bool> pin_memory) {
    return at::_ops::sparse_csr_tensor_crow_col_value::call(crow_indices, col_indices, values, dtype, layout, device, pin_memory);
}

}
