// #include "core/ml_utilities.h"
// #include "core/ml_graphics_context.h"

#include "gl_eye_tracking/ros_ml_client.h"



int main()
{
	RosMLClient ros_ml_client;
	if (ros_ml_client.Construct())
		ros_ml_client.Start();
	return 0;
}