#ifndef ROS_ML_CLIENT_H
#define ROS_ML_CLIENT_H


#include "core/game_engine.h"

#include <unordered_map>
#include <cassert>
#include <fstream>

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
	void ParseCloudFromFile(const std::string file_path, float vertices[], const int n_points);
};

#endif