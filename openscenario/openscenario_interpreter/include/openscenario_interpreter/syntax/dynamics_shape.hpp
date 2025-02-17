// Copyright 2015-2020 Tier IV, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef OPENSCENARIO_INTERPRETER__SYNTAX__DYNAMICS_SHAPE_HPP_
#define OPENSCENARIO_INTERPRETER__SYNTAX__DYNAMICS_SHAPE_HPP_

#include <iostream>

namespace openscenario_interpreter
{
inline namespace syntax
{
/* ---- DynamicsShape ----------------------------------------------------------
 *
 *  <xsd:simpleType name="DynamicsShape">
 *    <xsd:union>
 *      <xsd:simpleType>
 *        <xsd:restriction base="xsd:string">
 *          <xsd:enumeration value="linear"/>
 *          <xsd:enumeration value="cubic"/>
 *          <xsd:enumeration value="sinusoidal"/>
 *          <xsd:enumeration value="step"/>
 *        </xsd:restriction>
 *      </xsd:simpleType>
 *      <xsd:simpleType>
 *        <xsd:restriction base="parameter"/>
 *      </xsd:simpleType>
 *    </xsd:union>
 *  </xsd:simpleType>
 *
 * -------------------------------------------------------------------------- */
struct DynamicsShape
{
  enum value_type {

    /* ---- NOTE ---------------------------------------------------------------
     *
     *  Value changes in a linear function:
     *
     *    f(x) = f_0 + rate * x.
     *
     * ---------------------------------------------------------------------- */
    linear,

    /* ---- NOTE ---------------------------------------------------------------
     *
     *  Cubical transition
     *
     *    f(x) = A * x^3 + B * x^2 + C * x + D
     *
     *  with the constraint that the gradient must be zero at start and end.
     *
     * ---------------------------------------------------------------------- */
    cubic,

    /* ---- NOTE ---------------------------------------------------------------
     *
     *  Sinusoidal transition
     *
     *    f(x) = A * sin(x) + B
     *
     *  with the constraint that the gradient must be zero at start and end.
     *
     * ---------------------------------------------------------------------- */
    sinusoidal,

    /* ---- NOTE ---------------------------------------------------------------
     *
     *  Step transition.
     *
     * ---------------------------------------------------------------------- */
    step,
  } value;

  explicit DynamicsShape() = default;

  constexpr operator value_type() const noexcept { return value; }
};

static_assert(std::is_standard_layout<DynamicsShape>::value, "");

static_assert(std::is_trivial<DynamicsShape>::value, "");

std::istream & operator>>(std::istream &, DynamicsShape &);

std::ostream & operator<<(std::ostream &, const DynamicsShape &);
}  // namespace syntax
}  // namespace openscenario_interpreter

#endif  // OPENSCENARIO_INTERPRETER__SYNTAX__DYNAMICS_SHAPE_HPP_
