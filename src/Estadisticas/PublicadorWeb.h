//
// Created by rafael on 18/09/17.
//

#ifndef CONCU_VOLEY_PUBLICADORWEB_H
#define CONCU_VOLEY_PUBLICADORWEB_H
#include <list>
#include <Serializados.h>
#define ARCHIVO_HTML    "/tmp/webvoley.html"

/**
 * Una instancia de esta clase permite actualizar una página web.
 */
class PublicadorWeb {

private:

    int fd=-1;

public:

    /**
     * Actualiza el contenido de la página web a las ligas parámetro.
     *
     * @param resultadosPartidos : resultados de los partidos como lista no nula.
     * @param jugadoresPuntajes : jugadores con su puntaje como lista no nula.
     */
    void update(std::list<TResultadoSerializado>* resultadosPartidos,
                std::list<TJugadorPuntaje>* jugadoresPuntajes);

private:

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
