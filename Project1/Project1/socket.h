#pragma once
#include<WinSock2.h>
#include <WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")

//ʹ�ö˿�
constexpr int kPORT = 7777;
//��������С
constexpr int kMAX = 100;

/**
* @brief ���ڳ�ʼ���͹ر������
*/
class Socket
{
public:
	//��ʼ�������
	static bool init_Socket();

	//�ر������
	static bool close_Socket();

};
