
#include "gl_eye_tracking/ros_ml_client.h"

RosMLClient::RosMLClient() : olc::GameEngine()
{
	// std::cout << "RosMLClient::RosMLClient()\n";
	ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::RosMLClient()");
	sAppName = "MMO Client";

	n_points = 307200;
	vertices_length = n_points * 6;
  vertices_size = vertices_length * sizeof(float);

  vertices = new Vertex[n_points];

  ParseCloudFromFile("data/res/cloud/depth_data.txt");
}

RosMLClient::~RosMLClient()
{
	// std::cout << "RosMLClient::~RosMLClient()\n";
	ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::~RosMLClient()");
	
}


bool RosMLClient::OnUserCreate()
{
	std::cout << "RosMLClient::OnUserCreate()\n";
	return true;
}

bool RosMLClient::OnUserUpdate(float fElapsedTime)
{
	// std::cout << "RosMLClient::OnUserUpdate()\n";
	// ML_LOG_TAG(Debug, APP_TAG, "RosMLClient::OnUserUpdate()");
	GameEngine::OnUserUpdate(fElapsedTime);
	return true;
}

void RosMLClient::Deserialize(const char* data, float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++;
  }
}

void RosMLClient::ParseCloudFromFile(const std::string cloud_file_path)
{
  int n_values_read_from_file  = 0;

  std::ifstream file_handler(cloud_file_path);
  std::string each_value_str;
  // std::string each_value_clean_str;
  float value_float;

  for(int i = 0; i < n_points; i++)
  {
    Vertex v;

    file_handler >> each_value_str;
    v.Position.v0 = std::stof(each_value_str);

    file_handler >> each_value_str;
    v.Position.v1 = std::stof(each_value_str);

    file_handler >> each_value_str;
    v.Position.v2 = std::stof(each_value_str);


    file_handler >> each_value_str;
    v.Color.v0 = std::stof(each_value_str);

    file_handler >> each_value_str;
    v.Color.v1 = std::stof(each_value_str);

    file_handler >> each_value_str;
    v.Color.v2 = std::stof(each_value_str);

    vertices[i] = v;
  }
}