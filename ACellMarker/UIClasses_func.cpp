#include "UIClasses.h"

void MainWidget::newProj()
{
	if (isEdited) {
		// show dialog that leads to save
	}
	// close the previous images and project file

	// open a new project and change title
	projTitle = "Untitled.acproj";
	emit titleChanged(projTitle);
	emit projOpened(true);
	QApplication::setApplicationDisplayName(projTitle);
}