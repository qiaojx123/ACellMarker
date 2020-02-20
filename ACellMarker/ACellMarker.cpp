#include <iostream>
#include "UIClasses.h"
#include "UIConf.h"

int main(int argc, char** argv)
{
	QApplication::setLibraryPaths(QStringList("../QtLibs/plugins"));
	QApplication app(argc,argv);
	

	MMainWindow appMainWindow;
	InitMainWindow(appMainWindow, app);
	appMainWindow.show();

	QObject::connect(&appMainWindow, SIGNAL(destroyed()), &app, SLOT(quit()));
	return app.exec();

/*	//Example
	QApplication app(argc,argv);
	QWidget window;
	QPushButton parentButton;
	ExampleButton childButton;
	window.setMinimumSize(QSize(500, 250));

	parentButton.setParent(&window);
	parentButton.setGeometry(10, 10, 300, 150);
	parentButton.setText("A pretty button");

	childButton.setParent(&parentButton);
	childButton.setGeometry(20, 20, 100, 30);
	childButton.setText("child");
	childButton.setCounter(3);

	window.show();

	QObject::connect(&parentButton, SIGNAL(clicked()), &childButton, SLOT(changeState()));
	QObject::connect(&childButton, SIGNAL(counterReached()), &parentButton, SLOT(hide()));
	return app.exec();
*/
}