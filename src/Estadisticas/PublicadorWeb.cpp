//
// Created by rafael on 18/09/17.
//

#include <fcntl.h>
#include <iostream>
#include "PublicadorWeb.h"

PublicadorWeb::PublicadorWeb() {

}

void PublicadorWeb::add(TResultadoSerializado &resultado) {
    resultados.push_back(resultado);
}

void PublicadorWeb::update() {
    fd=open(ARCHIVO_HTML,O_WRONLY|O_CREAT|O_TRUNC);
    this->escribirHeader();
    this->escribirBody();
    this->escribirFooter();
    close(fd);
    fd=-1;
}

PublicadorWeb::~PublicadorWeb() {
    resultados.clear();
}

void PublicadorWeb::escribirTabla() {
    std::string cadena("<table>\n");
    cadena+="<style type=\"text/css\">\n";
    cadena+="table {border: red 3px solid;\n}\n";
    cadena+="td {border: black 1px solid;\n}\n";
    cadena+="</style>\n";
    cadena+="<tr>\n";
    cadena+="<td><strong>Cancha</strong></td>\n";
    cadena+="<td><strong>Equipo 1</strong></td>\n";
    cadena+="<td><strong>Equipo 2</strong></td>\n";
    for(int i=1;i<6;i++)
        cadena+="<td><strong>Set "+std::to_string(i)+"</strong></td>\n";
    escribirEnWeb(cadena);
    escribirEnWeb("</tr>\n");
    for(std::list<TResultadoSerializado>::iterator it=resultados.begin();it!=resultados.end();++it){
        std::string cadena("<tr>\n");
        cadena+="<td><strong>"+std::to_string(it->fila)+","+std::to_string(it->columna)+"</strong></td>\n";
        cadena+="<td><strong>"+std::to_string(it->equipo1[0])+","+std::to_string(it->equipo1[1])+"</strong></td>\n";
        cadena+="<td><strong>"+std::to_string(it->equipo2[0])+","+std::to_string(it->equipo2[1])+"</strong></td>\n";
        for(int i=0;i<it->cantidadSets;i++)
            cadena+="<td><strong>"+std::to_string(it->resultadoSetsEquipo1[i])+" a "+std::to_string(it->resultadoSetsEquipo2[i])+"</strong></td>\n";
        cadena+="</tr>\n";
        escribirEnWeb(cadena);
    }
    escribirEnWeb("</table>\n");
}

void PublicadorWeb::escribirHeader() {
    escribirEnWeb("<!DOCTYPE html>\n<html><head>\n<title>Resultado Partidos</title>\n</head>");
}

void PublicadorWeb::escribirBody() {
    escribirEnWeb("<h1>Resultados Partidos</h1>");
    escribirEnWeb("<body bgcolor=\"#E6E6FA\">");
    escribirTabla();
    escribirEnWeb("</body>");
}

void PublicadorWeb::escribirFooter() {
    escribirEnWeb("</html>");
}

void PublicadorWeb::escribirEnWeb(const char *cadena) {
    write(fd,cadena,strlen(cadena));
}

void PublicadorWeb::escribirEnWeb(std::string &cadena) {
    escribirEnWeb(cadena.c_str());
}