#include"server.h"
#include"Statics.h"
#define PLAYER1 -2
#define PLAYER2 -3
#define BAD_INPUT -4
#define OK 1
#define NOK -1
#define bSup 2
Gamelogic * game = new Gamelogic;
#ifdef _WIN32 //for Windows
#pragma comment (lib, "ws2_32.lib")
#endif
Server::Server() {
	serv_sock = 0;
	clt_sock = 0;
	clen = sizeof(other);
	memset(&server, 0, sizeof(server));
	memset(buffer, 0, 255);



}
Server::~Server() {
#ifdef _WIN32
	WSACleanup();
	closesocket(serv_sock);
	closesocket(clt_sock);
#else
	close(serv_sock);
	close(clt_sock);
#endif
}

/*
	@brief: Functions set servers address struct
*/
void Server::Init_Addr_Struct()
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(7777);

}
/*
@brief: Functions send and recive message from client
@[in]: city - message that will be send to client
@[out]: buffer - class variable that contain recieved message
*/
char * Server::Send_and_Recieve(char * city)
{

	memset(buffer, 0, 255);
	int size;
#ifdef _WIN32
	if((send(clt_sock, city, strlen(city), 0))< 0)
#else
	if (write(clt_sock, city, strlen(city))< 0)
#endif
	{
		printf("Couldnt send data to client..\n");
		SLEEP(3000);
		exit(1);
	}
	while (OK){
		printf("Waiting client answer....\n");
#ifdef _WIN32
		if ((size = recv(clt_sock, buffer, 255, 0)) < 0)
#else
		if ((size = read(clt_sock, buffer, 255)) < 0)
#endif

		{
			printf("Couldnt recieve data from client..\n");
			SLEEP(3000);
			exit(1);
		}
		else {
			return buffer;
		}
	}
}
/*
@brief: Function initialize specific start of game as server
*/
void Server::Start_Win_Serv_Game(){
		char city[255];
		char* newcity; //pointer on Send_and_Recieve() return value
		remove("Used.txt");
		game->Fill_Alpha();
		int check = 10;
		int start = 0; //variable that indicates if first city was entered
		while (OK) {
		memset(city, 0, 255);
		printf("Enter your city: ");
		fgets(city, 255, stdin);
		if (start == OK){
			check = game->Game_Start(city);//launching or game logic
		}
		if (check == OK) {
			memset(newcity, 0, 255);
#ifdef _WIN32
			if ((send(clt_sock, "0", 15, 0)) < 0)
#else
			if ((write(clt_sock, "0", 15)) < 0)
#endif
			{
				printf("Failed to send message..\n");
				SLEEP(3000);
				exit(1);
			}
			newcity = Send_and_Recieve(city);
			check = game->Game_Start(newcity);
			if (check == OK) {
				printf("Player 2 entered %s\n", newcity);
			}
		}

		if (start == 0)
		{

			if (game->Write_word(city) == NOK){
				printf("Incorrect city!!! RE- ENTER! \n");
				Start_Win_Serv_Game();
			}
			game->Set_Buffer(city);
#ifdef _WIN32
			if ((send(clt_sock, "0", 15, 0)) < 0)
#else
			if ((write(clt_sock, "0", 15)) < 0)
#endif
			{
				printf("Failed to send message..\n");
				SLEEP(3000);
				exit(1);
			}
			newcity = Send_and_Recieve(city);
			check = game->Game_Start(newcity);
			if (check == OK) {
				printf("Player 2 entered %s \n", newcity);
			}
			start = OK;
		}

		 if(check == PLAYER1){
			remove("used.txt");

			printf("You win(read rules if don't know why)!!\n");

#ifdef _WIN32
			if ((send(clt_sock, "1", 15, 0)) < 0)
#else
			if ((write(clt_sock, "1", 15)) < 0)
#endif
			{
				printf("Failed to send message..\n");
				SLEEP(3000);
				exit(1);
			}
			SLEEP(2000);
			break;

		}
		 if (check == PLAYER2) {
			printf("You lost(read rules if don't know why)!!\n");
#ifdef _WIN32
			if ((send(clt_sock, "2", 15, 0)) < 0)
#else
			if ((write(clt_sock, "2", 15)) < 0)
#endif
			{
				printf("Failed to send message..\n");
				SLEEP(3000);
				exit(1);
			}
			SLEEP(2000);
			break;

		}



	}

	delete game;
	remove("used.txt");

}
/*
@brief: Function initialise server
*/
void Server::Server_Init()
{
	Init_Socket();
	Init_Addr_Struct();
	if (bind(serv_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("Bind failed\n");
		SLEEP(3000);
		exit(1);

	}

	if (listen(serv_sock, 10) < 0) {
		printf("Fail to listen\n");
		SLEEP(3000);
		exit(1);
	}
	while (OK) {
		printf("Waiting for Client......\n");
		if ((clt_sock = accept(serv_sock, (struct sockaddr*)&other, &clen))<0) {
			printf("No connections\n");
			SLEEP(3000);
			exit(1);
		}
		printf("Connected....\n");
		break;
	}

}
/*
@brief: Function display server Menu
*/
void Server::Menu()
{
	char menu_choice;
//	CLEAR();
	printf("\t\tHello!\n");
	printf("You decided to be a server!\n");
	printf("You write city first!\n");
	printf("Choose what you want to do\n");
	printf("1)Start game\n");
	printf("2)See rules\n");
	printf("3)Exit\n");
#ifdef _WIN32
	menu_choice = _getch();
#else
	char choice[25];
	scanf("%4s", choice);
	menu_choice = choice[0];
#endif
	switch (menu_choice) {
		case '1':
		CLEAR();
		remove("used.txt");
		Server_Init();
		Start_Win_Serv_Game();
		New_Game();
		SLEEP(2000);
		break;
	case '2':
		Show_Rules();
		SLEEP(3000);
		CLEAR();
		Menu();
		break;
	case '3':
		printf("Bye bye!\n");
		SLEEP(2000);
		exit(1);
	default:
		printf("Bad input!\n");
		SLEEP(2000);
		CLEAR();
		Menu();
	}

}
/*
@brief: Function initialise server socket
*/
int Server::Init_Socket()
{
#ifdef _WIN32
	if (WSAStartup(MAKEWORD(bSup, bSup), &wData) != 0)
	{
		printf("Failed\n");
		exit(EXIT_FAILURE);
	}
#endif
	int reuse = 1;

	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROT_TCP);
	if (serv_sock <0) {
		printf("Couldnt create socket\n");
		exit(1);
	}

	if (setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0){
		printf("Failed to use option");
		exit(1);
	}
	else
		return 1;

}
/*
@brief: Function ask if user want to start new game
*/
void Server::New_Game() {
	char menu_choice;
	printf("Do you want to start new game? (Y/N)  ");
#ifdef _WIN32
	menu_choice = _getch();
#else
	char check[10];
	scanf("%4s", check);
	menu_choice = check[0];
#endif
	switch (toupper(menu_choice)) {
	case 'Y':
		printf("Launchig new game!!!..");
		SLEEP(1000);
		CLEAR();
#ifdef _WIN32
		WSACleanup();
		closesocket(serv_sock);
		closesocket(clt_sock);
#else
		close(serv_sock);
		close(clt_sock);
#endif
		memset(buffer, 0, 255);
		game->ClearLogic();
		Menu();
		break;
	case 'N':
		printf("\nBye bye\n");
		SLEEP(2000);
		exit(1);
	default:
		printf("Bad input re-enter!\n");
		SLEEP(1000);
		system("CLS");
		New_Game();

	}


}
