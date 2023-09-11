/*     
*   Author: Ahmed Desoky
*   Date:   7/9/2023
*   Description:    Parser source file
*/
/*==========================================================================INCLUDES===================================================================================*/
#include "parser.h"
/*=====================================================================FUNCTIONS DEFINITION============================================================================*/
/***********************************************************************************************************************************************
    Function Description:   Function to know parse the path from the input
    [INPUTS]:   path variable address, input arguments
    [OUTPUTS]:  short variable to indicate if path is correctly entered or not
    NOTES: 
************************************************************************************************************************************************/
short get_path_option(char** path, char** argv)
{
    unsigned char path_found = 0;
    for(unsigned int j=0 ; argv[j] != NULL ; j++)
    {
        if(argv[j][0] != '-')   /*means it is not an option argument*/
        {
            *path = argv[j];
            path_found++;
            if(path_found >= 2)  /*means that 2 paths are passed, not supported*/
            {
                return -1;
            }
        }
    }
    if(path_found == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
/***********************************************************************************************************************************************
    Function Description:   Function to get options of display
    [INPUTS]:   input arguments
    [OUTPUTS]:  Options in char variable
    NOTES: 
************************************************************************************************************************************************/
char get_options (char** argv)
{
    char Options = 0;
    /*Options Variable:
    +-----------------------------------------------------------------------+
    | Bit 7  | Bit 6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
    | Unused | Unused | Unused | Unused | -f     | -i     | -a     | -l     |
    +-----------------------------------------------------------------------+*/
    for(unsigned int j=0 ; argv[j] != NULL ; j++)
    {
        if(argv[j][0] == '-')   /*means it is an option argument*/
        {
            for(unsigned int k=1 ; argv[j][k] != '\0' ; k++)
            {
                if(argv[j][k] == 'l')
                {
                    SET_BIT(Options,0); /*-l option*/
                }
                if(argv[j][k] == 'a')
                {
                    SET_BIT(Options,1); /*-a option*/
                }
                if(argv[j][k] == 'i')
                {
                    SET_BIT(Options,2); /*-i option*/
                }
                if(argv[j][k] == 'f')
                {
                    SET_BIT(Options,3); /*-f option*/
                }
            }
        }
    }
    return Options;
}