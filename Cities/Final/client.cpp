#include "client.h"
#define WIN -4
#define NTH -6
#define LOSE -5
#define bSup 2
#include"Statics.h"
char addr[50];
void Ip_check(){
	char Ip[50];
	printf("Enter server IP address: ");
	fgets(Ip, 17, stdin);
	unsigned int an = inet_addr(Ip);
	if (strlen(Ip) < 7 || an == INADDR_NONE){
		printf("Bad Ip adress, re-enter!\n");
		Ip_check();
	}
	else{
		strcpy(addr, Ip);
	}
}
Client::Client()
{

	serv_sock = 0;
	memset(cAnsw, 0, 255);
	memset(buffer, 0, 255);
	memset(&server, 0, sizeof(server));


}
Client::~Client() {
#ifdef _WIN32
	WSACleanup();
	closesocket(serv_sock);
#else
	close(serv_sock);
#endif
}
/*
@brief: Function initialize server(to what we want to connect) address structure
*/
void Client::Init_Addr_Struct(char*Ip_Addr)
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(Ip_Addr);
	server.sin_port = htons(7777);
}
/*
@brief: Function initialize client socket
*/
int Client::Init_Client_Socket()
{
#ifdef _WIN32
	if (WSAStartup(MAKEWORD(bSup, bSup), &wData) != 0)
	{
		printf("Failed\n");
		exit(1);
	}
#endif
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROT_TCP);
	if (serv_sock < 0) {
		printf("Couldnt create socket\n");
		return 0;
	}
	else
		return 1;
}
/*
@brief: Function recieve and send message to server
*/
void Client::Recieve_and_Send()
{
	int size = 0;
	char answer[255];
	memset(answer, 0, 255);
	memset(buffer, 0, 255);
	while (1){
		printf("Waiting server answer....\n");
#ifdef _WIN32
		if ((size = recv(serv_sock, buffer, 255, 0)) < 0) //used class variable buffer to save recieved message
#else
		if ((size = read(serv_sock, buffer, 255)) < 0)
#endif
		{
			printf("Couldnt recieve data from server..");
			exit(1);
		}
		break;
	}
	
		
		printf("Player 2 entered such city:  %s\n", buffer);
	
		strcpy(answer, Client_Answer());
#ifdef _WIN32
		if ((send(serv_sock, answer, 255, 0)) < 0)
#else
		if ((write(serv_sock, answer, 255)) < 0)
#endif
		{
			printf("Failed to send message..\n");
			exit(1);
		}

}
/*
@brief: Function ask user to enter his answer
@[out]: buf - variable that contains answer
*/
char* Client::Client_Answer() {
	puts("Please enter your answer:  ");
	fgets(cAnsw, 255, stdin);
	return cAnsw;

}
/*
@brief: Function initialize specific start of the game as client
*/
void Client::Client_Start() {
	int indic_winner= 0;
	while (1) {
		indic_winner = Check_for_Win();
		if (indic_winner == WIN) {
			printf("You win(read rules if don't know why)!!\n");
			break;
		}
		if (indic_winner == LOSE) {
			printf("You lost(read rules if don't know why)!!\n");
			break;
		}
		if (indic_winner == NTH){
			Recieve_and_Send();
		}
		else{
			break;
		}
	}

}
/*
@brief: Function initialize client
*/
void Client::Client_Init(char* Ip_Addr)
{
	Init_Client_Socket();
	Init_Addr_Struct(Ip_Addr);

}
/*
@brief: Function check for win, state is recieved from server
@[out]: WIN - if client wins, LOSE - if client lose
*/
int Client::Check_for_Win() {
	char win[25];
	memset(win, 0, 25);
	int size = 0;
	while (1){
			printf("Waiting for server move.....\n");
#ifdef _WIN32
			if ((size = recv(serv_sock, win, 25, 0)) < 0)
#else
			if ((size = read(serv_sock, win, 25)) < 0)
#endif
			{
			printf("Failed to recieve Data\n");
			exit(1);
		}
		break;
	}

		if (win[0] == '2') {
			return WIN;
		}
		if (win[0] == '1')	{
			return LOSE;
		}

		return NTH;

}
/*
@brief: Function display client menu
*/
void Client::Menu() {
	char menu_choice;
	CLEAR();
	printf("\t\tHello!\n");
	printf("You decided to be a Client!\n");
	printf("You write city second!\n");
	printf("Choose what you want to do\n");
	printf("1)Start game\n");
	printf("2)See rules\n");
	printf("3)Exit\n");
	remove("Used.txt");
#ifdef _WIN32
	menu_choice = _getch();
#else
	char choice[14];
	scanf("%4s", choice);
	menu_choice = choice[0];
#endif
	switch (menu_choice){
	case '1':
		CLEAR();
		Ip_check();
		if (addr == NULL){
			exit(1);
		}
		Client_Init(addr);
				printf("Connecting to server\n");
				if ((connect(serv_sock, (struct sockaddr*)&server, sizeof(server))) < 0) {
				printf("Failed to connect");
				SLEEP(2000);
				exit(1);
			}
			printf("Connected.....\n");
			printf("Game Starts\n");
			SLEEP(1000);
			CLEAR();
		Client_Start();
		New_Game();
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
		printf("Bad input!");
		SLEEP(2000);
		CLEAR();
		Menu();
	}
}
/*
@brief: Function ask if user want to start new game
*/
void Client::New_Game() {
	char menu_choice;
	printf("Do you want to start new game? (Y/N)  ");
#ifdef _WIN32
	menu_choice = _getch();
#else
	char check[14];
	scanf("%3s", check);
	menu_choice = check[0];
#endif
	switch (toupper(menu_choice)) {
	case 'Y':
		printf("Launchig new game!!!..");
		SLEEP(1000);
		CLEAR();
		closesocket(serv_sock);
		Menu();
		break;
	case 'N':
		printf("\nBye bye\n");
		SLEEP(1500);
		exit(1);
	default:
		printf("Bad input re-enter!\n");
		SLEEP(1000);
		CLEAR();
		New_Game();

	}


}
