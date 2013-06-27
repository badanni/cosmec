#ifndef COSMEC_H
#define COSMEC_H

#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QImage>
#include <QtGui/QComboBox>
#include <QtGui/QRadioButton>
#include <QtGui/QCheckBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QThread>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QtDebug>
#include "ncreport.h"
#include "ncreportpreviewwindow.h"
#include "ncreportpreviewoutput.h"
#include "libpq-fe.h"
#include "ui_cosmec.h"
#include "dialogdetalle.h"
#include "db.h"
#include "XmlExcel.h"


class cosmec : public QMainWindow
{
	Q_OBJECT

public:
	cosmec(QWidget *parent = 0, Qt::WFlags flags = 0);
	~cosmec();

private:
	Ui::cosmecClass ui;
	QComboBox *comboMaquina, *comboCategoria, *comboCarg, *comboAct, *comboInsumo;
	QString host;
	QString pass2;
	QString puerto;
	QString usuario;
	double iva;
	QSqlDatabase cosmecdb;
	QSqlRecord record;
	int *idquery1;
	int *idmaquinacot;
	int *idact;
	int *idmaquinas;
	int *idserv;
	int *idherramientas;
	int *idconsumibles;
	int *idactividades;
	int *idcargo;
	int *idquery2;
	int *idenergia;
	int *idagua;
	int *idinsumo;
	int *idinsumocombo;
	int *idmaterial;
	int tamquery1;
	int tamquery2;
	int numerocoti;
	double vcomp;
	NCReport *report;
	NCReportPreviewWindow *pv;
	void comboMaq(QTableWidget *tableNum,int fil, int col);
	void comboCat(QTableWidget *tableNum,int fil, int col);
	void comboCargo(QTableWidget *tableNum,int fil, int col);
	void comboActividades(QTableWidget *tableNum,int fil, int col);
	void comboinsumos(QTableWidget *tableNum,int fil, int col);
	void reportesinter(NCReport *report);
	void llenartabla(QTableWidget *tableNum,QString sql);
	void insertarsql(QSqlQuery respuesta);
	void insertarsql(QString sql);
	QVariant sql_maquina(int id,int para);
	QVariant sql_herramienta(int id,int para);
	QVariant sql_consumibles(int id,int para);
	QVariant sql_general(QString sql,int para);
	void cargaridenergia();
	void cargaridagua();
	void cargaridactividades();
	void cargaridinsumo();
	void borrartabla(QTableWidget *tableNum);
	double calcularcotizacion(int numero);
	double calcularcotizacion2(int numero);
	void borrartabla2(QTableWidget *tableNum2);
	

private slots:
	//cotizaciones
	void combocotizacion(int index);
	void combocotizacion2(int index);
	//Configuracion
	void guardarConfig();
	void configurar();
	void conexion();
	//reportes
	void reportgenerador();
	void reporteexel();
	//Cambios de stack
	void setmaquina();
	void setherramienta();
	void setconsumible();
	void setenergia();
	void setmantenimiento();
	void setmanoobra();
	void setactividades();
	void setconfig();
	void setactividadesMo();
	void setnuevaCotizacion();
	void setbuscarCotizacion();
	void setmateriales();
	void setrptcotizaciones();
	void setServiciosExternos();
	//reportes
	void setgenerador();
	void setreporteexel();
	//mano de obra - cargos
	void agregarfila();
	void actualizar();
	void eliminarFila();
	void filaEditable(int row, int column);
	//maquinaria
	void agregarfilaMaq();
	void actualizarMaq();
	void eliminarFilaMaq();
	void filaEditableMaq(int row, int column);
	//servicios externos
	void agregarfilaSExternos();
	void actualizarSExternos();
	void eliminarFilaSExternos();
	void filaEditableSExternos(int row, int column);
	//herramientas
	void agregarfilaHe();
	void actualizarHe();
	void eliminarFilaHe();
	void filaEditableHe(int row, int column);
	//consumibles
	void agregarfilaCons();
	void actualizarCons();
	void eliminarFilaCons();
	void filaEditableCons(int row, int column);
	//servicios básicos
	void agregarfilaSer();
	void actualizarSer();
	void eliminarFilaSer();
	void filaEditableSer(int row, int column);
	//mtto -insumos
	void agregarfilaMtto();
	void actualizarMtto();
	void eliminarFilaMtto();
	void filaEditableMtto(int row, int column);
	//mtto - preventivo
	//void agregarfilaPrev();
	//void actualizarPrev();
	//void eliminarFilaPrev();
	//void filaEditablePrev(int row, int column);
	//actividades -categorias
	void agregarfilaActC();
	void actualizarActC();
	void eliminarFilaActC();
	void filaEditableActC(int row, int column);
	//actividades -actividades
	void agregarfilaActAct();
	void actualizarActAct();
	void eliminarFilaActAct();
	void filaEditableActAct(int row, int column);
	//mano de obra - actividades
	void agregarfilaMo();
	void actualizarMo();
	void eliminarFilaMo();
	void filaEditableMo(int row, int column);
	//actividades - maquina
	void agregarfilaMaqActividades();
	//void actualizarMaqActividades();
	void eliminarFilaMaqActividades();
	//void filaEditableMaqActividades(int row,int column);
	//materiales
	void agregarfilaMat();
	void actualizarMat();
	void eliminarFilaMat();
	void filaEditableMat(int row, int column);
	//buscar cotización
	void habilitarBuscarRuc();
	void habilitarBuscarCotizacion();
	void buscarCotizacion();
	void resultadoCotizacion();
	void imprimirCotizacion();
	void detalle();
	//nueva cotización
	void sumarHerramienta();
	void sumarConsumible();
	void eliminarPrimeraCotizacion();
	void segundaParte();
	void sumarMaq();
	void sumarActividad();
	void sumarMo();
	void sumarMaterial();
	void sumarServExt();
	void eliminarSegundaCotizacion();
	void terminarCotizacion();
	void cancelarCotizacion();

};

#endif // COSMEC_H
