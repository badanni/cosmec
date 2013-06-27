#ifndef DB_H
#define DB_H
#include <libpq-fe.h>
#include <iostream>
#include <sstream>
#include <string>
#include "XmlExcel.h"
#include <list>
#include "ctype.h"


using namespace std;

extern elemento da;
extern hoja das;


class db{
	public:
	db();
	~db();
	void inicio(string ip_db, string puerto_db, string base_db, string usuario_db, string clave_db);
	PGconn *conectar();
	void consulta(PGconn *conn,string nombre,string columnas);
	void consulta_tipo(PGconn *conn,string nombre);
	list <hoja> consulta(PGconn *conn,list <hoja> list_filas,string sql_e);
	list <hoja> db::consulta_menus(PGconn *conn,list <hoja> list_filas,string item);
	void usuarios_predefinidos(PGconn *conn,string nombre,string clave,int nivel, string correo,int cedula);
	void clientes_predefinidos(PGconn *conn,string cedula,string nombre,string apellido,string telefono1, string telefono2, string correo);
	void paradas_predefinidos(PGconn *conn,string coord,string nombre);
	void choferes_predefinidos(PGconn *conn,int cedula,string nombre,string apellido,string telefono);
	void vehiculo_predefinidos(PGconn *conn,string placa,int velocidad,string coord,string monitoreo_continuo, int cedula_choferes);
	void ruta_predefinidos(PGconn *conn,string nombre,int id_paradas,int id_vehiculo, int orden);
	void desconectar(PGconn *conn);
	void borrar_datos(PGconn *conn,string nombre);
	void reinicio_seq(PGconn *conn,string sequiencia,string tabla);
	void lectura();
	bool db::esunnumero(char* dato);
	void escritura(int a);
	private:
	string ip;
	string puerto;
	string base;
	string usuario;
	string clave;
};

#endif
