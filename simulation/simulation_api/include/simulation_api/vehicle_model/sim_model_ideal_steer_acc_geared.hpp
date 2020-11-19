// Copyright 2020 The Autoware Foundation.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SIMULATION_API__VEHICLE_MODEL__SIM_MODEL_IDEAL_STEER_ACC_GEARED_HPP_
#define SIMULATION_API__VEHICLE_MODEL__SIM_MODEL_IDEAL_STEER_ACC_GEARED_HPP_

#include "simple_planning_simulator/vehicle_model/sim_model_interface.hpp"

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/LU>
#include <iostream>

/**
 * @class wf_simulator ideal acceleration and steering model
 * @brief calculate ideal steering dynamics
 */
class SimModelIdealSteerAccGeard : public SimModelInterface
{
public:
  /**
   * @brief constructor
   * @param [in] wheelbase vehicle wheelbase length [m]
   */
  explicit SimModelIdealSteerAccGeard(double wheelbase);

  /**
   * @brief destructor
   */
  ~SimModelIdealSteerAccGeard() = default;

private:
  enum IDX
  {
    X = 0,
    Y,
    YAW,
    VX
  };
  enum IDX_U
  {
    AX_DES = 0,
    STEER_DES,
    GEAR_DES,
  };

  const double wheelbase_;  //!< @brief vehicle wheelbase length
  double current_acc_;  //!< @brief current_acc with gear consideration

  /**
   * @brief get vehicle position x
   */
  double getX() override;

  /**
   * @brief get vehicle position y
   */
  double getY() override;

  /**
   * @brief get vehicle angle yaw
   */
  double getYaw() override;

  /**
   * @brief get vehicle longitudinal velocity
   */
  double getVx() override;

  /**
   * @brief get vehicle lateral velocity
   */
  double getVy() override;

  /**
   * @brief get vehicle longiudinal acceleration
   */
  double getAx() override;

  /**
   * @brief get vehicle angular-velocity wz
   */
  double getWz() override;

  /**
   * @brief get vehicle steering angle
   */
  double getSteer() override;

  /**
   * @brief update vehicle states
   * @param [in] dt delta time [s]
   */
  void update(const double & dt) override;

  /**
   * @brief calculate derivative of states with ideal steering model
   * @param [in] state current model state
   * @param [in] input input vector to model
   */
  Eigen::VectorXd calcModel(const Eigen::VectorXd & state, const Eigen::VectorXd & input) override;
};

#endif  // SIMULATION_API__VEHICLE_MODEL__SIM_MODEL_IDEAL_STEER_ACC_GEARED_HPP_
