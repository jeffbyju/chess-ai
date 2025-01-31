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



#include <ATen/ops/glu_jvp_ops.h>

namespace at {


// aten::glu_jvp(Tensor glu, Tensor x, Tensor dx, int dim) -> Tensor
inline at::Tensor glu_jvp(const at::Tensor & glu, const at::Tensor & x, const at::Tensor & dx, int64_t dim) {
    return at::_ops::glu_jvp::call(glu, x, dx, dim);
}

// aten::glu_jvp.out(Tensor glu, Tensor x, Tensor dx, int dim, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & glu_jvp_out(at::Tensor & out, const at::Tensor & glu, const at::Tensor & x, const at::Tensor & dx, int64_t dim) {
    return at::_ops::glu_jvp_out::call(glu, x, dx, dim, out);
}
// aten::glu_jvp.out(Tensor glu, Tensor x, Tensor dx, int dim, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & glu_jvp_outf(const at::Tensor & glu, const at::Tensor & x, const at::Tensor & dx, int64_t dim, at::Tensor & out) {
    return at::_ops::glu_jvp_out::call(glu, x, dx, dim, out);
}

}
