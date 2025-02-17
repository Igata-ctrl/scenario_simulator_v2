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

#ifndef OPENSCENARIO_INTERPRETER__SYNTAX__PROPERTIES_HPP_
#define OPENSCENARIO_INTERPRETER__SYNTAX__PROPERTIES_HPP_

#include <openscenario_interpreter/syntax/file.hpp>
#include <openscenario_interpreter/syntax/property.hpp>
#include <unordered_map>
#include <utility>
#include <vector>

namespace openscenario_interpreter
{
inline namespace syntax
{
/* ---- Properties -------------------------------------------------------------
 *
 *  Container for one or more properties. Properties encloses multiple property
 *  instances and/or multiple file references.
 *
 *  <xsd:complexType name="Properties">
 *    <xsd:sequence>
 *      <xsd:element name="Property" minOccurs="0" maxOccurs="unbounded" type="Property"/>
 *      <xsd:element name="File" type="File" minOccurs="0" maxOccurs="unbounded"/>
 *    </xsd:sequence>
 *  </xsd:complexType>
 *
 * -------------------------------------------------------------------------- */
struct Properties
{
  /* ---- properties -----------------------------------------------------------
   *
   *  A name-value pair. The semantic of the name/values are subject of a
   *  contract between the provider of a simulation environment and the author
   *  of a scenario.
   *
   * ------------------------------------------------------------------------ */
  std::unordered_map<Property::Name, Property> properties;

  /* ---- files ----------------------------------------------------------------
   *
   *  A list of arbitrary files attached to an object that owns the properties.
   *  The semantic and the file formats are subject of a contract between the
   *  provider of a simulation environment and the author of a scenario.
   *
   *  Note: currently ignored.
   *
   * ------------------------------------------------------------------------ */
  std::list<File> files;

  Properties() = default;

  template <typename Node, typename Scope>
  explicit Properties(const Node & node, Scope & outer_scope)
  {
    callWithElements(node, "Property", 0, unbounded, [&](auto && node) {
      return properties.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(readAttribute<Property::Name>("name", node, outer_scope)),
        std::forward_as_tuple(node, outer_scope));
    });

    callWithElements(node, "File", 0, unbounded, [&](auto && node) {
      return files.emplace_back(std::forward<decltype(node)>(node), outer_scope);
    });
  }

  template <typename... Ts>
  decltype(auto) operator[](Ts &&... xs)
  {
    return properties.operator[](std::forward<decltype(xs)>(xs)...);
  }
};
}  // namespace syntax
}  // namespace openscenario_interpreter

#endif  // OPENSCENARIO_INTERPRETER__SYNTAX__PROPERTIES_HPP_
