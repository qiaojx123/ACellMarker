#pragma once

#include <string>

#include "UIClasses.h"
#include "QtWidgets/qmenubar.h"
#include "QtWidgets/qtoolbar.h"

#define M_ICONSIZE 50
#define M_ICONSPACE 10
#define M_MWINDOWWID 512
#define M_MWINDOWHEI 384

// Define menu items
#if 1 
	#define MENU_FILE_TITLE "File"
	#define MENU_FILE_NEW 0
	#define MENU_FILE_NEW_T "New Project"
	#define MENU_FILE_OPENPROJ 1
	#define MENU_FILE_OPENPROJ_T "Open Project"
	#define MENU_FILE_OPENIMG 2
	#define MENU_FILE_OPENIMG_T "Open Image"
	#define MENU_FILE_SAVE 3
	#define MENU_FILE_SAVE_T "Save"
	#define MENU_FILE_SAVEAS 4
	#define MENU_FILE_SAVEAS_T "Save As"
	#define MENU_FILE_QUIT 6
	#define MENU_FILE_QUIT_T "Quit"
	#define MENU_FILE_TOTAL 7

	#define MENU_EDIT_TITLE "Edit"
	#define MENU_EDIT_UNDO 0
	#define MENU_EDIT_UNDO_T "Undo"
	#define MENU_EDIT_REDO 1
	#define MENU_EDIT_REDO_T "Redo"
	#define MENU_EDIT_TOTAL 2
	
	#define MENU_HELP_TITLE "Help"
	#define MENU_HELP_HELP 0
	#define MENU_HELP_HELP_T "Help"
	#define MENU_HELP_ABOUT 1
	#define MENU_HELP_ABOUT_T "About"
	#define MENU_HELP_TOTAL 2
#endif

// Define toolbar items
#if 1
#define TOOLBAR_TEST1 0
#define TOOLBAR_TEST1_T "Test 1"
#define TOOLBAR_TEST1_I	"../res/icons/test.png"
#define TOOLBAR_TEST2 1
#define TOOLBAR_TEST2_T "Test 2"
#define TOOLBAR_TEST2_I	"../res/icons/test.png"
#define TOOLBAR_TEST3 3
#define TOOLBAR_TEST3_T "Test 3"
#define TOOLBAR_TEST3_I	"../res/icons/test.png"
#define TOOLBAR_TOTAL 4
#endif

void InitMainWindow(MMainWindow& appMain, QApplication& app);

QMenu* InitFileMenu();

QMenu* InitEditMenu();

QMenu* InitHelpMenu();

QToolBar* InitToolBar();