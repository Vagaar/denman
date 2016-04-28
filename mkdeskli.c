/*
   Copyright (C) 2016 Dmytro Volovnenko

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
*  @file mkdeskli.c - Main source file.
*/

#include "include.h"

/**
*   @var static unsigned short isUseEditor
*   @brief Indicate need or not external editor
*/
static unsigned short isUseEditor;
//------------------------------------------------------------------------------

/**
*   @var static unsigned char inputFlags
*   @brief Indicate what command line arguments be using by user
*   @brief One flag-per-bit |-|-|-u|-i|-p|-n|-h|-v|
*/
static unsigned char inputFlags;
//------------------------------------------------------------------------------
/*
*   //@struct struct desktopLink
*   //@brief Define
*/
 static desklink_t desklink;
//------------------------------------------------------------------------------


/**
*   @fn void parsIncomingArg(int argc, char* argv[])
*   @brief Function for parsing incoming arguments that providing through command line.
*   @brief Function use getopt_long() providing by getopt.h
*   @param argc      - length of array with arguments
*   @param argv[]    - array with arguments
*   @return void
*/
void parsIncomingArg(int argc, char* argv[]);
//------------------------------------------------------------------------------
/**
*   @fn void phelp(const char* appNameBin)
*   @brief Function for printin help to stdout.
*   @param appNameBin - name of current binary image
*   @return void
*/
void phelp(const char* appNameBin);
//------------------------------------------------------------------------------
/**
*   @fn void useExtEditor(void)
*   @brief Function make fork and start external editor (that defined in $EDITOR invorement variable) for editing link parameters.
*   @return void
*/
void useExtEditor(void);
//------------------------------------------------------------------------------
/**
*   @fn inline void setFlag(InputFlagsEnum flag)
*   @brief Set flag in char inputFlags that defined in enum InputFlagsEnum.
*   @param  flag - flag from InputFlagsEnum
*   @return void
*/
inline void setFlag(InputFlagsEnum flag);
//------------------------------------------------------------------------------
/**
*   @fn inline int isFlag(InputFlagsEnum flag)
*   @brief Check needed flag in inputFlags.
*   @param  flag - flag from InputFlagsEnum
*   @return void
*   @return int - boolean value
*/
inline int isFlag(InputFlagsEnum flag);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
*   @fn int main(int argc, char* argv[])
*   @brief Main - entery point of application.
*   @param argc     - length of array with arguments
*   @param argv[]   - array with arguments
*   @return Exit status
*/
int main(int argc, char* argv[])
{
    memset(&desklink, 0, sizeof(desklink_t));
    parsIncomingArg(argc, argv);

    printf("[%s]: %-14s %3d\t%-15s\n", APP_NAME, "Flag NAME:", isFlag(NAME), desklink.name);
    printf("[%s]: %-14s %3d\t%-15s\n", APP_NAME, "Flag PATH:", isFlag(PATH), desklink.appPath);
    printf("[%s]: %-14s %3d\t%-15s\n", APP_NAME, "Flag IMAGE:", isFlag(IMAGE), desklink.imagePath);
    printf("[%s]: %-14s %3d\n", APP_NAME, "Flag EDITOR:", isFlag(EDITOR));

    exit(EXIT_SUCCESS);
}
//------------------------------------------------------------------------------

/**
*   @fn void parsIncomingArg(int argc, char* argv[])
*   @brief Function for parsing incoming arguments that providing through command line.
*   @brief Function use getopt_long() providing by getopt.h
*   @param argc      - length of array with arguments
*   @param argv[]    - array with arguments
*   @return void
*/
void parsIncomingArg(int argc, char* argv[])
{

    int opt;
    int option_index = 0;
    static struct option long_options[] =
    {
        {"version",     no_argument,             0, 'v'},
        {"help",        no_argument,             0, 'h'},
        {"name",        required_argument,       0, 'n'},
        {"path",        required_argument,       0, 'p'},
        {"image",       required_argument,       0, 'i'},
        {"use-editor",  no_argument,             0, 'u'},
        {0, 0, 0, 0}
    };

    static char *options_string = "vhn:p:i:u";

    while ((opt = getopt_long(argc, argv, options_string, long_options, &option_index)) != -1)
    {
        switch (opt)
        {
            case 'v':
                printf(APP_NAME " version: " APP_VERSION ".\n");
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                phelp(argv[0]);
                exit(EXIT_SUCCESS);
                break;
            case 'n':
                setFlag(NAME);
                if (optarg)
                {
                   strcpy(desklink.name, optarg);
                }
                break;
            case 'p':
                setFlag(PATH);
                if (optarg)
                {
                    strcpy(desklink.appPath, optarg);
                }
                break;
            case 'i':
                setFlag(IMAGE);
                if (optarg)
                {
                    strcpy(desklink.imagePath, optarg);
                }
                break;
            case 'u':
                setFlag(EDITOR);
                break;

            case '?':
            default:
                exit(EXIT_FAILURE);

        }//switch (opt)
    }//while
}
//------------------------------------------------------------------------------
/**
*   @fn void phelp(const char* appNameBin)
*   @brief Function for printin help to stdout.
*   @param appNameBin - name of current binary image
*   @return void
*/
void phelp(const char* appNameBin)
{

    printf("\n* "APP_NAME " version: " APP_VERSION " \n* (c)" APP_DATE " Dmytro Volovnenko.\n\n");
    printf("                    ----------------------\n");
    printf("                         Make Desktop Links\n");
    printf("                          ----------------------\n");
    printf("* Putting your application in the desktop menus makes more easily.\n\n");
    printf("* Usage: %s [-vhuni] [-n <name>][-p <path>] \n", appNameBin);
    printf("   -v --version               show program version and exit\n");
    printf("   -h --help                  display this help and exit\n");
    printf("   -u --use-editor            use default text editor to edit link parameters.\n");
    printf("   -n --name  < string >      name of application for the main menu\n");
    printf("   -p --path  < path >        path to what execute\n");
    printf("   -i --image < path >        path to image associated with this application.\n\n");


}
//------------------------------------------------------------------------------
/**
*   @fn void useExtEditor(void)
*   @brief Function make fork and start external editor (that defined in $EDITOR invorement variable) for editing link parameters.
*   @return void
*/
void useExtEditor(void)
{
    pid_t pid = fork();

}
//------------------------------------------------------------------------------
/**
*   @fn inline void setFlag(InputFlagsEnum flag)
*   @brief Set flag in char inputFlags that defined in enum InputFlagsEnum.
*   @param  flag - flag from InputFlagsEnum
*   @return void
*/
inline void setFlag(InputFlagsEnum flag)
{
    inputFlags |= (1 << flag);
}
//------------------------------------------------------------------------------
/**
*   @fn inline int isFlag(InputFlagsEnum flag)
*   @brief Check needed flag in inputFlags.
*   @param  flag - flag from InputFlagsEnum
*   @return void
*   @return int - boolean value
*/
inline int isFlag(InputFlagsEnum flag)
{
    return ((inputFlags >> flag) & 1);
}
//------------------------------------------------------------------------------

