#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "GameClient.h"
using namespace std;
TCPClient::TCPClient() {//��ʼ��winsocket�˿�
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(55555);  // ���Ӷ˿� 55555
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // ���ӷ�����

    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
}

void TCPClient::SendMessage(const char* message) {//������Ϣ
    send(clientSocket, message, strlen(message), 0);
    std::cout << "Message sent!" << std::endl;
}
void TCPClient::receive() {
    char recvBuffer[1024]; // ������Ϣ�Ļ�����
    int result;
    result = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);//������Ϣ
    if (result > 0) {//�ɹ�����
        std::cout << "Message received: " << recvBuffer << std::endl;
    }
    else if (result == 0) {//�Ͽ�����
        std::cout << "Connection closed." << std::endl;
    }
    else {//����ʧ��
        std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
    }
}
TCPClient::~TCPClient() {
    closesocket(clientSocket);
    WSACleanup();
}
