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

#ifndef OPENSCENARIO_INTERPRETER__SYNTAX__DOUBLE_HPP_
#define OPENSCENARIO_INTERPRETER__SYNTAX__DOUBLE_HPP_

#include <boost/lexical_cast.hpp>
#include <openscenario_interpreter/error.hpp>
#include <std_msgs/msg/float64.hpp>

#include <limits>
#include <string>

namespace openscenario_interpreter
{
inline namespace syntax
{
struct Double
  : public std_msgs::msg::Float64
{
  using value_type = decltype(std_msgs::msg::Float64::data);

  explicit Double(value_type value = {})
  {
    data = value;
  }

  explicit Double(const std::string & s) try
  {
    data = boost::lexical_cast<value_type>(s);
  } catch (const boost::bad_lexical_cast &) {
    std::stringstream ss {};
    ss << "can't treat value \"" << s << "\" as type Double";
    throw SyntaxError(ss.str());
  }

  constexpr operator value_type() const noexcept
  {
    return data;
  }

  static auto infinity() noexcept
  {
    return static_cast<Double>(std::numeric_limits<value_type>::infinity());
  }

  auto & operator+=(const double & rhs)
  {
    data += rhs;
    return *this;
  }

  auto & operator*=(const double & rhs)
  {
    data *= rhs;
    return *this;
  }
};

std::ostream & operator<<(std::ostream &, const Double &);
std::istream & operator>>(std::istream &, Double &);
}
}  // namespace openscenario_interpreter

#endif  // OPENSCENARIO_INTERPRETER__SYNTAX__DOUBLE_HPP_
