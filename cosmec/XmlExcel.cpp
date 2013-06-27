#include "XmlExcel.h"

XmlExcel::XmlExcel(void)
{
}

XmlExcel::~XmlExcel(void)
{
}
TiXmlDeclaration* XmlExcel::cabecera(){
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	return decl;
}
TiXmlElement* XmlExcel::crear_estilos(){
	TiXmlElement * styles = new TiXmlElement( "Styles" );
	TiXmlElement * style = new TiXmlElement( "Style" );
	TiXmlElement * style1 = new TiXmlElement( "Style" );
	TiXmlElement * style2 = new TiXmlElement( "Style" );
	TiXmlElement * style3 = new TiXmlElement( "Style" );
	TiXmlElement * style4 = new TiXmlElement( "Style" );
	TiXmlElement * style5 = new TiXmlElement( "Style" );
	TiXmlElement * style6 = new TiXmlElement( "Style" );
	TiXmlElement * style7 = new TiXmlElement( "Style" );
	style->SetAttribute("ss:ID","Default");
	style->SetAttribute("ss:Name","Normal");
	style1->SetAttribute("ss:ID","s16");
	style2->SetAttribute("ss:ID","s18");
	style3->SetAttribute("ss:ID","s19");
	style4->SetAttribute("ss:ID","s20");
	style5->SetAttribute("ss:ID","s21");
	style6->SetAttribute("ss:ID","s22");
	style7->SetAttribute("ss:ID","s23");
	//Default
	TiXmlElement * alignment= new TiXmlElement( "Alignment" );
	alignment->SetAttribute("ss:Vertical","Bottom");
	TiXmlElement * borders= new TiXmlElement( "Borders" );
	TiXmlElement * font= new TiXmlElement( "Font" );
	font->SetAttribute("ss:FontName","Calibri");
	font->SetAttribute("x:Family","Swiss");
	font->SetAttribute("ss:Size","11");
	font->SetAttribute("ss:Color","#000000");
	TiXmlElement * interior= new TiXmlElement( "Interior" );
	TiXmlElement * numberformat= new TiXmlElement( "NumberFormat" );
	TiXmlElement * protection= new TiXmlElement( "Protection" );
	style->LinkEndChild(alignment);
	style->LinkEndChild(borders);
	style->LinkEndChild(font);
	style->LinkEndChild(interior);
	style->LinkEndChild(numberformat);
	style->LinkEndChild(protection);
	//s16
	TiXmlElement * alignment1= new TiXmlElement( "Alignment" );
	alignment1->SetAttribute("ss:Horizontal","Center");
	alignment1->SetAttribute("ss:Vertical","Center");
	TiXmlElement * borders1= new TiXmlElement( "Borders" );
	style1->LinkEndChild(alignment1);
	style1->LinkEndChild(borders1);
	//s18
	TiXmlElement * alignment2= new TiXmlElement( "Alignment" );
	alignment2->SetAttribute("ss:Horizontal","Center");
	alignment2->SetAttribute("ss:Vertical","Center");
	TiXmlElement * borders2= new TiXmlElement( "Borders" );
	TiXmlElement * border2a= new TiXmlElement( "Border" );
	border2a->SetAttribute("ss:Position","Bottom");
	border2a->SetAttribute("ss:LineStyle","Continuous");
	border2a->SetAttribute("ss:Weight","1");
	border2a->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border2b= new TiXmlElement( "Border" );
	border2b->SetAttribute("ss:Position","Left");
	border2b->SetAttribute("ss:LineStyle","Continuous");
	border2b->SetAttribute("ss:Weight","1");
	border2b->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border2c= new TiXmlElement( "Border" );
	border2c->SetAttribute("ss:Position","Right");
	border2c->SetAttribute("ss:LineStyle","Continuous");
	border2c->SetAttribute("ss:Weight","1");
	border2c->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border2d= new TiXmlElement( "Border" );
	border2d->SetAttribute("ss:Position","Top");
	border2d->SetAttribute("ss:LineStyle","Continuous");
	border2d->SetAttribute("ss:Weight","3");
	TiXmlElement * font2= new TiXmlElement( "Font" );
	font2->SetAttribute("ss:FontName","Calibri");
	font2->SetAttribute("x:Family","Swiss");
	font2->SetAttribute("ss:Size","11");
	font2->SetAttribute("ss:Bold","1");
	TiXmlElement * interior2= new TiXmlElement( "Interior" );
	interior2->SetAttribute("ss:Color","#C4D79B");
	interior2->SetAttribute("ss:Pattern","Solid");
	style2->LinkEndChild(alignment2);
	borders2->LinkEndChild(border2a);
	borders2->LinkEndChild(border2b);
	borders2->LinkEndChild(border2c);
	borders2->LinkEndChild(border2d);
	style2->LinkEndChild(borders2);
	style2->LinkEndChild(font2);
	style2->LinkEndChild(interior2);
	//s19
	TiXmlElement * alignment3= new TiXmlElement( "Alignment" );
	alignment3->SetAttribute("ss:Horizontal","Center");
	alignment3->SetAttribute("ss:Vertical","Center");
	TiXmlElement * borders3= new TiXmlElement( "Borders" );
	TiXmlElement * border3a= new TiXmlElement( "Border" );
	border3a->SetAttribute("ss:Position","Bottom");
	border3a->SetAttribute("ss:LineStyle","Continuous");
	border3a->SetAttribute("ss:Weight","1");
	border3a->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border3b= new TiXmlElement( "Border" );
	border3b->SetAttribute("ss:Position","Left");
	border3b->SetAttribute("ss:LineStyle","Continuous");
	border3b->SetAttribute("ss:Weight","1");
	border3b->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border3c= new TiXmlElement( "Border" );
	border3c->SetAttribute("ss:Position","Right");
	border3c->SetAttribute("ss:LineStyle","Continuous");
	border3c->SetAttribute("ss:Weight","1");
	border3c->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border3d= new TiXmlElement( "Border" );
	border3d->SetAttribute("ss:Position","Top");
	border3d->SetAttribute("ss:LineStyle","Continuous");
	border3d->SetAttribute("ss:Weight","1");
	border3d->SetAttribute("ss:Color","#76933C");
	style3->LinkEndChild(alignment3);
	borders3->LinkEndChild(border3a);
	borders3->LinkEndChild(border3b);
	borders3->LinkEndChild(border3c);
	borders3->LinkEndChild(border3d);
	style3->LinkEndChild(borders3);
	//s20
	TiXmlElement * alignment4= new TiXmlElement( "Alignment" );
	alignment4->SetAttribute("ss:Horizontal","Center");
	alignment4->SetAttribute("ss:Vertical","Center");
	TiXmlElement * borders4= new TiXmlElement( "Borders" );
	TiXmlElement * border4a= new TiXmlElement( "Border" );
	border4a->SetAttribute("ss:Position","Bottom");
	border4a->SetAttribute("ss:LineStyle","Continuous");
	border4a->SetAttribute("ss:Weight","1");
	border4a->SetAttribute("ss:Color","#76933C");
	TiXmlElement * font4= new TiXmlElement( "Font" );
	font4->SetAttribute("ss:FontName","Calibri");
	font4->SetAttribute("x:Family","Swiss");
	font4->SetAttribute("ss:Size","11");
	font4->SetAttribute("ss:Bold","1");
	TiXmlElement * interior4= new TiXmlElement( "Interior" );
	interior4->SetAttribute("ss:Color","#C4D79B");
	interior4->SetAttribute("ss:Pattern","Solid");
	style4->LinkEndChild(alignment4);
	borders4->LinkEndChild(border4a);
	style4->LinkEndChild(borders4);
	style4->LinkEndChild(font4);
	style4->LinkEndChild(interior4);
	//s21
	TiXmlElement * alignment5= new TiXmlElement( "Alignment" );
	alignment5->SetAttribute("ss:Horizontal","Center");
	alignment5->SetAttribute("ss:Vertical","Center");
	TiXmlElement * borders5= new TiXmlElement( "Borders" );
	TiXmlElement * border5a= new TiXmlElement( "Border" );
	border5a->SetAttribute("ss:Position","Bottom");
	border5a->SetAttribute("ss:LineStyle","Continuous");
	border5a->SetAttribute("ss:Weight","1");
	border5a->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border5b= new TiXmlElement( "Border" );
	border5b->SetAttribute("ss:Position","Left");
	border5b->SetAttribute("ss:LineStyle","Continuous");
	border5b->SetAttribute("ss:Weight","1");
	border5b->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border5c= new TiXmlElement( "Border" );
	border5c->SetAttribute("ss:Position","Right");
	border5c->SetAttribute("ss:LineStyle","Continuous");
	border5c->SetAttribute("ss:Weight","1");
	border5c->SetAttribute("ss:Color","#76933C");
	TiXmlElement * font5= new TiXmlElement( "Font" );
	font5->SetAttribute("ss:FontName","Calibri");
	font5->SetAttribute("x:Family","Swiss");
	font5->SetAttribute("ss:Size","11");
	font5->SetAttribute("ss:Bold","1");
	TiXmlElement * interior5= new TiXmlElement( "Interior" );
	interior5->SetAttribute("ss:Color","#C4D79B");
	interior5->SetAttribute("ss:Pattern","Solid");
	style5->LinkEndChild(alignment5);
	borders5->LinkEndChild(border5a);
	borders5->LinkEndChild(border5b);
	borders5->LinkEndChild(border5c);
	style5->LinkEndChild(borders5);
	style5->LinkEndChild(font5);
	style5->LinkEndChild(interior5);
	//s22
	TiXmlElement * alignment6= new TiXmlElement( "Alignment" );
	alignment6->SetAttribute("ss:Horizontal","Center");
	alignment6->SetAttribute("ss:Vertical","Center");
	alignment6->SetAttribute("ss:WrapText","1");
	TiXmlElement * borders6= new TiXmlElement( "Borders" );
	TiXmlElement * border6a= new TiXmlElement( "Border" );
	border6a->SetAttribute("ss:Position","Bottom");
	border6a->SetAttribute("ss:LineStyle","Continuous");
	border6a->SetAttribute("ss:Weight","1");
	border6a->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border6b= new TiXmlElement( "Border" );
	border6b->SetAttribute("ss:Position","Left");
	border6b->SetAttribute("ss:LineStyle","Continuous");
	border6b->SetAttribute("ss:Weight","1");
	border6b->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border6c= new TiXmlElement( "Border" );
	border6c->SetAttribute("ss:Position","Right");
	border6c->SetAttribute("ss:LineStyle","Continuous");
	border6c->SetAttribute("ss:Weight","1");
	border6c->SetAttribute("ss:Color","#76933C");
	TiXmlElement * border6d= new TiXmlElement( "Border" );
	border6d->SetAttribute("ss:Position","Top");
	border6d->SetAttribute("ss:LineStyle","Continuous");
	border6d->SetAttribute("ss:Weight","3");
	TiXmlElement * font6= new TiXmlElement( "Font" );
	font6->SetAttribute("ss:FontName","Calibri");
	font6->SetAttribute("x:Family","Swiss");
	font6->SetAttribute("ss:Size","11");
	font6->SetAttribute("ss:Bold","1");
	TiXmlElement * interior6= new TiXmlElement( "Interior" );
	interior6->SetAttribute("ss:Color","#C4D79B");
	interior6->SetAttribute("ss:Pattern","Solid");
	TiXmlElement * numberformat6= new TiXmlElement( "NumberFormat" );
	numberformat6->SetAttribute("ss:Format","@");
	style6->LinkEndChild(alignment6);
	borders6->LinkEndChild(border6a);
	borders6->LinkEndChild(border6b);
	borders6->LinkEndChild(border6c);
	borders6->LinkEndChild(border6d);
	style6->LinkEndChild(borders6);
	style6->LinkEndChild(font6);
	style6->LinkEndChild(interior6);
	style6->LinkEndChild(numberformat6);
	//s23
	TiXmlElement * alignment7= new TiXmlElement( "Alignment" );
	alignment7->SetAttribute("ss:Horizontal","Center");
	alignment7->SetAttribute("ss:Vertical","Center");
	TiXmlElement * borders7= new TiXmlElement( "Borders" );
	TiXmlElement * border7a= new TiXmlElement( "Border" );
	border7a->SetAttribute("ss:Position","Bottom");
	border7a->SetAttribute("ss:LineStyle","Continuous");
	border7a->SetAttribute("ss:Weight","3");
	TiXmlElement * border7b= new TiXmlElement( "Border" );
	border7b->SetAttribute("ss:Position","Top");
	border7b->SetAttribute("ss:LineStyle","Continuous");
	border7b->SetAttribute("ss:Weight","3");
	TiXmlElement * font7= new TiXmlElement( "Font" );
	font7->SetAttribute("ss:FontName","Calibri");
	font7->SetAttribute("x:Family","Swiss");
	font7->SetAttribute("ss:Size","11");
	font7->SetAttribute("ss:Color","#FFFFFF");
	TiXmlElement * interior7= new TiXmlElement( "Interior" );
	interior7->SetAttribute("ss:Color","#76933C");
	interior7->SetAttribute("ss:Pattern","Solid");
	style7->LinkEndChild(alignment7);
	borders7->LinkEndChild(border7a);
	borders7->LinkEndChild(border7b);
	style7->LinkEndChild(borders7);
	style7->LinkEndChild(font7);
	style7->LinkEndChild(interior7);
	
	styles->LinkEndChild(style);
	styles->LinkEndChild(style1);
	styles->LinkEndChild(style2);
	styles->LinkEndChild(style3);
	styles->LinkEndChild(style4);
	styles->LinkEndChild(style5);
	styles->LinkEndChild(style6);
	styles->LinkEndChild(style7);
	return styles;
}
TiXmlElement* XmlExcel::crear_documento_libro(char autor1[],char fecha1[]){
	//falta crear la linea <?mso-application prodif="Excel.Sheet" ?>
	TiXmlElement * workbook = new TiXmlElement( "Workbook" );
	//
	TiXmlElement * documentproperties = new TiXmlElement( "DocumentProperties" );
	TiXmlElement * autor = new TiXmlElement( "Author" );
	TiXmlElement * ultimoautor = new TiXmlElement( "LastAuthor" );
	TiXmlElement * creado = new TiXmlElement( "Created" );
	TiXmlElement * version = new TiXmlElement( "Version" );
	TiXmlText * quien = new TiXmlText( autor1 ); //Autor del archivo
	TiXmlText * ultimoquien = new TiXmlText( autor1 ); //Autor del archivo
	TiXmlText * created = new TiXmlText( fecha1 ); //Fecha creacion
	TiXmlText * version_text = new TiXmlText( "14" ); //Version
	autor->LinkEndChild( quien );
	ultimoautor->LinkEndChild( ultimoquien );
	creado->LinkEndChild( created );
	version->LinkEndChild( version_text );
	documentproperties->LinkEndChild(autor);
	documentproperties->LinkEndChild(ultimoautor);
	documentproperties->LinkEndChild(creado);
	documentproperties->LinkEndChild(version);
	documentproperties->SetAttribute("xmlns","urn:schemas-microsoft-com:office:office");
	//
	TiXmlElement * officedocumentsettings = new TiXmlElement( "OfficeDocumentSettings" );
	TiXmlElement * allowpng = new TiXmlElement( "AllowPNG" );
	officedocumentsettings->SetAttribute("xmlns","urn:schemas-microsoft-com:office:office");
	officedocumentsettings->LinkEndChild(allowpng);
	workbook->LinkEndChild(documentproperties);
	workbook->LinkEndChild(officedocumentsettings);
	workbook->SetAttribute("xmlns","urn:schemas-microsoft-com:office:spreadsheet");
	workbook->SetAttribute("xmlns:o","urn:schemas-microsoft-com:office:office");
	workbook->SetAttribute("xmlns:x","urn:schemas-microsoft-com:office:excel");
	workbook->SetAttribute("xmlns:ss","urn:schemas-microsoft-com:office:spreadsheet");
	workbook->SetAttribute("xmlns:html","http://www.w3.org/TR/REC-html40");
	return workbook;
}
TiXmlElement* XmlExcel::crear_hoja(char nombre[]){
	TiXmlElement * worksheet = new TiXmlElement( "Worksheet" );
	worksheet->SetAttribute("ss:Name",nombre);//Nombre de la hoja de excel
	return worksheet;
}
TiXmlElement* XmlExcel::crear_tabla(char x[],char y[]){
	TiXmlElement * table1 = new TiXmlElement( "Table" );
	table1->SetAttribute("ss:ExpandedColumnCount",x); //Numero maximo de columnas 
	table1->SetAttribute("ss:ExpandedRowCount",y); //Numero maximo de filas
	table1->SetAttribute("x:FullColumns","1");
	table1->SetAttribute("x:FullRows","1");
	table1->SetAttribute("ss:DefaultColumnWidth","60");
	table1->SetAttribute("ss:DefaultRowHeight","15");
	return table1;
}

TiXmlElement * XmlExcel::salto_linea(){
	TiXmlElement * row = new TiXmlElement( "Row" );
	return row;
}
TiXmlElement * XmlExcel::crear_cell_tabla_titulo(char titulo[],char tipo1[],char longi[]){
	TiXmlElement * row = new TiXmlElement( "Row" );
	row->SetAttribute("ss:Height","30");
	TiXmlElement * cell = new TiXmlElement( "Cell" );
	TiXmlElement * data = new TiXmlElement( "Data" );	
	TiXmlText * valor1 = new TiXmlText( titulo ); //titulo
	data->SetAttribute("ss:Type",tipo1); //fijando el dato como numero
	data->LinkEndChild(valor1);//Anadiendo un dato 
	cell->SetAttribute("ss:Index","2");
	cell->SetAttribute("ss:MergeAcross",longi); //fijando el ancho de celdas unidas
	cell->SetAttribute("ss:StyleID","s23");	
	cell->LinkEndChild(data);
	row->LinkEndChild(cell);
	return row;
}
TiXmlElement * XmlExcel::crear_general_titulo(char titulo[],char tipo1[],char comienzo[],char longi[],char height[]){
	TiXmlElement * row = new TiXmlElement( "Row" );
	row->SetAttribute("ss:Height",height);
	TiXmlElement * cell = new TiXmlElement( "Cell" );
	TiXmlElement * data = new TiXmlElement( "Data" );	
	TiXmlText * valor1 = new TiXmlText( titulo ); //titulo
	data->SetAttribute("ss:Type",tipo1); //fijando el dato como numero
	data->LinkEndChild(valor1);//Anadiendo un dato 
	cell->SetAttribute("ss:Index",comienzo);
	cell->SetAttribute("ss:MergeAcross",longi); //fijando el ancho de celdas unidas
	cell->SetAttribute("ss:StyleID","s23");	
	cell->LinkEndChild(data);
	row->LinkEndChild(cell);
	return row;
}
TiXmlElement* XmlExcel::row_anadido_dato(TiXmlElement* row,char dato[],char tipo[],char estilo_tipo[],bool menu){
	row->SetAttribute("ss:AutoFitHeight","1");
	TiXmlElement * cell = new TiXmlElement( "Cell" );
	TiXmlElement * data = new TiXmlElement( "Data" );
	TiXmlText * valor = new TiXmlText( dato );
	data->SetAttribute("ss:Type",tipo);
	data->LinkEndChild(valor);
	cell->LinkEndChild(data);
	cell->SetAttribute("ss:StyleID",estilo_tipo);
	row->LinkEndChild(cell);
	if (menu){
		row->SetAttribute("ss:Height","25");
	}
	else{
		row->SetAttribute("ss:Height","15");
	}
	return row;
}
TiXmlElement* XmlExcel::row_anadido_dato(TiXmlElement* row,char dato[],char tipo[],char estilo_tipo[], char posicion_tipo[],bool menu){
	row->SetAttribute("ss:AutoFitHeight","1");
	TiXmlElement * cell = new TiXmlElement( "Cell" );
	TiXmlElement * data = new TiXmlElement( "Data" );
	TiXmlText * valor = new TiXmlText( dato );
	data->SetAttribute("ss:Type",tipo);
	data->LinkEndChild(valor);
	cell->LinkEndChild(data);
	cell->SetAttribute("ss:StyleID",estilo_tipo);
	cell->SetAttribute("ss:Index",posicion_tipo);
	row->LinkEndChild(cell);
	if (menu){
		row->SetAttribute("ss:Height","25");
	}
	else{
		row->SetAttribute("ss:Height","15");
	}

	return row;
}
void XmlExcel::guardar_archivo(TiXmlDocument doc,char archivo[]){
	doc.SaveFile(archivo);
}
void XmlExcel::abrir_archivo(char archivo[]){
	char result[80]="start excel "; // archivo solo tiene 64 caracteres para el nombre
	strcat(result,archivo); 
	system(result); //abrir el archivo de EXCEL
}
list <hoja> XmlExcel::row_anadido_menu(list <hoja> list_filas,int opcion){
	elemento coor;
	hoja who;
	list <elemento> list_coordenadas;
	strcpy(coor.dato,"hola como");
	strcpy(coor.tipo,"String");
	coor.menu=true;
	list_coordenadas.push_back(coor);
	strcpy(coor.dato,"estas?");
	strcpy(coor.tipo,"String");
	coor.menu=true;
	list_coordenadas.push_back(coor);
	//final
	who.tabla=list_coordenadas; //engresa el row de datos a la tabla who
	list_filas.push_back(who);
	list_coordenadas.clear();
	return list_filas;
};

TiXmlElement* XmlExcel::row_lista_anadido_dato(TiXmlElement* table,list <hoja> list_filas){
	TiXmlElement * row;
	elemento coor2;
	hoja k9;
	list<hoja>::iterator pos_fila;
	pos_fila=list_filas.begin();
	while (pos_fila!=list_filas.end()){
		row=salto_linea(); //crear un elemento row de excel para anadir los datos
		k9=*pos_fila;
		list<elemento>::iterator pos_list;
		pos_list=k9.tabla.begin();
		while(pos_list!=k9.tabla.end()){
			coor2=*pos_list;
			//usar XmlExcel
			if (coor2.menu){
				if (pos_list==k9.tabla.begin()){
					row_anadido_dato(row,coor2.dato,coor2.tipo,"s18", "2",true);
				}
				else{
					row_anadido_dato(row,coor2.dato,coor2.tipo,"s18",true);
				}
			}
			else{
				if (pos_list==k9.tabla.begin()){
					row_anadido_dato(row,coor2.dato,coor2.tipo,"s19", "2",false);
				}
				else{
					row_anadido_dato(row,coor2.dato,coor2.tipo,"s19",false);
				}
			}
			pos_list++;
		}
		pos_fila++;
		table->LinkEndChild(row);
	}
	return table;
}