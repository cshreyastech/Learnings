#include<ml_logging.h>

int main(int argc, char **argv) {
	ML_LOG(Info, "You have entered %d arguments:", argc);

	for (int i = 0; i < argc; ++i)
	  ML_LOG(Info, "%s", argv[i]);
	return 0;
}