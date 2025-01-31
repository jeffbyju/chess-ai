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



#include <ATen/ops/resize_ops.h>

namespace at {


namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  const at::Tensor & resize_(const at::Tensor & self, at::IntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize_::call(self, c10::fromIntArrayRefSlow(size), memory_format);
  }
}

namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  const at::Tensor & resize_(const at::Tensor & self, c10::SymIntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize_::call(self, size, memory_format);
  }
}

// aten::resize.out(Tensor self, SymInt[] size, *, MemoryFormat? memory_format=None, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & resize_out(const at::Tensor & out, const at::Tensor & self, at::IntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize_out::call(self, c10::fromIntArrayRefSlow(size), memory_format, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  const at::Tensor & resize_out(const at::Tensor & out, const at::Tensor & self, at::IntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize_out::call(self, c10::fromIntArrayRefSlow(size), memory_format, out);
  }
}

// aten::resize.out(Tensor self, SymInt[] size, *, MemoryFormat? memory_format=None, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & resize_outf(const at::Tensor & self, at::IntArrayRef size, ::std::optional<at::MemoryFormat> memory_format, const at::Tensor & out) {
    return at::_ops::resize_out::call(self, c10::fromIntArrayRefSlow(size), memory_format, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  const at::Tensor & resize_outf(const at::Tensor & self, at::IntArrayRef size, ::std::optional<at::MemoryFormat> memory_format, const at::Tensor & out) {
    return at::_ops::resize_out::call(self, c10::fromIntArrayRefSlow(size), memory_format, out);
  }
}

// aten::resize.out(Tensor self, SymInt[] size, *, MemoryFormat? memory_format=None, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & resize_symint_out(const at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize_out::call(self, size, memory_format, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  const at::Tensor & resize_out(const at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize_out::call(self, size, memory_format, out);
  }
}

// aten::resize.out(Tensor self, SymInt[] size, *, MemoryFormat? memory_format=None, Tensor(a!) out) -> Tensor(a!)
inline const at::Tensor & resize_symint_outf(const at::Tensor & self, c10::SymIntArrayRef size, ::std::optional<at::MemoryFormat> memory_format, const at::Tensor & out) {
    return at::_ops::resize_out::call(self, size, memory_format, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  const at::Tensor & resize_outf(const at::Tensor & self, c10::SymIntArrayRef size, ::std::optional<at::MemoryFormat> memory_format, const at::Tensor & out) {
    return at::_ops::resize_out::call(self, size, memory_format, out);
  }
}

// aten::resize(Tensor self, SymInt[] size, *, MemoryFormat? memory_format=None) -> Tensor
inline at::Tensor resize(const at::Tensor & self, at::IntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize::call(self, c10::fromIntArrayRefSlow(size), memory_format);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor resize(const at::Tensor & self, at::IntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize::call(self, c10::fromIntArrayRefSlow(size), memory_format);
  }
}

// aten::resize(Tensor self, SymInt[] size, *, MemoryFormat? memory_format=None) -> Tensor
inline at::Tensor resize_symint(const at::Tensor & self, c10::SymIntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize::call(self, size, memory_format);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor resize(const at::Tensor & self, c10::SymIntArrayRef size, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt) {
    return at::_ops::resize::call(self, size, memory_format);
  }
}

}
