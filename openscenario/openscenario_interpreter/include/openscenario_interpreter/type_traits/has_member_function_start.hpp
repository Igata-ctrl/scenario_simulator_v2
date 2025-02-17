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

#ifndef OPENSCENARIO_INTERPRETER__TYPE_TRAITS__HAS_MEMBER_FUNCTION_START_HPP_
#define OPENSCENARIO_INTERPRETER__TYPE_TRAITS__HAS_MEMBER_FUNCTION_START_HPP_

#include <openscenario_interpreter/type_traits/void_t.hpp>

namespace openscenario_interpreter
{
inline namespace type_traits
{
template <typename T, typename = void>
struct HasMemberFunctionStart : public std::false_type
{
};

template <typename T>
struct HasMemberFunctionStart<T, void_t<decltype(std::declval<T>().start())>>
: public std::true_type
{
};
}  // namespace type_traits
}  // namespace openscenario_interpreter

#endif  // OPENSCENARIO_INTERPRETER__TYPE_TRAITS__HAS_MEMBER_FUNCTION_START_HPP_
