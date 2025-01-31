#pragma once

// @generated by torchgen/gen.py from Operator.h

#include <tuple>
#include <vector>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {
namespace _ops {


struct TORCH_API lstm_mps_backward {
  using schema = ::std::tuple<at::Tensor,::std::vector<at::Tensor>,::std::vector<at::Tensor>> (const ::std::optional<at::Tensor> &, const ::std::optional<at::Tensor> &, const ::std::optional<at::Tensor> &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, at::TensorList, at::TensorList, bool, int64_t, double, bool, bool, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::lstm_mps_backward")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "lstm_mps_backward(Tensor? grad_y, Tensor? grad_hy, Tensor? grad_cy, Tensor z_state, Tensor cell_state_fwd, Tensor input, Tensor layersOutputs, Tensor[] hx, Tensor[] params, bool has_biases, int num_layers, float dropout, bool train, bool bidirectional, bool batch_first) -> (Tensor, Tensor[], Tensor[])")
  static ::std::tuple<at::Tensor,::std::vector<at::Tensor>,::std::vector<at::Tensor>> call(const ::std::optional<at::Tensor> & grad_y, const ::std::optional<at::Tensor> & grad_hy, const ::std::optional<at::Tensor> & grad_cy, const at::Tensor & z_state, const at::Tensor & cell_state_fwd, const at::Tensor & input, const at::Tensor & layersOutputs, at::TensorList hx, at::TensorList params, bool has_biases, int64_t num_layers, double dropout, bool train, bool bidirectional, bool batch_first);
  static ::std::tuple<at::Tensor,::std::vector<at::Tensor>,::std::vector<at::Tensor>> redispatch(c10::DispatchKeySet dispatchKeySet, const ::std::optional<at::Tensor> & grad_y, const ::std::optional<at::Tensor> & grad_hy, const ::std::optional<at::Tensor> & grad_cy, const at::Tensor & z_state, const at::Tensor & cell_state_fwd, const at::Tensor & input, const at::Tensor & layersOutputs, at::TensorList hx, at::TensorList params, bool has_biases, int64_t num_layers, double dropout, bool train, bool bidirectional, bool batch_first);
};

struct TORCH_API lstm_mps_backward_out {
  using schema = void (const ::std::optional<at::Tensor> &, const ::std::optional<at::Tensor> &, const ::std::optional<at::Tensor> &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, at::TensorList, at::TensorList, bool, int64_t, double, bool, bool, bool, at::Tensor &, at::TensorList, at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::lstm_mps_backward")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "lstm_mps_backward.out(Tensor? grad_y, Tensor? grad_hy, Tensor? grad_cy, Tensor z_state, Tensor cell_state_fwd, Tensor input, Tensor layersOutputs, Tensor[] hx, Tensor[] params, bool has_biases, int num_layers, float dropout, bool train, bool bidirectional, bool batch_first, *, Tensor(a!) out0, Tensor(b!)[] out1, Tensor(c!)[] out2) -> ()")
  static void call(const ::std::optional<at::Tensor> & grad_y, const ::std::optional<at::Tensor> & grad_hy, const ::std::optional<at::Tensor> & grad_cy, const at::Tensor & z_state, const at::Tensor & cell_state_fwd, const at::Tensor & input, const at::Tensor & layersOutputs, at::TensorList hx, at::TensorList params, bool has_biases, int64_t num_layers, double dropout, bool train, bool bidirectional, bool batch_first, at::Tensor & out0, at::TensorList out1, at::TensorList out2);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, const ::std::optional<at::Tensor> & grad_y, const ::std::optional<at::Tensor> & grad_hy, const ::std::optional<at::Tensor> & grad_cy, const at::Tensor & z_state, const at::Tensor & cell_state_fwd, const at::Tensor & input, const at::Tensor & layersOutputs, at::TensorList hx, at::TensorList params, bool has_biases, int64_t num_layers, double dropout, bool train, bool bidirectional, bool batch_first, at::Tensor & out0, at::TensorList out1, at::TensorList out2);
};

}} // namespace at::_ops
