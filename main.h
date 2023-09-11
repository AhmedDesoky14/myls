/*==========================================================================INCLUDES===================================================================================*/
#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "functions.h"
/*======================================================================GLOBAL VARIABES================================================================================*/
struct dirent* directory_content;   /*structure to contain file data*/
struct stat statbuffer;    /*structure to contain file stat*/  /*!!! we will try only to pass the name*/
unsigned int files_number = 0;  /*declaring a variable to store number of files*/
file_data** Files;  /*creating dynamically allocated pointer to pointer (array of pointers) of type that structure*/
char file_path[STD_NAME_SIZE];  /*string to hold file with complete path*/
char* path;  /*directory path string*/