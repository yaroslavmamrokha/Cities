#include"server.h"
#include"client.h"
int main() {
	char menu_choice;
	Server* server = new Server;
	Client* client = new Client;
	printf("\t\tHello!\n");
	printf("This is <CITY> game\n");
	printf("Please choose server or client\n");
	printf("NOTE: Server write first, Client second\n");
	printf("1)Start as Server\n");
	printf("2)Start as Client\n");
	printf("3)Exit\n");
#ifdef _WIN32
	menu_choice = _getch();
#else
    char choice[10];
	scanf("%4s", choice);
	menu_choice = choice[0];
#endif
	switch (menu_choice) {
	case '1':
		remove("Used.txt");
		server->Menu();
		delete server;
		break;
	case '2':
		client->Menu();
		delete client;
		break;
	case '3':
		printf("Bye Bye!");
		SLEEP(2000);
		exit(1);
	default:
		printf("Bad input!!");
		SLEEP(2000);
		CLEAR();
		main();
	}
return 0;
}
