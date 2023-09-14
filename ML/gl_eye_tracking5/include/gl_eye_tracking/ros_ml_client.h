#ifndef ROS_ML_CLIENT_H
#define ROS_ML_CLIENT_H


// #include "../../ros_ml_server/include/ros_ml_server/ros_ml_common.h"
// #include "../../ros_ml_server/include/ros_ml_server/ros_ml_network.h"
#include "core/game_engine.h"

#include <unordered_map>
#include <cassert>


class RosMLClient : public olc::GameEngine
{
public:
	RosMLClient();
 ~RosMLClient();


private:

public:
	bool OnUserCreate() override;
  bool OnUserUpdate(float fElapsedTime) override;

private:
	void Deserialize(const char* data, float vertices[], const int vertices_length);
};

#endif