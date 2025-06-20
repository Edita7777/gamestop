#ifndef STRUKTURE_H
#define STRUKTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    CONSOLE_PS5,
    CONSOLE_XBOX,
    CONSOLE_SWITCH,
    CONSOLE_PC,
    CONSOLE_UNKNOWN
} console_platform;

typedef struct {
    int id;
    char first_name[20];
    char last_name[20];
    char address[30];
} customer;

typedef struct {
    char name[30];
    int id;
    int copies_number;
    float price;
    console_platform console;
} game;


#endif
