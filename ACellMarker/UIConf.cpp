#include "UIConf.h"

void InitMainWindow(QMainWindow& appMain, QApplication& app)
{
	appMain.setMinimumSize(QSize(512, 384));
	
	QMenuBar* appMenuBar;
	appMenuBar = appMain.menuBar();

	QMenu *fileMenu, *editMenu;
	fileMenu = appMenuBar->addMenu("File");
	fileMenu->addAction("Open");
	fileMenu->addAction("Save");
	fileMenu->addAction("Save As");
	fileMenu->addSeparator();
	fileMenu->addAction("Quit");
	QObject::connect(fileMenu->actions().at(4), SIGNAL(triggered()), &app, SLOT(quit()));

	editMenu = appMenuBar->addMenu("Edit");
	editMenu->addAction("Undo");
	editMenu->addAction("Redo");
}
