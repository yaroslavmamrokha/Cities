/*Header that contains server class for Windows and Linux*/
#ifndef SERVER_H
#define SERVER_H
#include"SameLib.h"
#include"gamelogic.h"
/* analizing platform via #ifdef */
class Server {
private:
#ifdef _WIN32
	SOCKET serv_sock;
	SOCKET clt_sock;
	int clen;
	WSADATA wData;
#else
	int serv_sock;
	int clt_sock;
	socklen_t clen;
#endif
	struct sockaddr_in server, other;
	char buffer[255];
public:
	Server();
	~Server();
	int Init_Socket();
	void Init_Addr_Struct();
	char* Send_and_Recieve(char*);
	void Start_Win_Serv_Game();
	void Server_Init();
	void Menu();
	void New_Game();
};



#endif
