#ifndef STATICS_H
#define STATICS_H
#include<stdio.h>

static void Show_Rules()
{
	CLEAR();
	printf("Game based on 4 rules\n");
	printf("1)Enter ONLY Ukrainian cities!\n");
	printf("2)Don't repeat cities it will prevent you to lose the game\n");
	printf("3)Beginning of new city must be same as in previous city ending\n");
	printf("If not you'll lose the game\n");
	printf("4)First who enter wrong city lose the game\n");

}
#endif