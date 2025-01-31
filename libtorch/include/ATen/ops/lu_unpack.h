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



#include <ATen/ops/lu_unpack_ops.h>

namespace at {


// aten::lu_unpack(Tensor LU_data, Tensor LU_pivots, bool unpack_data=True, bool unpack_pivots=True) -> (Tensor P, Tensor L, Tensor U)
inline ::std::tuple<at::Tensor,at::Tensor,at::Tensor> lu_unpack(const at::Tensor & LU_data, const at::Tensor & LU_pivots, bool unpack_data=true, bool unpack_pivots=true) {
    return at::_ops::lu_unpack::call(LU_data, LU_pivots, unpack_data, unpack_pivots);
}

// aten::lu_unpack.out(Tensor LU_data, Tensor LU_pivots, bool unpack_data=True, bool unpack_pivots=True, *, Tensor(a!) P, Tensor(b!) L, Tensor(c!) U) -> (Tensor(a!) P, Tensor(b!) L, Tensor(c!) U)
inline ::std::tuple<at::Tensor &,at::Tensor &,at::Tensor &> lu_unpack_out(at::Tensor & P, at::Tensor & L, at::Tensor & U, const at::Tensor & LU_data, const at::Tensor & LU_pivots, bool unpack_data=true, bool unpack_pivots=true) {
    return at::_ops::lu_unpack_out::call(LU_data, LU_pivots, unpack_data, unpack_pivots, P, L, U);
}
// aten::lu_unpack.out(Tensor LU_data, Tensor LU_pivots, bool unpack_data=True, bool unpack_pivots=True, *, Tensor(a!) P, Tensor(b!) L, Tensor(c!) U) -> (Tensor(a!) P, Tensor(b!) L, Tensor(c!) U)
inline ::std::tuple<at::Tensor &,at::Tensor &,at::Tensor &> lu_unpack_outf(const at::Tensor & LU_data, const at::Tensor & LU_pivots, bool unpack_data, bool unpack_pivots, at::Tensor & P, at::Tensor & L, at::Tensor & U) {
    return at::_ops::lu_unpack_out::call(LU_data, LU_pivots, unpack_data, unpack_pivots, P, L, U);
}

}
