#include "dialogdetalle.h"

dialogDetalle::dialogDetalle(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

dialogDetalle::~dialogDetalle()
{

}

void dialogDetalle::tablaDetalle(int fila,QString dato1,QString dato2,QString dato3){
	ui.tableWidget->insertRow(ui.tableWidget->rowCount());
	QTableWidgetItem *itemid1 = new QTableWidgetItem;
	QTableWidgetItem *itemid2 = new QTableWidgetItem;
	QTableWidgetItem *itemid3 = new QTableWidgetItem;
	itemid1->setText(dato1);
	itemid2->setText(dato2);
	itemid3->setText(dato3);
	ui.tableWidget->setItem(fila,0,itemid1);
	ui.tableWidget->setItem(fila,1,itemid2);
	ui.tableWidget->setItem(fila,2,itemid3);
}