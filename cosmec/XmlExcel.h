#ifndef xmlexcel_H
#define xmlexcel_H
#include "tinyxml.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

typedef struct {
	char dato[60];
	char tipo[20];
	bool menu;
}elemento;

typedef struct {
	list <elemento> tabla;
}hoja;

class XmlExcel
{
public:
	XmlExcel(void);
	~XmlExcel(void);
	TiXmlDeclaration* XmlExcel::cabecera();
	TiXmlElement* XmlExcel::crear_estilos();
	TiXmlElement* XmlExcel::crear_documento_libro(char autor1[],char fecha1[]);
	TiXmlElement* XmlExcel::crear_hoja(char nombre[]);
	TiXmlElement* XmlExcel::crear_tabla(char x[],char y[]);
	TiXmlElement * XmlExcel::salto_linea();
	TiXmlElement * XmlExcel::crear_cell_tabla_titulo(char titulo[],char tipo1[],char longi[]);
	TiXmlElement * XmlExcel::crear_general_titulo(char titulo[],char tipo1[],char comienzo[],char longi[],char height[]);
	TiXmlElement* XmlExcel::row_anadido_dato(TiXmlElement* row,char dato[],char tipo[],char estilo_tipo[],bool menu);
	TiXmlElement* XmlExcel::row_anadido_dato(TiXmlElement* row,char dato[],char tipo[],char estilo_tipo[], char posicion_tipo[],bool menu);
	void XmlExcel::guardar_archivo(TiXmlDocument doc,char archivo[]);
	void XmlExcel::abrir_archivo(char archivo[]);
	TiXmlElement* XmlExcel::row_lista_anadido_dato(TiXmlElement* table,list <hoja> list_filas);
	list <hoja> XmlExcel::row_anadido_menu(list <hoja> list_filas,int opcion);
private:
};
#endif
