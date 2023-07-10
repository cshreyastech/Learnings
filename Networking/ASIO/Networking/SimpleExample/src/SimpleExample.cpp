#include <iostream>
#include <vector>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDLONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket)
{
	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
		[&](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				std::cout << "\n\nRead " << length << " bytes\n\n";

				for (int i = 0; i < length; i++)
					std::cout << vBuffer[i];

				GrabSomeData(socket);
			}
		}
	);
}

int main()
{
	asio::error_code ec;

	// Create a "context" - essentially the platform specific interface
	asio::io_context context;

	// Get the address of somewhere we wis to connect to
	//asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);
	//asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 80);

	// Create a socket, the contet will deliver the implementation
	asio::ip::tcp::socket socket(context);

	// Tell socket to try and connect
	socket.connect(endpoint, ec);

	if (!ec)
	{
		std::cout << "Connected!" << std::endl;
	}
	else
	{
		std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
	}

	if (socket.is_open())
	{
		std::string sRequest =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		// Send as much as data as possible from server
		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

		// Wait until response
		socket.wait(socket.wait_read);

		// Read available data in socket
		size_t bytes = socket.available();

		if (bytes > 0)
		{
			std::vector<char> vBuffer(bytes);
			socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

			for (auto c : vBuffer)
				std::cout << c;
		}
	}
	system("pause");
	return 0;
}