/*Header file that includes libraries that use server, client and game logic implementations*/
#ifndef SAMELIB_H
#define SAMELIB_H
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<sstream>
#include<fstream>
#include <stdlib.h>



#ifdef _WIN32
#include<winsock2.h>
#include<conio.h>
#include <windows.h>
#define CLEAR() system("CLS")
#define SLEEP(a) Sleep(a)
#
#else
#include<unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#define SLEEP(a) sleep(a/1000)
#define CLEAR() system("clear")
#endif




#define  IPPROT_TCP 6
#endif
