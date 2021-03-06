//
// Created by rafael on 18/09/17.
//

#include <fcntl.h>
#include <iostream>
#include "PublicadorWeb.h"

PublicadorWeb::PublicadorWeb(string archivo) : archivo_(archivo) {
}

void PublicadorWeb::update(std::list<TResultadoSerializado>* resultadosPartidos,
                           std::list<TJugadorPuntaje>* jugadoresPuntajes) {
    fd=open(archivo_.c_str(),O_WRONLY|O_CREAT|O_TRUNC,0644);
    jugadoresPuntajes->sort(compareJugadorPuntajeReverse);
    this->escribirHeader();
    this->escribirBody(resultadosPartidos,jugadoresPuntajes);
    this->escribirFooter();
    close(fd);
    fd=-1;
}

void PublicadorWeb::escribirTablaResultados(std::list<TResultadoSerializado>* resultadosPartidos) {
    escribirEnWeb("<h1>Resultados Partidos</h1>");
    std::string cadena("<table>\n");
    cadena+="<style type=\"text/css\">\n";
    cadena+="table {border: red 3px solid;\n}\n";
    cadena+="td {border: black 1px solid;\n}\n";
    cadena+="</style>\n";
    cadena+="<tr>\n";
    cadena+="<td><strong>Equipo 1</strong></td>\n";
    cadena+="<td><strong>Equipo 2</strong></td>\n";
    cadena+="<td><strong>Puntaje Equipo 1</strong></td>\n";
    cadena+="<td><strong>Puntaje Equipo 2</strong></td>\n";
    escribirEnWeb(cadena);
    escribirEnWeb("</tr>\n");
    for(std::list<TResultadoSerializado>::iterator it=resultadosPartidos->begin();it!=resultadosPartidos->end();++it){
        std::string cadena("<tr>\n");
        cadena+="<td><strong>"+std::to_string(it->equipo1[0])+","+std::to_string(it->equipo1[1])+"</strong></td>\n";
        cadena+="<td><strong>"+std::to_string(it->equipo2[0])+","+std::to_string(it->equipo2[1])+"</strong></td>\n";
        cadena+="<td><strong>"+std::to_string(it->puntajeEquipo1)+"</strong></td>\n";
        cadena+="<td><strong>"+std::to_string(it->puntajeEquipo2)+"</strong></td>\n";
        cadena+="</tr>\n";
        escribirEnWeb(cadena);
    }
    escribirEnWeb("</table>\n");
}

void PublicadorWeb::escribirHeader() {
    escribirEnWeb("<!DOCTYPE html>\n<html><head>\n<title>Torneo de Voley</title>\n</head>");
}

void PublicadorWeb::escribirBody(std::list<TResultadoSerializado>* resultadosPartidos,
                                 std::list<TJugadorPuntaje>* jugadoresPuntajes) {
    escribirEnWeb("<body bgcolor=\"#E6E6FA\">");
    escribirTablaPuntajeJugadores(jugadoresPuntajes);
    escribirTablaResultados(resultadosPartidos);
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

void PublicadorWeb::escribirTablaPuntajeJugadores(std::list<TJugadorPuntaje>* jugadoresPuntajes) {
     if(jugadoresPuntajes->size()>0) {
         escribirEnWeb("<h1>Puntaje Jugadores</h1>");
         std::string cadena("<table>\n");
         cadena += "<style type=\"text/css\">\n";
         cadena += "table {border: red 3px solid;\n}\n";
         cadena += "td {border: black 1px solid;\n}\n";
         cadena += "</style>\n";
         cadena += "<tr>\n";
         cadena += "<td><strong>POSICION</strong></td>\n";
         cadena += "<td><strong>JUGADOR</strong></td>\n";
         cadena += "<td><strong>PUNTAJE</strong></td>\n";
         escribirEnWeb(cadena);
         escribirEnWeb("</tr>\n");
         unsigned int posicion=0;
         unsigned int puntaje=0;
         for(std::list<TJugadorPuntaje>::iterator it=jugadoresPuntajes->begin();it!=jugadoresPuntajes->end();++it){
            if(puntaje!=it->puntaje){
                 puntaje=it->puntaje;
                 posicion++;
            }
            std::string cadena("<tr>\n");
            cadena+="<td><strong>"+std::to_string(posicion)+"</strong></td>\n";
            cadena+="<td><strong>"+std::to_string(it->jugador)+"</strong></td>\n";
            cadena+="<td><strong>"+std::to_string(it->puntaje)+"</strong></td>\n";
            cadena+="</tr>\n";
            escribirEnWeb(cadena);
         }
         escribirEnWeb("</table>\n");
     }
}
