#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
//�ͻ��˴���
class TCPClient {
public:
    TCPClient();//���캯�����޲��� 

    void SendMessage(const char* message);//������Ϣ 
    void receive();//������Ϣ 
    ~TCPClient();//�������� 
private:
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
};
