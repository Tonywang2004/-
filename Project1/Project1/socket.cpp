#include "Socket.h"

bool Socket::init_Socket()
{
	WSAData wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))//windows socket ansyc(windows�첽�׽���),���һ������WORD���ͺ������ָ���汾��
	{
		std::cerr << "WSAStartup\n";
		return false;
	}
	return true;
}

bool Socket::close_Socket()
{
	if (0 != WSACleanup())
	{
		std::cerr << "WSACleanup\n";
		return false;
	}
	return true;
}