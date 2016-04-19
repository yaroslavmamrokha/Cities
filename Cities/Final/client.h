/*Header that contains client class for Windows and Linux*/
#ifndef CLIENT_H
#define CLIENT_H
#include"SameLib.h"

/* analizing platform via #ifdef */
#ifdef _WIN32 //windows platform
#pragma comment (lib, "ws2_32.lib")
#endif
class Client {
private:
#ifdef _WIN32
	SOCKET serv_sock;
	WSADATA wData;

#else
	int serv_sock;
#endif
	struct sockaddr_in server;
	char buffer[255];
	char cAnsw[255];
public:
	Client();
	void Init_Addr_Struct(char *Ip_Addr);
	int Init_Client_Socket();
	void Recieve_and_Send();
	char* Client_Answer();
	void Client_Start();
	void Client_Init(char* Ip_Addr);
	int Check_for_Win();
	void Menu();

	void New_Game();
	~Client();

};


#endif
