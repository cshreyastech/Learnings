#include <stdio.h>
#include <unistd.h>     // unlink(), _exit(), read(), write(), close(),
                        // lseek(), isatty(), chown(), fsync()
#include <fcntl.h>      // open(), O_CREAT, O_EXCL, O_RDONLY, O_TRUNC,
                        // O_WRONLY, fcntl(), F_FULLFSYNC
#include <dirent.h>     // opendir(), readdir(), closedir(), DIR,
                        // struct dirent
#include <string.h>
#include <stdlib.h>

void deserialize(unsigned char data[], float vertices[], const int vertices_length);
int main()
{
	const int n_points = 307200;
	const int vertices_length = n_points * 6;
	// const size_t vertices_size = vertices_length * sizeof(float);
	// unsigned char p_vertices[307200 * 6 * 4]; 
	unsigned char* p_vertices = (unsigned char*)malloc(307200 * 6 * 4);

	float vertices[307200 * 6];

	// int len = 1024 * 100;
	int len = 1024;
	unsigned char buf[len];
	
	char *inf = "/home/shreyas/Downloads/cloud_data/induvidual_rows/tbd/test/depth_data_test_p_vertices.txt";
	// open input file
	int desc = open(inf, 'r', 0);
	if (desc < 0)
	{
		printf("read error on %s", inf);
		return 0;
	}
		
	
	int ret = 0;

	int start_index = 0;
	while (ret > -1) {
		ret = read(desc, buf, len);

		// printf("ret: %d\n", ret);

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
	// for(int i = 0; i < vertices_length; i++)
	// {
	// 	printf("%d: , %ff, %ff, %ff, %ff, %ff, %ff, \n", 
	// 		i / 6 + 1,
	// 		vertices[i + 0], vertices[i + 1], vertices[i + 2], 
	// 		vertices[i + 3], vertices[i + 4], vertices[i + 5]
	// 		);
	// 	i+=5;
	// }




	// https://www.learnc.net/c-tutorial/c-write-text-file/
	char *filename = "/home/shreyas/Downloads/cloud_data/induvidual_rows/tbd/test/depth_data_test_verify.txt";

	// open the file for writing
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Error opening the file %s", filename);
		return -1;
	}
	// write to the text file
	// for (int i = 0; i < 10; i++)
	// 	fprintf(fp, "This is the line #%d\n", i + 1);


	for(int i = 0; i < vertices_length; i++)
	{
		fprintf(fp, "%ff, %ff, %ff, %ff, %ff, %ff, \n", 
			vertices[i + 0], vertices[i + 1], vertices[i + 2], 
			vertices[i + 3], vertices[i + 4], vertices[i + 5]
		);

		i+=5;
	}




	// close the file
	fclose(fp);
	free(p_vertices);	
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