#include "cosmec.h"

int filaEdit=-1;
bool comboH=false,comboG=false;

struct repcot {
	int id;
	QString maquina;
	int costo;
};
cosmec::cosmec(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	QImage espe("espe.png");
	ui.label_8->setPixmap(QPixmap::fromImage(espe));
	ui.label_8->setScaledContents(true);

	QImage mecanica("lmecanica.jpg");
	ui.label_9->setPixmap(QPixmap::fromImage(mecanica));
	ui.label_9->setScaledContents(true);

	ui.stackedWidget->setCurrentIndex(0);
	
	//Parametros Base de datos
	QFile file("in.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		QMessageBox msgBox;
		msgBox.setText("Error al cargar configuracion de conexion host, se coloca como default localhost");
		msgBox.exec();
		host="localhost";
		pass2 ="merlin";
		usuario="postgres";
		puerto="5432";
		iva=0.12;
		vcomp=0.3;
	}else{
		QTextStream stream(&file);
		host = stream.readLine();
		pass2 = stream.readLine();
		usuario=stream.readLine();
		puerto=stream.readLine();
		iva=(QString(stream.readLine()).toDouble())/100;
		vcomp=0.3;
		ui.ip->setText(host);
		ui.usuario->setText(usuario);
		ui.passw->setText(pass2);
		ui.port->setText(puerto);
		ui.lineEdit_7->setText(QString::number(iva*100));
	}
	conexion();
	connect(ui.actionConfiguracion, SIGNAL(triggered()),this, SLOT(setconfig()));
    connect(ui.editconfig,SIGNAL(toggled(bool)),this,SLOT(configurar()));
    connect(ui.cargarconfig, SIGNAL(clicked()),this, SLOT(conexion()));
	connect(ui.actionExportar_a_PDF,SIGNAL(triggered()),this,SLOT(setgenerador()));
	connect(ui.actionExportar_a_Exel,SIGNAL(triggered()),this,SLOT(setreporteexel()));
	//cotizacion
	//connect(ui.comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(combocotizacion(int)));
	//connect(ui.comboBox_5,SIGNAL(currentIndexChanged(int)),this,SLOT(combocotizacion2(int)));
	//reportes
	connect(ui.genreport,SIGNAL(clicked()),this,SLOT(reportgenerador()));
	connect(ui.pushButton_31,SIGNAL(clicked()),this,SLOT(reporteexel()));
	
	//desplegar pantallas de menú
	connect(ui.actionMaquina, SIGNAL(triggered()),this, SLOT(setmaquina()));
	connect(ui.actionHerramientas, SIGNAL(triggered()),this, SLOT(setherramienta()));
	connect(ui.actionConsumibles, SIGNAL(triggered()),this, SLOT(setconsumible()));
	connect(ui.actionConsumo_de_Energia, SIGNAL(triggered()),this, SLOT(setenergia()));
	connect(ui.actionMantenimiento, SIGNAL(triggered()),this, SLOT(setmantenimiento()));
	connect(ui.actionMano_de_Obra, SIGNAL(triggered()),this, SLOT(setmanoobra()));
	connect(ui.actionActividades, SIGNAL(triggered()),this, SLOT(setactividades()));
    connect(ui.actionMano_de_Obra_2, SIGNAL(triggered()),this, SLOT(setactividadesMo()));
	connect(ui.actionNueva, SIGNAL(triggered()),this, SLOT(setnuevaCotizacion()));
	connect(ui.actionBuscar, SIGNAL(triggered()),this, SLOT(setbuscarCotizacion()));
	connect(ui.actionMateriales, SIGNAL(triggered()),this, SLOT(setmateriales()));
	connect(ui.actionReportes_de_cotizaciones,SIGNAL(triggered()),this,SLOT(setrptcotizaciones()));
	connect(ui.actionServicios_Externos, SIGNAL(triggered()),this, SLOT(setServiciosExternos()));

	//mano de obra - cargos
	connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(agregarfila())); //boton +
	connect(ui.pushButton_5,SIGNAL(toggled(bool)),this,SLOT(actualizar())); //boton editar estados
	connect(ui.pushButton_2,SIGNAL(clicked()),this,SLOT(eliminarFila())); //boton -
	connect(ui.tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditable(int,int))); //boton editar accion

	//mano de obra - actividades
	connect(ui.pushButton_4,SIGNAL(clicked()),this,SLOT(agregarfilaMo())); //boton +
	connect(ui.pushButton_6,SIGNAL(toggled(bool)),this,SLOT(actualizarMo())); //boton editar estados
	connect(ui.pushButton_3,SIGNAL(clicked()),this,SLOT(eliminarFilaMo())); //boton -
	connect(ui.tableWidget_2,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableMo(int,int))); //boton editar accion

	//maquina
	connect(ui.pushButton_22,SIGNAL(clicked()),this,SLOT(agregarfilaMaq())); //boton +
	connect(ui.pushButton_23,SIGNAL(toggled(bool)),this,SLOT(actualizarMaq())); //boton editar estados
	connect(ui.pushButton_24,SIGNAL(clicked()),this,SLOT(eliminarFilaMaq())); //boton -
	connect(ui.tableWidget_3,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableMaq(int,int))); //boton editar accion

	//servicios externos
	connect(ui.pushButton_37,SIGNAL(clicked()),this,SLOT(agregarfilaSExternos())); //boton +
	connect(ui.pushButton_32,SIGNAL(toggled(bool)),this,SLOT(actualizarSExternos())); //boton editar estados
	connect(ui.pushButton_33,SIGNAL(clicked()),this,SLOT(eliminarFilaSExternos())); //boton -
	connect(ui.tableWidget_15,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableSExternos(int,int))); //boton editar accion

	//materiales
	connect(ui.pushButton_44,SIGNAL(clicked()),this,SLOT(agregarfilaMat())); //boton +
	connect(ui.pushButton_41,SIGNAL(toggled(bool)),this,SLOT(actualizarMat())); //boton editar estados
	connect(ui.pushButton_43,SIGNAL(clicked()),this,SLOT(eliminarFilaMat())); //boton -
	connect(ui.tableWidget_14,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableMat(int,int))); //boton editar accion
	
	//herramientas
	connect(ui.pushButton_27,SIGNAL(clicked()),this,SLOT(agregarfilaHe())); //boton +
	connect(ui.pushButton_25,SIGNAL(toggled(bool)),this,SLOT(actualizarHe())); //boton editar estados
	connect(ui.pushButton_26,SIGNAL(clicked()),this,SLOT(eliminarFilaHe())); //boton -
	connect(ui.tableWidget_4,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableHe(int,int))); //boton editar accion

	//consumibles
	connect(ui.pushButton_29,SIGNAL(clicked()),this,SLOT(agregarfilaCons())); //boton +
	connect(ui.pushButton_30,SIGNAL(toggled(bool)),this,SLOT(actualizarCons())); //boton editar estados
	connect(ui.pushButton_28,SIGNAL(clicked()),this,SLOT(eliminarFilaCons())); //boton -
	connect(ui.tableWidget_5,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableCons(int,int))); //boton editar accion

	//servicios básicos
	connect(ui.pushButton_8,SIGNAL(clicked()),this,SLOT(agregarfilaSer())); //boton +
	connect(ui.pushButton_9,SIGNAL(toggled(bool)),this,SLOT(actualizarSer())); //boton editar estados
	connect(ui.pushButton_7,SIGNAL(clicked()),this,SLOT(eliminarFilaSer())); //boton -
	connect(ui.tableWidget_6,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableSer(int,int))); //boton editar accion
	
	//mtto - insumos
	connect(ui.pushButton_15,SIGNAL(clicked()),this,SLOT(agregarfilaMtto())); //boton +
	connect(ui.pushButton_14,SIGNAL(toggled(bool)),this,SLOT(actualizarMtto())); //boton editar estados
	connect(ui.pushButton_13,SIGNAL(clicked()),this,SLOT(eliminarFilaMtto())); //boton -
	connect(ui.tableWidget_7,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableMtto(int,int))); //boton editar accion

	//mtto - preventivo y correctivo
	//connect(ui.pushButton_11,SIGNAL(clicked()),this,SLOT(agregarfilaPrev())); //boton +
	//connect(ui.pushButton_10,SIGNAL(toggled(bool)),this,SLOT(actualizarPrev())); //boton editar estados
	//connect(ui.pushButton_12,SIGNAL(clicked()),this,SLOT(eliminarFilaPrev())); //boton -
	//connect(ui.tableWidget_8,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditablePrev(int,int))); //boton editar accion

	//actividades - categorías
	connect(ui.pushButton_16,SIGNAL(clicked()),this,SLOT(agregarfilaActC())); //boton +
	connect(ui.pushButton_18,SIGNAL(toggled(bool)),this,SLOT(actualizarActC())); //boton editar estados
	connect(ui.pushButton_17,SIGNAL(clicked()),this,SLOT(eliminarFilaActC())); //boton -
	connect(ui.tableWidget_9,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableActC(int,int))); //boton editar accion

	//actividades - actividades
	connect(ui.pushButton_20,SIGNAL(clicked()),this,SLOT(agregarfilaActAct())); //boton +
	connect(ui.pushButton_19,SIGNAL(toggled(bool)),this,SLOT(actualizarActAct())); //boton editar estados
	connect(ui.pushButton_21,SIGNAL(clicked()),this,SLOT(eliminarFilaActAct())); //boton -
	connect(ui.tableWidget_10,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableActAct(int,int))); //boton editar accion
	
	//actividades - Maquina
	connect(ui.pushButton_39,SIGNAL(clicked()),this,SLOT(agregarfilaMaqActividades())); //boton +
	//connect(ui.pushButton_40,SIGNAL(toggled(bool)),this,SLOT(actualizarMaqActividades())); //boton editar estados
	connect(ui.pushButton_38,SIGNAL(clicked()),this,SLOT(eliminarFilaMaqActividades())); //boton -
	connect(ui.tableWidget_13,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(filaEditableMaqActividades(int,int))); //boton editar accion

	//buscar cotización
	connect(ui.radioButton,SIGNAL(clicked()),this,SLOT(habilitarBuscarCotizacion()));
	connect(ui.radioButton_2,SIGNAL(clicked()),this,SLOT(habilitarBuscarRuc()));
	connect(ui.pushButton_36,SIGNAL(clicked()),this,SLOT(buscarCotizacion()));
	connect(ui.commandLinkButton_2,SIGNAL(clicked()),this,SLOT(resultadoCotizacion()));
	connect(ui.pushButton_35,SIGNAL(clicked()),this,SLOT(detalle()));
	connect(ui.commandLinkButton_4,SIGNAL(clicked()),this,SLOT(imprimirCotizacion()));
	//nueva cotización
	/*connect(ui.pushButton_32,SIGNAL(clicked()),this,SLOT(sumarHerramienta()));
	connect(ui.pushButton_33,SIGNAL(clicked()),this,SLOT(sumarConsumible()));*/
	connect(ui.pushButton_34,SIGNAL(clicked()),this,SLOT(eliminarPrimeraCotizacion()));
	connect(ui.commandLinkButton,SIGNAL(clicked()),this,SLOT(segundaParte()));
	connect(ui.pushButton_71,SIGNAL(clicked()),this,SLOT(sumarMaq()));
	connect(ui.pushButton_72,SIGNAL(clicked()),this,SLOT(sumarActividad()));
	connect(ui.pushButton_73,SIGNAL(clicked()),this,SLOT(sumarMo()));
	//connect(ui.pushButton_37,SIGNAL(clicked()),this,SLOT(eliminarSegundaCotizacion()));
	//connect(ui.commandLinkButton_3,SIGNAL(clicked()),this,SLOT(terminarCotizacion()));
	//connect(ui.pushButton_42,SIGNAL(clicked()),this,SLOT(cancelarCotizacion()));
	connect(ui.pushButton_74,SIGNAL(clicked()),this,SLOT(sumarServExt()));
	connect(ui.pushButton_93,SIGNAL(clicked()),this,SLOT(sumarMaterial()));

}

cosmec::~cosmec()
{

}
void cosmec::comboMaq(QTableWidget *tableNum,int fil, int col){
	comboMaquina=new QComboBox(this);
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec("SELECT a.serie,a.modelo FROM maquinas AS a ORDER BY a.modelo");
	record = respuesta.record();
	tamquery1=respuesta.size();
	idmaquinas=new int[tamquery1];
	int fila=0;
	while(respuesta.next()){
		QString uno;
		idmaquinas[fila]=respuesta.value(0).toInt();
		uno=respuesta.value(1).toString();
		comboMaquina->addItem(uno);
		fila++;
	}
	tableNum->setCellWidget(fil,col,comboMaquina);
	
}
void cosmec::comboCat(QTableWidget *tableNum,int fil, int col){
	comboCategoria=new QComboBox(this);
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec("SELECT a.id_categoria_actividades,a.nombre FROM categoria_actividades AS a ORDER BY a.nombre");
	record = respuesta.record();
	tamquery1=respuesta.size();
	idactividades=new int[tamquery1];
	int fila=0;
	while(respuesta.next()){
		QString uno;
		idactividades[fila]=respuesta.value(0).toInt();
		uno=respuesta.value(1).toString();
		comboCategoria->addItem(uno);
		fila++;
	}
	tableNum->setCellWidget(fil,col,comboCategoria);
}
void cosmec::comboCargo(QTableWidget *tableNum,int fil, int col){
	comboCarg=new QComboBox(this);
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec("SELECT a.id_cargo,a.nombre FROM cargo AS a ORDER BY a.nombre");
	record = respuesta.record();
	tamquery1=respuesta.size();
	idcargo=new int[tamquery1];
	int fila=0;
	while(respuesta.next()){
		QString uno;
		idcargo[fila]=respuesta.value(0).toInt();
		uno=respuesta.value(1).toString();
		comboCarg->addItem(uno);
		fila++;
	}
	tableNum->setCellWidget(fil,col,comboCarg);
}

void cosmec::comboActividades(QTableWidget *tableNum,int fil, int col){
	comboAct=new QComboBox(this);
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec("SELECT c.id_actividad, c.nombre FROM actividades_trabajo AS c ORDER BY id_actividad");
	record = respuesta.record();
	tamquery1=respuesta.size();
	idact=new int[tamquery1];
	int fila=0;
	while(respuesta.next()){
		QString uno;
		idact[fila]=respuesta.value(0).toInt();
		uno=respuesta.value(1).toString();
		comboAct->addItem(uno);
		qDebug()<<idact[fila];
		fila++;
	}
	tableNum->setCellWidget(fil,col,comboAct);
	cosmecdb.close();
}
void cosmec::comboinsumos(QTableWidget *tableNum,int fil, int col){
	comboInsumo=new QComboBox(this);
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec("SELECT a.id_insumo, a.nombre FROM insumos AS a ORDER BY a.id_insumo");
	record = respuesta.record();
	tamquery1=respuesta.size();
	idinsumocombo=new int[tamquery1];
	int fila=0;
	while(respuesta.next()){
		QString uno;
		idinsumocombo[fila]=respuesta.value(0).toInt();
		uno=respuesta.value(1).toString();
		comboInsumo->addItem(uno);
		fila++;
	}
	tableNum->setCellWidget(fil,col,comboInsumo);
}
//mano de obra - cargos
void cosmec::filaEditable(int row,int column)
{
	bool actChecked=ui.pushButton_5->isChecked();
	bool ultF= (row+1)==ui.tableWidget->rowCount();
	
	if(actChecked&&filaEdit==-1){ //para saber q fila
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
	}

	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFila()
{
	QString sql;
	int currentRow=ui.tableWidget->currentRow();
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget->item(currentRow,0);
		int id=QString(itab1->text()).toInt();
		sql=QString("DELETE FROM cargo WHERE id_cargo=%1").arg(id);
		insertarsql(sql);
		sql="SELECT a.id_cargo,a.nombre,a.salario FROM cargo AS a";
		llenartabla(ui.tableWidget,sql);
		comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
	}
}
void cosmec::actualizar()
{
	if(ui.pushButton_5->isChecked()){
		ui.pushButton_5->setText("Guardar");
		ui.pushButton->setEnabled(false);
		ui.pushButton_2->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		QString sql;
		QTableWidgetItem *itab1 = ui.tableWidget->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget->item(filaEdit,2);
		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false))){
			int id=QString(itab1->text()).toInt();
			QString nombre=itab2->text();
			double salario=QString(itab3->text()).toDouble();
			sql=QString("UPDATE cargo SET nombre='%1', salario=%2 "
				"WHERE id_cargo=%3").arg(nombre).arg(salario).arg(id);
			insertarsql(sql);
			sql="SELECT a.id_cargo,a.nombre,a.salario FROM cargo AS a";
			llenartabla(ui.tableWidget,sql);
			comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_5->setText("Actualizar");
		ui.pushButton->setEnabled(true);
		ui.pushButton_2->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfila(){
	const int currentRow =ui.tableWidget->rowCount();  
	QTableWidgetItem *itab2 = ui.tableWidget->item(currentRow-1,1);
	QTableWidgetItem *itab3 = ui.tableWidget->item(currentRow-1,2);
	QString sql;
	if(currentRow!=0){	
		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false))||(currentRow==0)){
		
			QString nombre=itab2->text();
			double salario=QString(itab3->text()).toDouble();
			sql=QString("INSERT INTO cargo(nombre, salario)"
				"VALUES ('%1',%2)").arg(nombre).arg(salario);
			insertarsql(sql);
			sql="SELECT a.id_cargo,a.nombre,a.salario FROM cargo AS a";
			llenartabla(ui.tableWidget,sql);
			comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_2->insertRow(currentRow);
		comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
	}
}

//maquinaria
void cosmec::filaEditableMaq(int row,int column)
{
	bool actChecked=ui.pushButton_23->isChecked();
	bool ultF= (row+1)==ui.tableWidget_3->rowCount();
	
	if(actChecked&&filaEdit==-1){ //para saber q fila
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		ui.tableWidget_3->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaMaq()
{
	int currentRow=ui.tableWidget_3->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_3->item(currentRow,0);
		sql=QString("DELETE FROM maquinas WHERE serie=%1").arg(itab1->text());
		insertarsql(sql);
		sql="SELECT a.serie,a.modelo,a.costo,a.vida_util,a.horas_trabajo_anual,a.deprecicacion,a.costo_hora,a.presupuesto_anual FROM maquinas AS a";
		llenartabla(ui.tableWidget_3,sql);
	}
	
}
void cosmec::actualizarMaq()
{
	if(ui.pushButton_23->isChecked()){
		ui.pushButton_23->setText("Guardar");
		ui.pushButton_22->setEnabled(false);
		ui.pushButton_24->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		QString sql;
		QTableWidgetItem *itab1 = ui.tableWidget_3->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_3->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_3->item(filaEdit,2);
		QTableWidgetItem *itab4 = ui.tableWidget_3->item(filaEdit,3);
		QTableWidgetItem *itab5 = ui.tableWidget_3->item(filaEdit,4);
		QTableWidgetItem *itab6 = ui.tableWidget_3->item(filaEdit,5);
		QTableWidgetItem *itab7 = ui.tableWidget_3->item(filaEdit,6);
		QTableWidgetItem *itab8 = ui.tableWidget_3->item(filaEdit,7);
		if (((itab1!=0&& itab1->text().isEmpty()==false) && (itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false)  && (itab5!=0&& itab5->text().isEmpty()==false) && (itab8!=0&& itab8->text().isEmpty()==false))){
			QString serie=itab1->text();
			QString modelo=itab2->text();
			QString costo=itab3->text();
			QString vida=itab4->text();
			QString horas=itab5->text();
			double depre=QString(costo).toDouble()/QString(vida).toDouble();
			double costo_hora=(2*QString(costo).toDouble())/(QString(horas).toDouble()*QString(vida).toDouble());
			QString presu=itab8->text();
		    sql=QString("UPDATE maquinas SET modelo='%2',costo=%3,vida_util=%4,horas_trabajo_anual=%5,deprecicacion=%6,costo_hora=%7,presupuesto_anual=%8 WHERE serie=%1").arg(serie.toInt()).arg(modelo).arg(costo.toDouble()).arg(vida.toInt()).arg(horas.toInt()).arg(depre).arg(costo_hora).arg(presu.toDouble());
			qDebug()<<sql;
			insertarsql(sql);
			sql="SELECT a.serie,a.modelo,a.costo,a.vida_util,a.horas_trabajo_anual,a.deprecicacion,a.costo_hora,a.presupuesto_anual FROM maquinas AS a ORDER BY a.modelo";
			llenartabla(ui.tableWidget_3,sql);
		}
			//-------------------------
		filaEdit=-1;
		comboH=false;
		ui.pushButton_23->setText("Actualizar");
		ui.pushButton_22->setEnabled(true);
		ui.pushButton_24->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaMaq(){
	const int currentRow =ui.tableWidget_3->rowCount();
	if(currentRow!=0){
		QTableWidgetItem *itab1 = ui.tableWidget_3->item(currentRow-1,0);
		QTableWidgetItem *itab2 = ui.tableWidget_3->item(currentRow-1,1);
		QTableWidgetItem *itab3 = ui.tableWidget_3->item(currentRow-1,2);
		QTableWidgetItem *itab4 = ui.tableWidget_3->item(currentRow-1,3);
		QTableWidgetItem *itab5 = ui.tableWidget_3->item(currentRow-1,4);
		QTableWidgetItem *itab6 = ui.tableWidget_3->item(currentRow-1,5);
		QTableWidgetItem *itab7 = ui.tableWidget_3->item(currentRow-1,6);
		QTableWidgetItem *itab8 = ui.tableWidget_3->item(currentRow-1,7);
	    
		if (((itab1!=0&& itab1->text().isEmpty()==false) && (itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false) && (itab5!=0&& itab5->text().isEmpty()==false) && (itab8!=0&& itab8->text().isEmpty()==false))||(currentRow==0)){
			QString sql;
			QString serie=itab1->text();
			QString modelo=itab2->text();
			QString costo=itab3->text();
			QString vida=itab4->text();
			QString horas=itab5->text();
			double depre=QString(costo).toDouble()/QString(vida).toDouble();
			double costo_hora=(2*QString(costo).toDouble())/(QString(horas).toDouble()*QString(vida).toDouble());
			QString presu=itab8->text();
			sql=QString("INSERT INTO maquinas (serie,modelo,costo,vida_util,horas_trabajo_anual,deprecicacion,costo_hora,presupuesto_anual) VALUES (%1,'%2',%3,%4,%5,%6,%7,%8)").arg(serie.toInt()).arg(modelo).arg(costo.toDouble()).arg(vida.toInt()).arg(horas.toInt()).arg(depre).arg(costo_hora).arg(presu.toDouble());
			insertarsql(sql);
			sql="SELECT a.serie,a.modelo,a.costo,a.vida_util,a.horas_trabajo_anual,a.deprecicacion,a.costo_hora,a.presupuesto_anual FROM maquinas AS a";
			llenartabla(ui.tableWidget_3,sql);
			
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_3->insertRow(currentRow);
	}
}



//servicios externos
void cosmec::filaEditableSExternos(int row,int column)
{
	bool actChecked=ui.pushButton_32->isChecked();
	bool ultF= (row+1)==ui.tableWidget_15->rowCount();

	if(actChecked&&filaEdit==-1){ //para saber q fila
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		ui.tableWidget_15->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_15->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaSExternos()
{
	int currentRow=ui.tableWidget_15->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_15->item(currentRow,0);
		sql=QString("DELETE FROM servicios_externos	WHERE id_servicios=%1").arg(itab1->text());
		insertarsql(sql);
		sql="SELECT id_servicios, nombre_srevicio, costo_hora FROM servicios_externos";
		llenartabla(ui.tableWidget_15,sql);
		
	}

}
void cosmec::actualizarSExternos()
{
	if(ui.pushButton_32->isChecked()){
		ui.pushButton_32->setText("Guardar");
		ui.pushButton_33->setEnabled(false);
		ui.pushButton_37->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		QString sql;
		QTableWidgetItem *itab1 = ui.tableWidget_15->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_15->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_15->item(filaEdit,2);

		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false))){
			QString idSEx=itab1->text();
			QString nombre=itab2->text();
			double costo=QString(itab3->text()).toDouble();
			
			sql=QString("UPDATE servicios_externos SET nombre_srevicio='%1', costo_hora=%2"
				" WHERE id_servicios=%3").arg(nombre).arg(costo).arg(idSEx);
			insertarsql(sql);
			sql="SELECT id_servicios, nombre_srevicio, costo_hora FROM servicios_externos";
			llenartabla(ui.tableWidget_15,sql);
			
		}
		//-------------------------
		filaEdit=-1;
		comboH=false;
		ui.pushButton_32->setText("Actualizar");
		ui.pushButton_37->setEnabled(true);
		ui.pushButton_33->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaSExternos(){
	const int currentRow =ui.tableWidget_15->rowCount();
	if(currentRow!=0){
		QTableWidgetItem *itab1 = ui.tableWidget_15->item(currentRow-1,0);
		QTableWidgetItem *itab2 = ui.tableWidget_15->item(currentRow-1,1);
		QTableWidgetItem *itab3 = ui.tableWidget_15->item(currentRow-1,2);


		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false))||(currentRow==0)){
			QString sql;
			//QString idSEx=itab1->text();
			QString nombre=itab2->text();
			double costo=QString(itab3->text()).toDouble();

			sql=QString("INSERT INTO servicios_externos(nombre_srevicio, costo_hora)"
				" VALUES ('%1',%2)").arg(nombre).arg(costo);
			insertarsql(sql);
			sql="SELECT id_servicios,nombre_srevicio, costo_hora FROM servicios_externos";
			llenartabla(ui.tableWidget_15,sql);
			

		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_15->insertRow(currentRow);
	}
}


//materiales
void cosmec::filaEditableMat(int row,int column)
{
	bool actChecked=ui.pushButton_41->isChecked();
	bool ultF= (row+1)==ui.tableWidget_14->rowCount();

	if(actChecked&&filaEdit==-1){ //para saber q fila
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		ui.tableWidget_14->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_14->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaMat()
{
	int currentRow=ui.tableWidget_14->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_14->item(currentRow,0);
		sql=QString("DELETE FROM materiales WHERE id_material=%1").arg(itab1->text());
		insertarsql(sql);
		sql="SELECT id_material, nombre, geometria, dimencion, costo"
			" FROM materiales";
		llenartabla(ui.tableWidget_14,sql);
	}

}
void cosmec::actualizarMat()
{
	if(ui.pushButton_41->isChecked()){
		ui.pushButton_41->setText("Guardar");
		ui.pushButton_44->setEnabled(false);
		ui.pushButton_43->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		QString sql;
		QTableWidgetItem *itab1 = ui.tableWidget_14->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_14->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_14->item(filaEdit,2);
		QTableWidgetItem *itab4 = ui.tableWidget_14->item(filaEdit,3);
		QTableWidgetItem *itab5 = ui.tableWidget_14->item(filaEdit,4);
		if (((itab1!=0&& itab1->text().isEmpty()==false) &&(itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false) && (itab5!=0&& itab5->text().isEmpty()==false))){
			QString id=itab1->text();
			QString material=itab2->text();
			QString geometria=itab3->text();
			QString dimensiones=itab4->text();
			QString costo=itab5->text();
			sql=QString("UPDATE materiales SET  nombre='%1', geometria='%2', dimencion='%3', costo=%4 "
				"WHERE id_material=%5").arg(material).arg(geometria).arg(dimensiones).arg(costo).arg(id);
			insertarsql(sql);
			sql="SELECT id_material, nombre, geometria, dimencion, costo"
				" FROM materiales";
			llenartabla(ui.tableWidget_14,sql);
		}
		//-------------------------
		filaEdit=-1;
		comboH=false;
		ui.pushButton_41->setText("Actualizar");
		ui.pushButton_43->setEnabled(true);
		ui.pushButton_44->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaMat(){
	const int currentRow =ui.tableWidget_14->rowCount();

	if(currentRow!=0){
		QTableWidgetItem *itab2 = ui.tableWidget_14->item(currentRow-1,1);
		QTableWidgetItem *itab3 = ui.tableWidget_14->item(currentRow-1,2);
		QTableWidgetItem *itab4 = ui.tableWidget_14->item(currentRow-1,3);
		QTableWidgetItem *itab5 = ui.tableWidget_14->item(currentRow-1,4);

		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false) && (itab5!=0&& itab5->text().isEmpty()==false))||(currentRow==0)){
			QString sql;
			QString material=itab2->text();
			QString geometria=itab3->text();
			QString dimensiones=itab4->text();
			QString costo=itab5->text();
			sql=QString("INSERT INTO materiales(nombre, geometria, dimencion, costo)"
				"VALUES ('%1','%2','%3',%4)").arg(material).arg(geometria).arg(dimensiones).arg(costo);
			insertarsql(sql);
			sql="SELECT id_material, nombre, geometria, dimencion, costo"
			" FROM materiales";
			llenartabla(ui.tableWidget_14,sql);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_14->insertRow(currentRow);
	}
}
//
//herramientas
void cosmec::filaEditableHe(int row,int column)
{
	bool actChecked=ui.pushButton_25->isChecked();
	bool ultF= (row+1)==ui.tableWidget_4->rowCount();
	
	if(actChecked&&filaEdit==-1){ //para saber q fila
		filaEdit=row;
	}
		
	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){ //validar fila editable
		if(actChecked&&column==7){
			comboH=true; //para saber si hay combo
			comboMaq(ui.tableWidget_4,row,7);
		}
		ui.tableWidget_4->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaHe()
{
	int currentRow=ui.tableWidget_4->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_4->item(currentRow,0);
		sql=QString("DELETE FROM herramientas WHERE id_herramienta=%1").arg(itab1->text());
		insertarsql(sql);
		QString sql="SELECT a.id_herramienta,a.nombre_herramienta,a.cantidad_anual,a.costo_unitario,a.vida_util,a.depreciacion,a.costo_hora,b.modelo FROM maquinas AS b,herramientas AS a WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
		llenartabla(ui.tableWidget_4,sql);
		if(ui.tableWidget_4->rowCount()!=0){
			comboMaq(ui.tableWidget_4,ui.tableWidget_4->rowCount()-1,7);
		}
	}
}
void cosmec::actualizarHe()
{
	int id;
	QString sql;
	if(ui.pushButton_25->isChecked()){
		ui.pushButton_25->setText("Guardar");
		ui.pushButton_27->setEnabled(false);
		ui.pushButton_26->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{	
		//quitar combobox y poner texto
		QTableWidgetItem *itab1 = ui.tableWidget_4->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_4->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_4->item(filaEdit,2);
		QTableWidgetItem *itab4 = ui.tableWidget_4->item(filaEdit,3);
		QTableWidgetItem *itab5 = ui.tableWidget_4->item(filaEdit,4);
		//datos
		if ((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false) && (itab5!=0&& itab5->text().isEmpty()==false)){
			int id_herramiento=QString(itab1->text()).toInt();
			if(comboH){
				QComboBox* anterio=(QComboBox*)ui.tableWidget_4->cellWidget(filaEdit,7);
				id=idmaquinas[anterio->currentIndex()];
			}else{
				id=sql_herramienta(id_herramiento,9).toInt();
			}
			
			QString nombre=itab2->text();
			int cantidad=QString(itab3->text()).toInt();
			double costo=QString(itab4->text()).toDouble();
			int vida=QString(itab5->text()).toInt();
			int hora=sql_maquina(id,4).toInt();
			double costo_cant=costo*cantidad;
			//calculos
			double depre=costo_cant/vida;
			double costo_hora=costo_cant/hora;
			double depre_hora=depre/hora;
			double costo_total=costo_hora+depre_hora;
			sql=QString("UPDATE herramientas SET nombre_herramienta='%1', costo_unitario=%2, vida_util=%3,depreciacion=%4, valor_hora=%5, depreciacion_hora=%6, costo_hora=%7,cantidad_anual=%8,serie_maquinas=%9 WHERE id_herramienta=%10").arg(nombre).arg(costo).arg(vida).arg(depre).arg(costo_hora).arg(depre_hora).arg(costo_total).arg(cantidad).arg(id).arg(id_herramiento);
			qDebug()<<sql;
			insertarsql(sql);
			QString sql="SELECT a.id_herramienta,a.nombre_herramienta,a.cantidad_anual,a.costo_unitario,a.vida_util,a.depreciacion,a.costo_hora,b.modelo FROM maquinas AS b,herramientas AS a WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
			llenartabla(ui.tableWidget_4,sql);
			comboMaq(ui.tableWidget_4,ui.tableWidget_4->rowCount()-1,7);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_25->setText("Actualizar");
		ui.pushButton_27->setEnabled(true);
		ui.pushButton_26->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaHe(){
	const int currentRow =ui.tableWidget_4->rowCount();
	//verificar que no esté vacío
	QTableWidgetItem *itab2 = ui.tableWidget_4->item(currentRow-1,1);
	QTableWidgetItem *itab3 = ui.tableWidget_4->item(currentRow-1,2);
	QTableWidgetItem *itab4 = ui.tableWidget_4->item(currentRow-1,3);
	QTableWidgetItem *itab5 = ui.tableWidget_4->item(currentRow-1,4);
	if(currentRow!=0){	
		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false) && (itab5!=0&& itab5->text().isEmpty()==false))||(currentRow==0)){
			//quitar combobox y poner texto
			QComboBox* anterio=(QComboBox*)ui.tableWidget_4->cellWidget(currentRow-1,7);
			QString sql;
			//datos
			int fila=anterio->currentIndex();
			QString nombre=itab2->text();
			int cantidad=QString(itab3->text()).toInt();
			double costo=QString(itab4->text()).toDouble();
			int vida=QString(itab5->text()).toInt();
			int horas=sql_maquina(idmaquinas[fila],4).toInt();
			double costo_cant=costo*cantidad;
			//calculos
			double depre=(costo_cant/vida);
			double unitario_hora=(costo_cant/horas);
			double depre_hora=depre/horas;
			double costo_total=unitario_hora+depre_hora;
			sql=QString("INSERT INTO herramientas(nombre_herramienta,costo_unitario,vida_util,depreciacion,valor_hora,depreciacion_hora,costo_hora,cantidad_anual,serie_maquinas) VALUES ('%1',%2,%3,%4,%5,%6,%7,%8,%9)").arg(nombre).arg(costo).arg(vida).arg(depre).arg(unitario_hora).arg(depre_hora).arg(costo_total).arg(cantidad).arg(idmaquinas[fila]);
			insertarsql(sql);
			sql="SELECT a.id_herramienta,a.nombre_herramienta,a.cantidad_anual,a.costo_unitario,a.vida_util,a.depreciacion,a.costo_hora,b.modelo FROM maquinas AS b,herramientas AS a WHERE a.serie_maquinas=b.serie ORDER BY b.model";
			llenartabla(ui.tableWidget_4,sql);
			comboMaq(ui.tableWidget_4,ui.tableWidget_4->rowCount()-1,7);
		}
		else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_4->insertRow(currentRow);
		comboMaq(ui.tableWidget_4,ui.tableWidget_4->rowCount()-1,7);
	}
}

//consumibles
void cosmec::filaEditableCons(int row,int column)
{
	bool actChecked=ui.pushButton_30->isChecked();
	bool ultF= (row+1)==ui.tableWidget_5->rowCount();

	if(actChecked&&filaEdit==-1){
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		if(actChecked&&column==5){
			comboH=true;
			comboMaq(ui.tableWidget_5,row,5);
		}
		ui.tableWidget_5->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaCons()
{
	int currentRow=ui.tableWidget_5->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_5->item(currentRow,0);
		sql=QString("DELETE FROM consumible WHERE id_consumible=%1").arg(itab1->text());
		insertarsql(sql);
		QString sql="SELECT a.id_consumible,a.nombre_consumible,a.cantidad_anual,a.costo_unitario,a.costo_hora,b.modelo FROM maquinas AS b,consumible AS a WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
		llenartabla(ui.tableWidget_5,sql);
		if(ui.tableWidget_5->rowCount()!=0){
			comboMaq(ui.tableWidget_5,ui.tableWidget_5->rowCount()-1,5);
		}
	}
}
void cosmec::actualizarCons()
{
	int id;
	QString sql;
	if(ui.pushButton_30->isChecked()){
		ui.pushButton_30->setText("Guardar");
		ui.pushButton_29->setEnabled(false);
		ui.pushButton_28->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		//quitar combobox y poner texto
		QTableWidgetItem *itab1 = ui.tableWidget_5->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_5->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_5->item(filaEdit,2);
		QTableWidgetItem *itab4 = ui.tableWidget_5->item(filaEdit,3);
		//datos
		if((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false)){
			int id_consumible=QString(itab1->text()).toInt();
			if(comboH){
				QComboBox* anterio=(QComboBox*)ui.tableWidget_5->cellWidget(filaEdit,5);
				id=idmaquinas[anterio->currentIndex()];
			}else{
				id=sql_consumibles(id_consumible,5).toInt();
			}
			QString nombre=itab2->text();
			int cantidad=QString(itab3->text()).toInt();
			double costo=QString(itab4->text()).toDouble();
			int horas=sql_maquina(id,4).toInt();
			double costo_cant=costo*cantidad;
			qDebug()<<horas;
			//calculos
			double costo_hora=costo_cant/horas;
			sql=QString("UPDATE consumible SET nombre_consumible='%1', costo_unitario=%2, costo_hora=%3, cantidad_anual=%4, " 
				"serie_maquinas=%5 WHERE id_consumible=%6").arg(nombre).arg(costo).arg(costo_hora).arg(cantidad).arg(id).arg(id_consumible);
			insertarsql(sql);
			sql="SELECT a.id_consumible,a.nombre_consumible,a.cantidad_anual,a.costo_unitario,a.costo_hora,b.modelo FROM maquinas AS b,consumible AS a WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
			llenartabla(ui.tableWidget_5,sql);
			comboMaq(ui.tableWidget_5,ui.tableWidget_5->rowCount()-1,5);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_30->setText("Actualizar");
		ui.pushButton_29->setEnabled(true);
		ui.pushButton_28->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaCons(){
	const int currentRow =ui.tableWidget_5->rowCount();  
	QTableWidgetItem *itab2 = ui.tableWidget_5->item(currentRow-1,1);
	QTableWidgetItem *itab3 = ui.tableWidget_5->item(currentRow-1,2);
	QTableWidgetItem *itab4 = ui.tableWidget_5->item(currentRow-1,3);
	if(currentRow!=0){
		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab4!=0&& itab4->text().isEmpty()==false))||(currentRow==0)){
			//quitar combobox y poner texto
			QComboBox* anterio=(QComboBox*)ui.tableWidget_5->cellWidget(currentRow-1,5);
			QString sql;
			//datos
			int fila=anterio->currentIndex();
			QString nombre=itab2->text();
			int cantidad=QString(itab3->text()).toInt();
			double costo=QString(itab4->text()).toDouble();
			int horas=sql_maquina(idmaquinas[fila],4).toInt();
			double costo_cant=costo*cantidad;
			//calculos
			double costo_hora=costo_cant/horas;
			sql=QString("INSERT INTO consumible(nombre_consumible, costo_unitario, costo_hora,cantidad_anual," 
				"serie_maquinas) VALUES ('%1',%2,%3,%4,%5)").arg(nombre).arg(costo).arg(costo_hora).arg(cantidad).arg(idmaquinas[fila]);
			insertarsql(sql);
			sql="SELECT a.id_consumible,a.nombre_consumible,a.cantidad_anual,a.costo_unitario,a.costo_hora,b.modelo FROM maquinas AS b,consumible AS a WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
			llenartabla(ui.tableWidget_5,sql);
			comboMaq(ui.tableWidget_5,ui.tableWidget_5->rowCount()-1,5);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();	
		}
	}else{
		ui.tableWidget_5->insertRow(currentRow);
		comboMaq(ui.tableWidget_5,ui.tableWidget_5->rowCount()-1,5);
	}
}
//servicios básicos
void cosmec::filaEditableSer(int row,int column)
{
	bool actChecked=ui.pushButton_9->isChecked();
	bool ultF= (row+1)==ui.tableWidget_6->rowCount();

	if(actChecked&&filaEdit==-1){
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		if(actChecked&&column==0)
		{
			comboH=true;
			comboMaq(ui.tableWidget_6,row,0);
		}
		ui.tableWidget_6->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_6->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaSer()
{
	int currentRow=ui.tableWidget_6->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		sql=QString("DELETE FROM agua WHERE serie_maquinas=%1").arg(idmaquinas[currentRow]);
		insertarsql(sql);
		sql=QString("DELETE FROM energia WHERE serie_maquinas=%1").arg(idmaquinas[currentRow]);
		insertarsql(sql);
		QString sql="SELECT c.modelo,a.consumo,a.costo_consumo,a.costo_energia,b.consumo_anual,b.costo_consumo,b.consumo_hora,b.costo_hora  FROM energia AS a, agua AS b, maquinas AS c WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie ORDER BY c.modelo";
		llenartabla(ui.tableWidget_6,sql);
		llenartabla(ui.tableWidget_6,sql);
		if(ui.tableWidget_6->rowCount()!=0){
			comboMaq(ui.tableWidget_6,ui.tableWidget_6->rowCount()-1,0);
		}
	}
}
void cosmec::actualizarSer()
{
	QString sql;
	if(ui.pushButton_9->isChecked()){
		ui.pushButton_9->setText("Guardar");
		ui.pushButton_8->setEnabled(false);
		ui.pushButton_7->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		int id;
		QTableWidgetItem *itab2 = ui.tableWidget_6->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_6->item(filaEdit,2);
		QTableWidgetItem *itab5 = ui.tableWidget_6->item(filaEdit,4);
		QTableWidgetItem *itab6 = ui.tableWidget_6->item(filaEdit,5);
		if ((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab5!=0&& itab5->text().isEmpty()==false) && (itab6!=0&& itab6->text().isEmpty()==false)){
			int id_agua=idagua[filaEdit];
			int id_energia=idenergia[filaEdit];
			if(comboH){
				QComboBox* anterio=(QComboBox*)ui.tableWidget_6->cellWidget(filaEdit,0);
				id=idmaquinas[anterio->currentIndex()];
			}else{
				sql=QString("SELECT * FROM agua WHERE id_agua=%1").arg(id_agua);
				id=sql_general(sql,5).toInt();
			}
			//datos
			int horas=sql_maquina(id,4).toInt();
			//datos energia
			double consumo_energi=QString(itab2->text()).toDouble();
			double uni_energia=QString(itab3->text()).toDouble();
			//datos agua
			double consumo_agua=QString(itab5->text()).toDouble();
			double uni_agua=QString(itab6->text()).toDouble();
			//calculos
			double costo_energia=consumo_energi*uni_energia;
			double hora_agua=consumo_agua/horas;
			double costo_agua=hora_agua*uni_agua;
			sql=QString("UPDATE energia	SET consumo=%1, costo_consumo=%2, costo_energia=%3, serie_maquinas=%4"
				" WHERE id_energia=%5").arg(consumo_energi).arg(uni_energia).arg(costo_energia).arg(id).arg(id_energia);
			insertarsql(sql);
			sql=QString("UPDATE agua SET consumo_anual=%1, costo_consumo=%2, consumo_hora=%3,costo_hora=%4, serie_maquinas=%5"
				" WHERE id_agua=%6").arg(consumo_agua).arg(uni_agua).arg(hora_agua).arg(costo_agua).arg(id).arg(id_agua);
			insertarsql(sql);
			sql="SELECT c.modelo,a.consumo,a.costo_consumo,a.costo_energia,b.consumo_anual,b.costo_consumo,b.costo_hora  FROM energia AS a, agua AS b, maquinas AS c WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie ORDER BY c.modelo";
			llenartabla(ui.tableWidget_6,sql);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_9->setText("Actualizar");
		ui.pushButton_8->setEnabled(true);
		ui.pushButton_7->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaSer(){
	const int currentRow =ui.tableWidget_6->rowCount();  
	QTableWidgetItem *itab2 = ui.tableWidget_6->item(currentRow-1,1);
	QTableWidgetItem *itab3 = ui.tableWidget_6->item(currentRow-1,2);
	QTableWidgetItem *itab5 = ui.tableWidget_6->item(currentRow-1,4);
	QTableWidgetItem *itab6 = ui.tableWidget_6->item(currentRow-1,5);
	
	if(currentRow!=0){
		if (((itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false) && (itab5!=0&& itab5->text().isEmpty()==false) && (itab6!=0&& itab6->text().isEmpty()==false))||(currentRow==0)){
			//quitar combobox y poner texto
			QComboBox* anterio=(QComboBox*)ui.tableWidget_6->cellWidget(currentRow-1,0);
			QString sql;
			//datos
			int fila=anterio->currentIndex();
			int horas=sql_maquina(idmaquinas[fila],4).toInt();
			//datos energia
			double consumo_energi=QString(itab2->text()).toDouble();
			double uni_energia=QString(itab3->text()).toDouble();
			//datos agua
			double consumo_agua=QString(itab5->text()).toDouble();
			double uni_agua=QString(itab6->text()).toDouble();
			//calculos
			double costo_energia=consumo_energi*uni_energia;
			double hora_agua=consumo_agua/horas;
			double costo_agua=hora_agua*uni_agua;
			sql=QString("INSERT INTO energia(consumo, costo_consumo, costo_energia, serie_maquinas)"
				"VALUES (%1,%2,%3,%4)").arg(consumo_energi).arg(uni_energia).arg(costo_energia).arg(idmaquinas[fila]);
			insertarsql(sql);
			sql=QString("INSERT INTO agua(consumo_anual, costo_consumo, consumo_hora, costo_hora," 
				"serie_maquinas) VALUES (%1,%2,%3,%4,%5)").arg(consumo_agua).arg(uni_agua).arg(hora_agua).arg(costo_agua).arg(idmaquinas[fila]);
			insertarsql(sql);
			sql="SELECT c.modelo,a.consumo,a.costo_consumo,a.costo_energia,b.consumo_anual,b.costo_consumo,b.costo_hora  FROM energia AS a, agua AS b, maquinas AS c WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie ORDER BY c.modelo";
			llenartabla(ui.tableWidget_6,sql);
			comboMaq(ui.tableWidget_6,ui.tableWidget_6->rowCount()-1,0);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_6->insertRow(currentRow);
		comboMaq(ui.tableWidget_6,ui.tableWidget_6->rowCount()-1,0);
	}
}

//mtto insumos
void cosmec::filaEditableMtto(int row,int column)
{
	bool actChecked=ui.pushButton_14->isChecked();
	bool ultF= (row+1)==ui.tableWidget_7->rowCount();

	if(actChecked&&filaEdit==-1){
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		if(actChecked&&column==5)
		{
			comboH=true;
			comboMaq(ui.tableWidget_7,row,5);
		}
		ui.tableWidget_7->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_7->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaMtto()
{
	int currentRow=ui.tableWidget_7->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		sql=QString("DELETE FROM mantenimiento_preventivo"
			" WHERE id_insumo=%1").arg(idinsumo[currentRow]);
		insertarsql(sql);

		QString sql="SELECT a.nombre, a.costo_unitario, a.cantidad_anual, "
			"a.valor_total, a.costo_hora, b.modelo FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
		llenartabla(ui.tableWidget_7,sql);
		llenartabla(ui.tableWidget_7,sql);
		cargaridinsumo();

		sql="SELECT SUM(a.costo_hora) AS suma_prev, b.presupuesto_anual, b.presupuesto_anual/b.horas_trabajo_anual AS costo_hora,(b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora)), b.modelo AS costo_total FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie GROUP BY b.serie ORDER BY b.modelo";
		llenartabla(ui.tableWidget_8,sql);
		llenartabla(ui.tableWidget_8,sql);
		if(ui.tableWidget_7->rowCount()!=0){
			comboMaq(ui.tableWidget_7,ui.tableWidget_7->rowCount()-1,5);
		}
	}
	
}
void cosmec::actualizarMtto()
{
	if(ui.pushButton_14->isChecked()){
		ui.pushButton_14->setText("Guardar");
		ui.pushButton_15->setEnabled(false);
		ui.pushButton_13->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		QTableWidgetItem *itab1 = ui.tableWidget_7->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_7->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_7->item(filaEdit,2);
		int id_maquina;
		QString sql;
		if (((itab1!=0&& itab1->text().isEmpty()==false)&& (itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false))){
			if(comboH){
				QComboBox* anterio=(QComboBox*)ui.tableWidget_7->cellWidget(filaEdit,5);
				id_maquina=idmaquinas[anterio->currentIndex()];
			}else{
				sql=QString("SELECT * FROM mantenimiento_preventivo WHERE id_insumo=%1").arg(idinsumo[filaEdit]);
				id_maquina=sql_general(sql,6).toInt();
			}
			int horas=sql_maquina(id_maquina,4).toInt();
			QString nombre=itab1->text();
			double costo_unitari=QString(itab2->text()).toDouble();
			int cantidad_anual=QString(itab3->text()).toInt();
			double valor_total=costo_unitari*cantidad_anual;
			double costo_hora=valor_total/horas;
			sql=QString("UPDATE mantenimiento_preventivo SET nombre='%1', costo_unitario=%2,"
				"cantidad_anual=%3, valor_total=%4,costo_hora=%5, serie_maquinas=%6"
				"WHERE id_insumo=%7").arg(nombre).arg(costo_unitari).arg(cantidad_anual).arg(valor_total).arg(costo_hora).arg(id_maquina).arg(idinsumo[filaEdit]);
			insertarsql(sql);
			sql="SELECT a.nombre, a.costo_unitario, a.cantidad_anual, "
				"a.valor_total, a.costo_hora, b.modelo FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
			llenartabla(ui.tableWidget_7,sql);
			cargaridinsumo();

			sql="SELECT SUM(a.costo_hora) AS suma_prev, b.presupuesto_anual, b.presupuesto_anual/b.horas_trabajo_anual AS costo_hora,(b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora)), b.modelo AS costo_total FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie GROUP BY b.serie ORDER BY b.modelo";
			llenartabla(ui.tableWidget_8,sql);

			comboMaq(ui.tableWidget_7,ui.tableWidget_7->rowCount()-1,5);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_14->setText("Actualizar");
		ui.pushButton_15->setEnabled(true);
		ui.pushButton_13->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaMtto(){
	const int currentRow =ui.tableWidget_7->rowCount();  
	QTableWidgetItem *itab1 = ui.tableWidget_7->item(currentRow-1,0);
	QTableWidgetItem *itab2 = ui.tableWidget_7->item(currentRow-1,1);
	QTableWidgetItem *itab3 = ui.tableWidget_7->item(currentRow-1,2);
	

	if (((itab1!=0&& itab1->text().isEmpty()==false)&& (itab2!=0&& itab2->text().isEmpty()==false) && (itab3!=0&& itab3->text().isEmpty()==false))||(currentRow==0)){
		if(currentRow!=0){
			//quitar combobox y poner texto
			QString sql;
			QComboBox* anterio=(QComboBox*)ui.tableWidget_7->cellWidget(currentRow-1,5);
			int fila=anterio->currentIndex();
			int horas=sql_maquina(idmaquinas[fila],4).toInt();
			QString nombre=itab1->text();
			double costo_unitari=QString(itab2->text()).toDouble();
			int cantidad_anual=QString(itab3->text()).toInt();
			double valor_total=costo_unitari*cantidad_anual;
			double costo_hora=valor_total/horas;
			sql=QString("INSERT INTO mantenimiento_preventivo(nombre, costo_unitario, cantidad_anual, valor_total," 
				"costo_hora, serie_maquinas) VALUES ('%1',%2,%3,%4,%5,%6)").arg(nombre).arg(costo_unitari).arg(cantidad_anual).arg(valor_total).arg(costo_hora).arg(idmaquinas[fila]);
			insertarsql(sql);
			sql="SELECT a.nombre, a.costo_unitario, a.cantidad_anual, "
				"a.valor_total, a.costo_hora, b.modelo FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
			llenartabla(ui.tableWidget_7,sql);
			cargaridinsumo();

			sql="SELECT SUM(a.costo_hora) AS suma_prev, b.presupuesto_anual, b.presupuesto_anual/b.horas_trabajo_anual AS costo_hora,(b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora)), b.modelo AS costo_total FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie GROUP BY b.serie ORDER BY b.modelo";
			llenartabla(ui.tableWidget_8,sql);
			
			comboMaq(ui.tableWidget_7,ui.tableWidget_7->rowCount()-1,5);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_7->insertRow(currentRow);
		comboMaq(ui.tableWidget_7,ui.tableWidget_7->rowCount()-1,5);
	}
}

/*//mtto - preventivo y correctivo
void cosmec::filaEditablePrev(int row,int column)
{
	bool actChecked=ui.pushButton_10->isChecked();
	bool ultF= (row+1)==ui.tableWidget_8->rowCount();

	if(actChecked&&filaEdit==-1){
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		if(actChecked&&column==4)
		{
			comboH=true;
			comboMaq(ui.tableWidget_8,row,4);
		}
		ui.tableWidget_8->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_8->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaPrev()
{
	int currentRow=ui.tableWidget_8->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		
	}
	ui.tableWidget_8->removeRow(currentRow);
}
void cosmec::actualizarPrev()
{
	if(ui.pushButton_10->isChecked()){
		ui.pushButton_10->setText("Guardar");
		ui.pushButton_11->setEnabled(false);
		ui.pushButton_12->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		if(comboH){
			QComboBox* anterio=(QComboBox*)ui.tableWidget_8->cellWidget(filaEdit,4);
			QString tAnterior=anterio->currentText();
			ui.tableWidget_8->removeCellWidget(filaEdit,4);
			QTableWidgetItem *itemA = new QTableWidgetItem;
			itemA->setText(tAnterior);
			ui.tableWidget_8->setItem(filaEdit,4,itemA);
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_10->setText("Actualizar");
		ui.pushButton_11->setEnabled(true);
		ui.pushButton_12->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaPrev(){
	const int currentRow =ui.tableWidget_8->rowCount();  
	QTableWidgetItem *itab1 = ui.tableWidget_8->item(currentRow-1,0);
	QTableWidgetItem *itab2 = ui.tableWidget_8->item(currentRow-1,1);
	QTableWidgetItem *itab3 = ui.tableWidget_8->item(currentRow-1,2);
	QTableWidgetItem *itab4 = ui.tableWidget_8->item(currentRow-1,3);
	if(currentRow!=0){
		if (((itab1!=0&& itab1->text().isEmpty()==false)&&(itab2!=0&& itab2->text().isEmpty()==false)&& (itab3!=0&& itab3->text().isEmpty()==false)&& (itab4!=0&& itab4->text().isEmpty()==false))||(currentRow==0)){
			//quitar combobox y poner texto
			QComboBox* anterio=(QComboBox*)ui.tableWidget_8->cellWidget(currentRow-1,4);
			QString tAnterior=anterio->currentText();
			ui.tableWidget_8->removeCellWidget(currentRow-1,4);
			QTableWidgetItem *itemA = new QTableWidgetItem;
			itemA->setText(tAnterior);
			ui.tableWidget_8->setItem(currentRow-1,4,itemA);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_8->insertRow(currentRow);
		comboMaq(ui.tableWidget_8,ui.tableWidget_8->rowCount()-1,4);
	}
}

*///actividades - categorias
void cosmec::filaEditableActC(int row,int column)
{
	bool actChecked=ui.pushButton_18->isChecked();
	bool ultF= (row+1)==ui.tableWidget_9->rowCount();
	
	if(actChecked&&filaEdit==-1){
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		ui.tableWidget_9->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_9->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaActC()
{
	int currentRow=ui.tableWidget_9->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_9->item(currentRow,0);
		int id_cat=QString(itab1->text()).toInt();
		sql=QString("DELETE FROM actividades WHERE id_categoria_actividades_categoria_actividades=%1").arg(id_cat);
		insertarsql(sql);
		sql=QString("DELETE FROM categoria_actividades WHERE id_categoria_actividades=%1").arg(id_cat);
		insertarsql(sql);
		sql="SELECT a.id_categoria_actividades, a.nombre FROM categoria_actividades AS a";
		llenartabla(ui.tableWidget_9,sql);
		llenartabla(ui.tableWidget_9,sql);
		sql="SELECT a.id_actividad, a.nombre, a.costo_hora, b.nombre AS cargo FROM actividades AS a, categoria_actividades AS b WHERE a.id_categoria_actividades_categoria_actividades=b.id_categoria_actividades";
		llenartabla(ui.tableWidget_10,sql);
		llenartabla(ui.tableWidget_10,sql);
		if(ui.tableWidget_10->rowCount()!=0){
			comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
		}
	}
	
}
void cosmec::actualizarActC()
{
	if(ui.pushButton_18->isChecked()){
		ui.pushButton_18->setText("Guardar");
		ui.pushButton_16->setEnabled(false);
		ui.pushButton_17->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		QTableWidgetItem *itab1 = ui.tableWidget_9->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_9->item(filaEdit,1);
		QString sql;
		if (((itab2!=0 && itab2->text().isEmpty()==false))){
			int id_cat=QString(itab1->text()).toInt();
			QString nombre=itab2->text();
			sql=QString("UPDATE categoria_actividades SET nombre='%1' "
				"WHERE id_categoria_actividades=%2").arg(nombre).arg(id_cat);
			insertarsql(sql);
			sql="SELECT a.id_categoria_actividades, a.nombre FROM categoria_actividades AS a";
			llenartabla(ui.tableWidget_9,sql);
			llenartabla(ui.tableWidget_9,sql);
			sql="SELECT a.id_actividad, a.nombre, a.costo_hora, b.nombre AS cargo FROM actividades AS a, categoria_actividades AS b WHERE a.id_categoria_actividades_categoria_actividades=b.id_categoria_actividades";
			llenartabla(ui.tableWidget_10,sql);
			llenartabla(ui.tableWidget_10,sql);
			//leer la base de máquinas para tener datos
			comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_18->setText("Actualizar");
		ui.pushButton_16->setEnabled(true);
		ui.pushButton_17->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaActC(){
	const int currentRow =ui.tableWidget_9->rowCount();  
	QTableWidgetItem *itab2 = ui.tableWidget_9->item(currentRow-1,1);
	if(currentRow!=0){
		if (((itab2!=0 && itab2->text().isEmpty()==false))||(currentRow==0)){
			QString nombre=itab2->text();
			QString sql;
			sql=QString("INSERT INTO categoria_actividades(nombre) VALUES ('%1')").arg(nombre);
			insertarsql(sql);
			sql="SELECT a.id_categoria_actividades, a.nombre FROM categoria_actividades AS a";
			llenartabla(ui.tableWidget_9,sql);
			llenartabla(ui.tableWidget_9,sql);
			sql="SELECT a.id_actividad, a.nombre, a.costo_hora, b.nombre AS cargo FROM actividades AS a, categoria_actividades AS b WHERE a.id_categoria_actividades_categoria_actividades=b.id_categoria_actividades";
			llenartabla(ui.tableWidget_10,sql);
			llenartabla(ui.tableWidget_10,sql);
			//leer la base de máquinas para tener datos
	     	comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();	
		}
	}else{
		ui.tableWidget_10->insertRow(currentRow);
		comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
	}
}
//actividades - actividades
void cosmec::filaEditableActAct(int row,int column)
{
	bool actChecked=ui.pushButton_19->isChecked();
	bool ultF= (row+1)==ui.tableWidget_10->rowCount();

	if(actChecked&&filaEdit==-1){
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		if(actChecked&&column==3)
		{
			comboH=true;
			comboCat(ui.tableWidget_10,row,3);
		}
		ui.tableWidget_10->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_10->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaActAct()
{
	QString sql;
	int currentRow=ui.tableWidget_10->currentRow();
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_10->item(currentRow,0);
		int id_acti=QString(itab1->text()).toInt();
		sql=QString("DELETE FROM actividades WHERE id_actividad=%1").arg(id_acti);
		insertarsql(sql);
		sql="SELECT a.id_categoria_actividades, a.nombre FROM categoria_actividades AS a";
		llenartabla(ui.tableWidget_9,sql);
		llenartabla(ui.tableWidget_9,sql);
		sql="SELECT a.id_actividad, a.nombre, a.costo_hora, b.nombre AS cargo FROM actividades AS a, categoria_actividades AS b WHERE a.id_categoria_actividades_categoria_actividades=b.id_categoria_actividades";
		llenartabla(ui.tableWidget_10,sql);
		llenartabla(ui.tableWidget_10,sql);
		if(ui.tableWidget_10->rowCount()!=0){
			comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
		}
	}
}
void cosmec::actualizarActAct()
{
	if(ui.pushButton_19->isChecked()){
		ui.pushButton_19->setText("Guardar");
		ui.pushButton_20->setEnabled(false);
		ui.pushButton_21->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{
		QString sql;
		int id_cargo;
		QTableWidgetItem *itab1 = ui.tableWidget_10->item(filaEdit,0);
		QTableWidgetItem *itab2 = ui.tableWidget_10->item(filaEdit,1);
		QTableWidgetItem *itab3 = ui.tableWidget_10->item(filaEdit,2);
		if (((itab2!=0&& itab2->text().isEmpty()==false)&& (itab3!=0&& itab3->text().isEmpty()==false))){	
			int id_actividad=QString(itab1->text()).toInt();
			if(comboH){
				QComboBox* anterio=(QComboBox*)ui.tableWidget_10->cellWidget(filaEdit,3);
				id_cargo=idactividades[anterio->currentIndex()];
			}else{
				sql=QString("SELECT id_categoria_actividades_categoria_actividades FROM actividades WHERE id_actividad=%1").arg(id_actividad);
				id_cargo=sql_general(sql,0).toInt();	
			}
			QString nombre=itab2->text();
			double costo_hora=QString(itab3->text()).toDouble();
			sql=QString("UPDATE actividades	SET nombre='%1', costo_hora=%2, id_categoria_actividades_categoria_actividades=%3"
				"WHERE id_actividad=%4").arg(nombre).arg(costo_hora).arg(id_cargo).arg(id_actividad);
			insertarsql(sql);
			sql="SELECT a.id_categoria_actividades, a.nombre FROM categoria_actividades AS a";
			llenartabla(ui.tableWidget_9,sql);
			llenartabla(ui.tableWidget_9,sql);
			sql="SELECT a.id_actividad, a.nombre, a.costo_hora, b.nombre AS cargo FROM actividades AS a, categoria_actividades AS b WHERE a.id_categoria_actividades_categoria_actividades=b.id_categoria_actividades";
			llenartabla(ui.tableWidget_10,sql);
			llenartabla(ui.tableWidget_10,sql);
			comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_19->setText("Actualizar");
		ui.pushButton_20->setEnabled(true);
		ui.pushButton_21->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaActAct(){
	QString sql;
	const int currentRow =ui.tableWidget_10->rowCount();  
	//QTableWidgetItem *itab1 = ui.tableWidget_10->item(currentRow-1,0);
	QTableWidgetItem *itab2 = ui.tableWidget_10->item(currentRow-1,1);
	QTableWidgetItem *itab3 = ui.tableWidget_10->item(currentRow-1,2);
	if(currentRow!=0){
		if (((itab2!=0&& itab2->text().isEmpty()==false)&& (itab3!=0&& itab3->text().isEmpty()==false))||(currentRow==0)){
		
			//quitar combobox y poner texto
			QComboBox* anterio=(QComboBox*)ui.tableWidget_10->cellWidget(currentRow-1,3);
			int id_cargo=idactividades[anterio->currentIndex()];
			QString nombre=itab2->text();
			double costo_hora=QString(itab3->text()).toDouble();
			sql=QString("INSERT INTO actividades(nombre, costo_hora, id_categoria_actividades_categoria_actividades)"
				" VALUES ('%1',%2,%3)").arg(nombre).arg(costo_hora).arg(id_cargo);
			insertarsql(sql);
			sql="SELECT a.id_categoria_actividades, a.nombre FROM categoria_actividades AS a";
			llenartabla(ui.tableWidget_9,sql);
			llenartabla(ui.tableWidget_9,sql);
			sql="SELECT a.id_actividad, a.nombre, a.costo_hora, b.nombre AS cargo FROM actividades AS a, categoria_actividades AS b WHERE a.id_categoria_actividades_categoria_actividades=b.id_categoria_actividades";
			llenartabla(ui.tableWidget_10,sql);
			llenartabla(ui.tableWidget_10,sql);
			comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_10->insertRow(currentRow);
		comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
	}
}

//mano de obra - actividades
void cosmec::filaEditableMo(int row,int column)
{
	bool actChecked=ui.pushButton_6->isChecked();
	bool ultF= (row+1)==ui.tableWidget_2->rowCount();

	if(actChecked&&filaEdit==-1){
		filaEdit=row;
	}

	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
		if(actChecked&&column==1)
		{
			comboH=true;
			comboCargo(ui.tableWidget_2,row,1);
		}
		ui.tableWidget_2->setEditTriggers(QAbstractItemView::DoubleClicked);
	}
	else{
		if(actChecked&&filaEdit!=row){
			QMessageBox msgBox;
			msgBox.setText("Solo puede editar una fila a la vez");
			msgBox.exec();
		}
		ui.tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}
void cosmec::eliminarFilaMo()
{
	int currentRow=ui.tableWidget_2->currentRow();
	QString sql;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		sql=QString("DELETE FROM actividades_trabajo"
			" WHERE id_actividad=%1").arg(idactividades[currentRow]);
		insertarsql(sql);
		cargaridactividades();
		sql="SELECT b.nombre, a.nombre AS nombre_cargo, b.hora_mensual, b.costo_mes, b.costo_hora FROM cargo AS a,actividades_trabajo AS b WHERE a.id_cargo=b.id_cargo_cargo ORDER BY a.nombre";
		llenartabla(ui.tableWidget_2,sql);
		if(ui.tableWidget_2->rowCount()!=0){
			comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
		}
	}
}
void cosmec::actualizarMo()
{
	QString sql;
	int id_cargo;
	if(ui.pushButton_6->isChecked()){
		ui.pushButton_6->setText("Guardar");
		ui.pushButton_4->setEnabled(false);
		ui.pushButton_3->setEnabled(false);
		ui.menuBar->setEnabled(false);
	}
	else
	{	
		QTableWidgetItem *itab1 = ui.tableWidget_2->item(filaEdit,0);
		QTableWidgetItem *itab3 = ui.tableWidget_2->item(filaEdit,2);
		QTableWidgetItem *itab4 = ui.tableWidget_2->item(filaEdit,3);
		if (((itab1!=0&&itab1->text().isEmpty()==false)&& (itab3!=0&& itab3->text().isEmpty()==false)&& (itab4!=0&& itab4->text().isEmpty()==false))){
			int id_actividad=idactividades[filaEdit];
			if(comboH){
				QComboBox* anterio=(QComboBox*)ui.tableWidget_2->cellWidget(filaEdit,1);
				id_cargo=idcargo[anterio->currentIndex()];
			}else{
				sql=QString("SELECT * FROM actividades_trabajo WHERE id_actividad=%1").arg(id_actividad);
				id_cargo=sql_general(sql,5).toInt();
			}
			//datos
			QString nombre=itab1->text();
			int horas_mes=QString(itab3->text()).toInt();
			double costo_mes=QString(itab4->text()).toDouble();
			//calculos
			double costo_hora=costo_mes/horas_mes;
			sql=QString("UPDATE actividades_trabajo	SET nombre='%1', hora_mensual=%2, costo_mes=%3, costo_hora=%4, " 
				"id_cargo_cargo=%5 WHERE id_actividad=%6").arg(nombre).arg(horas_mes).arg(costo_mes).arg(costo_hora).arg(id_cargo).arg(id_actividad);
			insertarsql(sql);
			cargaridactividades();
			sql="SELECT b.nombre, a.nombre AS nombre_cargo, b.hora_mensual, b.costo_mes, b.costo_hora FROM cargo AS a,actividades_trabajo AS b WHERE a.id_cargo=b.id_cargo_cargo ORDER BY a.nombre";
			llenartabla(ui.tableWidget_2,sql);
			comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
		}
		filaEdit=-1;
		comboH=false;
		ui.pushButton_6->setText("Actualizar");
		ui.pushButton_4->setEnabled(true);
		ui.pushButton_3->setEnabled(true);
		ui.menuBar->setEnabled(true);
	}
}
void cosmec::agregarfilaMo(){
	const int currentRow =ui.tableWidget_2->rowCount();  
	QTableWidgetItem *itab1 = ui.tableWidget_2->item(currentRow-1,0);
	QTableWidgetItem *itab3 = ui.tableWidget_2->item(currentRow-1,2);
	QTableWidgetItem *itab4 = ui.tableWidget_2->item(currentRow-1,3);
	
	if (((itab1!=0&&itab1->text().isEmpty()==false)&& (itab3!=0&& itab3->text().isEmpty()==false)&& (itab4!=0&& itab4->text().isEmpty()==false))||(currentRow==0)){
		if(currentRow!=0){
			//quitar combobox y poner texto
			QComboBox* anterio=(QComboBox*)ui.tableWidget_2->cellWidget(currentRow-1,1);
			QString sql;
			//datos
			int fila=anterio->currentIndex();
			int id_cargo=idcargo[fila];
			QString nombre=itab1->text();
			int horas_mes=QString(itab3->text()).toInt();
			double costo_mes=QString(itab4->text()).toDouble();
			//calculos
			double costo_hora=costo_mes/horas_mes;
			sql=QString("INSERT INTO actividades_trabajo(nombre, hora_mensual, costo_mes, costo_hora, id_cargo_cargo) VALUES ('%1',%2,%3,%4,%5)").arg(nombre).arg(horas_mes).arg(costo_mes).arg(costo_hora).arg(id_cargo);
			insertarsql(sql);
			cargaridactividades();
			sql="SELECT b.nombre, a.nombre AS nombre_cargo, b.hora_mensual, b.costo_mes, b.costo_hora FROM cargo AS a,actividades_trabajo AS b WHERE a.id_cargo=b.id_cargo_cargo ORDER BY a.nombre";
			llenartabla(ui.tableWidget_2,sql);
			comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
		}else{
			QMessageBox msgBox;
			msgBox.setText("Error: Un dato esta vacio");
			msgBox.exec();
		}
	}else{
		ui.tableWidget_2->insertRow(currentRow);
		comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
	}
}
//cambiar de widget en stack
void cosmec::setgenerador(){
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec("SELECT a.serie, a.modelo FROM maquinas AS a ORDER BY a.modelo");
	tamquery1=respuesta.size();
	idquery1=new int[tamquery1];
	int b=0;
	while(respuesta.next()){
		idquery1[b]=respuesta.value(0).toInt();
		ui.combobasicos->addItem(respuesta.value(1).toString());
		ui.comboconsuibles->addItem(respuesta.value(1).toString());
		ui.comboherramientas->addItem(respuesta.value(1).toString());
		ui.combomanoobra->addItem(respuesta.value(1).toString());
		ui.combomaqmantenimiento->addItem(respuesta.value(1).toString());
		b++;
	}

	respuesta.exec("SELECT a.id_cargo, a.nombre FROM cargo AS a");
	tamquery2=respuesta.size();
	idquery2=new int[tamquery2];
	b=0;
	while(respuesta.next()){
		idquery2[b]=respuesta.value(0).toInt();
		ui.comboactividades->addItem(respuesta.value(1).toString());
		b++;
	}
	cosmecdb.close();
	ui.stackedWidget->setCurrentIndex(9);
}
void cosmec::setreporteexel(){
	ui.stackedWidget->setCurrentIndex(10);
}
void cosmec::setconfig(){
	ui.stackedWidget->setCurrentIndex(8);
}

void cosmec::setServiciosExternos(){
	QString sql="SELECT id_servicios, nombre_srevicio, costo_hora FROM servicios_externos";
	llenartabla(ui.tableWidget_15,sql);
	llenartabla(ui.tableWidget_15,sql);
	ui.stackedWidget->setCurrentIndex(16);
}
void cosmec::setmaquina(){
	QString sql="SELECT a.serie,a.modelo,a.costo,a.vida_util,a.horas_trabajo_anual,a.deprecicacion,a.costo_hora,a.presupuesto_anual FROM maquinas AS a";
	llenartabla(ui.tableWidget_3,sql);
	ui.stackedWidget->setCurrentIndex(1);
}
void cosmec::setherramienta(){
	QString sql="SELECT a.id_herramienta,a.nombre_herramienta,a.cantidad_anual,a.costo_unitario,a.vida_util,a.depreciacion,a.costo_hora,b.modelo FROM maquinas AS b,herramientas AS a WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
	llenartabla(ui.tableWidget_4,sql);
	ui.stackedWidget->setCurrentIndex(2);
	//leer la base de máquinas para tener datos
	if(ui.tableWidget_4->rowCount()!=0){
		comboMaq(ui.tableWidget_4,ui.tableWidget_4->rowCount()-1,7);
	}
}
void cosmec::setconsumible(){
	QString sql="SELECT a.id_consumible,a.nombre_consumible,a.cantidad_anual,a.costo_unitario,a.costo_hora,b.modelo FROM maquinas AS b,consumible AS a WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
	llenartabla(ui.tableWidget_5,sql);
	ui.stackedWidget->setCurrentIndex(3);

	//leer la base de máquinas para tener datos
	if(ui.tableWidget_5->rowCount()!=0){
		comboMaq(ui.tableWidget_5,ui.tableWidget_5->rowCount()-1,5);
	}
}
void cosmec::setenergia(){
	QString sql="SELECT c.modelo,a.consumo,a.costo_consumo,a.costo_energia,b.consumo_anual,b.costo_consumo,b.costo_hora  FROM energia AS a, agua AS b, maquinas AS c WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie ORDER BY c.modelo";
	cargaridenergia();
	cargaridagua();
	llenartabla(ui.tableWidget_6,sql);
	llenartabla(ui.tableWidget_6,sql);
    ui.stackedWidget->setCurrentIndex(5);

	//leer la base de máquinas para tener datos
	if(ui.tableWidget_6->rowCount()!=0){
		comboMaq(ui.tableWidget_6,ui.tableWidget_6->rowCount()-1,0);
	}
}
void cosmec::setmantenimiento(){
	QString sql="SELECT a.nombre, a.costo_unitario, a.cantidad_anual, "
		"a.valor_total, a.costo_hora, b.modelo FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie ORDER BY b.modelo";
	llenartabla(ui.tableWidget_7,sql);
	llenartabla(ui.tableWidget_7,sql);
	cargaridinsumo();
	
	sql="SELECT SUM(a.costo_hora) AS suma_prev, b.presupuesto_anual, b.presupuesto_anual/b.horas_trabajo_anual AS costo_hora,(b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora)), b.modelo AS costo_total FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie GROUP BY b.serie ORDER BY b.modelo";
	llenartabla(ui.tableWidget_8,sql);
	llenartabla(ui.tableWidget_8,sql);
	ui.stackedWidget->setCurrentIndex(6);
	
	//leer la base de máquinas para tener datos insumos
	if(ui.tableWidget_7->rowCount()!=0){
		comboMaq(ui.tableWidget_7,ui.tableWidget_7->rowCount()-1,5);
	}
	//leer la base de máquinas para tener datos prev-correct
	ui.tableWidget_8->removeRow(ui.tableWidget_8->rowCount()-1);
}
void cosmec::setmanoobra(){
	cargaridactividades();
	QString sql;
	sql="SELECT a.id_cargo,a.nombre,a.salario FROM cargo AS a";
	llenartabla(ui.tableWidget,sql);
	llenartabla(ui.tableWidget,sql);

	//sql="SELECT b.nombre, a.nombre AS nombre_cargo, b.hora_mensual, b.costo_mes, b.costo_hora, d.modelo FROM cargo AS a,actividades_trabajo AS b,mano_obra AS c,maquinas AS d WHERE a.id_cargo=b.id_cargo_cargo AND b.id_actividad=c.id_actividad_actividades_trabajo AND c.serie_maquinas=d.serie";
	sql="SELECT b.nombre, a.nombre AS nombre_cargo, b.hora_mensual, b.costo_mes, b.costo_hora FROM cargo AS a,actividades_trabajo AS b WHERE a.id_cargo=b.id_cargo_cargo ORDER BY a.nombre";
	llenartabla(ui.tableWidget_2,sql);
	llenartabla(ui.tableWidget_2,sql);
	ui.stackedWidget->setCurrentIndex(4);

	if(ui.tableWidget_2->rowCount()!=0){
		comboCargo(ui.tableWidget_2,ui.tableWidget_2->rowCount()-1,1);
	}
}
void cosmec::setactividades(){
	QString sql;
	sql="SELECT a.id_categoria_actividades, a.nombre FROM categoria_actividades AS a";
	llenartabla(ui.tableWidget_9,sql);
	llenartabla(ui.tableWidget_9,sql);
	sql="SELECT a.id_actividad, a.nombre, a.costo_hora, b.nombre AS cargo FROM actividades AS a, categoria_actividades AS b WHERE a.id_categoria_actividades_categoria_actividades=b.id_categoria_actividades";
	llenartabla(ui.tableWidget_10,sql);
	llenartabla(ui.tableWidget_10,sql);
	ui.stackedWidget->setCurrentIndex(7);

	//leer la base de máquinas para tener datos
	if(ui.tableWidget_10->rowCount()!=0){
		comboCat(ui.tableWidget_10,ui.tableWidget_10->rowCount()-1,3);
	}
}
void cosmec::setrptcotizaciones(){
	ui.stackedWidget->setCurrentIndex(17);
}
void cosmec::guardarConfig()
{
	if(ui.pushButton_23->isChecked()){
		ui.pushButton_23->setText("Guardar");
		ui.pushButton_22->setEnabled(false);
		ui.pushButton_24->setEnabled(false);
	}
	else
	{
		ui.pushButton_23->setText("Actualizar");
		ui.pushButton_22->setEnabled(true);
		ui.pushButton_24->setEnabled(true);
	}
}
void cosmec::configurar()
{
	ui.editconfig->setText("Editar");

	if(ui.editconfig->isChecked()){
		ui.editconfig->setText("Guardar");
		ui.ip->setEnabled(true);
		ui.usuario->setEnabled(true);
		ui.passw->setEnabled(true);
		ui.port->setEnabled(true);
		ui.lineEdit_7->setEnabled(true);
	}
	else
	{
		QFile file("in.txt");
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
			QMessageBox msgBox;
			msgBox.setText("Error al guardar configuracion de conexion host");
			msgBox.exec();
		}else{
			QTextStream out(&file);
			out << ui.ip->text()<<"\n";
			out << ui.passw->text()<<"\n";
			out << ui.usuario->text()<<"\n";
			out << ui.port->text()<<"\n";
			out << ui.lineEdit_7->text()<<"\n";
			file.close();
			host=ui.ip->text();
			pass2=ui.passw->text();
			puerto=ui.port->text();
			usuario=ui.usuario->text();
			iva=(QString(ui.lineEdit_7->text()).toDouble())/100;
			qDebug()<<iva;
            ui.ip->setEnabled(false);
			ui.usuario->setEnabled(false);
			ui.passw->setEnabled(false);
			ui.port->setEnabled(false);
			ui.lineEdit_7->setEnabled(false);
		}
		
	}
}
void cosmec::conexion(){
	cosmecdb = QSqlDatabase::addDatabase("QPSQL","cosmec");
	if ( !cosmecdb.isValid() ) {
		QMessageBox::warning(0, "Error de Conexion", QObject::tr("No se cargo el controlador de la base de datos."));
	}
	cosmecdb.setHostName(host);
	cosmecdb.setDatabaseName( "cosmec" );
	cosmecdb.setUserName( usuario );
	cosmecdb.setPassword( pass2 );
	cosmecdb.setPort(puerto.toInt());
	if ( !cosmecdb.open() ) {
		QMessageBox::warning( 0,"Error de Conexion", QObject::tr("No se pudo conectar: ")+cosmecdb.lastError().databaseText());
	}

}
void cosmec::reportgenerador(){
	report = new NCReport();
	report->reset(true);
	QString a;
	if(ui.checkherrg->isChecked()){
		report->setReportFile("../reportes/herramienta_general.xml");
		reportesinter(report);
	}
	
	if(ui.checkherr->isChecked()){
		a=QString::number(idquery1[ui.comboherramientas->currentIndex()]);
		report->setReportFile("../reportes/herramienta_maquina.xml");
		report->addParameter("maquina",a);
		reportesinter(report);
	}
	if(ui.checkconsug->isChecked()){
		report->setReportFile("../reportes/consumibles_general.xml");
		reportesinter(report);
	}

	if(ui.checkconsu->isChecked()){
		a=QString::number(idquery1[ui.comboconsuibles->currentIndex()]);
		report->setReportFile("../reportes/consumibles_maquina.xml");
		report->addParameter("maquina",a);
		reportesinter(report);
	}
	if(ui.checkmantg->isChecked()){
		report->setReportFile("../reportes/isumos_general.xml");
		reportesinter(report);
	}

	if(ui.checkmant->isChecked()){
		a=QString::number(idquery1[ui.combomaqmantenimiento->currentIndex()]);
		report->setReportFile("../reportes/isumos_maquina.xml");
		report->addParameter("maquina",a);
		reportesinter(report);
	}
	if(ui.checkmanog->isChecked()){
		report->setReportFile("../reportes/manoobra_general.xml");
		reportesinter(report);
	}

	if(ui.checkmano->isChecked()){
		a=QString::number(idquery1[ui.combomanoobra->currentIndex()]);
		report->setReportFile("../reportes/manoobra_maquina.xml");
		report->addParameter("maquina",a);
		reportesinter(report);
	}
	if(ui.checkactivg->isChecked()){
		report->setReportFile("../reportes/actividades_general.xml");
		reportesinter(report);
	}

	if(ui.checkactiv->isChecked()){
		a=QString::number(idquery2[ui.comboactividades->currentIndex()]);
		report->setReportFile("../reportes/actividades_cargo.xml");
		report->addParameter("cargo",a);
		reportesinter(report);
	}
	if(ui.checkbasg->isChecked()){
		report->setReportFile("../reportes/serviciosgenerales_general.xml");
		reportesinter(report);
	}

	if(ui.checkbas->isChecked()){
		a=QString::number(idquery1[ui.combobasicos->currentIndex()]);
		report->setReportFile("../reportes/serviciosgenerales_maquina.xml");
		report->addParameter("maquina",a);
		reportesinter(report);
	}
	if(ui.checkmaqg->isChecked()){
		report->setReportFile("../reportes/reportmaquina.xml");
		reportesinter(report);
	}
}
void cosmec::reportesinter(NCReport *report){
	pv = new NCReportPreviewWindow();
	report->runReportToPreview();
	if(!report->hasError())
	{
		pv->setReport( report );
		pv->setOutput((NCReportPreviewOutput *)report->output());
		pv->setWindowModality(Qt::ApplicationModal);
		pv->setAttribute(Qt::WA_DeleteOnClose);
		pv->show();
		report->reset(true);
	}
	else
	{
		QMessageBox::about(0,"Error in Report",	report->lastErrorMsg());
	}
}
void cosmec::llenartabla(QTableWidget *tableNum,QString sql){
	if(tableNum->rowCount()>1){
		for(int a=tableNum->rowCount();a!=0;a--){
			tableNum->removeRow(a);
		}
	}
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al agregar datos :"+respuesta.lastError().databaseText());
		msgBox.exec();
	}
		record = respuesta.record();
		int forint=record.count();
		tamquery1=respuesta.size();
		int fila=0;
	while(respuesta.next()){
		for(int columna=0;columna<forint;columna++){
			QTableWidgetItem *nuevo=new QTableWidgetItem();
			nuevo->setText(respuesta.value(columna).toString());
			tableNum->setItem(fila,columna,nuevo);
		}
		tableNum->insertRow(tableNum->rowCount());
		fila++;
	}
	cosmecdb.close();
}
void cosmec::insertarsql(QString sql){
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al agregar datos :"+respuesta.lastError().databaseText());
		msgBox.exec();
	}
	cosmecdb.close();
}
void cosmec::reporteexel(){
	db basedatos;
	PGconn *conn;
	basedatos.inicio(host.toStdString(),puerto.toStdString(),"cosmec",usuario.toStdString(),pass2.toStdString());
	conn=basedatos.conectar();
	if (PQstatus(conn) == CONNECTION_BAD){
		QMessageBox msgBox;
		msgBox.setText("Error al conectar base de datos :"+QString(PQerrorMessage(conn)));
		msgBox.exec();
		
	}else{
		XmlExcel archivo;
		TiXmlDocument doc;
		TiXmlDeclaration * decl;
		TiXmlElement * workbook; 
		TiXmlElement * estilo; 
		TiXmlElement* worksheet;
		TiXmlElement * table;
		TiXmlElement * row;
		list <hoja> list_filas;
		decl=archivo.cabecera();
		workbook=archivo.crear_documento_libro("COSMEC","2013-06-05T15:20:15Z"); //autor, fecha
		estilo=archivo.crear_estilos();
		workbook ->LinkEndChild(estilo);

		if(ui.checkBox->isChecked()){
			//crea hoja de datos
			worksheet=archivo.crear_hoja("Maquinas"); //Nombre de la hoja
			table=archivo.crear_tabla("199","200"); //dimensiones maxima de la hoja x,y
			//Cabecera de hoja
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Escuela Politecnica del Ejercito","String","2","6","25");
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Departamento de ciencias de la energia y mecanica","String","2","6","15");
			table->LinkEndChild(row);
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			//
			row=archivo.crear_cell_tabla_titulo("SERVICIOS GENERALES","String","6");
			table->LinkEndChild(row);
			//lsitas para los datos
			//se tiene que cambiar por consulta
			
			//list_filas=archivo.row_anadido_menu(list_filas,1);
			list_filas=basedatos.consulta_menus(conn,list_filas,"1");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT a.serie,a.modelo,a.costo,a.vida_util,a.horas_trabajo_anual,a.deprecicacion,a.costo_hora FROM maquinas AS a"); //lee de la base de datos y almacena en la lista
			table=archivo.row_lista_anadido_dato(table,list_filas);
			worksheet->LinkEndChild(table);
			workbook ->LinkEndChild(worksheet);
		}
		//otra hoja
		if(ui.checkBox_2->isChecked()){
			//crea hoja de datos
			worksheet=archivo.crear_hoja("Consumibles y Herrameintas"); //Nombre de la hoja
			table=archivo.crear_tabla("199","2000"); //dimensiones maxima de la hoja x,y
			//Cabecera de hoja
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Escuela Politecnica del Ejercito","String","2","7","25");
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Departamento de ciencias de la energia y mecanica","String","2","7","15");
			table->LinkEndChild(row);
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			//
			//creado de tabla
			row=archivo.crear_cell_tabla_titulo("HERRAMIENTAS","String","7");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"2");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT a.modelo,b.nombre_herramienta, b.costo_unitario, b.vida_util, b.depreciacion, b.valor_hora, b.depreciacion_hora, b.costo_hora FROM maquinas AS a,herramientas AS b WHERE b.serie_maquinas=a.serie");
			table=archivo.row_lista_anadido_dato(table,list_filas); //ya hace el LinkEndChild internamente
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_cell_tabla_titulo("CONSUMIBLES","String","3");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"3");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT a.modelo, b.nombre_consumible, b.costo_unitario, b.costo_hora FROM maquinas a,consumible b WHERE a.serie=b.serie_maquinas"); //lee de la base de datos y almacena en la lista
			table=archivo.row_lista_anadido_dato(table,list_filas); 
			//
			worksheet->LinkEndChild(table);
			workbook ->LinkEndChild(worksheet);
		}
		//hoja3
		if(ui.checkBox_3->isChecked()){
			worksheet=archivo.crear_hoja("Mantenimiento"); //Nombre de la hoja
			table=archivo.crear_tabla("199","2000"); //dimensiones maxima de la hoja x,y
			//Cabecera de hoja
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Escuela Politecnica del Ejercito","String","2","4","25");
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Departamento de ciencias de la energia y mecanica","String","2","4","15");
			table->LinkEndChild(row);
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			//
			//creado de tabla
			row=archivo.crear_cell_tabla_titulo("MANTENIMIENTO PREVENTIVO","String","4");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"4");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT a.nombre,b.modelo, a.costo_unitario, a.cantidad_anual, "
				"a.valor_total FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie ORDER BY b.modelo");
			table=archivo.row_lista_anadido_dato(table,list_filas); //ya hace el LinkEndChild internamente
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_cell_tabla_titulo("MANTENIMIENTO","String","4");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"5");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT b.modelo, b.presupuesto_anual, b.presupuesto_anual/b.horas_trabajo_anual AS costo_hora, SUM(a.costo_hora) AS suma_prev,(b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora))  AS costo_total FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie GROUP BY b.serie ORDER BY b.modelo"); //lee de la base de datos y almacena en la lista
			table=archivo.row_lista_anadido_dato(table,list_filas); 
			//
			worksheet->LinkEndChild(table);
			workbook ->LinkEndChild(worksheet);
		}
		//hoja4
		if(ui.checkBox_4->isChecked()){
			worksheet=archivo.crear_hoja("Servicios y Mano de Obra"); //Nombre de la hoja
			table=archivo.crear_tabla("199","2000"); //dimensiones maxima de la hoja x,y
			//Cabecera de hoja
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Escuela Politecnica del Ejercito","String","2","7","25");
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Departamento de ciencias de la energia y mecanica","String","2","7","15");
			table->LinkEndChild(row);
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			//
			//creado de tabla
			row=archivo.crear_cell_tabla_titulo("SERVICIOS GENERALES","String","7");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"6");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT c.modelo,b.consumo_anual AS anual_agua,b.costo_consumo AS costo_agua,a.consumo,a.costo_consumo,b.costo_hora,a.costo_energia,b.costo_hora+a.costo_energia  FROM energia AS a, agua AS b, maquinas AS c WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie");
			table=archivo.row_lista_anadido_dato(table,list_filas); //ya hace el LinkEndChild internamente
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_cell_tabla_titulo("MANO DE OBRA","String","4");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"7");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT d.modelo, b.nombre, b.hora_mensual, b.costo_mes, b.costo_hora FROM cargo AS a,actividades_trabajo AS b,mano_obra AS c,maquinas AS d WHERE a.id_cargo=b.id_cargo_cargo AND b.id_actividad=c.id_actividad_actividades_trabajo AND c.serie_maquinas=d.serie"); //lee de la base de datos y almacena en la lista
			table=archivo.row_lista_anadido_dato(table,list_filas); 
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_cell_tabla_titulo("ACTIVIDADES DE TRABAJO","String","4");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"8");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT b.nombre, a.nombre AS nombre_cargo, b.hora_mensual, b.costo_mes, b.costo_hora FROM cargo AS a,actividades_trabajo AS b WHERE a.id_cargo=b.id_cargo_cargo ORDER BY a.nombre"); //lee de la base de datos y almacena en la lista
			table=archivo.row_lista_anadido_dato(table,list_filas);

			worksheet->LinkEndChild(table);
			workbook ->LinkEndChild(worksheet);
		}
		//hoja 5
		if(ui.checkBox_5->isChecked()){
			worksheet=archivo.crear_hoja("Actividades"); //Nombre de la hoja
			table=archivo.crear_tabla("199","2000"); //dimensiones maxima de la hoja x,y
			//Cabecera de hoja
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Escuela Politecnica del Ejercito","String","2","2","25");
			table->LinkEndChild(row);
			row=archivo.crear_general_titulo("Departamento de ciencias de la energia y mecanica","String","2","2","15");
			table->LinkEndChild(row);
			row=archivo.salto_linea();
			table->LinkEndChild(row);
			//
			//creado de tabla
			row=archivo.crear_cell_tabla_titulo("ACTIVIDADES","String","2");
			table->LinkEndChild(row);
			list_filas.clear();
			list_filas=basedatos.consulta_menus(conn,list_filas,"9");
			list_filas=basedatos.consulta(conn,list_filas,"SELECT b.nombre,a.nombre AS categoria,b.costo_hora FROM categoria_actividades AS a,actividades AS b WHERE a.id_categoria_actividades=b.id_categoria_actividades_categoria_actividades");
			table=archivo.row_lista_anadido_dato(table,list_filas); //ya hace el LinkEndChild internamente

			worksheet->LinkEndChild(table);
			workbook ->LinkEndChild(worksheet);
		}
		//hoja 6
		//worksheet=archivo.crear_hoja("General"); //Nombre de la hoja
		//table=archivo.crear_tabla("199","2000"); //dimensiones maxima de la hoja x,y
		////Cabecera de hoja
		//row=archivo.salto_linea();
		//table->LinkEndChild(row);
		//row=archivo.crear_general_titulo("Escuela Politecnica del Ejercito","String","2","4","25");
		//table->LinkEndChild(row);
		//row=archivo.crear_general_titulo("Departamento de ciencias de la energia y mecanica","String","2","4","15");
		//table->LinkEndChild(row);
		//row=archivo.salto_linea();
		//table->LinkEndChild(row);
		////
		////creado de tabla
		//row=archivo.crear_cell_tabla_titulo("COSTOS GENERALES","String","4");
		//table->LinkEndChild(row);
		//list_filas.clear();
		//list_filas=basedatos.consulta_menus(conn,list_filas,"10");
		////list_filas=basedatos.consulta(conn,list_filas,"select * from herramientas");
		//table=archivo.row_lista_anadido_dato(table,list_filas); //ya hace el LinkEndChild internamente

		//worksheet->LinkEndChild(table);
		//workbook ->LinkEndChild(worksheet);


		//Armado del archivo
		doc.LinkEndChild( decl );
		doc.LinkEndChild( workbook );
		//Creacion del xml y visualizacion
		archivo.guardar_archivo(doc,"excel1a.xml");
		archivo.abrir_archivo("excel1a.xml");
		//string a;
		//cin>>a;

	}
}
void cosmec::setactividadesMo(){
	QString sql="SELECT c.id_actividad,c.nombre,a.serie, a.modelo FROM maquinas AS a,mano_obra AS b,actividades_trabajo AS c WHERE c.id_actividad=b.id_actividad_actividades_trabajo AND b.serie_maquinas=a.serie ORDER BY a.modelo";
	llenartabla(ui.tableWidget_13,sql);
	llenartabla(ui.tableWidget_13,sql);
	ui.stackedWidget->setCurrentIndex(15);
	if(ui.tableWidget_13->rowCount()!=0){
		comboActividades(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,1);
		comboMaq(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,3);
	}
}
void cosmec::setnuevaCotizacion(){
	QString sql;
	sql="SELECT setval('cotizacion_numero_seq',(SELECT nextval('cotizacion_numero_seq'))-1)";
	numerocoti=sql_general(sql,0).toInt()+1;
	ui.label_27->setText(QString::number(numerocoti));
	//llenar combo de máquinas combo
	ui.comboBox_5->clear();
	ui.comboBox_6->clear();
	ui.comboBox->clear();
	ui.comboBox_11->clear();
	ui.tableWidget_12->clearContents();
	ui.tableWidget_24->clearContents();
	borrartabla(ui.tableWidget_12);
	borrartabla(ui.tableWidget_24);
	ui.doubleSpinBox->setValue(0);
	ui.doubleSpinBox_2->setValue(0);
	ui.doubleSpinBox_2->setValue(0);
	ui.doubleSpinBox_5->setValue(0);
	ui.doubleSpinBox_7->setValue(0);
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.lineEdit_4->clear();
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec("SELECT a.serie, a.modelo FROM maquinas AS a ORDER BY a.modelo");
	tamquery1=respuesta.size();
	idmaquinas=new int[tamquery1];
	int b=0;
	while(respuesta.next()){
		idmaquinas[b]=respuesta.value(0).toInt();
		ui.comboBox_5->addItem(respuesta.value(1).toString());
		b++;
	}
	cosmecdb.close();

	cosmecdb.open();
	respuesta.exec(QString("SELECT a.id_actividad, a.nombre FROM actividades AS a ORDER BY a.nombre"));
	tamquery1=respuesta.size();
	qDebug()<<tamquery1;
	idactividades=new int[tamquery1];
	b=0;
	while(respuesta.next()){
		idactividades[b]=respuesta.value(0).toInt();
		ui.comboBox_11->addItem(respuesta.value(1).toString());
		b++;
	}
	cosmecdb.close();

	cosmecdb.open();
	respuesta.exec(QString("SELECT a.id_material, a.nombre FROM materiales AS a ORDER BY a.nombre"));
	tamquery2=respuesta.size();
	idmaterial=new int[tamquery2];
	b=0;
	while(respuesta.next()){
		idmaterial[b]=respuesta.value(0).toInt();
		ui.comboBox->addItem(respuesta.value(1).toString());
		b++;
	}
	cosmecdb.close();

	cosmecdb.open();
	respuesta.exec(QString("SELECT id_servicios, nombre_srevicio FROM servicios_externos"));
	tamquery2=respuesta.size();
	idserv=new int[tamquery2];
	b=0;
	while(respuesta.next()){
		idserv[b]=respuesta.value(0).toInt();
		ui.comboBox_6->addItem(respuesta.value(1).toString());
		b++;
	}
	cosmecdb.close();
	ui.stackedWidget->setCurrentIndex(11);
}
void cosmec::setbuscarCotizacion(){
	borrartabla(ui.tableWidget_24);
	borrartabla(ui.tableWidget_11);
	ui.lineEdit_5->clear();
	ui.lineEdit_6->clear();
	ui.radioButton->setChecked(false);
	ui.radioButton_2->setChecked(false);
	ui.stackedWidget->setCurrentIndex(12);
}
void cosmec::setmateriales(){
	QString sql="SELECT id_material, nombre, geometria, dimencion, costo"
		" FROM materiales";
	llenartabla(ui.tableWidget_14,sql);
	llenartabla(ui.tableWidget_14,sql);
	ui.stackedWidget->setCurrentIndex(14);
}

//actividades - maquina
void cosmec::agregarfilaMaqActividades(){
	const int currentRow =ui.tableWidget_13->rowCount();  
	if(currentRow!=0){
			QString sql;
			//quitar combobox y poner texto
			QComboBox* anterio=(QComboBox*)ui.tableWidget_13->cellWidget(currentRow-1,1);
			int fila=anterio->currentIndex();
			qDebug()<<fila;
			int idnoce=idact[fila];
			qDebug()<<idact[2];
			QComboBox* anterio2=(QComboBox*)ui.tableWidget_13->cellWidget(currentRow-1,3);
			int id_maquina=idmaquinas[anterio2->currentIndex()];
			qDebug()<<id_maquina;
			sql=QString("INSERT INTO mano_obra(serie_maquinas, id_actividad_actividades_trabajo)"
				"VALUES (%1,%2)").arg(id_maquina).arg(idnoce);
			insertarsql(sql);
			sql="SELECT c.id_actividad,c.nombre,a.serie, a.modelo FROM maquinas AS a,mano_obra AS b,actividades_trabajo AS c WHERE c.id_actividad=b.id_actividad_actividades_trabajo AND b.serie_maquinas=a.serie ORDER BY a.modelo";
			llenartabla(ui.tableWidget_13,sql);
			if(ui.tableWidget_13->rowCount()!=0){
				comboActividades(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,1);
				comboMaq(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,3);
			}
	}else{
		ui.tableWidget_13->insertRow(currentRow);
		comboActividades(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,0);
		comboMaq(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,1);
	}
}
//void cosmec::actualizarMaqActividades(){
//	if(ui.pushButton_40->isChecked()){
//		ui.pushButton_40->setText("Guardar");
//		ui.pushButton_39->setEnabled(false);
//		ui.pushButton_38->setEnabled(false);
//		ui.menuBar->setEnabled(false);
//	}
//	else
//	{
//		if(comboH){
//			QComboBox* anterio=(QComboBox*)ui.tableWidget_13->cellWidget(filaEdit,1);
//			QString tAnterior=anterio->currentText();
//			ui.tableWidget_13->removeCellWidget(filaEdit,1);
//			QTableWidgetItem *itemA = new QTableWidgetItem;
//			itemA->setText(tAnterior);
//			ui.tableWidget_13->setItem(filaEdit,1,itemA);
//		}
//		if(comboG){
//			QComboBox* anterio=(QComboBox*)ui.tableWidget_13->cellWidget(filaEdit,3);
//			QString tAnterior=anterio->currentText();
//			ui.tableWidget_13->removeCellWidget(filaEdit,3);
//			QTableWidgetItem *itemA = new QTableWidgetItem;
//			itemA->setText(tAnterior);
//			ui.tableWidget_13->setItem(filaEdit,3,itemA);
//		}
//		filaEdit=-1;
//		comboH=false;
//		comboG=false;
//		ui.pushButton_40->setText("Actualizar");
//		ui.pushButton_39->setEnabled(true);
//		ui.pushButton_38->setEnabled(true);
//		ui.menuBar->setEnabled(true);
//	}
//}
void cosmec::eliminarFilaMaqActividades(){
	int currentRow=ui.tableWidget_13->currentRow();
	QString sql;
	QTableWidgetItem *itab1 = ui.tableWidget_13->item(currentRow,0);
	QTableWidgetItem *itab3 = ui.tableWidget_13->item(currentRow,2);
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		int id_actividad=QString(itab1->text()).toInt();
		int id_maquina=QString(itab3->text()).toInt();
		sql=QString("DELETE FROM mano_obra WHERE serie_maquinas=%1 AND id_actividad_actividades_trabajo=%2").arg(id_maquina).arg(id_actividad);
		insertarsql(sql);
		QString sql="SELECT c.id_actividad,c.nombre,a.serie, a.modelo FROM maquinas AS a,mano_obra AS b,actividades_trabajo AS c WHERE c.id_actividad=b.id_actividad_actividades_trabajo AND b.serie_maquinas=a.serie ORDER BY a.modelo";
		llenartabla(ui.tableWidget_13,sql);
		if(ui.tableWidget_13->rowCount()!=0){
			comboActividades(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,1);
			comboMaq(ui.tableWidget_13,ui.tableWidget_13->rowCount()-1,3);
		}
	}
	
}
//void cosmec::filaEditableMaqActividades(int row,int column){
//	bool actChecked=ui.pushButton_40->isChecked();
//	bool ultF= (row+1)==ui.tableWidget_13->rowCount();
//
//	if(actChecked&&filaEdit==-1){
//		filaEdit=row;
//	}
//
//	if((actChecked&&filaEdit==row)||(ultF&&!actChecked)){
//		if(actChecked&&column==1)
//		{
//			comboH=true;
//			comboActividades(ui.tableWidget_13,row,1);
//		}
//		if(actChecked&&column==3)
//		{
//			comboG=true;
//			comboMaq(ui.tableWidget_13,row,3);
//		}
//		ui.tableWidget_13->setEditTriggers(QAbstractItemView::DoubleClicked);
//	}
//	else{
//		if(actChecked&&filaEdit!=row){
//			QMessageBox msgBox;
//			msgBox.setText("Solo puede editar una fila a la vez");
//			msgBox.exec();
//		}
//		ui.tableWidget_13->setEditTriggers(QAbstractItemView::NoEditTriggers);
//	}
//}
//

//buscar cotización
void cosmec::habilitarBuscarRuc(){
	ui.lineEdit_5->setEnabled(false);
	ui.lineEdit_6->setEnabled(true);
}
void cosmec::habilitarBuscarCotizacion(){
	ui.lineEdit_5->setEnabled(true);
	ui.lineEdit_6->setEnabled(false);
}
void cosmec::buscarCotizacion(){//llenar tabla de cotizaciones encontradas con ese valor de RUC o # cotizacion
	QString sql;
	//cosmecdb.open()
	//QSqlQuery aux(cosmecdb);
	if(ui.radioButton->isChecked() || ui.radioButton_2->isChecked()){
		if(ui.radioButton->isChecked()){
			sql=QString("SELECT numero,nombre, ruc, subtotal_cotizacion FROM cotizacion WHERE numero=%1").arg(ui.lineEdit_5->text());
			llenartabla(ui.tableWidget_11,sql);
			llenartabla(ui.tableWidget_11,sql);
			ui.tableWidget_11->removeRow(ui.tableWidget_11->rowCount()-1);
		}else{
			sql=QString("SELECT numero,nombre, ruc, subtotal_cotizacion FROM cotizacion WHERE ruc=%1").arg(ui.lineEdit_6->text());
			llenartabla(ui.tableWidget_11,sql);
			llenartabla(ui.tableWidget_11,sql);
			ui.tableWidget_11->removeRow(ui.tableWidget_11->rowCount()-1);
		}
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("Escoja un parámetro de búsqueda");
		msgBox.exec();
	}
}
void cosmec::resultadoCotizacion(){
	int currentRow=ui.tableWidget_11->currentRow();
	QTableWidgetItem *itab1 = ui.tableWidget_11->item(currentRow,0);
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("Debe elegir una cotización");
		msgBox.exec();
	}
	else{
		numerocoti=QString(itab1->text()).toInt();
		double subtotal=calcularcotizacion(numerocoti);
		ui.lineEdit_27->setText(QString::number(subtotal));
		ui.lineEdit_30->setText(QString::number(iva*subtotal));
		ui.lineEdit_29->setText(QString::number((1+iva)*subtotal));
		ui.pushButton_35->setVisible(true);
		ui.stackedWidget->setCurrentIndex(13);

	}
}
void cosmec::imprimirCotizacion()
{
	//preview de cotización
	report = new NCReport();
	report->reset(true);
	report->setReportFile("../reportes/cotizacion.xml");
	report->addParameter("numerop",numerocoti);
	reportesinter(report);
}
void cosmec::detalle(){
	dialogDetalle *pop=new dialogDetalle();
	int currentRow=ui.tableWidget_24->currentRow();
	double mano_total=0;
	QString dato1;
	QString dato2;
	QString dato3;
	QString dato4;
	QString dato5;
	QString sql;
	bool flag=false;
	if(currentRow==-1){
		QMessageBox msgBox;
		msgBox.setText("No hay fila seleccionada");
		msgBox.exec();
	}else{
		QTableWidgetItem *itab1 = ui.tableWidget_24->item(currentRow,0);
		QTableWidgetItem *itab2 = ui.tableWidget_24->item(currentRow,1);
		double aux=QString(itab1->text()).toDouble();
		int indice=(int)aux;
		double val=aux-indice;
		int fila=0;
		int ind=1;
		qDebug()<<val;
		if(val==0 && (itab2->text()!="Actividades" && itab2->text()!="Servicios Extras")){
			flag=true;
			int serie=idmaquinacot[indice-1];	
			sql=QString("SELECT SUM(costo_hora) FROM herramientas WHERE serie_maquinas=%1 GROUP BY serie_maquinas").arg(serie);
			double valor_herra=sql_general(sql,0).toDouble();
			
			dato1=QString::number(ind);
			dato2="Herramientas";
			dato3=QString::number(valor_herra);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;

			sql=QString("SELECT SUM(costo_hora) FROM consumible WHERE serie_maquinas=%1 GROUP BY serie_maquinas").arg(serie);
			double valor_consu=sql_general(sql,0).toDouble();
			
			dato1=QString::number(ind);
			dato2="Consumibles";
			dato3=QString::number(valor_consu);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;

			sql=QString("SELECT a.costo_energia+b.costo_hora,c.modelo  FROM energia AS a, agua AS b, maquinas AS c "
				"WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie AND c.serie=%1").arg(serie);
			double servicios=sql_general(sql,0).toDouble();
			
			dato1=QString::number(ind);
			dato2="Servicios Basicos";
			dato3=QString::number(servicios);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;

			sql=QString("SELECT (b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora)) AS costo_total "
				"FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie AND b.serie=%1 GROUP BY b.serie").arg(serie);
			double manteni=sql_general(sql,0).toDouble();
			
			dato1=QString::number(ind);
			dato2="Mantenimiento";
			dato3=QString::number(manteni);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;

			sql=QString("SELECT ((2*costo)/(vida_util*horas_trabajo_anual)) FROM maquinas WHERE serie=%1").arg(serie);
			double costomaqui=sql_general(sql,0).toDouble();
			
			double maquina=(valor_herra+valor_consu+servicios+manteni+costomaqui);
			
			dato1=QString::number(ind);
			dato2="Costo maquina y depreciacion ";
			dato3=QString::number(costomaqui);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;

			dato1="";
			dato2="Costo hora total";
			dato3=QString::number(maquina);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;

			dato1="";
			dato2="Precio total "+QString::number(vcomp*100)+"%";
			dato3=QString::number(maquina*(1+vcomp));
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;
		}
		if(QString::number(val)=="0.1" && itab2->text()=="Mano de obra"){
			flag=true;
			cosmecdb.open();
			QSqlQuery respuesta(cosmecdb);
			QString sql=QString("SELECT c.nombre, c.costo_mes FROM maquinas AS a, mano_obra AS b, actividades_trabajo AS c,cotizacion_manoobra AS d WHERE d.serie_maquina=a.serie AND d.numero_cotizacion=%1 AND a.serie=b.serie_maquinas AND b.id_actividad_actividades_trabajo=c.id_actividad AND a.serie=%2").arg(numerocoti).arg(idmaquinacot[indice-1]);
			if(!respuesta.exec(sql)){
				QMessageBox msgBox;
				msgBox.setText("Error al agregar datos :"+respuesta.lastError().databaseText());
				msgBox.exec();
			}
			while(respuesta.next()){
				dato1=QString::number(ind);
				dato2=respuesta.value(0).toString();
				dato3=respuesta.value(1).toString();
				pop->tablaDetalle(fila,dato1,dato2,dato3);
				double man=respuesta.value(1).toDouble();
				mano_total=mano_total+man;
				fila++;
				ind++;
			}

			dato1="";
			dato2="Costo total";
			dato3=QString::number(mano_total);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;
			
			dato1="";
			dato2="Costo hora";
			dato3=QString::number(mano_total/160);
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;

			dato1="";
			dato2="Precio total "+QString::number(vcomp*100)+"%";
			dato3=QString::number((mano_total/160)*(1+vcomp));
			pop->tablaDetalle(fila,dato1,dato2,dato3);
			fila++;
			ind++;
		}
		//pop->tablaDetalle();//funcion para llenar la tabla. modificar con los parámtros que necesites
		if(flag){
			pop->show();
		}else{
			QMessageBox msgBox;
			msgBox.setText("Sin opción de búsqueda");
			msgBox.exec();
		}
	}
}

//nueva cotización
void cosmec::sumarHerramienta(){
	/*QString herramienta=ui.comboBox_2->currentText();
	QString maq=ui.comboBox_3->currentText();
	int cantH=ui.spinBox->value();
	
	if(cantH!=0){
		ui.tableWidget_12->insertRow(ui.tableWidget_12->rowCount());
		
		QTableWidgetItem *itemMaquina = new QTableWidgetItem;
		QTableWidgetItem *itemDesc = new QTableWidgetItem;
		QTableWidgetItem *itemCate = new QTableWidgetItem;
		QTableWidgetItem *itemcant = new QTableWidgetItem;
		QTableWidgetItem *itemIdMaq = new QTableWidgetItem;
		QTableWidgetItem *itemIdDesc = new QTableWidgetItem;

		itemMaquina->setText(maq);
		itemDesc->setText(herramienta);
		itemCate->setText("Herramienta");
		itemcant->setText(QString::number(cantH));
		itemIdMaq->setText(QString::number(idmaquinas[ui.comboBox_3->currentIndex()]));
		itemIdDesc->setText(QString::number(idherramientas[ui.comboBox_2->currentIndex()]));

		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,0,itemMaquina);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,1,itemIdMaq);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,2,itemDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,3,itemIdDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,4,itemCate);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,5,itemcant);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("La cantidad debe ser diferente de 0");
		msgBox.exec();
	}*/
}
void cosmec::sumarConsumible(){
	/*QString consumible=ui.comboBox_4->currentText();
	QString maq=ui.comboBox_3->currentText();
	int cantH=ui.spinBox_2->value();

	if(cantH!=0){
		ui.tableWidget_12->insertRow(ui.tableWidget_12->rowCount());

		QTableWidgetItem *itemMaquina = new QTableWidgetItem;
		QTableWidgetItem *itemDesc = new QTableWidgetItem;
		QTableWidgetItem *itemCate = new QTableWidgetItem;
		QTableWidgetItem *itemcant = new QTableWidgetItem;
		QTableWidgetItem *itemIdMaq = new QTableWidgetItem;
		QTableWidgetItem *itemIdDesc = new QTableWidgetItem;

		itemMaquina->setText(maq);
		itemDesc->setText(consumible);
		itemCate->setText("Consumible");
		itemcant->setText(QString::number(cantH));
		itemIdMaq->setText(QString::number(idmaquinas[ui.comboBox_3->currentIndex()]));
		itemIdDesc->setText(QString::number(idconsumibles[ui.comboBox_4->currentIndex()]));

		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,0,itemMaquina);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,1,itemIdMaq);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,2,itemDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,3,itemIdDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,4,itemCate);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,5,itemcant);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("La cantidad debe ser diferente de 0");
		msgBox.exec();
	}*/
}
void cosmec::eliminarPrimeraCotizacion(){
	int currentRow=ui.tableWidget_12->currentRow();
	ui.tableWidget_12->removeRow(currentRow);
}
void cosmec::segundaParte(){
	if(ui.lineEdit_2->text()!="" && ui.lineEdit->text()!=""){
		
		//ui.menuBar->setEnabled(false);

		QString sql;
		int numfilas=ui.tableWidget_12->rowCount();
		QString nobre=ui.lineEdit_2->text();
		int ruc=QString(ui.lineEdit->text()).toInt();
		QString direc=ui.lineEdit_3->text();
		QString telf=ui.lineEdit_4->text();
		sql=QString("INSERT INTO cotizacion(nombre,ruc,telefono,direccion)"
			"VALUES ('%1',%2,'%3','%4')").arg(nobre).arg(ruc).arg(telf).arg(direc);
		insertarsql(sql);
		
		for(int a=0;a<numfilas;a++){
			QTableWidgetItem *itab1 = ui.tableWidget_12->item(a,4);
			QTableWidgetItem *itab2 = ui.tableWidget_12->item(a,1);
			QTableWidgetItem *itab4 = ui.tableWidget_12->item(a,3);
			QTableWidgetItem *itab5 = ui.tableWidget_12->item(a,5);
			int id_maquina=QString(itab2->text()).toInt();
			int id_item=QString(itab4->text()).toInt();
			double cantidad=QString(itab5->text()).toDouble();
			double valor;
			if(itab1->text()=="Máquina"){
				sql=QString("INSERT INTO maquina_cotizacion(cantidad, numero_cotizacion, serie_maquinas) "
					"VALUES (%1,%2,%3)").arg(cantidad).arg(numerocoti).arg(id_maquina);
				insertarsql(sql);
			}
			if(itab1->text()=="Actividad"){
				sql=QString("INSERT INTO actividades_cotizacion(id_actividad_actividades, numero_cotizacion, cantidad) "
					"VALUES (%1,%2,%3)").arg(id_item).arg(numerocoti).arg(cantidad);
				insertarsql(sql);
			}
			if(itab1->text()=="Mano de obra"){
				sql=QString("SELECT SUM(a.costo_mes), c.modelo FROM actividades_trabajo AS a,mano_obra AS b, maquinas AS c "
					"WHERE c.serie=b.serie_maquinas AND b.id_actividad_actividades_trabajo=a.id_actividad AND c.serie=%1 GROUP BY c.serie").arg(id_maquina);
				double valor=sql_general(sql,0).toDouble()/160;

				sql=QString("INSERT INTO cotizacion_manoobra(serie_maquina, valor_mano, cantidad_mano, numero_cotizacion) "
					"VALUES (%1,%2,%3,%4)").arg(id_maquina).arg(valor).arg(cantidad).arg(numerocoti);
				insertarsql(sql);
			}
			if(itab1->text()=="Material"){
				sql=QString("INSERT INTO cotizacion_material(cantidad, serie_maquinas, numero_cotizacion, id_material_materiales) "
					"VALUES (%1,%2,%3,%4)").arg(cantidad).arg(id_maquina).arg(numerocoti).arg(id_item);
				insertarsql(sql);
			}
			if(itab1->text()=="Servicio Externo"){
				sql=QString("INSERT INTO servicios_cotizacion(numero_cotizacion, id_servicios_servicios_externos, " 
					"cantidad_servicios) VALUES (%1,%2,%3)").arg(numerocoti).arg(id_item).arg(cantidad);
				insertarsql(sql);
			}
		}
		ui.pushButton_35->setVisible(false);
		double subtotal=calcularcotizacion2(numerocoti);
		sql=QString("UPDATE cotizacion SET subtotal_cotizacion=%1 WHERE numero=%2").arg(subtotal).arg(numerocoti);
		insertarsql(sql);
		ui.lineEdit_27->setText(QString::number(subtotal));
		ui.lineEdit_30->setText(QString::number(iva*subtotal));
		ui.lineEdit_29->setText(QString::number((1+iva)*subtotal));
		ui.stackedWidget->setCurrentIndex(13);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("Ingrese nombre y CI/RUC del cliente");
		msgBox.exec();
	}

}
void cosmec::sumarMaq(){
	QString maquina=ui.comboBox_5->currentText();
	double cantH=ui.doubleSpinBox_2->value();

	if(cantH!=0){
		ui.tableWidget_12->insertRow(ui.tableWidget_12->rowCount());

		QTableWidgetItem *itemMaquina = new QTableWidgetItem;
		QTableWidgetItem *itemDesc = new QTableWidgetItem;
		QTableWidgetItem *itemCate = new QTableWidgetItem;
		QTableWidgetItem *itemcant = new QTableWidgetItem;
		QTableWidgetItem *itemIdMaq = new QTableWidgetItem;
		QTableWidgetItem *itemIdDesc = new QTableWidgetItem;

		itemMaquina->setText(maquina);
		itemDesc->setText(maquina);
		itemCate->setText("Máquina");
		itemcant->setText(QString::number(cantH));
		itemIdMaq->setText(QString::number(idmaquinas[ui.comboBox_5->currentIndex()])); //id maquina
		itemIdDesc->setText(QString::number(idmaquinas[ui.comboBox_5->currentIndex()])); //id maquina

		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,0,itemMaquina);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,1,itemIdMaq);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,2,itemDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,3,itemIdDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,4,itemCate);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,5,itemcant);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("El tiempo debe ser diferente de 0");
		msgBox.exec();
	}
}
void cosmec::sumarActividad(){
	QString actividad=ui.comboBox_11->currentText();
	QString maq=ui.comboBox_5->currentText();
	double cantH=ui.doubleSpinBox->value();

	if(cantH!=0){
		ui.tableWidget_12->insertRow(ui.tableWidget_12->rowCount());

		QTableWidgetItem *itemMaquina = new QTableWidgetItem;
		QTableWidgetItem *itemDesc = new QTableWidgetItem;
		QTableWidgetItem *itemCate = new QTableWidgetItem;
		QTableWidgetItem *itemcant = new QTableWidgetItem;
		QTableWidgetItem *itemIdMaq = new QTableWidgetItem;
		QTableWidgetItem *itemIdDesc = new QTableWidgetItem;

		itemMaquina->setText("Cotizacion");
		itemDesc->setText(actividad);
		itemCate->setText("Actividad");
		itemcant->setText(QString::number(cantH));
		itemIdMaq->setText(QString::number(numerocoti)); //id maquina
		itemIdDesc->setText(QString::number(idactividades[ui.comboBox_11->currentIndex()])); //id actividad

		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,0,itemMaquina);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,1,itemIdMaq);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,2,itemDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,3,itemIdDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,4,itemCate);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,5,itemcant);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("El tiempo debe ser diferente de 0");
		msgBox.exec();
	}
}
void cosmec::sumarMo(){
	QString maquina=ui.comboBox_5->currentText();
	double cantH=ui.doubleSpinBox_5->value();

	if(cantH!=0){
		ui.tableWidget_12->insertRow(ui.tableWidget_12->rowCount());

		QTableWidgetItem *itemMaquina = new QTableWidgetItem;
		QTableWidgetItem *itemDesc = new QTableWidgetItem;
		QTableWidgetItem *itemCate = new QTableWidgetItem;
		QTableWidgetItem *itemcant = new QTableWidgetItem;
		QTableWidgetItem *itemIdMaq = new QTableWidgetItem;
		QTableWidgetItem *itemIdDesc = new QTableWidgetItem;

		itemMaquina->setText(maquina);
		itemDesc->setText("Mano de obra");
		itemCate->setText("Mano de obra");
		itemcant->setText(QString::number(cantH));
		itemIdMaq->setText(QString::number(idmaquinas[ui.comboBox_5->currentIndex()])); //id maquina
		itemIdDesc->setText("Sin Id"); //id maquina

		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,0,itemMaquina);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,1,itemIdMaq);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,2,itemDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,3,itemIdDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,4,itemCate);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,5,itemcant);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("El tiempo debe ser diferente de 0");
		msgBox.exec();
	}
}
void cosmec::eliminarSegundaCotizacion(){
	int currentRow=ui.tableWidget_15->currentRow();
	ui.tableWidget_15->removeRow(currentRow);
}
void cosmec::terminarCotizacion(){
	ui.menuBar->setEnabled(true);
    //------------------------------------
	QString sql;
	int numfilas=ui.tableWidget_15->rowCount();
	for(int a=0;a<numfilas;a++){
		QTableWidgetItem *itab1 = ui.tableWidget_15->item(a,4);
		QTableWidgetItem *itab2 = ui.tableWidget_15->item(a,1);
		QTableWidgetItem *itab4 = ui.tableWidget_15->item(a,3);
		QTableWidgetItem *itab5 = ui.tableWidget_15->item(a,5);
		int id_maquina=QString(itab2->text()).toInt();
		int id_item=QString(itab4->text()).toInt();
		double cantidad=QString(itab5->text()).toDouble();
		if(itab1->text()=="Máquina"){
			sql=QString("INSERT INTO maquina_cotizacion(cantidad, numero_cotizacion, serie_maquinas) "
				"VALUES (%1,%2,%3)").arg(cantidad).arg(numerocoti).arg(id_maquina);
			insertarsql(sql);
		}
		if(itab1->text()=="Actividad"){
			sql=QString("INSERT INTO actividades_cotizacion(serie_maquinas, id_actividad_actividades, numero_cotizacion, cantidad) "
			    "VALUES (%1,%2,%3,%4)").arg(id_maquina).arg(id_item).arg(numerocoti).arg(cantidad);
			insertarsql(sql);
		}
		if(itab1->text()=="Mano de obra"){
			sql=QString("SELECT SUM(a.costo_mes), c.modelo FROM actividades_trabajo AS a,mano_obra AS b, maquinas AS c "
				"WHERE c.serie=b.serie_maquinas AND b.id_actividad_actividades_trabajo=a.id_actividad AND c.serie=%1 GROUP BY c.serie").arg(id_maquina);
			double valor=sql_general(sql,0).toDouble()/160;
			
			sql=QString("INSERT INTO cotizacion_manoobra(serie_maquina, valor_mano, cantidad_mano, numero_cotizacion) "
				"VALUES (%1,%2,%3,%4)").arg(id_maquina).arg(valor).arg(cantidad).arg(numerocoti);
			insertarsql(sql);
		}
		if(itab1->text()=="Material"){
			sql=QString("INSERT INTO cotizacion_material(cantidad, serie_maquinas, numero_cotizacion, id_material_materiales) "
			"VALUES (%1,%2,%3,%4)").arg(cantidad).arg(id_maquina).arg(numerocoti).arg(id_item);
			insertarsql(sql);
		}
	}
	//------------------------------------
	double subtotal=calcularcotizacion2(numerocoti);
	sql=QString("UPDATE cotizacion SET subtotal_cotizacion=%1 WHERE numero=%2").arg(subtotal).arg(numerocoti);
	insertarsql(sql);
	ui.lineEdit_27->setText(QString::number(subtotal));
	ui.lineEdit_30->setText(QString::number(iva*subtotal));
	ui.lineEdit_29->setText(QString::number((1+iva)*subtotal));
	ui.pushButton_35->setVisible(false);
	ui.stackedWidget->setCurrentIndex(14);
}
void cosmec::cancelarCotizacion(){
	//eliminar cotizacion
	QString sql;
	sql=QString("DELETE FROM herramientas_cotizacion WHERE numero_cotizacion=%1").arg(numerocoti);
	insertarsql(sql);
	sql=QString("DELETE FROM cotizacion_consumible WHERE numero_cotizacion=%1").arg(numerocoti);
	insertarsql(sql);
	sql=QString("DELETE FROM cotizacion	WHERE numero=%1").arg(numerocoti);
	insertarsql(sql);
	sql=sql="SELECT setval('cotizacion_numero_seq',(SELECT nextval('cotizacion_numero_seq'))-1)";
	int sec=sql_general(sql,0).toInt()-1;
	sql=QString("SELECT setval('cotizacion_numero_seq',%1)").arg(sec);
	insertarsql(sql);
	ui.menuBar->setEnabled(true);
	ui.stackedWidget->setCurrentIndex(0);
}
void cosmec::sumarMaterial(){
	QString maquina=ui.comboBox_5->currentText();
	QString material=ui.comboBox->currentText();
	double cantH=ui.doubleSpinBox_7->value();

	if(cantH!=0){
		ui.tableWidget_12->insertRow(ui.tableWidget_12->rowCount());

		QTableWidgetItem *itemMaquina = new QTableWidgetItem;
		QTableWidgetItem *itemDesc = new QTableWidgetItem;
		QTableWidgetItem *itemCate = new QTableWidgetItem;
		QTableWidgetItem *itemcant = new QTableWidgetItem;
		QTableWidgetItem *itemIdMaq = new QTableWidgetItem;
		QTableWidgetItem *itemIdDesc = new QTableWidgetItem;

		itemMaquina->setText(maquina);
		itemDesc->setText(material);
		itemCate->setText("Material");
		itemcant->setText(QString::number(cantH));
		itemIdMaq->setText(QString::number(idmaquinas[ui.comboBox_5->currentIndex()])); //id maquina
		itemIdDesc->setText(QString::number(idmaterial[ui.comboBox->currentIndex()])); //id maquina

		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,0,itemMaquina);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,1,itemIdMaq);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,2,itemDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,3,itemIdDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,4,itemCate);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,5,itemcant);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("La cantidad debe ser diferente de 0");
		msgBox.exec();
	}
}
void cosmec::sumarServExt(){
	QString servext=ui.comboBox_6->currentText();
	double cantH=ui.doubleSpinBox_3->value();

	if(cantH!=0){
		ui.tableWidget_12->insertRow(ui.tableWidget_12->rowCount());

		QTableWidgetItem *itemMaquina = new QTableWidgetItem;
		QTableWidgetItem *itemDesc = new QTableWidgetItem;
		QTableWidgetItem *itemCate = new QTableWidgetItem;
		QTableWidgetItem *itemcant = new QTableWidgetItem;
		QTableWidgetItem *itemIdMaq = new QTableWidgetItem;
		QTableWidgetItem *itemIdDesc = new QTableWidgetItem;

		itemMaquina->setText("Cotizacion");
		itemDesc->setText(servext);
		itemCate->setText("Servicio Externo");
		itemcant->setText(QString::number(cantH));
		itemIdMaq->setText(QString::number(numerocoti)); //id maquina
		itemIdDesc->setText(QString::number(idserv[ui.comboBox_6->currentIndex()])); //id actividad

		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,0,itemMaquina);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,1,itemIdMaq);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,2,itemDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,3,itemIdDesc);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,4,itemCate);
		ui.tableWidget_12->setItem(ui.tableWidget_12->rowCount()-1,5,itemcant);
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("El tiempo debe ser diferente de 0");
		msgBox.exec();
	}
}
QVariant cosmec::sql_maquina(int id,int para){
	cosmecdb.open();
	QVariant res;
	QString sql=QString("SELECT * FROM maquinas WHERE serie=%1").arg(id);
	QSqlQuery respuesta(cosmecdb);
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos :"+respuesta.lastError().databaseText());
		msgBox.exec();
		return -1;
	}else{
		while(respuesta.next()){
			res=respuesta.value(para);
		}
		cosmecdb.close();
		return res;
	}
}
QVariant cosmec::sql_herramienta(int id,int para){
	cosmecdb.open();
	QVariant res;
	QString sql=QString("SELECT * FROM herramientas WHERE id_herramienta=%1").arg(id);
	QSqlQuery respuesta(cosmecdb);
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos :"+respuesta.lastError().databaseText());
		msgBox.exec();
		return -1;
	}else{
		while(respuesta.next()){
			res=respuesta.value(para);
		}
		cosmecdb.close();
		return res;
	}
}
QVariant cosmec::sql_consumibles(int id,int para){
	cosmecdb.open();
	QVariant res;
	QString sql=QString("SELECT * FROM consumible WHERE id_consumible=%1").arg(id);
	QSqlQuery respuesta(cosmecdb);
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos"+respuesta.lastError().databaseText());
		msgBox.exec();
		return -1;
	}else{
		while(respuesta.next()){
			res=respuesta.value(para);
		}
		cosmecdb.close();
		return res;
	}
}
void cosmec::cargaridenergia(){
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	QString sql=QString("SELECT a.id_energia,b.serie FROM energia AS a, maquinas AS b WHERE b.serie=a.serie_maquinas ORDER BY b.modelo");
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos"+respuesta.lastError().databaseText());
		msgBox.exec();
	}else{
		int fila=0;
		idenergia=new int[respuesta.size()];
		while(respuesta.next()){
			idenergia[fila]=respuesta.value(0).toInt();
			fila++;
		}
		cosmecdb.close();
	}
}
void cosmec::cargaridagua(){
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	QString sql=QString("SELECT a.id_agua,b.serie FROM agua AS a, maquinas AS b WHERE b.serie=a.serie_maquinas ORDER BY b.modelo");
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos"+respuesta.lastError().databaseText());
		msgBox.exec();
	}else{
		int fila=0;
		idagua=new int[respuesta.size()];
		while(respuesta.next()){
			idagua[fila]=respuesta.value(0).toInt();
			fila++;
		}
		cosmecdb.close();
	}
}

void cosmec::cargaridactividades(){
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	QString sql=QString("SELECT b.id_actividad FROM cargo AS a,actividades_trabajo AS b WHERE a.id_cargo=b.id_cargo_cargo ORDER BY a.nombre");
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos"+respuesta.lastError().databaseText());
		msgBox.exec();
	}else{
		int fila=0;
		idactividades=new int[respuesta.size()];
		while(respuesta.next()){
			idactividades[fila]=respuesta.value(0).toInt();
			fila++;
		}
		cosmecdb.close();
	}
}
void cosmec::cargaridinsumo(){
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	QString sql=QString("SELECT a.id_insumo FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie ORDER BY b.modelo");
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos"+respuesta.lastError().databaseText());
		msgBox.exec();
	}else{
		int fila=0;
		idinsumo=new int[respuesta.size()];
		while(respuesta.next()){
			idinsumo[fila]=respuesta.value(0).toInt();
			fila++;
		}
		cosmecdb.close();
	}
}
QVariant cosmec::sql_general(QString sql,int para){
	cosmecdb.open();
	QVariant res;
	QSqlQuery respuesta(cosmecdb);
	if(!respuesta.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al consultar datos"+respuesta.lastError().databaseText());
		msgBox.exec();
		return 0;
	}else{
		while(respuesta.next()){
			res=respuesta.value(para);
		}
		return res;
	}
	cosmecdb.close();
}
void cosmec::combocotizacion(int index){
	//ui.comboBox_2->clear();
	//ui.comboBox_4->clear();
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec(QString("SELECT a.id_herramienta, a.nombre_herramienta FROM herramientas AS a, maquinas AS b WHERE a.serie_maquinas=b.serie AND b.serie=%1 ORDER BY b.modelo").arg(idmaquinas[index]));
	tamquery1=respuesta.size();
	qDebug()<<tamquery1;
	idherramientas=new int[tamquery1];
	int b=0;
	while(respuesta.next()){
		idherramientas[b]=respuesta.value(0).toInt();
		//ui.comboBox_2->addItem(respuesta.value(1).toString());
		b++;
	}

	respuesta.exec(QString("SELECT a.id_consumible, a.nombre_consumible FROM consumible AS a, maquinas AS b WHERE a.serie_maquinas=b.serie AND b.serie=%1 ORDER BY b.modelo").arg(idmaquinas[index]));
	tamquery2=respuesta.size();
	idconsumibles=new int[tamquery2];
	b=0;
	while(respuesta.next()){
		idconsumibles[b]=respuesta.value(0).toInt();
		//ui.comboBox_4->addItem(respuesta.value(1).toString());
		b++;
	}
	cosmecdb.close();
}
void cosmec::combocotizacion2(int index){
	ui.comboBox_11->clear();
	ui.comboBox->clear();
	cosmecdb.open();
	QSqlQuery respuesta(cosmecdb);
	respuesta.exec(QString("SELECT a.id_actividad, a.nombre FROM actividades AS a ORDER BY a.nombre"));
	tamquery1=respuesta.size();
	qDebug()<<tamquery1;
	idactividades=new int[tamquery1];
	int b=0;
	while(respuesta.next()){
		idactividades[b]=respuesta.value(0).toInt();
		ui.comboBox_11->addItem(respuesta.value(1).toString());
		b++;
	}

	respuesta.exec(QString("SELECT a.id_material, a.nombre FROM materiales AS a ORDER BY a.nombre").arg(idmaquinas[index]));
	tamquery2=respuesta.size();
	idmaterial=new int[tamquery2];
	b=0;
	while(respuesta.next()){
		idmaterial[b]=respuesta.value(0).toInt();
		ui.comboBox->addItem(respuesta.value(1).toString());
		b++;
	}

	cosmecdb.close();


}
void cosmec::borrartabla(QTableWidget *tableNum){
	int tam=tableNum->rowCount();
	while(tam!=0){
		qDebug()<<tam;
		//for(int a=0;a<tam-1;a++){
			qDebug()<<tableNum->rowCount()-1;
			tableNum->removeRow(tableNum->rowCount()-1);
			tam--;
		//}
	}
	tam=0;
}
void cosmec::borrartabla2(QTableWidget *tableNum2){
	int tam=tableNum2->rowCount();
	while(tam!=0){
		qDebug()<<tam;
		//for(int a=0;a<tam-1;a++){
		tableNum2->removeRow(tam);
		tam--;
		//}
	}
	tam=0;
}
double cosmec::calcularcotizacion(int numero){
	QString sql;
	QSqlQuery mac(cosmecdb);
	QSqlQuery aux(cosmecdb);
	QSqlQuery aux2(cosmecdb);
	QString nombre_maquina;
	QTableWidgetItem *nuevo;
	int b=0;
	int serie;
	int cantidad_maquina;
	double valor_herra;
	double total_mano_obra;
	double valor_consu;
	double servicios;
	double manteni;
	double costomaqui;
	double maquina;
	double total_maquina;
	double mano_obra;
	double cant_mano_obra;
	double costo_activi;
	double cant_activi;
	double total_activi=0;
	int fila=0;
	double indice=0;
	int indice2=1;
	double subtotal=0;
	double totalaux=0;
	double cant_mat=0;
	double costo_mat=0;
	double total_mat=0;
	double cant_serv=0;
	double costo_serv=0;
	double total_serv=0;
	int index=0;
	cosmecdb.open();
	mac.exec(QString("SELECT a.serie_maquinas, cantidad, b.modelo FROM  maquina_cotizacion AS a,maquinas AS b WHERE a.serie_maquinas=b.serie AND a.numero_cotizacion=%1").arg(numero));
	idmaquinacot=new int[mac.size()];
	while(mac.next()){
		serie=mac.value(0).toInt();
		idmaquinacot[index]=serie;
		cantidad_maquina=mac.value(1).toInt();
		nombre_maquina=mac.value(2).toString();
		
		//valor maquina
		sql=QString("SELECT SUM(costo_hora) FROM herramientas WHERE serie_maquinas=%1 GROUP BY serie_maquinas").arg(serie);
		valor_herra=sql_general(sql,0).toDouble();
		sql=QString("SELECT SUM(costo_hora) FROM consumible WHERE serie_maquinas=%1 GROUP BY serie_maquinas").arg(serie);
		valor_consu=sql_general(sql,0).toDouble();
		
		sql=QString("SELECT a.costo_energia+b.costo_hora,c.modelo  FROM energia AS a, agua AS b, maquinas AS c "
			"WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie AND c.serie=%1").arg(serie);
		servicios=sql_general(sql,0).toDouble();
		sql=QString("SELECT (b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora)) AS costo_total "
			"FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie AND b.serie=%1 GROUP BY b.serie").arg(serie);
		manteni=sql_general(sql,0).toDouble();
		sql=QString("SELECT ((2*costo)/(vida_util*horas_trabajo_anual)) FROM maquinas WHERE serie=%1").arg(serie);
		costomaqui=sql_general(sql,0).toDouble();
		maquina=(valor_herra+valor_consu+servicios+manteni+costomaqui);
		total_maquina=(maquina)*(1+vcomp)*cantidad_maquina;//<--
		
		//ingresa datos a tabla
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(nombre_maquina);
		ui.tableWidget_24->setItem(fila,1,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(maquina));
		ui.tableWidget_24->setItem(fila,2,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(cantidad_maquina));
		ui.tableWidget_24->setItem(fila,3,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(total_maquina));
		ui.tableWidget_24->setItem(fila,4,nuevo);
		
		fila++;
		indice=indice+0.1;

		//mano de obra
		sql=QString("SELECT valor_mano, cantidad_mano FROM cotizacion_manoobra WHERE serie_maquina=%1 AND numero_cotizacion=%2").arg(serie).arg(numero);
		mano_obra=sql_general(sql,0).toDouble();
		cant_mano_obra=sql_general(sql,1).toDouble();
		total_mano_obra=mano_obra*cant_mano_obra*(1+vcomp);//<---
		
		//ingresa datos a tabla
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText("Mano de obra");
		ui.tableWidget_24->setItem(fila,1,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(mano_obra));
		ui.tableWidget_24->setItem(fila,2,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(cant_mano_obra));
		ui.tableWidget_24->setItem(fila,3,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(total_mano_obra));
		ui.tableWidget_24->setItem(fila,4,nuevo);
		fila++;
		indice=indice+0.1;

		//Materiales
		cosmecdb.open();
		sql=QString("SELECT a.cantidad, b.costo, b.nombre FROM cotizacion_material AS a,materiales AS b WHERE a.id_material_materiales=b.id_material AND a.serie_maquinas=%1 AND a.numero_cotizacion=%2").arg(serie).arg(numero);
		if(!aux.exec(sql)){
			QMessageBox msgBox;
			msgBox.setText("Error al agregar datos :"+aux.lastError().databaseText());
			msgBox.exec();
		}else{
			while(aux.next()){
				//--------------------------------------
				cant_mat=aux.value(0).toDouble();
				costo_mat=aux.value(1).toDouble();
				total_mat=total_mat+(cant_mat*costo_mat);//<--
				//--------------------------------------
				ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(indice2+indice));
				ui.tableWidget_24->setItem(fila,0,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(aux.value(2).toString());
				ui.tableWidget_24->setItem(fila,1,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(cant_mat));
				ui.tableWidget_24->setItem(fila,3,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(costo_mat));
				ui.tableWidget_24->setItem(fila,2,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(cant_mat*costo_mat));
				ui.tableWidget_24->setItem(fila,4,nuevo);
				fila++;
				indice=indice+0.1;
			}
		}
		cosmecdb.close();
		index++;
		indice=0;
		indice2++;
		totalaux=total_maquina+total_mano_obra+total_mat;
		/*sql=QString("UPDATE maquina_cotizacion SET valor_maquina=%1 WHERE numero_cotizacion=%2 AND serie_maquinas=%3").arg(totalaux).arg(numero).arg(serie);
		insertarsql(sql);*/
		subtotal=subtotal+totalaux;
		
		//encere de variables
		valor_herra=0;
		valor_consu=0;
		servicios=0;
		manteni=0;
		costomaqui=0;
		maquina=0;
		total_maquina=0;
		mano_obra=0;
		cant_mano_obra=0;
		total_mano_obra=0;
		cant_activi=0;
		costo_activi=0;
		total_activi=0;
		cant_mat=0;
		costo_mat=0;;
		total_mat=0;
	}

	//Actividades
	cosmecdb.open();
	sql=QString("SELECT a.cantidad, b.costo_hora, b.nombre FROM actividades_cotizacion AS a,actividades AS b WHERE a.id_actividad_actividades=b.id_actividad AND a.numero_cotizacion=%2").arg(numero);
	if(!aux.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al agregar datos :"+aux.lastError().databaseText());
		msgBox.exec();
	}else{
		//cabezera
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText("Actividades");
		ui.tableWidget_24->setItem(fila,1,nuevo);
		indice=indice+0.1;
		fila++;

		while(aux.next()){
			//--------------------------------------
			cant_activi=aux.value(0).toDouble();
			costo_activi=aux.value(1).toDouble();
			total_activi=total_activi+((cant_activi*costo_activi)*(1+vcomp));//<-
			//--------------------------------------
			ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(indice2+indice));
			ui.tableWidget_24->setItem(fila,0,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(aux.value(2).toString());
			ui.tableWidget_24->setItem(fila,1,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(costo_activi));
			ui.tableWidget_24->setItem(fila,2,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_activi));
			ui.tableWidget_24->setItem(fila,3,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_activi*costo_activi));
			ui.tableWidget_24->setItem(fila,4,nuevo);
			fila++;
			indice=indice+0.1;
		}
		
	}
	cosmecdb.close();
	subtotal=subtotal+total_activi;
	indice2++;
	indice=0;

	//Servicios Externos
	cosmecdb.open();
	sql=QString("SELECT a.cantidad_servicios, b.costo_hora, b.nombre_srevicio FROM servicios_cotizacion a, servicios_externos AS b "
		"WHERE id_servicios_servicios_externos=id_servicios AND numero_cotizacion=%1").arg(numero);
	if(!aux2.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al agregar datos :"+aux2.lastError().databaseText());
		msgBox.exec();
	}else{
		//cabezera
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText("Servicios Extras");
		ui.tableWidget_24->setItem(fila,1,nuevo);
		indice=indice+0.1;
		fila++;

		while(aux2.next()){
			//--------------------------------------
			cant_serv=aux2.value(0).toDouble();
			costo_serv=aux2.value(1).toDouble();
			total_serv=total_serv+(cant_serv*costo_serv);//<-
			//--------------------------------------
			ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(indice2+indice));
			ui.tableWidget_24->setItem(fila,0,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(aux2.value(2).toString());
			ui.tableWidget_24->setItem(fila,1,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(costo_serv));
			ui.tableWidget_24->setItem(fila,2,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_serv));
			ui.tableWidget_24->setItem(fila,3,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_serv*costo_serv));
			ui.tableWidget_24->setItem(fila,4,nuevo);
			fila++;
			indice=indice+0.1;
		}
	}
	cosmecdb.close();
	subtotal=subtotal+total_serv;
	qDebug()<<subtotal;
	return subtotal;
}
double cosmec::calcularcotizacion2(int numero){
	QString sql;
	QSqlQuery mac(cosmecdb);
	QSqlQuery aux(cosmecdb);
	QSqlQuery aux2(cosmecdb);
	QString nombre_maquina;
	QTableWidgetItem *nuevo;
	int b=0;
	int serie;
	int cantidad_maquina;
	double valor_herra;
	double total_mano_obra;
	double valor_consu;
	double servicios;
	double manteni;
	double costomaqui;
	double maquina;
	double total_maquina;
	double mano_obra;
	double cant_mano_obra;
	double costo_activi;
	double cant_activi;
	double total_activi=0;
	int fila=0;
	double indice=0;
	int indice2=1;
	double subtotal=0;
	double totalaux=0;
	double cant_mat=0;
	double costo_mat=0;
	double total_mat=0;
	double cant_serv=0;
	double costo_serv=0;
	double total_serv=0;
	int index=0;
	cosmecdb.open();
	mac.exec(QString("SELECT a.serie_maquinas, cantidad, b.modelo FROM  maquina_cotizacion AS a,maquinas AS b WHERE a.serie_maquinas=b.serie AND a.numero_cotizacion=%1").arg(numero));
	idmaquinacot=new int[mac.size()];
	while(mac.next()){
		serie=mac.value(0).toInt();
		idmaquinacot[index]=serie;
		cantidad_maquina=mac.value(1).toInt();
		nombre_maquina=mac.value(2).toString();
		
		//valor maquina
		sql=QString("SELECT SUM(costo_hora) FROM herramientas WHERE serie_maquinas=%1 GROUP BY serie_maquinas").arg(serie);
		valor_herra=sql_general(sql,0).toDouble();
		sql=QString("SELECT SUM(costo_hora) FROM consumible WHERE serie_maquinas=%1 GROUP BY serie_maquinas").arg(serie);
		valor_consu=sql_general(sql,0).toDouble();
		
		sql=QString("SELECT a.costo_energia+b.costo_hora,c.modelo  FROM energia AS a, agua AS b, maquinas AS c "
			"WHERE b.serie_maquinas=a.serie_maquinas AND b.serie_maquinas=c.serie AND c.serie=%1").arg(serie);
		servicios=sql_general(sql,0).toDouble();
		sql=QString("SELECT (b.presupuesto_anual/b.horas_trabajo_anual)+(SUM(a.costo_hora)) AS costo_total "
			"FROM mantenimiento_preventivo AS a,maquinas AS b WHERE a.serie_maquinas=b.serie AND b.serie=%1 GROUP BY b.serie").arg(serie);
		manteni=sql_general(sql,0).toDouble();
		sql=QString("SELECT ((2*costo)/(vida_util*horas_trabajo_anual)) FROM maquinas WHERE serie=%1").arg(serie);
		costomaqui=sql_general(sql,0).toDouble();
		maquina=(valor_herra+valor_consu+servicios+manteni+costomaqui);
		total_maquina=(maquina)*(1+vcomp)*cantidad_maquina;//<--
		//----------------
		sql=QString("UPDATE cotizacion_manoobra SET valor_maquinas=%1, cantidad_maquina=%2 "
			"WHERE serie_maquina=%3 AND numero_cotizacion=%4").arg(maquina).arg(cantidad_maquina).arg(serie).arg(numero);
		insertarsql(sql);
		//----------------
		//ingresa datos a tabla
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(nombre_maquina);
		ui.tableWidget_24->setItem(fila,1,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(maquina));
		ui.tableWidget_24->setItem(fila,2,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(cantidad_maquina));
		ui.tableWidget_24->setItem(fila,3,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(total_maquina));
		ui.tableWidget_24->setItem(fila,4,nuevo);
		
		fila++;
		indice=indice+0.1;

		//mano de obra
		sql=QString("SELECT valor_mano, cantidad_mano FROM cotizacion_manoobra WHERE serie_maquina=%1 AND numero_cotizacion=%2").arg(serie).arg(numero);
		mano_obra=sql_general(sql,0).toDouble();
		cant_mano_obra=sql_general(sql,1).toDouble();
		total_mano_obra=mano_obra*cant_mano_obra*(1+vcomp);//<---
		
		//ingresa datos a tabla
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText("Mano de obra");
		ui.tableWidget_24->setItem(fila,1,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(mano_obra));
		ui.tableWidget_24->setItem(fila,2,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(cant_mano_obra));
		ui.tableWidget_24->setItem(fila,3,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(total_mano_obra));
		ui.tableWidget_24->setItem(fila,4,nuevo);
		fila++;
		indice=indice+0.1;

		//Materiales
		cosmecdb.open();
		sql=QString("SELECT a.cantidad, b.costo, b.nombre FROM cotizacion_material AS a,materiales AS b WHERE a.id_material_materiales=b.id_material AND a.serie_maquinas=%1 AND a.numero_cotizacion=%2").arg(serie).arg(numero);
		if(!aux.exec(sql)){
			QMessageBox msgBox;
			msgBox.setText("Error al agregar datos :"+aux.lastError().databaseText());
			msgBox.exec();
		}else{
			while(aux.next()){
				//--------------------------------------
				cant_mat=aux.value(0).toDouble();
				costo_mat=aux.value(1).toDouble();
				total_mat=total_mat+(cant_mat*costo_mat);//<--
				//--------------------------------------
				ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(indice2+indice));
				ui.tableWidget_24->setItem(fila,0,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(aux.value(2).toString());
				ui.tableWidget_24->setItem(fila,1,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(cant_mat));
				ui.tableWidget_24->setItem(fila,3,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(costo_mat));
				ui.tableWidget_24->setItem(fila,2,nuevo);
				nuevo=new QTableWidgetItem();
				nuevo->setText(QString::number(cant_mat*costo_mat));
				ui.tableWidget_24->setItem(fila,4,nuevo);
				fila++;
				indice=indice+0.1;
			}
		}
		cosmecdb.close();
		//--------------------------
		sql=QString("UPDATE cotizacion_manoobra SET valor_material=%1 "
			"WHERE serie_maquina=%2 AND numero_cotizacion=%3").arg(total_mat).arg(serie).arg(numero);
		insertarsql(sql);
		//--------------------------
		index++;
		indice=0;
		indice2++;
		totalaux=total_maquina+total_mano_obra+total_mat;
		/*sql=QString("UPDATE maquina_cotizacion SET valor_maquina=%1 WHERE numero_cotizacion=%2 AND serie_maquinas=%3").arg(totalaux).arg(numero).arg(serie);
		insertarsql(sql);*/
		subtotal=subtotal+totalaux;
		
		//encere de variables
		valor_herra=0;
		valor_consu=0;
		servicios=0;
		manteni=0;
		costomaqui=0;
		maquina=0;
		total_maquina=0;
		mano_obra=0;
		cant_mano_obra=0;
		total_mano_obra=0;
		cant_activi=0;
		costo_activi=0;
		total_activi=0;
		cant_mat=0;
		costo_mat=0;;
		total_mat=0;
	}

	//Actividades
	cosmecdb.open();
	sql=QString("SELECT a.cantidad, b.costo_hora, b.nombre FROM actividades_cotizacion AS a,actividades AS b WHERE a.id_actividad_actividades=b.id_actividad AND a.numero_cotizacion=%2").arg(numero);
	if(!aux.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al agregar datos :"+aux.lastError().databaseText());
		msgBox.exec();
	}else{
		//cabezera
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText("Actividades");
		ui.tableWidget_24->setItem(fila,1,nuevo);
		indice=indice+0.1;
		fila++;

		while(aux.next()){
			//--------------------------------------
			cant_activi=aux.value(0).toDouble();
			costo_activi=aux.value(1).toDouble();
			total_activi=total_activi+((cant_activi*costo_activi)*(1+vcomp));//<-
			//--------------------------------------
			ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(indice2+indice));
			ui.tableWidget_24->setItem(fila,0,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(aux.value(2).toString());
			ui.tableWidget_24->setItem(fila,1,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(costo_activi));
			ui.tableWidget_24->setItem(fila,2,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_activi));
			ui.tableWidget_24->setItem(fila,3,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_activi*costo_activi));
			ui.tableWidget_24->setItem(fila,4,nuevo);
			fila++;
			indice=indice+0.1;
		}
		
	}
	cosmecdb.close();
	subtotal=subtotal+total_activi;
	indice2++;
	indice=0;

	//Servicios Externos
	cosmecdb.open();
	sql=QString("SELECT a.cantidad_servicios, b.costo_hora, b.nombre_srevicio FROM servicios_cotizacion a, servicios_externos AS b "
		"WHERE id_servicios_servicios_externos=id_servicios AND numero_cotizacion=%1").arg(numero);
	if(!aux2.exec(sql)){
		QMessageBox msgBox;
		msgBox.setText("Error al agregar datos :"+aux2.lastError().databaseText());
		msgBox.exec();
	}else{
		//cabezera
		ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
		nuevo=new QTableWidgetItem();
		nuevo->setText(QString::number(indice2+indice));
		ui.tableWidget_24->setItem(fila,0,nuevo);
		nuevo=new QTableWidgetItem();
		nuevo->setText("Servicios Extras");
		ui.tableWidget_24->setItem(fila,1,nuevo);
		indice=indice+0.1;
		fila++;

		while(aux2.next()){
			//--------------------------------------
			cant_serv=aux2.value(0).toDouble();
			costo_serv=aux2.value(1).toDouble();
			total_serv=total_serv+(cant_serv*costo_serv);//<-
			//--------------------------------------
			ui.tableWidget_24->insertRow(ui.tableWidget_24->rowCount());
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(indice2+indice));
			ui.tableWidget_24->setItem(fila,0,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(aux2.value(2).toString());
			ui.tableWidget_24->setItem(fila,1,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(costo_serv));
			ui.tableWidget_24->setItem(fila,2,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_serv));
			ui.tableWidget_24->setItem(fila,3,nuevo);
			nuevo=new QTableWidgetItem();
			nuevo->setText(QString::number(cant_serv*costo_serv));
			ui.tableWidget_24->setItem(fila,4,nuevo);
			fila++;
			indice=indice+0.1;
		}
	}
	cosmecdb.close();
	subtotal=subtotal+total_serv;
	qDebug()<<subtotal;
	return subtotal;
}
