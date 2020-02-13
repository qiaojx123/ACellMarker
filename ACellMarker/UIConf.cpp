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

	QWidget* centralWidget = new QWidget();
	appMain.setCentralWidget(centralWidget);
	centralWidget->setGeometry(0, 0, 400, 400);

	QPushButton* button = new QPushButton();
	button->setText("aaa");
	button->setParent(centralWidget);

	QToolBar* appToolBar = new QToolBar("MainToolBar",nullptr);
	appMain.addToolBar(Qt::LeftToolBarArea,appToolBar);
	appToolBar->setAllowedAreas(Qt::LeftToolBarArea);
	appToolBar->setIconSize(QSize(M_ICONSIZE, M_ICONSIZE));
	appToolBar->setMinimumWidth(M_ICONSIZE);
	appToolBar->setMaximumWidth(2 * M_ICONSIZE + M_ICONSPACE);
	appToolBar->setMovable(false);
	appToolBar->setOrientation(Qt::Vertical);
	appToolBar->addAction(QIcon("../res/icons/test.png"), "Test Icon");
	appToolBar->addAction(QIcon("../res/icons/test.png"), "Test Icon2");
	appToolBar->addSeparator();
	appToolBar->addAction(QIcon("../res/icons/test.png"), "Test Icon3");
	appToolBar->addAction(QIcon("../res/icons/test.png"), "Test Icon4");

}
