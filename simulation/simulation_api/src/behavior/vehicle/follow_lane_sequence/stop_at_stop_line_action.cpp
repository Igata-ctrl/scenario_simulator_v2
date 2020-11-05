// Copyright 2015-2020 Autoware Foundation. All rights reserved.
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

#include <simulation_api/behavior/vehicle/behavior_tree.hpp>
#include <simulation_api/behavior/vehicle/follow_lane_sequence/stop_at_stop_line_action.hpp>

#include <string>
#include <vector>
#include <utility>

namespace entity_behavior
{
namespace vehicle
{
namespace follow_lane_sequence
{
StopAtStopLineAction::StopAtStopLineAction(
  const std::string & name,
  const BT::NodeConfiguration & config)
: entity_behavior::VehicleActionNode(name, config)
{
  stopped_ = false;
}

boost::optional<double> StopAtStopLineAction::calculateTargetSpeed(
  const std::vector<std::int64_t> & following_lanelets, double current_velocity)
{
  if (entity_status.coordinate == simulation_api::entity::CoordinateFrameTypes::WORLD) {
    return boost::none;
  }
  auto distance_to_stop_target = hdmap_utils->getDistanceToStopLine(following_lanelets,
      entity_status.lanelet_id,
      entity_status.s);
  if (!distance_to_stop_target) {
    return boost::none;
  }
  double rest_distance = distance_to_stop_target.get() -
    (vehicle_parameters->bounding_box.dimensions.length);
  if (rest_distance < calculateStopDistance()) {
    if (rest_distance > 0) {
      return std::sqrt(2 * 5 * rest_distance);
    } else {
      return 0;
    }
  }
  return current_velocity;
}

BT::NodeStatus StopAtStopLineAction::tick()
{
  getBlackBoardValues();
  if (request != "none" && request != "follow_lane") {
    stopped_ = false;
    return BT::NodeStatus::FAILURE;
  }
  if (entity_status.coordinate == simulation_api::entity::CoordinateFrameTypes::WORLD) {
    stopped_ = false;
    return BT::NodeStatus::FAILURE;
  }
  if (entity_status.coordinate == simulation_api::entity::CoordinateFrameTypes::LANE) {
    auto following_lanelets = hdmap_utils->getFollowingLanelets(entity_status.lanelet_id, 50);
    if (getRightOfWayEntities(following_lanelets).size() != 0) {
      return BT::NodeStatus::FAILURE;
    }
    auto dist_to_stopline = getDistanceToStopLine(following_lanelets);
    if (std::fabs(entity_status.twist.linear.x) < 0.001) {
      if (dist_to_stopline) {
        if (dist_to_stopline.get() <= vehicle_parameters->bounding_box.dimensions.length + 5) {
          stopped_ = true;
        }
      }
    }
    if (stopped_) {
      if (!target_speed) {
        target_speed = hdmap_utils->getSpeedLimit(following_lanelets);
      }
      if (!dist_to_stopline) {
        stopped_ = false;
        setOutput("updated_status", calculateEntityStatusUpdated(target_speed.get()));
        return BT::NodeStatus::SUCCESS;
      }
      setOutput("updated_status", calculateEntityStatusUpdated(target_speed.get()));
      return BT::NodeStatus::RUNNING;
    }
    auto target_linear_speed =
      calculateTargetSpeed(following_lanelets, entity_status.twist.linear.x);
    if (!target_linear_speed) {
      stopped_ = false;
      return BT::NodeStatus::FAILURE;
    }
    if (target_speed) {
      if (target_speed.get() > target_linear_speed.get()) {
        target_speed = target_linear_speed.get();
      }
    } else {
      target_speed = target_linear_speed.get();
    }
    setOutput("updated_status", calculateEntityStatusUpdated(target_speed.get()));
    stopped_ = false;
    return BT::NodeStatus::RUNNING;
  }
  stopped_ = false;
  return BT::NodeStatus::FAILURE;
}
}  // namespace follow_lane_sequence
}  // namespace vehicle
}  // namespace entity_behavior
