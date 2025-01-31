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



#include <ATen/ops/affine_grid_generator_ops.h>

namespace at {


// aten::affine_grid_generator(Tensor theta, SymInt[] size, bool align_corners) -> Tensor
inline at::Tensor affine_grid_generator(const at::Tensor & theta, at::IntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator::call(theta, c10::fromIntArrayRefSlow(size), align_corners);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor affine_grid_generator(const at::Tensor & theta, at::IntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator::call(theta, c10::fromIntArrayRefSlow(size), align_corners);
  }
}

// aten::affine_grid_generator(Tensor theta, SymInt[] size, bool align_corners) -> Tensor
inline at::Tensor affine_grid_generator_symint(const at::Tensor & theta, c10::SymIntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator::call(theta, size, align_corners);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor affine_grid_generator(const at::Tensor & theta, c10::SymIntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator::call(theta, size, align_corners);
  }
}

// aten::affine_grid_generator.out(Tensor theta, SymInt[] size, bool align_corners, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & affine_grid_generator_out(at::Tensor & out, const at::Tensor & theta, at::IntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_out::call(theta, c10::fromIntArrayRefSlow(size), align_corners, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor & affine_grid_generator_out(at::Tensor & out, const at::Tensor & theta, at::IntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_out::call(theta, c10::fromIntArrayRefSlow(size), align_corners, out);
  }
}

// aten::affine_grid_generator.out(Tensor theta, SymInt[] size, bool align_corners, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & affine_grid_generator_outf(const at::Tensor & theta, at::IntArrayRef size, bool align_corners, at::Tensor & out) {
    return at::_ops::affine_grid_generator_out::call(theta, c10::fromIntArrayRefSlow(size), align_corners, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor & affine_grid_generator_outf(const at::Tensor & theta, at::IntArrayRef size, bool align_corners, at::Tensor & out) {
    return at::_ops::affine_grid_generator_out::call(theta, c10::fromIntArrayRefSlow(size), align_corners, out);
  }
}

// aten::affine_grid_generator.out(Tensor theta, SymInt[] size, bool align_corners, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & affine_grid_generator_symint_out(at::Tensor & out, const at::Tensor & theta, c10::SymIntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_out::call(theta, size, align_corners, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor & affine_grid_generator_out(at::Tensor & out, const at::Tensor & theta, c10::SymIntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_out::call(theta, size, align_corners, out);
  }
}

// aten::affine_grid_generator.out(Tensor theta, SymInt[] size, bool align_corners, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & affine_grid_generator_symint_outf(const at::Tensor & theta, c10::SymIntArrayRef size, bool align_corners, at::Tensor & out) {
    return at::_ops::affine_grid_generator_out::call(theta, size, align_corners, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor & affine_grid_generator_outf(const at::Tensor & theta, c10::SymIntArrayRef size, bool align_corners, at::Tensor & out) {
    return at::_ops::affine_grid_generator_out::call(theta, size, align_corners, out);
  }
}

}
