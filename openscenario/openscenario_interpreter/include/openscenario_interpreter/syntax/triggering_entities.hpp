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

#ifndef OPENSCENARIO_INTERPRETER__SYNTAX__TRIGGERING_ENTITIES_HPP_
#define OPENSCENARIO_INTERPRETER__SYNTAX__TRIGGERING_ENTITIES_HPP_

#include <openscenario_interpreter/reader/element.hpp>
#include <openscenario_interpreter/syntax/entity_ref.hpp>
#include <openscenario_interpreter/syntax/triggering_entities_rule.hpp>
#include <openscenario_interpreter/utility/print.hpp>
#include <utility>
#include <vector>

namespace openscenario_interpreter
{
inline namespace syntax
{
/* ---- TriggeringEntities -----------------------------------------------------
 *
 *  <xsd:complexType name="TriggeringEntities">
 *    <xsd:sequence>
 *      <xsd:element name="EntityRef" maxOccurs="unbounded" type="EntityRef"/>
 *    </xsd:sequence>
 *    <xsd:attribute name="triggeringEntitiesRule" type="TriggeringEntitiesRule" use="required"/>
 *  </xsd:complexType>
 *
 * -------------------------------------------------------------------------- */
struct TriggeringEntities
{
  const TriggeringEntitiesRule triggering_entities_rule;

  const std::list<EntityRef> entity_refs;

  template <typename Node, typename Scope>
  explicit TriggeringEntities(const Node & node, Scope & scope)
  : triggering_entities_rule(
      readAttribute<TriggeringEntitiesRule>("triggeringEntitiesRule", node, scope)),
    entity_refs(readElements<EntityRef, 1>("EntityRef", node, scope))
  {
  }

  template <typename Predicate>
  constexpr decltype(auto) apply(Predicate && predicate) const
  {
    return triggering_entities_rule.apply(
      std::begin(entity_refs), std::end(entity_refs), std::forward<decltype(predicate)>(predicate));
  }

  template <typename... Ts>
  [[deprecated]] constexpr decltype(auto) operator()(Ts &&... xs) const
  {
    return apply(std::forward<decltype(xs)>(xs)...);
  }

  auto description() const
  {
    std::stringstream description;

    description << triggering_entities_rule.description() << " ";

    print_to(description, entity_refs);

    return description.str();
  }
};
}  // namespace syntax
}  // namespace openscenario_interpreter

#endif  // OPENSCENARIO_INTERPRETER__SYNTAX__TRIGGERING_ENTITIES_HPP_
