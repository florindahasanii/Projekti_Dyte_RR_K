#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main()
{
string ipAddress = "127.0.0.1"; //IP address of the server
int port = 54000; //Listening port of the server

//Initialize Winsock
WSADATA data;

WORD ver = MAKEWORD(2, 2);
int wsResult = WSAStartup(ver, &data);
if (wsResult != 0)
{
cerr << "Can't start winsock, Err #" << wsResult << endl;
return;
}


//Create SOCKET
SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock == INVALID_SOCKET)
{
cerr << "Can't create socket, Err #" <<WSAGetLastError() << endl;
WSACleanup;
return;
}


