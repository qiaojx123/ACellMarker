#include "UIClasses.h"
#include <iostream>

void MMainWindow::changeWindowTitle(const QString& newname, bool edited)
{
	if (newname == "") {
		setWindowTitle("ACellMarker");
		return;
	}
	if (edited) setWindowTitle(QString("ACellMarker - ").append(newname).append("*"));
	else setWindowTitle(QString("ACellMarker - ").append(newname));
	return;
}

/* Here begins the functions for ACProject.
 *
*/
bool ACProject::newProj()
{
	if (isEdited) {
		// show dialog that leads to save
		switch (saveOrDiscard())
		{
		case QMessageBox::Save:
			if (!saveProj()) {
				return false;
			}
		case QMessageBox::Discard:
			break;
		case QMessageBox::Cancel:
			return false;
		default:
			// Some thing is wrong!
			return false;
			break;
		}
	}
	// close the previous image
	emit imagePathChanged("");

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
	return true;
}

bool ACProject::openProj()
{
	QString fileName;
	fileName = QFileDialog::getOpenFileName(nullptr, "Open Project", projPath, "ACellMarker Project File (*.acproj)");

	QFile readFile(fileName);
	readFile.open(QIODevice::ReadOnly | QIODevice::Text);
	if (!readFile.isOpen()) {
		// Opening is canceled. Or something went wrong.
		return false;
	}

	if (isEdited) {
		// show dialog that leads to save
		switch (saveOrDiscard())
		{
		case QMessageBox::Save:
			if (!saveProj()) {
				return false;
			}
		case QMessageBox::Discard:
			break;
		case QMessageBox::Cancel:
			return false;
		default:
			// Some thing is wrong!
			return false;
			break;
		}
	}

	if (!fromByteArray(readFile.readAll())){
		// The file is not complete, or something else is wrong.
		// Maybe should initialize the app to opening no project......?
		projName = "";
		projPath = "";
		projImgPath = "";
		markList.clear();
		emit projEdited(false);
		emit projOpened(false);
		emit titleChanged(projName, false);
		emit imagePathChanged("");
		return false;
	}
	else {
		projPath = fileName.toStdString().substr(0, fileName.toStdString().find_last_of("\\/") + 1).c_str();
	}

	// Send signals
	isEdited = false;
	emit projEdited(false);
	emit projOpened(true);
	emit titleChanged(projName, false);
	emit imagePathChanged(projImgPath);
	return true;
}

bool ACProject::openImage()
{
	QString fileName;
	fileName = QFileDialog::getOpenFileName(nullptr, "Open Image", projPath, "Tiff Image File (*.tiff)");
	if (fileName == "") {
		return false;
	}
	
	projImgPath = fileName;

	// close the previous image
	emit imagePathChanged(fileName);

	// Send signals
	if (!isEdited) {
		isEdited = true;
		emit projEdited(true);
		emit titleChanged(projName, true);
	}
	return true;
}

bool ACProject::saveProj()
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
			return false;
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
		return false;
	}
	writeFile.write(toByteArray());
	writeFile.close();

	// Send signals
	isEdited = false;
	emit projEdited(false);
	emit titleChanged(projName, false);
	return true;
}

bool ACProject::saveProjAs()
{
	QString oldname(projName), oldpath(projPath);
	QString fileName;
	fileName = QFileDialog::getSaveFileName(nullptr, "Save Project As", projPath, "ACellMarker Project File (*.acproj)");
	std::string path, name;
	path = fileName.toStdString();
	int lastFolder = path.find_last_of("\\/");
	if (lastFolder == std::string::npos) {
		//Something must have been wrong...
		return false;
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
		return false;
	}
	writeFile.write(toByteArray());
	writeFile.close();

	// Send signals
	isEdited = false;
	emit projEdited(false);
	emit titleChanged(projName, false);
	return true;
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
	QVariantMap info;
	info["projName"] = QVariant(projName);
	info["imagePath"] = QVariant(projImgPath);

	QJsonArray markings;
	int l, r, t, b;
	for (int i = 0; i < markList.size(); ++i) {
		QString markTag;
		QVariantMap mark;
		markList[i].getBbox(l, r, t, b);
		markList[i].getTag(markTag);

		QJsonArray bbox;
		bbox.push_back(QJsonValue(l)); 
		bbox.push_back(QJsonValue(r)); 
		bbox.push_back(QJsonValue(t)); 
		bbox.push_back(QJsonValue(b));
		mark["bbox"] = bbox;
		mark["id"] = i;
		mark["tag"] = markTag;
		markings.push_back(QJsonObject::fromVariantMap(mark));
	}
	info["markings"] = markings;

	QJsonObject infoObj;
	infoObj = QJsonObject::fromVariantMap(info);

	QJsonDocument outDoc;
	outDoc.setObject(infoObj);

	return outDoc.toJson();
}

bool ACProject::fromByteArray(QByteArray input)
{
	QJsonDocument info;
	QJsonParseError err;
	info = QJsonDocument::fromJson(input, &err);

	if (info.isNull()) {
		std::cout<<err.errorString().toStdString();
		return false;
	}

	projName = info["projName"].toString();
	projImgPath = info["imagePath"].toString();
	QJsonArray markings;
	markings = info["markings"].toArray();
	markList.clear();
	for (int i = 0; i < markings.size(); ++i) {
		QJsonObject mark = markings[i].toObject();
		QJsonArray bbox = mark["bbox"].toArray();
		markList.push_back(Marking(bbox[0].toInt(), bbox[1].toInt(), bbox[2].toInt(), bbox[3].toInt(), mark["tag"].toString()));
	}
	if (0) {
		// To do: deal with wrong inputs.
	}

	return true;
}

int ACProject::saveOrDiscard()
{
	QMessageBox msgBox;
	msgBox.setText("The project has been edited.");
	msgBox.setInformativeText("Do you want to save the changes?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	return msgBox.exec();
}