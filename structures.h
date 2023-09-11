/*     
*   Author: Ahmed Desoky
*   Date:   8/9/2023
*   Description:    structures used
*/
/*==========================================================================INCLUDES===================================================================================*/
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
/*====================================================================STRUCTURES DATATYPES=============================================================================*/
/*
    Structure for data of each file
*/
typedef struct
{
    char name[256]; /*only fromr readdir*/
    ino_t inode;    /*all other from stat*/
    mode_t mode;
    nlink_t hrdlinks;
    uid_t usrIDowner;
    gid_t grpIDowner;
    off_t size;
    struct timespec modif_timestmp; /*time stamp of the last modification*/
}file_data;