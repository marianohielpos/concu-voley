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

    std::list<TResultadoSerializado> resultados;

public:

    PublicadorWeb();

    void add(TResultadoSerializado &resultado);

    void update();

    ~PublicadorWeb();

protected:

    void escribirTabla();

    void escribirHeader();

    void escribirFooter();

    void escribirBody();

    void escribirEnWeb(const char *cadena);

    void escribirEnWeb(std::string &cadena);

};


#endif //CONCU_VOLEY_PUBLICADORWEB_H
