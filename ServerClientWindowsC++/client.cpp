#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main()
{
string ipAddress = "127.0.0.1"; //IP address of the server
int port = 54000; //Listening port of the server

