#include "db.h"



db::db(){}
db::~db(){}
void db::inicio(string ip_db, string puerto_db, string base_db, string usuario_db, string clave_db){
	ip=ip_db;
	puerto=puerto_db;
	base=base_db;
	usuario=usuario_db;
	clave=clave_db;
	
}
PGconn *db::conectar(){
	PGconn *conn;
	const char *ip_a=ip.c_str();
	const char *puerto_a=puerto.c_str();
	const char *base_a=base.c_str();
	const char *usuario_a=usuario.c_str();
	const char *clave_a=clave.c_str();
	conn = PQsetdbLogin(ip_a,puerto_a,NULL,NULL,base_a,usuario_a,clave_a);
	//conn = PQsetdbLogin("192.168.1.120","5432",NULL,NULL,"nremit","base","sotus");
	return conn;
}
void db::consulta(PGconn *conn,string nombre,string columnas){
	PGresult *res;
	int i, j;
	string sql;
	stringstream msg;
	msg<<"select "<<columnas<<" from "<<nombre;
	sql=msg.str();
	const char *a=sql.c_str();
	if (PQstatus(conn) != CONNECTION_BAD){
	res = PQexec(conn, a);
	if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res)){
		for (i = 0; i < PQntuples(res); i++){
			for (j = 0; j < PQnfields(res); j++){
				printf("%s\t",PQgetvalue(res,i,j));
			}
			printf("\n");
		}
		PQclear(res);
	}
	}
}
void db::consulta_tipo(PGconn *conn,string nombre){
	PGresult *res;
	int i, j;
	string sql;
	stringstream msg;
	msg<<"Select  column_name, data_type from information_schema.columns WHERE TABLE_NAME='"<<nombre<<"'";
	sql=msg.str();
	const char *a=sql.c_str();
	if (PQstatus(conn) != CONNECTION_BAD){
	res = PQexec(conn, a);
	if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res)){
		for (i = 0; i < PQntuples(res); i++){
			for (j = 0; j < PQnfields(res); j++){
				printf("%s\t",PQgetvalue(res,i,j));
			}
			printf("\n");
		}
		PQclear(res);
	}
	}
}
bool db::esunnumero(char* dato){
	int aux;
	int longitud = strlen(dato);
	for (int i=0; i<longitud;i++){
		if(isalpha(dato[i])){
			return false;
		}
	}
	return true;
}
list <hoja> db::consulta(PGconn *conn,list <hoja> list_filas,string sql_e){
	elemento coor;
	hoja who;
	list <elemento> list_coordenadas;
	PGresult *res;
	int i, j;
	string sql;
	stringstream msg;
	//msg<<"select * from "<<nombre;
	msg<<sql_e;
	sql=msg.str();
	const char *a=sql.c_str();
	if (PQstatus(conn) != CONNECTION_BAD){
	res = PQexec(conn, a);
	if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res)){
		for (i = 0; i < PQntuples(res); i++){
			for (j = 0; j < PQnfields(res); j++){
				//printf("%s\t",PQgetvalue(res,i,j));
				strcpy(coor.dato,PQgetvalue(res,i,j));
				if (esunnumero(coor.dato)){ //solo si no tiene numero al comienzo
					strcpy(coor.tipo,"Number");
				}
				else{
					strcpy(coor.tipo,"String");
				}
				coor.menu=false;
				list_coordenadas.push_back(coor);
			}
			//printf("\n");
			who.tabla=list_coordenadas; //engresa el row de datos a la tabla who
			list_filas.push_back(who);
			list_coordenadas.clear();
		}
		PQclear(res);
	}
	}
	return list_filas;
}
list <hoja> db::consulta_menus(PGconn *conn,list <hoja> list_filas,string item){
	elemento coor;
	hoja who;
	list <elemento> list_coordenadas;
	PGresult *res;
	int i, j;
	string sql;
	stringstream msg;
	//select nombre, cantidad, cam1,cam2,cam3,cam4,cam5,cam6,cam7,cam8,cam9,cam10 from menus where id=1
	msg<<"select nombre, cantidad, cam1,cam2,cam3,cam4,cam5,cam6,cam7,cam8,cam9,cam10 from menus where id="<<item;
	sql=msg.str();
	const char *a=sql.c_str();
	if (PQstatus(conn) != CONNECTION_BAD){
	res = PQexec(conn, a);
	if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res)){
		for (i = 0; i < PQntuples(res); i++){
			int final=atoi(PQgetvalue(res,i,1))+2;
			//cout<<final;
			for (j = 2; j < final; j++){//for (j = 2; j < PQnfields(res); j++)
				//printf("%s\t",PQgetvalue(res,i,j));
				strcpy(coor.dato,PQgetvalue(res,i,j));
				strcpy(coor.tipo,"String");
				coor.menu=true;
				list_coordenadas.push_back(coor);
			}
			//printf("\n");
			who.tabla=list_coordenadas; //engresa el row de datos a la tabla who
			list_filas.push_back(who);
			list_coordenadas.clear();
		}
		PQclear(res);
	}
	}
	return list_filas;
}
void db::usuarios_predefinidos(PGconn *conn,string nombre,string clave,int nivel, string correo,int cedula){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"INSERT INTO usuario (nombre, clave, nivel, correo, cedula_cliente) VALUES ('"<<nombre<<"', '"<<clave<<"', "<<nivel<<", '"<<correo<<"', "<<cedula<<")";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		cout << "Fallo al crear al usuario "<<nombre<<" "<<cedula<<" \n";
	}
	else{
	cout << "Creado al usuario "<<nombre<<" "<<cedula<<" \n";
	}
	PQclear(res);
}
void db::clientes_predefinidos(PGconn *conn,string cedula,string nombre,string apellido,string telefono1, string telefono2, string correo){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"INSERT INTO cliente (cedula, nombre, apellido, telefono1, telefono2, correo) VALUES ("<<cedula<<", '"<<nombre<<"', '"<<apellido<<"', '"<<telefono1<<"', '"<<telefono2<<"', '"<<correo<<"')";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		cout << "Fallo al crear al cliente "<<nombre<<" "<<apellido<<" \n";
	}
	else{
		cout << "Creado el cliente "<<nombre<<" "<<apellido<<" \n";
	}
	PQclear(res);
}
void db::paradas_predefinidos(PGconn *conn,string coord,string nombre){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"INSERT INTO paradas (coordenadas, nombre) VALUES (point("<<coord<<"), '"<<nombre<<"')";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		cout << "Fallo al crear la parada en POINT("<<coord<<") "<<nombre<<" \n";
	}
	else{
		cout << "Creada la parada en POINT("<<coord<<") "<<nombre<<" \n";
	}
	PQclear(res);
}
void db::choferes_predefinidos(PGconn *conn,int cedula,string nombre,string apellido,string telefono){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"INSERT INTO choferes (cedula, nombre, apellido, telefono) VALUES ("<<cedula<<", '"<<nombre<<"', '"<<apellido<<"', '"<<telefono<<"')";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		cout << "Fallo al crear al chofer "<<nombre<<" "<<apellido<<" \n";
	}
	else{
		cout << "Creado el chofer "<<nombre<<" "<<apellido<<" \n";
	}
	PQclear(res);
}
void db::vehiculo_predefinidos(PGconn *conn,string placa,int velocidad,string coord,string monitoreo_continuo, int cedula_choferes){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"INSERT INTO vehiculo (placa, velocidad, coordenadas, monitoreo_continuo, cedula_choferes) VALUES ('"<<placa<<"', "<<velocidad<<", point("<<coord<<"), "<<monitoreo_continuo<<", "<<cedula_choferes<<")";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		cout << "Fallo al crear el vehiculo "<<placa<<" \n";
	}
	else{
		cout << "Creado el vehiculo "<<placa<<" \n";
	}
	PQclear(res);
}
void db::ruta_predefinidos(PGconn *conn,string nombre,int id_paradas,int id_vehiculo, int orden){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"INSERT INTO ruta (nombre, id_paradas, id_vehiculo, orden) VALUES ('"<<nombre<<"', "<<id_paradas<<", "<<id_vehiculo<<", "<<orden<<")";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		cout << "Fallo al crear la ruta '"<<nombre<<"' relacion parada="<<id_paradas<<" vehiculo="<<id_vehiculo<<" \n";
	}
	else{
		cout << "Creada la ruta '"<<nombre<<"' relacion parada="<<id_paradas<<" vehiculo="<<id_vehiculo<<" \n";;
	}
	PQclear(res);
}
void db::desconectar(PGconn *conn){
	PQfinish(conn);
}
void db::borrar_datos(PGconn *conn,string nombre){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"delete from "<<nombre<<" where true";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		cout << "Fallo al borrar los datos de la tabla "<<nombre<<"\n";
	}
	else{
		cout << "Borrado los datos de la tabla "<<nombre<<"\n";
	}
	PQclear(res);
}
void db::reinicio_seq(PGconn *conn,string sequiencia,string tabla){
	PGresult *res;
	string sql;
	stringstream msg;
	msg<<"ALTER SEQUENCE "<<sequiencia<<" RESTART";
	sql=msg.str();
	const char *a=sql.c_str();
	res=PQexec(conn,a);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		cout << "Listo 1"<<tabla<<endl;
	}
	else{
		cout << "Fallo 1 pero OK"<<tabla<<endl;
	}
	PQclear(res);
	//das
	PGresult *res1;
	string sql1;
	stringstream msg1;
	msg1<<"UPDATE "<<tabla<<" SET id = DEFAULT";
	sql1=msg1.str();
	const char *b=sql1.c_str();
	res1=PQexec(conn,b);
	if (PQresultStatus(res1) != PGRES_COMMAND_OK){
		cout << "Listo 2"<<tabla<<endl;
	}
	else{
		cout << "Fallo 2 pero OK"<<tabla<<endl;
	}
	PQclear(res1);
}
void db::lectura(){
	int a;
	a=1;
	cout<<a<<endl;
}
void db::escritura(int a){
	cout<<a<<endl;
}

