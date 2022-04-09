#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
 
using namespace std;
 
int main()
{
    // Create a socket - Krijimi i nje socketi 
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Nuk mund te krijohet socket-i!" << endl;
        return -1;
    }
 
    // Bind the ip address and port to a socket - Lidhja e ip adreses dhe portit me nje socket.
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    // Tell Winsock the socket is for listening - Socketi po degjon 
    // Winsock - Windows Sockets API. Eshtë një ndërfaqe programimi aplikacioni që përcakton se si softueri i aplikacionit të rrjetit Windows 
    //duhet të aksesojë shërbimet e rrjetit, veçanërisht TCP/IP.
    listen(listening, SOMAXCONN);
 
    // Wait for a connection - Pritja per nje lidhje 
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name - Emri i klientit ne distance 
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on - Porti ne te cilin klienti eshte lidhur 
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " lidhur ne portin " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " lidhur ne portin " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket - mbyllet socketi qe eshte duke degjuar 
    close(listening);
 
    // While loop: accept and echo message back to client - While loop: pranon dhe e kthen mesazhin prapa tek klienti
    char buf[4096];
 
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data - pritja per klientin per te derguar te dhena 
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error ne recv(). Duke u mbyllur." << endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            cout << "Klienti u shkeput " << endl;
            break;
        }
 
        cout << string(buf, 0, bytesReceived) << endl;
 
        // Echo message back to client - e kthen mesazhin prapa tek klienti
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
 
    // Close the socket - mbyllja e socketit
    close(clientSocket);
 
    return 0;
}
