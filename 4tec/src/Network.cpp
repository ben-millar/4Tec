#include <Network.h>

Network::~Network()
{
	disconnect();
	m_terminateThreads = true;
	if (m_recvThread.joinable())
		m_recvThread.join();
	if (m_connectThread.joinable())
		m_connectThread.join();
}

//*****************************************************************************

void Network::host(const char* t_ip, const int t_port)
try
{
	m_terminateThreads = false;
	WSAData wsaData;
	WORD version = MAKEWORD(2, 1);

	if (WSAStartup(version, &wsaData))
		throw std::exception("Winsock failed to start up\n");

	if (t_ip)
		inet_pton(AF_INET, t_ip, &m_addr.sin_addr.s_addr);
	else
		m_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	m_addr.sin_port = htons(t_port); //Port
	m_addr.sin_family = AF_INET; //IPv4 Socket

	m_socket = socket(AF_INET, SOCK_STREAM, 0); //Create socket to listen for new connections
	if (bind(m_socket, (SOCKADDR*)&m_addr, sizeof(m_addr)) == SOCKET_ERROR) //Bind the address to the socket, if we fail to bind the address..
		throw std::exception("Failed to bind the address to our listening socket.\n");

	if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR) //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max connections, if we fail to listen on listening socket...
		throw std::exception("Failed to listen on listening socket.\n");
	
	m_connectThread = std::thread(waitForConnection, std::ref(*this));
}
catch (std::exception& e)
{
	std::cout << e.what() << std::endl;
}

//*****************************************************************************

void Network::client(const char* t_ip, const int t_port)
try
{
	m_terminateThreads = false;
	WSAData wsaData;
	WORD version = MAKEWORD(2, 1);

	if (WSAStartup(version, &wsaData) != 0)
		throw std::exception("Error with WSAStartup in client");

	inet_pton(AF_INET, t_ip, &m_addr.sin_addr.s_addr);
	m_addr.sin_port = htons(t_port);
	m_addr.sin_family = AF_INET;

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (!connect(m_socket, (SOCKADDR*)&m_addr, sizeof(m_addr))) // connect correctly
	{
		initThreads();
	}
}
catch (std::exception& e)
{
	std::cout << e.what() << std::endl;
}

//*****************************************************************************

void Network::trySend(Move t_move)
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	std::tie(m_data[0], m_data[1], m_data[2]) = t_move;
	int returnCheck = send(m_socket, &m_data[0], MAX_BYTES, FLAGS);
	if (returnCheck == SOCKET_ERROR)
		std::cout << "ERROR Sending \n";
}

//*****************************************************************************

void Network::tryRecv(Network& t_instance)
{
	int check = recv(t_instance.m_socket, &t_instance.m_data[0], MAX_BYTES, FLAGS);
	if (check == SOCKET_ERROR) return;
	uint8_t level = t_instance.m_data[0];
	uint8_t row = t_instance.m_data[1];
	uint8_t col = t_instance.m_data[2];
	t_instance.notify({ level,row,col}, Player::RED);
	t_instance.initThreads();
}

//*****************************************************************************

void Network::disconnect()
{
	closesocket(m_socket);
}

//*****************************************************************************

void Network::waitForConnection(Network& t_caller)
{
	int len = sizeof(m_addr);
	t_caller.m_socket = accept(t_caller.m_socket, (SOCKADDR*)&t_caller.m_addr, &len);
	if (t_caller.m_socket)
	{
		std::cout << "Client Connected!\n";
		t_caller.initThreads();
	}
}

//*****************************************************************************

void Network::initThreads()
{
	if (m_recvThread.joinable())
		m_recvThread.join();
	m_recvThread = std::thread(tryRecv, std::ref(*this));
	m_recvThread.detach();
}
