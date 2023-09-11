/*     
*   Author: Ahmed Desoky
*   Date:   7/9/2023
*   Description:    Parser header file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include <string.h>
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
extern struct dirent* directory_content;   /*structure to contain file data*/
extern struct stat statbuffer;    /*structure to contain file stat*/  /*!!! we will try only to pass the name*/
/*=====================================================================FUNCTIONS PROTOTYPES============================================================================*/
/*Function Descriptions in .c file*/
short get_path_option(char** path, char** argv);
char get_options (char** argv);