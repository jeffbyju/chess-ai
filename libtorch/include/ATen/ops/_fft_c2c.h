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



#include <ATen/ops/_fft_c2c_ops.h>

namespace at {


// aten::_fft_c2c(Tensor self, SymInt[] dim, int normalization, bool forward) -> Tensor
inline at::Tensor _fft_c2c(const at::Tensor & self, at::IntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c::call(self, c10::fromIntArrayRefSlow(dim), normalization, forward);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor _fft_c2c(const at::Tensor & self, at::IntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c::call(self, c10::fromIntArrayRefSlow(dim), normalization, forward);
  }
}

// aten::_fft_c2c(Tensor self, SymInt[] dim, int normalization, bool forward) -> Tensor
inline at::Tensor _fft_c2c_symint(const at::Tensor & self, c10::SymIntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c::call(self, dim, normalization, forward);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor _fft_c2c(const at::Tensor & self, c10::SymIntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c::call(self, dim, normalization, forward);
  }
}

// aten::_fft_c2c.out(Tensor self, SymInt[] dim, int normalization, bool forward, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _fft_c2c_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c_out::call(self, c10::fromIntArrayRefSlow(dim), normalization, forward, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor & _fft_c2c_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c_out::call(self, c10::fromIntArrayRefSlow(dim), normalization, forward, out);
  }
}

// aten::_fft_c2c.out(Tensor self, SymInt[] dim, int normalization, bool forward, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _fft_c2c_outf(const at::Tensor & self, at::IntArrayRef dim, int64_t normalization, bool forward, at::Tensor & out) {
    return at::_ops::_fft_c2c_out::call(self, c10::fromIntArrayRefSlow(dim), normalization, forward, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor & _fft_c2c_outf(const at::Tensor & self, at::IntArrayRef dim, int64_t normalization, bool forward, at::Tensor & out) {
    return at::_ops::_fft_c2c_out::call(self, c10::fromIntArrayRefSlow(dim), normalization, forward, out);
  }
}

// aten::_fft_c2c.out(Tensor self, SymInt[] dim, int normalization, bool forward, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _fft_c2c_symint_out(at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c_out::call(self, dim, normalization, forward, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor & _fft_c2c_out(at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef dim, int64_t normalization, bool forward) {
    return at::_ops::_fft_c2c_out::call(self, dim, normalization, forward, out);
  }
}

// aten::_fft_c2c.out(Tensor self, SymInt[] dim, int normalization, bool forward, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _fft_c2c_symint_outf(const at::Tensor & self, c10::SymIntArrayRef dim, int64_t normalization, bool forward, at::Tensor & out) {
    return at::_ops::_fft_c2c_out::call(self, dim, normalization, forward, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor & _fft_c2c_outf(const at::Tensor & self, c10::SymIntArrayRef dim, int64_t normalization, bool forward, at::Tensor & out) {
    return at::_ops::_fft_c2c_out::call(self, dim, normalization, forward, out);
  }
}

}
