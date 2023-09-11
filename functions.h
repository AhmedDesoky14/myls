/*     
*   Author: Ahmed Desoky
*   Date:   10/9/2023
*   Description:    used functions header file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "structures.h"
/*==========================================================================MACROS=====================================================================================*/
/*Macro used to set bit in a 8 bit variable*/
#define SET_BIT(VAR8,BIT) (VAR8|=(1<<BIT))
/*Macro used to clear bit in a 8 bit variable*/
#define CLEAR_BIT(VAR8,BIT) (VAR8&=(~(1<<BIT)))
/*Macro used to check bit is set in a 8 bit variable*/
#define BIT_IS_SET(VAR8,BIT) (VAR8&(1<<BIT))
/*Macro used to check bit is clear in a 8 bit variable*/
#define BIT_IS_CLEAR(VAR8,BIT) (!(VAR8&(1<<BIT)))
/*========================================================================DEFINITIONS==================================================================================*/
#define STD_NAME_SIZE   256
/*===========================================================================EXTERNS===================================================================================*/
extern char* path;  /*extern path string*/
extern struct dirent* directory_content;   /*structure to contain file data*/
extern struct stat statbuffer;    /*structure to contain file stat*/  /*!!! we will try only to pass the name*/
extern unsigned int files_number;  /*declaring a variable to store number of files*/
extern file_data** Files;  /*creating dynamically allocated pointer to pointer (array of pointers) of type that structure*/
extern char file_path[STD_NAME_SIZE];  /*string to hold file with complete path*/
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function Descriptions in .c file*/
void Initialize(void);
void Fill_data(unsigned int file_number);
void get_file_path(char* file_name);
void Re_size (void);
void Display_Files(char Options);
void Display_long_format(char Options,unsigned int k /*index*/);    
