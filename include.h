#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED
 /**
 *  @file include.h - All includes of application.
 *  @file include.h - All const and defines.
 */
//includes
#include <stdio.h>      //ISO C99 Standard: 7.19 Input/output
#include <stdlib.h>     //ISO C99 Standard: 7.20 General utilities
#include <string.h>     //ISO C99 Standard: 7.21 String handling

#include <unistd.h>     //POSIX Standard: 2.10 Symbolic Constants
#include <getopt.h>
#include <dirent.h>

#include <limits.h>     //ISO C99 Standard: 7.10/5.2.4.2.1 Sizes of integer types
//-----------------------------------------------------
//Unix Systems
#include <sys/types.h>  //POSIX Standard: 2.6 Primitive System Data Type
#include <sys/stat.h>   //POSIX Standard: 5.6 File Characteristics
#include <fcntl.h>      //POSIX Standard: 6.5 File Control Operations
#include <sys/errno.h>

//-----------------------------------------------------
//defines
//app info
#define APP_VERSION     "0.0.2"
#define APP_DATE        "2016"
#define APP_NAME        "denman"
#define FILE_TYPE       ".desktop"
#define DESKT_DIR       "/usr/share/applications"
#define DESKT_DIR_USR   "/.local/share/applications"
//-----------------------------------------------------
#define PERR_APP        "["APP_NAME"]:"
//-----------------------------------------------------
//launcher templite
/*       fprintf(fp, "[Desktop Entry]\n");
        fprintf(fp, "Name=%s\n", desklink.name);
        fprintf(fp, "Comment=%s\n", desklink.name);
        fprintf(fp, "Exec=%s\n", desklink.appPath);
        fprintf(fp, "Icon=%s\n", desklink.imagePath);
        fprintf(fp, "Terminal=false\n");
        fprintf(fp, "Type=Application\n");
        fprintf(fp, "Categories=\n");*/
#define F_HEAD            "[Desktop Entry]\n"
#define F_NAME            "Name="
#define F_COMM            "Comment="
#define F_EXEC            "Exec="
#define F_ICON            "Icon="
#define F_TERM            "Terminal="
#define F_TYPE            "Type="
#define F_CTEG            "Categories="

#define F_LEN_COMM        1024
#define F_LEN_TYPE        28
#define F_LEN_CTEG        28
//-----------------------------------------------------
/*
*   //@enum enum InputFlagsEnum
*   @brief Define shift for operations with inputFlags
*   @typedef typedef enum InputFlagsEnum InputFlagsEnum
*   @brief typedef enum InputFlagsEnum to InputFlagsEnum
*/
enum InputFlagsEnum
{
    NAME=0,
    PATH,
    IMAGE,
    EDITOR,
    ALLU,
    TERM,
    REMV,
    SRCH
};

typedef enum InputFlagsEnum InputFlagsEnum;
//------------------------------------------------------------------------------
/*
*   //@struct struct desktopLink
*   @brief Define
*   @typedef typedef desktopLink desklink_t
*   @brief typedef desktopLink to desklink_t
*/
struct desklink_t
{
    char name[NAME_MAX];
    char appPath[PATH_MAX];
    char imagePath[PATH_MAX];
    char comment[F_LEN_COMM];
    char type[F_LEN_TYPE];
    char category[F_LEN_CTEG];
    int terminal;

};
typedef struct desklink_t desklink_t;
//------------------------------------------------------------------------------

#endif // INCLUDE_H_INCLUDED
