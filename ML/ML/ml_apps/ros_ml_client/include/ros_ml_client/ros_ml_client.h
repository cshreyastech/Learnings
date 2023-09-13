#ifndef ROS_ML_CLIENT_H
#define ROS_ML_CLIENT_H


#include "common/ros_ml_common.h"
#include "common/ros_ml_network.h"
#include "ros_ml_client/game_engine.h"

#include <unordered_map>
#include <cassert>

#include <ml_logging.h>
const char APP_TAG[] = "MAIN";


class RosMLClient : public olc::GameEngine, olc::net::client_interface<GameMsg>
{
public:
	RosMLClient();
 ~RosMLClient();

private:
	std::unordered_map<uint32_t, sPlayerDescription> mapObjects_;
	uint32_t nPlayerID_ = 0;
	bool bWaitingForConnection_{true};
	// float* vertices;
	// Should be the last declared variable as it as flexible array member
	sPlayerDescription descPlayer_;

public:
	bool OnUserCreate() override;
  bool OnUserUpdate(float fElapsedTime);

private:
	void Deserialize(const char* data, float vertices[], const int vertices_length);
};

#endif