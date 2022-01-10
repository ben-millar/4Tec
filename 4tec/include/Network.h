#ifndef NETWORK_INCLUDE
#define NETWORK_INCLUDE

#include <WS2tcpip.h>

#include <unordered_map>
#include <functional>
#include <iostream>
#include <thread>

#include <GameData.h>

#pragma comment(lib,"ws2_32.lib")

#define MAX_BYTES 4
#define FLAGS 0

class Network
{
public:
    /// <summary>
    /// Default Constructor for the network
    /// </summary>
    Network() = default;

    /// <summary>
    /// Destructor (Closes all the open threads and allows the network to close)
    /// </summary>
    ~Network();

    /// <summary>
    /// Gets the network to start hosting the game
    /// </summary>
    /// <param name="t_ip"> Local IP address </param>
    /// <param name="t_port"> Port the game looks for info from </param>
    void host(const char* t_ip, const int t_port);

    /// <summary>
    /// Allows the game to run in client mode (Connect to the host)
    /// </summary>
    /// <param name="t_ip"> IP to connect to (NEEDS TO BE LOCAL IP)</param>
    /// <param name="t_port"> Port the game is running on </param>
    void client(const char* t_ip, const int t_port);

    /// <summary>
    /// Allows the network to try send information to the port
    /// </summary>
    /// <param name="t_move"> The move the local player has played </param>
    void trySend(Move t_move);

    /// <summary>
    /// This will run on a thread as to not crash the game when waiting for a reply 
    /// Thread will end if the connection is lost.
    /// When receiving a move (EXPECTED TO BE A MOVE) the program will pass that move onto 
    /// </summary>
    /// <param name="t_instance"> Network instance that owns the thread </param>
    Move tryRecv();

    /// <summary>
    /// Close the socket and end the connection
    /// </summary>
    void disconnect();

protected:

    /// <summary>
    /// Gets the program to wait for someone to connect to the program before continuing 
    /// </summary>
    /// <param name="t_caller"></param>
    static void waitForConnection(Network& t_caller);

    char m_data[MAX_BYTES];
    SOCKET m_socket;
    SOCKADDR_IN m_addr;

    std::thread m_connectThread;
};
#endif