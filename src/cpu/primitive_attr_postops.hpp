/*******************************************************************************
* Copyright 2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef CPU_PRIMITIVE_ATTR_POSTOPS_HPP
#define CPU_PRIMITIVE_ATTR_POSTOPS_HPP

#include "common/primitive.hpp"
#include "common/primitive_attr.hpp"

namespace dnnl {
namespace impl {
namespace cpu {

float compute_binary_scalar(alg_kind_t alg, float x, float y);
float compute_eltwise_scalar_fwd(
        const alg_kind_t alg, float s, float alpha, float beta);
float compute_eltwise_scalar_bwd(
        const alg_kind_t alg, float dd, float s, float alpha, float beta);

struct ref_eltwise_scalar_fwd_t {
    ref_eltwise_scalar_fwd_t(
            alg_kind_t alg, float alpha, float beta, float scale);
    ref_eltwise_scalar_fwd_t(const post_ops_t::entry_t::eltwise_t &eltwise);

    float compute_scalar(float s) const;

    const alg_kind_t alg_;
    const float alpha_;
    const float beta_;
    const float scale_;
};

struct ref_post_ops_t {
    struct args_t {
        args_t() : dst_val(0.f) {}

        float dst_val; // sum arg
    };

    ref_post_ops_t(const post_ops_t &po);

    virtual ~ref_post_ops_t() = default;

    status_t execute(float &res, const args_t &args = args_t()) const;

private:
    const post_ops_t &po_;
    std::vector<ref_eltwise_scalar_fwd_t> eltwise_po_;
};

} // namespace cpu
} // namespace impl
} // namespace dnnl

#endif