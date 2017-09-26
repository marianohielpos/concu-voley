//
// Created by rafael on 18/09/17.
//

#ifndef CONCU_VOLEY_PUBLICADORWEB_H
#define CONCU_VOLEY_PUBLICADORWEB_H
#include <list>
#include <Serializados.h>

#define ARCHIVO_HTML    "/tmp/webvoley.html"

class PublicadorWeb {

private:

    int fd=-1;

public:

    void update(std::list<TResultadoSerializado>* resultadosPartidos,
                std::list<TJugadorPuntaje>* jugadoresPuntajes);

protected:

    void escribirTablaResultados(std::list<TResultadoSerializado> *resultadosPartidos);

    void escribirHeader();

    void escribirFooter();

    void escribirBody(std::list<TResultadoSerializado>* resultadosPartidos,
                      std::list<TJugadorPuntaje>* jugadoresPuntajes);

    void escribirEnWeb(const char *cadena);

    void escribirEnWeb(std::string &cadena);

    void escribirTablaPuntajeJugadores(std::list<TJugadorPuntaje>* jugadoresPuntajes);
};


#endif //CONCU_VOLEY_PUBLICADORWEB_H
