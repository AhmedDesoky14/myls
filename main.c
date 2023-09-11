/*     
*   Author: Ahmed Desoky
*   Date:   7/9/2023
*   Description:    main file for my ls program
*   Version: 1.0.0
    Last edit: 11/9/2023
    *******************************************************************************
*/
/*==========================================================================INCLUDES===================================================================================*/
#include "main.h"
/*============================================================================MAIN=====================================================================================*/
int main(int argc, char* argv[])
{   
    char* cwd = getcwd(cwd,STD_NAME_SIZE);  /*get current working*/
    short path_found = get_path_option(&path,argv+1);
    if(path_found == -1)    /*means that 2 paths are passed, not supported*/
    {
        printf("Error, please specify only one path\n");
        return -1;
    }
    else if(path_found == 0)    /*did not find a path*/
    {
        path = cwd;
    }
    DIR* dir_ectory = opendir(path);    /*Open directory*/
    if(dir_ectory == NULL)
    {
        printf("ls: cannot access '%s': No such file or directory\n",path);
        return -1;  /*exit program*/
    }
    while(directory_content = readdir(dir_ectory))
    {   
        get_file_path(directory_content->d_name);
        int state_read = lstat(file_path,&statbuffer);  /*Note: lstat identify symbolic links while stat follows the symbolic link to the linked file*/
        if(state_read == 0)
        {
            Re_size();
            Fill_data(files_number); 
        }
        else if(state_read == -1)
        {
            printf("Could not read the file");
        }
    }
    char Options = get_options(argv+1);  /*get options*/
    Display_Files(Options);             /*display files*/
}