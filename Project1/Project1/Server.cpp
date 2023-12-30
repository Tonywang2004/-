#include "Server.h"

TCPServer::TCPServer() {
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(55555);  // �����˿� 55555
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, 5);
}

void TCPServer::AcceptConnection() {
	SOCKET clientSocket;
	sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);

	while (true) {
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
		if (clientSocket != INVALID_SOCKET) {
			std::cout << "Client connected!" << std::endl;
			// �����������һ�����߳�������ͻ��˵�����
			//std::thread clientThread(&TCPServer::HandleClient, this, clientSocket);
			//clientThread.detach();  // ���̷߳��룬ʹ���ں�̨����
			std::thread clientThread(&TCPServer::createroom, this, clientSocket);
			clientThread.detach();  // ���̷߳��룬ʹ���ں�̨����
		}
	}
}
void TCPServer::HandleClient(SOCKET clientSocket) {
	// �����ﴦ�����Կͻ��˵�����
	char buffer[1024];
	while (true) {
		int bytesReceived = recv(clientSocket, buffer, 1024, 0);
		if (bytesReceived <= 0) break; // �ͻ��˶Ͽ����ӻ�������

		// ������յ�������
		std::cout << "Received: " << std::string(buffer, 0, bytesReceived) << std::endl;

		// ������Ӧ�������Ҫ��
		// ...
	}

	closesocket(clientSocket);  // �رտͻ����׽���
}
void TCPServer::createroom(SOCKET clientSocket)
{
	char buffer[1024];
	while (true) {
		int bytesReceived = recv(clientSocket, buffer, 1024, 0);
		if (bytesReceived <= 0) break; // �ͻ��˶Ͽ����ӻ�������

		// ������յ�������
		//std::cout << "Received: " << std::string(buffer, 0, bytesReceived) << std::endl;
		std::string receivedData(buffer, bytesReceived);
		// ���ڽ��յ������ݴ������
		
		//auto player = std::make_shared<Player>(clientSocket, receivedData);
		//��ȡ����ID
		int room_number = std::stoi(buffer);
		//��ʼ�����������
		roomManager = std::make_unique<RoomManager>();
		//�Ȳ��ҷ����
		auto foundRoom = roomManager->getRoom(room_number);
		if (foundRoom == nullptr) {
			//��������
			auto room = roomManager->createRoom(room_number);
			//������
			size_t player_count = room->GetPlayerCount() + 1;//��¼�����
			std::string str1 = "Player";
			std::string str2 = std::to_string(player_count);
			std::string str = str1 + str2;
			auto player = std::make_shared<Player>(clientSocket, str);
			room->AddPlayer(player);
		}
		else {
			//������
			size_t player_count = foundRoom->GetPlayerCount() + 1;//��¼�����
			std::string str1 = "Player";
			std::string str2 = std::to_string(player_count);
			std::string str = str1 + str2;
			auto player = std::make_shared<Player>(clientSocket, str);
			foundRoom->AddPlayer(player);
		}
		
		updateRoomInfo(room_number);
		// ������Ӧ�������Ҫ��
		// ...
	}
	
	closesocket(clientSocket);
	
}
void TCPServer::updateRoomInfo(int id) {
	Room* room1 = roomManager->getRoom(id); // ��ʾ����ID
	
	if (room1) { 
		std::string roomInfo = "Room ID: " + std::to_string(room1->getId());
		std::cout << roomInfo << std::endl;
		std::string playerList = "Players:\n";
		std::cout << "Player name: " << std::endl;
		std::vector<std::string> playerNames = room1->GetAllPlayerNames();
		for (const auto& name : playerNames) {
			std::cout << name << std::endl;
		}
		
	}
}
TCPServer::~TCPServer() {
	closesocket(serverSocket);
	WSACleanup();
}