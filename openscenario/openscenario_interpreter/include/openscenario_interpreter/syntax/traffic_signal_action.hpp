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

#ifndef OPENSCENARIO_INTERPRETER__SYNTAX__TRAFFIC_SIGNAL_ACTION_HPP_
#define OPENSCENARIO_INTERPRETER__SYNTAX__TRAFFIC_SIGNAL_ACTION_HPP_

#include <openscenario_interpreter/reader/element.hpp>
#include <openscenario_interpreter/syntax/traffic_signal_state_action.hpp>

#include <utility>

namespace openscenario_interpreter
{
inline namespace syntax
{
/* ==== TrafficSignalAction ==================================================
 *
 * <xsd:complexType name="TrafficSignalAction">
 *   <xsd:choice>
 *     <xsd:element name="TrafficSignalControllerAction" type="TrafficSignalControllerAction"/>
 *     <xsd:element name="TrafficSignalStateAction" type="TrafficSignalStateAction"/>
 *   </xsd:choice>
 * </xsd:complexType>
 *
 * ======================================================================== */
struct TrafficSignalAction
  : public Element
{
  template<typename Node, typename ... Ts>
  explicit TrafficSignalAction(const Node & node, Ts && ...)
  : Element(
      choice(
        node,
        std::make_pair("TrafficSignalControllerAction", [&](auto &&) {
          return unspecified;
        }),
        std::make_pair("TrafficSignalStateAction", UNSUPPORTED())))
  {}
};
}  // inline namespace syntax
}  // namespace openscenario_interpreter

#endif  // OPENSCENARIO_INTERPRETER__SYNTAX__TRAFFIC_SIGNAL_ACTION_HPP_
