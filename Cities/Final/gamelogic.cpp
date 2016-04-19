#include"gamelogic.h"

#define SUCSESS 1
#define FAIL -1

Gamelogic::Gamelogic() {

	memset(globallist, 0, 255);
	memset(usedlist, 0, 255);
	memset(buffer, 0, 255);
}



/*
* @brief - Function set buffer where we copy name of the city.
* @[in] - wrd: variable that contains city name.
*/
void Gamelogic::Set_Buffer(const char* wrd) {
	int i = 0;
	if (wrd == NULL) {
		printf("Error, you didn't enter anything. Closing program...");
		return;
	}

	int size = strlen(wrd);
	memset(buffer, 0, 255);
	while (wrd[i] != 0) {
		buffer[i] = wrd[i];
		i++;
	}
	buffer[size - 1] = 0;
}

/*
* @brief - Function return buffer.
* @[out] - buffer: class variable that contains city name.
*/
char* Gamelogic::Get_Buffer() {
	return buffer;
}

/*
* @brief - Function check if end symbol of first city is same as first symbol of next city .
* @[in] - wrd: variable that contains city name.
* @[out] - 1 if same, -1 if not.
*/
int Gamelogic::Check_for_end(const char *wrd) {
		char *buf = Get_Buffer();
	if (*buf != 0) {
		while (*buf != 0) {
		*(buf++);
		 }
		if (toupper(*(--buf)) == *wrd) {
			Set_Buffer(wrd);
			return SUCSESS;
		}
		else {

			return FAIL;

		}

	}
	;
	return FAIL;
}
/*
* @brief - Function that write used name into the file.
* @[in] - wrd: variable that contains city name.
* @[out] - 1 if everything is okay , -1 if not.
*/
int Gamelogic::Write_word(const char* wrd) {
	int check = 0;
	check = Check_in_global_list(wrd);
	if (check == SUCSESS) {
		check = Check_in_used_list(wrd);
		if (check == FAIL) {
			FILE* used;
			used = fopen("used.txt", "a+");
			if (used != NULL) {
				fprintf(used, "%s\n", wrd);
				fclose(used);
				return SUCSESS;
			}
			else {
				printf("Couldn't create output file...closing program");
				return 0;
			}
		}
	}else {

		return FAIL;
	}
	return FAIL;

}
/*
* @brief - Function that check if city name was already used.
* @[in] - wrd: variable that contains city name.
* @[out] - 1 if used  , -1 if not.
*/
int Gamelogic::Check_in_used_list(const char* wrd) {
	int i;
	char cpy[255];
	int is_found = 0;
	std::string line;
	strcpy(cpy, wrd);
	int size  = 0;
	size = strlen(cpy);
	cpy[0] = toupper(cpy[0]);
	cpy[size - 1] = 0;
	std::ifstream used("Used.txt");
	for (;std::getline(used, line);) {
		i = 0;
		while (line[i] != 0) {
			usedlist[i] = line[i];
			i++;
		}


		is_found = strcmp(usedlist, cpy);
		if (!is_found) {
			used.close();
			return SUCSESS;
		}
		memset(usedlist, 0, 255);

	}

	if (is_found > 0 || is_found < 0) {
		used.close();
		return FAIL;
	}
	used.close();
	return 0;
}
/*
* @brief - Function that check if city name is real.
* @[in] - wrd: variable that contains city name.
* @[out] - 1 if real, -1 if not.
*/
int Gamelogic::Check_in_global_list(const char* wrd) {
		char cpy[255];
	memset(cpy, 0, 255);
	int i;
	int is_found = 0;
	std::string line;
	std::ifstream global("Globallist.txt");
	int size = 0;
	size = strlen(wrd);
	strcpy(cpy, wrd);
	cpy[0] = toupper(cpy[0]);
	cpy[size-1] = 0;
	for (; std::getline(global, line);) {
		i = 0;

		while (line[i] != 0) {
			globallist[i] = line[i];
			i++;

		}


		is_found = strcmp(globallist, cpy);   //check if in there is such city name in global list
		if (!is_found) {
			global.close();
			return SUCSESS;
		}
		memset(globallist, 0, 255);

	}

	if (is_found > 0 || is_found < 0) {
		global.close();
		return FAIL;
	}
	global.close();
	return 0;

}
void Gamelogic::Fill_Alpha() {
	char alp = 'A';
	FILE* used;
	used = fopen("Used.txt", "a+");
	if (used != NULL) {
		while (alp <= 'Z') {
			fprintf(used, "%c\n", alp++);
		}
		fclose(used);

	}
}
/*
* @brief - Function that starts game
*/
int Gamelogic::Game_Start(char* wrd) {
	if (wrd == NULL){
		printf("Error!! NULL pointer");
		exit(1);
	}
	char city[255];
	memset(city, 0, 255);
	strcpy(city, wrd);
	int check;


	city[0] = toupper(city[0]); //our name in global list starts from uppercase
								//so we convert beginning of each city to uppercase.
	check = Check_for_end(city);
	if (check == SUCSESS) {
		check = Check_in_global_list(city);
		if (check == SUCSESS) {
			check = Check_in_used_list(city);
			if (check == FAIL) {
				if (Write_word(city) == SUCSESS) {
					Set_Buffer(city);
					turn = (turn == -2) ? -3 : -2;		
					return SUCSESS;
				}
				else if (Write_word(city) == FAIL) {
					return turn;
				}
			}

		}
	}
	else if (check == SUCSESS) {
				turn = -3;
				return turn;
			}
	turn = (turn == -2) ? -3 : -2;
	return  turn;


}

void Gamelogic::ClearLogic(){
	memset(buffer, 0, 255);
	memset(usedlist, 0, 255);
	memset(globallist, 0, 255);
	turn = -3;
}

Gamelogic::~Gamelogic() {
}
