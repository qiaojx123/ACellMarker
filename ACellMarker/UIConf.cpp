#include "UIConf.h"

void InitMainWindow(QMainWindow& appMain, QApplication& app)
{
	appMain.setMinimumSize(QSize(M_MWINDOWWID, M_MWINDOWHEI));

	QMenuBar* appMenuBar;
	appMenuBar = appMain.menuBar();

	QMenu *fileMenu, *editMenu, *helpMenu;

	//Init file menu.
	fileMenu = InitFileMenu();
	appMenuBar->addMenu(fileMenu);
	QObject::connect(fileMenu->actions().at(MENU_FILE_QUIT), SIGNAL(triggered()), &app, SLOT(quit()));

	//Init edit menu.
	editMenu = InitEditMenu();
	appMenuBar->addMenu(editMenu);

	//Init help Menu.
	helpMenu = InitHelpMenu();
	appMenuBar->addMenu(helpMenu);

	MainWidget* centralWidget = new MainWidget();
	appMain.setCentralWidget(centralWidget);
	centralWidget->setMinimumSize(M_MWINDOWWID - M_ICONSIZE, M_MWINDOWHEI);
	QObject::connect(fileMenu->actions().at(MENU_FILE_NEW), SIGNAL(triggered()), centralWidget, SLOT(newProj()));
	//Todo: Change the application title to "ACellMarker - Untitled.acproj*" when user new a project

	// Enable open image and save/saveas when a project is created.
	QObject::connect(centralWidget, SIGNAL(projOpened(bool)), fileMenu->actions().at(MENU_FILE_OPENIMG), SLOT(setEnabled(bool)));
	QObject::connect(centralWidget, SIGNAL(projOpened(bool)), fileMenu->actions().at(MENU_FILE_SAVE), SLOT(setEnabled(bool)));
	QObject::connect(centralWidget, SIGNAL(projOpened(bool)), fileMenu->actions().at(MENU_FILE_SAVEAS), SLOT(setEnabled(bool)));

	QPushButton* button = new QPushButton();
	button->setText("aaa");
	button->setParent(centralWidget);
	button->hide();

	QToolBar* appToolBar;
	appToolBar = InitToolBar();
	appMain.addToolBar(Qt::LeftToolBarArea, appToolBar);
	QObject::connect(appToolBar->actions().at(TOOLBAR_TEST3), SIGNAL(triggered()), &app, SLOT(quit()));

	QStatusBar* appStatusBar;

	QFileDialog* openDialog;
	openDialog = InitOpenDialog();
	// Use exec() instead of show() to block other windows
	QObject::connect(fileMenu->actions().at(MENU_FILE_OPENPROJ), SIGNAL(triggered()), openDialog, SLOT(exec()));
	
	QObject::connect(openDialog, SIGNAL(fileSelected(const QString&)), button, SLOT(setToolTip(const QString&)));
	QObject::connect(openDialog, SIGNAL(accepted()), button, SLOT(show()));
}

QMenu* InitFileMenu()
{
	QMenu* fileMenu = new QMenu();
	std::string menulist[MENU_FILE_TOTAL];
	menulist[MENU_FILE_NEW		] = MENU_FILE_NEW_T;
	menulist[MENU_FILE_OPENPROJ	] = MENU_FILE_OPENPROJ_T;
	menulist[MENU_FILE_OPENIMG	] = MENU_FILE_OPENIMG_T;
	menulist[MENU_FILE_QUIT		] = MENU_FILE_QUIT_T;
	menulist[MENU_FILE_SAVE		] = MENU_FILE_SAVE_T;
	menulist[MENU_FILE_SAVEAS	] = MENU_FILE_SAVEAS_T;

	fileMenu->setTitle(MENU_FILE_TITLE);
	for (int i = 0; i < MENU_FILE_TOTAL; ++i)
		if (menulist[i] == "") fileMenu->addSeparator();
		else fileMenu->addAction(menulist[i].c_str());

	fileMenu->actions().at(MENU_FILE_OPENIMG)->setDisabled(true);
	fileMenu->actions().at(MENU_FILE_SAVE)->setDisabled(true);
	fileMenu->actions().at(MENU_FILE_SAVEAS)->setDisabled(true);

	return fileMenu;
}

QMenu* InitEditMenu()
{
	QMenu* editMenu = new QMenu();
	std::string menulist[MENU_EDIT_TOTAL];
	menulist[MENU_EDIT_UNDO] = MENU_EDIT_UNDO_T;
	menulist[MENU_EDIT_REDO] = MENU_EDIT_REDO_T;

	editMenu->setTitle(MENU_EDIT_TITLE);
	for (int i = 0; i < MENU_EDIT_TOTAL; ++i)
		if (menulist[i] == "") editMenu->addSeparator();
		else editMenu->addAction(menulist[i].c_str());

	editMenu->actions().at(MENU_EDIT_UNDO)->setDisabled(true);
	editMenu->actions().at(MENU_EDIT_REDO)->setDisabled(true);

	return editMenu;
}

QMenu* InitHelpMenu()
{
	QMenu* helpMenu = new QMenu();
	std::string menulist[MENU_HELP_TOTAL];
	menulist[MENU_HELP_HELP	] = MENU_HELP_HELP_T;
	menulist[MENU_HELP_ABOUT] = MENU_HELP_ABOUT_T;

	helpMenu->setTitle(MENU_HELP_TITLE);
	for (int i = 0; i < MENU_HELP_TOTAL; ++i)
		if (menulist[i] == "") helpMenu->addSeparator();
		else helpMenu->addAction(menulist[i].c_str());

	return helpMenu;
}

QToolBar* InitToolBar()
{
	QToolBar* toolBar = new QToolBar();
	std::string toollist[TOOLBAR_TOTAL], iconlist[TOOLBAR_TOTAL];
	toollist[TOOLBAR_TEST1] = TOOLBAR_TEST1_T;
	toollist[TOOLBAR_TEST2] = TOOLBAR_TEST2_T;
	toollist[TOOLBAR_TEST3] = TOOLBAR_TEST3_T;
	iconlist[TOOLBAR_TEST1] = TOOLBAR_TEST1_I;
	iconlist[TOOLBAR_TEST2] = TOOLBAR_TEST2_I;
	iconlist[TOOLBAR_TEST3] = TOOLBAR_TEST3_I;

	toolBar->setAllowedAreas(Qt::LeftToolBarArea);
	toolBar->setIconSize(QSize(M_ICONSIZE, M_ICONSIZE));
	toolBar->setMinimumWidth(M_ICONSIZE);
	toolBar->setMaximumWidth(2 * M_ICONSIZE + M_ICONSPACE);
	toolBar->setMovable(false);
	toolBar->setOrientation(Qt::Vertical);

	for (int i = 0; i < TOOLBAR_TOTAL; ++i)
		if (toollist[i] == "") toolBar->addSeparator();
		else toolBar->addAction(QIcon(iconlist[i].c_str()), toollist[i].c_str());
	return toolBar;
}

QFileDialog* InitOpenDialog()
{
	QFileDialog* openDialog = new QFileDialog();
	openDialog->hide();
	openDialog->setAcceptMode(QFileDialog::AcceptOpen);
	openDialog->setViewMode(QFileDialog::Detail);
	openDialog->setFileMode(QFileDialog::ExistingFile);
	openDialog->setNameFilter("ACellMarker Project File (*.acproj)");
	return openDialog;
}