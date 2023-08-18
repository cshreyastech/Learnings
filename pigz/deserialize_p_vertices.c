#include <stdio.h>
#include <unistd.h>     // unlink(), _exit(), read(), write(), close(),
                        // lseek(), isatty(), chown(), fsync()
#include <fcntl.h>      // open(), O_CREAT, O_EXCL, O_RDONLY, O_TRUNC,
                        // O_WRONLY, fcntl(), F_FULLFSYNC
#include <dirent.h>     // opendir(), readdir(), closedir(), DIR,
                        // struct dirent
#include <string.h>

void deserialize(unsigned char data[], float vertices[], const int vertices_length);
int main()
{

	const int n_points = 2;
	const int vertices_length = n_points * 6;
	// const size_t vertices_size = vertices_length * sizeof(float);

	float vertices[2 * 6];

	// int len = 1024 * 100;
	int len = 1024;
	unsigned char buf[len];
	
	char *inf = "/home/shreyas/Downloads/cloud_data/induvidual_rows/tbd/test/depth_data_test_p_vertices.txt";
	// open input file
	int desc = open(inf, O_RDONLY, 0);
	if (desc < 0)
	{
		printf("read error on %s", inf);
		return 0;
	}
		
	unsigned char p_vertices[135];
	int ret = 0;

	int start_index = 0;
	while (ret > -1) {
		ret = read(desc, buf, len);

		printf("ret: %d\n", ret);

		if (ret < 0)
		{
			printf("read error on %s", inf);
			return 0;
		}

		if (ret == 0)
			break;

		memmove((p_vertices + start_index), buf, ret);
		start_index += ret;
	}
	// Closing the file
	close(desc);

	deserialize(p_vertices, vertices, vertices_length);

	for(int i = 0; i < vertices_length; i++)
		printf("vertices[%d]: %f\n", i, vertices[i]);
	
  return 0;
}


void deserialize(unsigned char data[], float vertices[], const int vertices_length)
{
  float *q = (float*)data;
  for(int i = 0; i < vertices_length; i++)
  {
    vertices[i] = *q; q++;
  }
}