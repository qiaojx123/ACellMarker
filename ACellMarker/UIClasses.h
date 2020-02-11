#pragma once

#include "QtWidgets/qapplication.h"
#include "QtWidgets/qpushbutton.h"

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