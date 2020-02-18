#include "UIClasses.h"

void MMainWindow::changeWindowTitle(const QString& newname, bool edited)
{
	if (newname == "") {
		setWindowTitle("ACellMarker");
		return;
	}
	if (edited) setWindowTitle(QString("ACellMarker - ").append(newname).append("*"));
	else setWindowTitle(QString("ACellMakrer - ").append(newname));
	return;
}

/* Here begins the functions for ACProject.
 *
*/
void ACProject::newProj()
{
	if (isEdited) {
		// show dialog that leads to save
	}
	// close the previous images and project file

	// open a new project and change title
	projName = "Untitled.acproj";
	projPath = "";
	projImgPath = "";
	isEdited = true;
	markList.clear();

	// Send signals
	emit titleChanged(projName, isEdited);
	emit projEdited(isEdited);
	emit projOpened(true);
}

void ACProject::openProj(const QString)
{

}

void ACProject::saveProj()
{
	QString oldname(projName), oldpath(projPath);
	if (projPath == "") {
		// Select somewhere to save it.
		QString fileName;
		fileName = QFileDialog::getSaveFileName(nullptr, "Save Project", projPath, "ACellMarker Project File (*.acproj)");
		std::string path, name;
		path = fileName.toStdString();
		int lastFolder = path.find_last_of("\\/");
		if (lastFolder == std::string::npos) {
			//Something must have been wrong...
			return;
		}
		name = path.substr(lastFolder + 1);
		path = path.substr(0, lastFolder + 1);

		projName = name.c_str();
		projPath = path.c_str();
	}
	// Save changes
	QFile writeFile(projPath + projName);
	writeFile.open(QIODevice::WriteOnly | QIODevice::Text);
	if (!writeFile.isOpen()) {
		//Something must have been wrong...
		projName = oldname;
		projPath = oldpath;
		return;
	}
	writeFile.write(toByteArray());
	writeFile.close();

	// Send signals
	isEdited = false;
	emit projEdited(false);
	emit titleChanged(projName, false);
}

void ACProject::saveProjAs()
{
	QString oldname(projName), oldpath(projPath);
	QString fileName;
	fileName = QFileDialog::getSaveFileName(nullptr, "Save Project", projPath, "ACellMarker Project File (*.acproj)");
	std::string path, name;
	path = fileName.toStdString();
	int lastFolder = path.find_last_of("\\/");
	if (lastFolder == std::string::npos) {
		//Something must have been wrong...
		return;
	}
	name = path.substr(lastFolder + 1);
	path = path.substr(0, lastFolder + 1);

	projName = name.c_str();
	projPath = path.c_str();

	QFile writeFile(projPath + projName);
	writeFile.open(QIODevice::WriteOnly | QIODevice::Text);
	if (!writeFile.isOpen()) {
		//Something must have been wrong...
		projName = oldname;
		projPath = oldpath;
		return;
	}
	writeFile.write(toByteArray());
	writeFile.close();

	// Send signals
	isEdited = false;
	emit projEdited(false);
	emit titleChanged(projName, false);
}

// This will send a signal to change the window title.
void ACProject::setProjName(const QString name)
{
	projName = name;
	emit titleChanged(projName, false);
}

void ACProject::setProjPath(const QString path)
{
	projPath = path;
}

void ACProject::setImgPath(const QString)
{

}

QByteArray ACProject::toByteArray()
{
	//Todo: 将标记信息添加到输出中
	QVariantMap info;
	info["projName"] = QVariant(projName);
	info["imagePath"] = QVariant(projImgPath);

	QJsonObject infoObj;
	infoObj = QJsonObject::fromVariantMap(info);

	QJsonDocument outDoc;
	outDoc.setObject(infoObj);

	return outDoc.toJson();
}