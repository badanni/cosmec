/********************************************************************************
** Form generated from reading UI file 'dialogdetalle.ui'
**
** Created: Wed 26. Jun 21:52:16 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDETALLE_H
#define UI_DIALOGDETALLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogDetalle
{
public:
    QTableWidget *tableWidget;
    QLabel *label;

    void setupUi(QWidget *dialogDetalle)
    {
        if (dialogDetalle->objectName().isEmpty())
            dialogDetalle->setObjectName(QString::fromUtf8("dialogDetalle"));
        dialogDetalle->resize(590, 393);
        dialogDetalle->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"background:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(193, 197, 255, 255), stop:0.130682 rgba(228, 228, 245, 255), stop:0.528409 rgba(255, 255, 255, 255));\n"
"border: 1px solid black;\n"
"} \n"
"QFrame {\n"
" border: 1px inset gray;\n"
" border-radius: 5px;\n"
" background:  transparent;\n"
"}\n"
"\n"
"QLabel {/*titulos de p\303\241g*/\n"
"border: 1px inset gray;\n"
"font: bold 12pt \"Calibri\";\n"
"background:#68778e;\n"
"color:white;\n"
"qproperty-alignment: AlignCenter\n"
"}\n"
"QTableWidget {\n"
" background: transparent;\n"
" color: black;\n"
" font:10pt \"Calibri\";\n"
" text-align: center;\n"
" gridline-color: rgb(165, 165, 165);\n"
"}\n"
".QPushButton {\n"
"background: qlineargradient(\n"
"  x1:0, y1:0, x2:0, y2:1,\n"
"  stop:0 #68778e,\n"
"  stop: 0.4 #5c637d\n"
"  stop: 0.5 #717990,\n"
"  stop:1 #bec1d2\n"
" );\n"
" color: white;\n"
"}\n"
".QPushButton:pressed {\n"
"background: qlineargradient(\n"
"  x1:0, y1:0, x2:0, y2:1,\n"
"  stop:0 #68778e,\n"
"  stop: 0.4 "
                        "#5c637d\n"
"  stop: 0.5 #717990,\n"
"  stop:1 #bec1d2\n"
" );\n"
" color: black;\n"
"}\n"
".QPushButton:checked {\n"
" color: black;\n"
"}\n"
"\n"
"QLineEdit {\n"
"     border: 1px inset darkblue;\n"
"     border-radius: 5px;\n"
"     background:white;\n"
"     selection-background-color: darkgray;\n"
" }"));
        tableWidget = new QTableWidget(dialogDetalle);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(90, 70, 431, 261));
        tableWidget->horizontalHeader()->setDefaultSectionSize(140);
        tableWidget->verticalHeader()->setVisible(false);
        label = new QLabel(dialogDetalle);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 571, 21));

        retranslateUi(dialogDetalle);

        QMetaObject::connectSlotsByName(dialogDetalle);
    } // setupUi

    void retranslateUi(QWidget *dialogDetalle)
    {
        dialogDetalle->setWindowTitle(QApplication::translate("dialogDetalle", "Detalle de Componente de Cotizaci\303\263n", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("dialogDetalle", "\303\215tem", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("dialogDetalle", "Descripci\303\263n", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("dialogDetalle", "Costo hora", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dialogDetalle", "Detalle", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dialogDetalle: public Ui_dialogDetalle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDETALLE_H
