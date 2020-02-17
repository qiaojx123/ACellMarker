#pragma once

#include "QtWidgets/qapplication.h"
#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qmainwindow.h"
#include "QtWidgets/qdockwidget.h"
#include "QtCore/qlist.h"
#include "QtCore/qjsondocument.h"

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

class DockMarkList : public QDockWidget
{
Q_OBJECT
public:

private:
	QList<Marking>* markList;
};

class MainWidget : public QWidget
{
Q_OBJECT
public slots:
//	void openProj(const QString& path);
	void newProj();
signals:
	void titleChanged(const QString& newTitle);
	void projOpened(bool open);
public:
	MainWidget() : projTitle(""), isEdited(false) {};

private:
	QString projTitle;
	bool isEdited;
	QJsonDocument project;
	QList<Marking> markList;
};