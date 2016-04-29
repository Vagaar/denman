#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED
 /**
 *  @file include.h - All includes of application.
 *  @file include.h - All const and defines.
 */
//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <getopt.h>

#include <limits.h>

//-----------------------------------------------------
//defines
//app info
#define APP_VERSION     "0.0.1"
#define APP_DATE        "2016"
#define APP_NAME        "MkDeskLi"
#define FILE_TYPE       ".desktop"
#define DESKT_DIR       "/home/sliderdv/temp" // /usr/share/applications/
#define DESKT_DIR_USR   "" // ~/.local/share/applications
//-----------------------------------------------------
#define PERR_APP        "["APP_NAME"]:"
//-----------------------------------------------------
/*
*   //@enum enum InputFlagsEnum
*   @brief Define shift for operations with inputFlags
*   @typedef typedef enum InputFlagsEnum InputFlagsEnum
*   @brief typedef enum InputFlagsEnum to InputFlagsEnum
*/
enum InputFlagsEnum
{
    VERSION = 0,
    HELP,
    NAME,
    PATH,
    IMAGE,
    EDITOR,
    UONLY
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

};
typedef struct desklink_t desklink_t;
//------------------------------------------------------------------------------

#endif // INCLUDE_H_INCLUDED
