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

#ifndef OPENSCENARIO_INTERPRETER__SYNTAX__OVERRIDE_CONTROLLER_VALUE_ACTION_HPP_
#define OPENSCENARIO_INTERPRETER__SYNTAX__OVERRIDE_CONTROLLER_VALUE_ACTION_HPP_

namespace openscenario_interpreter
{
inline namespace syntax
{
/* ---- OverrideControllerValueAction ------------------------------------------
 *
 *  Overrides entity controller values. Mostly suited for motor vehicles.
 *
 *  <xsd:complexType name="OverrideControllerValueAction">
 *    <xsd:all>
 *      <xsd:element name="Throttle" type="OverrideThrottleAction"/>
 *      <xsd:element name="Brake" type="OverrideBrakeAction"/>
 *      <xsd:element name="Clutch" type="OverrideClutchAction"/>
 *      <xsd:element name="ParkingBrake" type="OverrideParkingBrakeAction"/>
 *      <xsd:element name="SteeringWheel" type="OverrideSteeringWheelAction"/>
 *      <xsd:element name="Gear" type="OverrideGearAction"/>
 *    </xsd:all>
 *  </xsd:complexType>
 *
 * -------------------------------------------------------------------------- */
struct OverrideControllerValueAction
{
  /* ---- OverrideThrottleAction -----------------------------------------------
   *
   *  New value for throttle pedal position or unset value.
   *
   * ------------------------------------------------------------------------ */
  // TODO(yamacir-kit): const OverrideThrottleAction overrideThrottle;

  /* ---- OverrideBrakeAction --------------------------------------------------
   *
   *  New value for brake position or unset value.
   *
   * ------------------------------------------------------------------------ */
  // TODO(yamacir-kit): const OverrideBrakeAction overrideBrake;

  /* ---- OverrideClutchAction -------------------------------------------------
   *
   *  New value for clutch position or unset value.
   *
   * ------------------------------------------------------------------------ */
  // TODO(yamacir-kit): const OverrideClutchAction overrideClutch;

  /* ---- OverrideParkingBrakeAction -------------------------------------------
   *
   *  New value for parking brake position or unset value.
   *
   * ------------------------------------------------------------------------ */
  // TODO(yamacir-kit): const OverrideParkingBrakeAction overrideParkingBrake;

  /* ---- OverrideSteeringWheelAction ------------------------------------------
   *
   *  New value for steering wheel position or unset value.
   *
   * ------------------------------------------------------------------------ */
  // TODO(yamacir-kit): const OverrideSteeringWheelAction overrideSteeringWheel;

  /* ---- OverrideGearAction ---------------------------------------------------
   *
   *  New value for gear position or unset value.
   *
   * ------------------------------------------------------------------------ */
  // TODO(yamacir-kit): const OverrideGearAction overrideGear;

  template <typename Node, typename Scope>
  explicit OverrideControllerValueAction(const Node &, Scope &)
  {
  }
};
}  // namespace syntax
}  // namespace openscenario_interpreter

#endif  // OPENSCENARIO_INTERPRETER__SYNTAX__OVERRIDE_CONTROLLER_VALUE_ACTION_HPP_
