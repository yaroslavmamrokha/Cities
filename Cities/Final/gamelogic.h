 /*Header file that includes class with functions used to create game logic*/
#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include"SameLib.h"

class Gamelogic {
private:
	char globallist[255];
	char usedlist[255];
	char buffer[255];
	int turn = -3;
public:
	void ClearLogic();
	int Check_for_end(const char* wrd);
	int Check_in_used_list(const char* wrd);
	int Check_in_global_list(const char* wrd);
	int Write_word(const char* wrd);
	void Set_Buffer(const char* wrd);
	char* Get_Buffer();
	void Fill_Alpha();
	int Game_Start(char* wrd);
	Gamelogic();
	~Gamelogic();


};
#endif
