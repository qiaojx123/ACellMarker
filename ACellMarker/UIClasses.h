#pragma once

#include "QtWidgets/qapplication.h"
#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qmainwindow.h"
#include "QtWidgets/qdockwidget.h"
#include "QtCore/qlist.h"
#include "QtCore/qjsonobject.h"
#include "QtCore/qjsondocument.h"
#include "QtWidgets/qfiledialog.h"

class ExampleButton : public QPushButton
{
Q_OBJECT
public slots:
	void changeState() {
		if (shown) {
			hide();
			emit counterDecrease();
		}
		else show();
		shown = !shown;
	}
	void counterDecrease() {
		buttonCounter = buttonCounter > 0 ? buttonCounter - 1 : 0;
		if (buttonCounter == 0) emit counterReached();
	}
signals:
	void counterReached();
public:
	ExampleButton() : buttonCounter(0), shown(true) {}
	int counter() { return buttonCounter; }
	void setCounter(int x) { buttonCounter = x; }
	bool isShown() { return shown; }
private:
	int buttonCounter;
	bool shown;
};

class Marking
{
public:
	Marking() : leftEdge(0), rightEdge(0), bottomEdge(0), topEdge(0), mark(""), valid(false) {}
	Marking(const int left, const int right, const int top, const int bottom) : leftEdge(left), rightEdge(right), topEdge(top), bottomEdge(bottom), mark("Default"), valid(true) {};
	Marking(const int left, const int right, const int top, const int bottom, const QString mark) : leftEdge(left), rightEdge(right), topEdge(top), bottomEdge(bottom), mark(mark), valid(true) {};
	void setBbox(const int left, const int right, const int top, const int bottom) { leftEdge = left, rightEdge = right, topEdge = top, bottomEdge = bottom; }
	bool getBbox(int& left, int& right, int& top, int& bottom) const { left = leftEdge, right = rightEdge, top = topEdge, bottom = bottomEdge; }
	void setMark(const QString mark) { this->mark = mark; }
	bool getMark(QString& mark) const { if (valid) mark = this->mark; return valid; }
	int getArea() const { return (rightEdge - leftEdge) * (bottomEdge - topEdge); }
private:
	int leftEdge, topEdge, rightEdge, bottomEdge;
	QString mark;
	bool valid;
};

class MMainWindow : public QMainWindow
{
Q_OBJECT
public slots:
	void changeWindowTitle(const QString& newname, bool edited);
};

class DockMarkList : public QDockWidget
{
Q_OBJECT
public:

private:
	QList<Marking>* markList;
};

class ACProject : public QObject
{
Q_OBJECT
public slots:
	void newProj();
	void openProj(const QString);
	void saveProj();
	void saveProjAs();
	void setProjName(const QString);
	void setProjPath(const QString);
	void setImgPath(const QString);
signals:
	void titleChanged(const QString&, bool);
	void projEdited(bool);
	void projOpened(bool);
	void openFailed();
public:
	ACProject() : projName(""), projPath(""), projImgPath(""), isEdited(false) {}
	ACProject(QString path);
	bool getProjName(QString& name) const;
	bool getProjPath(QString& path) const;
	bool getImgPath(QString& path) const;
	void addMark2List(const Marking mark);
	int delMarkinList(const Marking mark);
	QByteArray toByteArray();
private:
	QString projName, projPath, projImgPath;
	QList<Marking> markList;
	bool isEdited;
	//Todo: ¼ÇÂ¼Undo¡¢RedoÊý¾Ý¡£
};

class MainWidget : public QWidget
{
Q_OBJECT
public slots:

signals:

public:
	MainWidget(ACProject* project) :proj(project) {};
	ACProject* project() { return proj; }
private:
	ACProject* proj;
};