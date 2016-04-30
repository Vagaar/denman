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
/**
*   @var static char luncherFileFullPath
*   @brief Contain full path of launcher .desktop file
*/
static char launcherFileFullPath[PATH_MAX];
//------------------------------------------------------------------------------
/**
*   @brief Contain all needed data for creating launcher file
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
/**
*   @fn int createLaunchFile(int flag)
*   @brief Create or open *.desktop file and write data from desklink_t structere
*   @param  flag - create/open, rewrite/norewrite
*   @return int - boolean value
*/
int createLaunchFile(int flag);
//------------------------------------------------------------------------------
/**
*   @fn void generateFilePath()
*   @brief Function generate full path to creating .desktop file
*   @return void
*/
void generateFilePath();
//------------------------------------------------------------------------------
/**
*   @fn int writeFullStr(int fd, const char *sourceStr, size_t lenth)
*   @brief write full string to file(provided fd)
*   @param fd - file descriptor
*   @param str -
*   @return int - boolean value
*/
int writeFullStr(int fd, const char *sourceStr, size_t lenth);
//------------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////
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
    generateFilePath();

    printf("[%s]: %-25s %-3d\t%-15s\n", APP_NAME, "Flag NAME:", isFlag(NAME), desklink.name);
    printf("[%s]: %-25s %-3d\t%-15s\n", APP_NAME, "Flag PATH:", isFlag(PATH), desklink.appPath);
    printf("[%s]: %-25s %-3d\t%-15s\n", APP_NAME, "Flag IMAGE:", isFlag(IMAGE), desklink.imagePath);
    printf("[%s]: %-25s %-3d\n", APP_NAME, "Flag EDITOR:", isFlag(EDITOR));
    printf("[%s]: %-25s %-3d\n", APP_NAME, "Flag USER_ONLY:", isFlag(UONLY));
    //createLinkFile(0);
    createLaunchFile(0);

    if (isFlag(EDITOR))
    {
        useExtEditor();
    }

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
        {"user-only",   no_argument,             0, 'o'},
        {0, 0, 0, 0}
    };

    static char *options_string = "vhn:p:i:uo";

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
                   //strcat(desklink.name, FILE_TYPE);
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
            case 'o':
                setFlag(UONLY);
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
    printf("   -i --image < path >        path to image associated with this application.\n");
    printf("   -o --user-only             make accessible to a single user(don\'t need su permission).\n\n");


}
//------------------------------------------------------------------------------
/**
*   @fn void useExtEditor(void)
*   @brief Function make fork and start external editor (that defined in $EDITOR invorement variable) for editing link parameters.
*   @return void
*/
void useExtEditor(void)
{
    char *editor = getenv("EDITOR");
    printf("[%s]: %s\n", APP_NAME, editor);

    if (editor != NULL && (execlp(editor, editor, launcherFileFullPath, NULL)) == -1)
    {
        printf("[%s]: %s\n", APP_DATE, editor);
        perror("execlp");
    }
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
/**
*   @fn int createLaunchFile(int flag)
*   @brief Create or open *.desktop file and write data from desklink_t structere
*   @param  flag - create/open, rewrite/norewrite
*   @return int - boolean value
*/
int createLaunchFile(int flag)
{

    /*

    AudioVideo  	Application for presenting, creating, or processing multimedia (audio/video)
    Development	    An application for development
    Education	    Educational software
    Game	        A game
    Graphics	    Application for viewing, creating, or processing graphics
    Network	        Network application such as a web browser
    Office	        An office type application
    Science	        Scientific software
    Settings	    Settings applications
    System	        System application, "System Tools" such as say a log viewer or network monitor
    Utility         Small utility application, "Accessories"
    */
    FILE *fp;

    printf("[%s]: %s\n", APP_NAME,  launcherFileFullPath);

    fp = fopen(launcherFileFullPath, "w");
    int fd = fileno(fp);

    if (fp)
    {
        fprintf(fp, "[Desktop Entry]\n");
        fprintf(fp, "Name=%s\n", desklink.name);
        fprintf(fp, "Comment=%s\n", desklink.name);
        fprintf(fp, "Exec=%s\n", desklink.appPath);
        fprintf(fp, "Icon=%s\n", desklink.imagePath);
        fprintf(fp, "Terminal=false\n");
        fprintf(fp, "Type=Application\n");
        fprintf(fp, "Categories=\n");
        fclose(fp);
        fchmod(fd, S_IRWXU | S_IRWXG | S_IRWXO);

        close(fd);
    }
    else
    {
        perror(PERR_APP" open file");
        exit(EXIT_FAILURE);
    }

    return 0;
}

//------------------------------------------------------------------------------
/**
*   @fn void generateFilePath()
*   @brief Function generate full path to creating .desktop file
*   @return void
*/
void generateFilePath()
{
    char homeDir[PATH_MAX/2];

    if (isFlag(UONLY))
    {
        memset(homeDir, 0, sizeof(homeDir));
        strcpy(homeDir, getenv("HOME"));
        if (homeDir == NULL)
        {
            perror(PERR_APP" getenv()");
            exit(EXIT_FAILURE);
        }

        strcat(homeDir, DESKT_DIR_USR);
        strcpy(launcherFileFullPath, homeDir);
    }
    else
    {
        strcpy(launcherFileFullPath, DESKT_DIR);
    }

    strcat(launcherFileFullPath, "/");
    strcat(launcherFileFullPath, desklink.name);
    strcat(launcherFileFullPath, FILE_TYPE);
}
//------------------------------------------------------------------------------
/**
*   @fn int writeFullStr(int fd, const char *sourceStr, size_t lenth)
*   @brief write full string to file(provided fd)
*   @param fd - file descriptor
*   @param str -
*   @return int - boolean value
*/
int writeFullStr(int fd, const char *sourceStr, size_t lenth)
{
    size_t ret;

    while (lenth != 0 && (ret = write(fd, sourceStr, lenth)) != 0)
    {
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;
            perror(PERR_APP" write");
            break;
        }
        lenth -= ret;
        sourceStr += ret;
    }
}
//------------------------------------------------------------------------------




