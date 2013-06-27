#ifndef DIALOGDETALLE_H
#define DIALOGDETALLE_H

#include <QWidget>
#include "ui_dialogdetalle.h"

class dialogDetalle : public QWidget
{
	Q_OBJECT

public:
	dialogDetalle(QWidget *parent = 0);
	~dialogDetalle();
	void tablaDetalle(int fila,QString dato1,QString dato2,QString dato3);

private:
	Ui::dialogDetalle ui;
};

#endif // DIALOGDETALLE_H
