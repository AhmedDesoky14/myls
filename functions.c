/*     
*   Author: Ahmed Desoky
*   Date:   10/9/2023
*   Description:    used functions source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include "functions.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   Private function used in sorting process by comparing arguments
    [INPUTS]:   2 pointers to arguments to be compared
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
static int cmpstringp(const void *p1, const void *p2)
{
    /* The actual arguments to this function are "pointers to
       pointers to char", but strcmp(3) arguments are "pointers
       to char", hence the following cast plus dereference */
    return strcmp(*(const char **) p1, *(const char **) p2);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Private function used to sort files of the directory
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
static void Sort_Files(void)
{
    qsort(Files,files_number,sizeof(file_data*),cmpstringp);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Private function used to remove a character from a string
    [INPUTS]:   The string to remove the character from, the character
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
static void remove_char(char* str,char character)
{
    int i,j;
    int len = strlen(str);
    for (i = j = 0; i < len; i++) 
    {
        if (str[i] != character) 
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function to allocate memory for the Files data to display later
    [INPUTS]:   NONE
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Initialize(void)
{
    Files = (file_data**)malloc(sizeof(file_data*)); /*creating dynamically allocated pointer to pointer (array of pointers) of type that structure*/
    Files[0] = NULL;    /*first pointer points to NULL*/
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function to store file data in an object of strcture file_data 
    [INPUTS]:   file number
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Fill_data(unsigned int file_number)
{
    //strcpy(files_names[file_number-1],directory_content->d_name);       /*Copying names*/
    strcpy(Files[file_number-1]->name,directory_content->d_name);       /*Copying names*/
    Files[file_number-1]->inode = statbuffer.st_ino;        /*getting inode number*/
    Files[file_number-1]->mode = statbuffer.st_mode;        /*getting mode and type*/
    Files[file_number-1]->hrdlinks = statbuffer.st_nlink;   /*getting number of hard links*/
    Files[file_number-1]->usrIDowner = statbuffer.st_uid;   /*getting user ID of the owner*/
    Files[file_number-1]->grpIDowner = statbuffer.st_gid;   /*getting group ID of the owner*/
    Files[file_number-1]->size = statbuffer.st_size;        /*getting size*/
    Files[file_number-1]->modif_timestmp.tv_sec = statbuffer.st_mtime;  /*getting last modification time, recheck this if not working*/
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function to get file full path
    [INPUTS]:   file name is pointer to character
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void get_file_path(char* file_name)
{
    strcpy(file_path,path);
    strcat(file_path,"/");
    strcat(file_path,file_name);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function to increase size of the array of pointers of type file_data to store more files data to display later
    [INPUTS]:   file number
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Re_size(void)
{
    files_number++; /*entry found*/
    file_data* file = (file_data*)malloc(sizeof(file_data));    /*allocate memory for the file data*/
    Files = (file_data**)realloc(Files,(files_number+1)*sizeof(file_data*));    /*increase number of pointers*/
    Files[files_number-1] = file;   /*make the pointer points the allocated space*/
    Files[files_number] = NULL;     /*make the last pointer points to NULL*/
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function to display the files in its different options
    [INPUTS]:   Display options
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Display_Files(char Options)
{
    /*Options Variable: 
    +-----------------------------------------------------------------------+
    | Bit 7  | Bit 6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
    | Unused | Unused | Unused | Unused | -f     | -i     | -a     | -l     |
    +-----------------------------------------------------------------------+*/
    /*==========================================WITH SORTING================================================================*/
    if(BIT_IS_CLEAR(Options,3))
    {
        Sort_Files();
        if(BIT_IS_CLEAR(Options,0)) /*long format is not set*/
        {
            for(unsigned int k=0 ; k<files_number ; k++)
            {   
                if(BIT_IS_CLEAR(Options,1) && (Files[k]->name[0] == '.'))   /*check show hidden files option*/
                {
                    continue;
                }
                if(BIT_IS_SET(Options,2))   /*check inode option*/
                {
                    printf("\033[1;33m%ld\033[1;0m ",Files[k]->inode);
                }
                if(((Files[k]->mode) & S_IFMT) == S_IFLNK)  /*if file is symbolic link*/
                {
                    printf("\033[1;36m%s\033[1;0m  ",Files[k]->name);
                }
                else if(((Files[k]->mode) & S_IFMT) == S_IFDIR)
                {
                    printf("\033[1;34m%s\033[1;0m  ",Files[k]->name);
                }
                else if (((Files[k]->mode) & S_IFMT) != S_IFREG)
                {
                    printf("\033[1;33m%s\033[1;0m  ",Files[k]->name);
                }
                else
                {
                    printf("%s  ",Files[k]->name);
                }
            }
            printf("\n");
        }
        else if(BIT_IS_SET(Options,0))  /*long format is set*/
        {
            for(unsigned int k=0 ; k<files_number ; k++)
            {       
                Display_long_format(Options,k);
            }
        }
        return; /*to stop and not to go to the next if condition*/
    }
    /*============================================WITHOUT SORTING===========================================================*/
    if(BIT_IS_CLEAR(Options,0)) /*long format is not set*/
    {
        for(unsigned int k=0 ; k<files_number ; k++)
        {
            if(BIT_IS_CLEAR(Options,1) && (Files[k]->name[0] == '.'))   /*check show hidden files option*/
            {
                continue;
            }
            if(BIT_IS_SET(Options,2))   /*check inode option*/
            {
                printf("\033[1;33m%ld\033[1;0m ",Files[k]->inode);
            }
            if(((Files[k]->mode) & S_IFMT) == S_IFLNK)  /*if file is symbolic link*/
            {
                printf("\033[1;36m%s\033[1;0m  ",Files[k]->name);
            }
            else if(((Files[k]->mode) & S_IFMT) == S_IFDIR)
            {
                printf("\033[1;34m%s\033[1;0m  ",Files[k]->name);
            }
            else if (((Files[k]->mode) & S_IFMT) != S_IFREG)
            {
                printf("\033[1;33m%s\033[1;0m  ",Files[k]->name);
            }
            else
            {
                printf("%s  ",Files[k]->name);
            }
        }
        printf("\n");
    }
    else if(BIT_IS_SET(Options,0))  /*long format is set*/
    {
        for(unsigned int k=0 ; k<files_number ; k++)
        {
            Display_long_format(Options,k);
        }
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function to help Display_Files to display files in long format
    [INPUTS]:   Display options and file index
    [OUTPUTS]:  NONE
    NOTES: 
************************************************************************************************************************************************/
void Display_long_format(char Options,unsigned int k /*index*/)
{
    char symbolic_link = 0;  /*reset the variable*/
    struct passwd* file_owner_data; /*structure to contain file owner data*/
    struct group* file_group_data;  /*structure to contain file group owner data*/
    if(BIT_IS_CLEAR(Options,1) && (Files[k]->name[0] == '.'))   /*check show hidden files option*/
    {
        return;
    }
    if(BIT_IS_SET(Options,2))
    {
        printf("\033[1;33m\t\b\b%ld\033[1;0m ",Files[k]->inode);
    }
    switch(Files[k]->mode & S_IFMT) /*check file type*/
    {
        case S_IFIFO:    /*FIFO File*/
            printf("\033[1;32m\t%c\033[1;0m",'f');
            break;
        case S_IFCHR:   /*Character Device File*/
            printf("\033[1;32m\t%c\033[1;0m",'c');
            break;
        case S_IFDIR:   /*Directory File*/
            printf("\033[1;32m\t%c\033[1;0m",'d');
            break;
        case S_IFBLK:   /*Block Device File*/
            printf("\033[1;32m\t%c\033[1;0m",'b');
            break;
        case S_IFREG:   /*Regular File*/
            printf("\033[1;32m\t%c\033[1;0m",'-');
            break;
        case S_IFLNK:   /*Symbolic link File*/
            printf("\033[1;32m\t%c\033[1;0m",'l');
            symbolic_link = 1;  /*set as symbolic link*/
            break;
        case S_IFSOCK:   /*SocketFile*/
            printf("\033[1;32m\t%c\033[1;0m",'s');
            break;
    }
    /*-----------------------------------------------------------------*/
    if(Files[k]->mode & S_IRUSR)    /*check user owner read permission*/
    {
        printf("\033[1;31mr\033[1;0m");
    }
    else
    {
        printf("\033[1;31m-\033[1;0m");
    }
    if(Files[k]->mode & S_IWUSR)    /*check user owner write permission*/
    {
        printf("\033[1;31mw\033[1;0m");
    }
    else
    {
        printf("\033[1;31m-\033[1;0m");
    }
    if(Files[k]->mode & S_ISUID)        /*check SUID permission*/
    {
        printf("\033[1;31mS\033[1;0m");
    }
    else if(Files[k]->mode & S_ISGID)   /*check GUID permission*/
    {
        printf("\033[1;31mG\033[1;0m");
    }
    else if(Files[k]->mode & S_IXUSR)   /*check user owner execute permission*/
    {
        printf("\033[1;31mx\033[1;0m");
    }
    else
    {
        printf("\033[1;31m-\033[1;0m");
    }
    /*-----------------------------------------------------------------*/
    if(Files[k]->mode & S_IRGRP)    /*check group owner read permission*/
    {
        printf("\033[1;33mr\033[1;0m");
    }
    else
    {
        printf("\033[1;33m-\033[1;0m");
    }
    if(Files[k]->mode & S_IWGRP)    /*check group owner write permission*/
    {
        printf("\033[1;33mw\033[1;0m");
    }
    else
    {
        printf("\033[1;33m-\033[1;0m");
    }
    if(Files[k]->mode & S_IXGRP)    /*check group owner execute permission*/
    {
        printf("\033[1;33mx\033[1;0m");
    }
    else
    {
        printf("\033[1;33m-\033[1;0m");
    }
    /*-----------------------------------------------------------------*/
    if(Files[k]->mode & S_IROTH)    /*check others read permission*/
    {
        printf("\033[1;34mr\033[1;0m");
    }
    else
    {
        printf("\033[1;34m-\033[1;0m");
    }
    if(Files[k]->mode & S_IWOTH)    /*check others write permission*/
    {
        printf("\033[1;34mw\033[1;0m");
    }
    else
    {
        printf("\033[1;34m-\033[1;0m");
    }
    if(Files[k]->mode & S_IXOTH)    /*check others execute permission*/
    {
        printf("\033[1;34mx\033[1;0m");
    }
    else
    {
        printf("\033[1;34m-\033[1;0m");
    }
    /*-----------------------------------------------------------------*/
    if(Files[k]->mode & S_ISVTX)    /*check Sticky bit*/
    {
        printf("t");
        printf("%5ld   ",Files[k]->hrdlinks);   /*print number of hard links*/
    }
    else
    {
        printf(" %5ld   ",Files[k]->hrdlinks);   /*print number of hard links*/
    }    
    /*-----------------------------------------------------------------*/
    file_owner_data = getpwuid(Files[k]->usrIDowner);     /*get file owner data*/
    file_group_data = getgrgid(Files[k]->grpIDowner);   /*get file group owner data*/
    printf("%s %s\t",file_owner_data->pw_name,file_group_data->gr_name); /*printing name of file owner and its group*/
    /*-----------------------------------------------------------------*/
    printf("\033[1;35m%10ld\033[1;0m ",Files[k]->size);   /*printing size*/
    /*-----------------------------------------------------------------*/
    char* mod_time = ctime(&(Files[k]->modif_timestmp.tv_sec)); /*getting time format*/
    remove_char(mod_time,'\n');
    printf("%s ",mod_time+4);   /*print modification time*/
    /*-----------------------------------------------------------------*/
    if(symbolic_link == 1)  /*if file is symbolic link*/
    {
        char file_full_path[STD_NAME_SIZE];
        char* Link  = malloc(STD_NAME_SIZE*sizeof(char));
        strcpy(file_full_path,path);
        strcat(file_full_path,"/");
        strcat(file_full_path,Files[k]->name);
        ssize_t readlink_stat = readlink(file_full_path,Link,STD_NAME_SIZE);
        if(readlink_stat == -1)
        {
            printf("\nSymbolic Link Error\n");
        }
         printf("\033[1;36m%s\033[1;0m -> \033[1;34m%s\033[1;0m\n",Files[k]->name,Link); /*print name and the link*/
        free(Link);
    }
    else if(((Files[k]->mode) & S_IFMT) == S_IFDIR)
    {
        printf("\033[1;34m%s\n\033[1;0m  ",Files[k]->name);
    }
    else if (((Files[k]->mode) & S_IFMT) != S_IFREG)
    {
        printf("\033[1;33m%s\033[1;0m  ",Files[k]->name);
    }
    else
    {
       printf("%s\n",Files[k]->name); /*print name*/
    }
}