//
// Created by rafael on 14/10/17.
//

#include "LockMemoriaCompartidaPersonas.h"
#include "participantes.h"

LockMemoriaCompartidaPersonas ::LockMemoriaCompartidaPersonas(unsigned int cantidadPersonas,
                                 unsigned int capacidadPredio)throw(std::exception){
    this->nombre=ARCHIVO_LOCK_MEMORIA_COMPARTIDA_PERSONAS;
    this->inicializarLock();
    this->tomarLock();
    try{
        this->memoriaCompartidaPersonas=new MemoriaCompartidaPersonas(cantidadPersonas,capacidadPredio);
    }catch(std::exception e){
        this->liberarLock();
        throw e;
    }
    this->liberarLock();
}

int LockMemoriaCompartidaPersonas :: tomarLock () {
    this->fl.l_type = F_WRLCK;
    return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockMemoriaCompartidaPersonas :: liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

LockMemoriaCompartidaPersonas :: ~LockMemoriaCompartidaPersonas () {
    close ( this->fd );
    delete(memoriaCompartidaPersonas);
    memoriaCompartidaPersonas=NULL;
}

void LockMemoriaCompartidaPersonas::inicializarLock() {
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open ( this->nombre.c_str(),O_CREAT | O_WRONLY,0666 );
}

void LockMemoriaCompartidaPersonas::escribir(const TPersona &persona)throw(std::exception) {
    this->tomarLock();
    this->memoriaCompartidaPersonas->escribir(persona);
    this->liberarLock();
}

std::list<TPersona>* LockMemoriaCompartidaPersonas::readAll() {
    std::list<TPersona>* retorno;
    this->tomarLock();
    retorno=this->doReadAll();
    this->liberarLock();
    return retorno;
}

void LockMemoriaCompartidaPersonas::cleanMemoria() {
    this->tomarLock();
    this->memoriaCompartidaPersonas->cleanMemoria();
    this->liberarLock();
}

void LockMemoriaCompartidaPersonas::liberarRecursos() {
    this->memoriaCompartidaPersonas->liberar();
}

std::list<TPersona>* LockMemoriaCompartidaPersonas::doReadAll() {
    return this->memoriaCompartidaPersonas->readAll();
}

void LockMemoriaCompartidaPersonas::llenarCola(std::queue<TPersona> &cola) {
    this->tomarLock();
    std::list<TPersona>* personasLeidas=memoriaCompartidaPersonas->readAllFueraDelPredio();
    for(std::list<TPersona>::iterator it=personasLeidas->begin();it!=personasLeidas->end();++it){
        cola.push(*it);
    }
    delete(personasLeidas);
    this->liberarLock();
}

bool LockMemoriaCompartidaPersonas::ingresarPersona(TPersona& persona) {
    this->tomarLock();
    if(!this->memoriaCompartidaPersonas->capacidadPredioAgotada()){
        persona.enPredio=true;
        this->memoriaCompartidaPersonas->escribir(persona);
        return true;
    }
    this->liberarLock();
}

void LockMemoriaCompartidaPersonas::retirarPersona() {
    this->tomarLock();
    std::list<TPersona>* personasLeidas=memoriaCompartidaPersonas->readAllEnPredioEsperandoParaJugar();
    for(std::list<TPersona>::iterator it=personasLeidas->begin();it!=personasLeidas->end();++it){
        if(calcularSalida()){
            TPersona persona;
            persona.init(it->idPersona,false,false);
            memoriaCompartidaPersonas->escribir(persona);
            break;
        }
    }
    delete(personasLeidas);
    this->liberarLock();
}

bool LockMemoriaCompartidaPersonas::obtenerParticipantes(std::vector<Jugador>& jugadores,participantes &p, std::map<pid_t, Partido> &partidos_) {
    this->tomarLock();
    bool retorno=doObtenerParticipantes(jugadores,p,partidos_);
    this->marcarEstadoJugando(p,true);
    this->liberarLock();
    return retorno;
}

bool LockMemoriaCompartidaPersonas::sePuedenObtenerParticipantes(std::vector<Jugador>& jugadores,std::map<pid_t, Partido> &partidos_) {
    participantes p {-1, -1, -1, -1};
    this->tomarLock();
    bool retorno=doObtenerParticipantes(jugadores,p,partidos_);
    this->liberarLock();
    return retorno;
}

bool LockMemoriaCompartidaPersonas::doObtenerParticipantes(std::vector<Jugador>& jugadores,participantes &p, std::map<pid_t, Partido> &partidos_) {
    this->doActualizarEstados(jugadores);
    bool parEncontrado;
    for (int i = 0; i < 2; i++) {
        parEncontrado = false;
        for (Jugador const& j1 : jugadores) {
            if (j1.disponible()) {

                if (i > 0 && (p[0] == j1.getId() || p[1] == j1.getId())) {
                    // Si estoy buscando el segundo par de jugadores, me fijo que no lo haya
                    // incluido en el primer par
                    continue;
                }

                for (Jugador const& j2 : jugadores) {
                    if ((&j1 != &j2) && j2.disponible() && j1.puedeJugarCon(j2.getId())) {

                        if (i > 0 && (p[0] == j2.getId() || p[1] == j2.getId())) {
                            continue;
                        }

                        p[0 + i * 2] = j1.getId();
                        p[1 + i * 2] = j2.getId();
                        parEncontrado = true;
                        break;
                    }
                }
            }
            if (parEncontrado) {
                break;
            }
        }
        if (!parEncontrado) {
            break;
        }
    }
    return parEncontrado;
}

unsigned int LockMemoriaCompartidaPersonas::calcularRandom() {
    srand(time(NULL));
    return (rand()%10+1);
}

bool LockMemoriaCompartidaPersonas::calcularSalida() {
    return (calcularRandom()>5);
}

void LockMemoriaCompartidaPersonas::marcarComoEsperandoJugar(participantes& p) {
    this->tomarLock();
    this->marcarEstadoJugando(p, false);
    this->liberarLock();
}

void LockMemoriaCompartidaPersonas::marcarEstadoJugando(participantes &p, bool jugando) {
    for(unsigned int i=0; i < 4 ;i++) {
        doMarcarEstadoJugando(p[i], jugando);
    }
}

void LockMemoriaCompartidaPersonas::doMarcarEstadoJugando(unsigned int idPersona,bool jugando) {
    Persona persona;
    persona.init(idPersona,true,jugando);
    this->memoriaCompartidaPersonas->escribir(persona);
}

unsigned int LockMemoriaCompartidaPersonas::cantidadEnPredio() {
    this->tomarLock();
    unsigned int retorno=this->memoriaCompartidaPersonas->cantidadPersonasDentroDelPredio();
    this->liberarLock();
    return retorno;
}

void LockMemoriaCompartidaPersonas::doActualizarEstados(std::vector<Jugador> &jugadores_) {
    std::vector<TPersona>* personas=memoriaCompartidaPersonas->readAllAsVector();
    for(std::vector<TPersona>::iterator it=personas->begin();it!=personas->end();++it){
        if(it->enPredio){
            jugadores_[it->idPersona].entrarPredio();
        }else{
            jugadores_[it->idPersona].salirPredio();
        }
        jugadores_[it->idPersona].setDisponible(!it->jugando);
    }
    delete(personas);
}

void LockMemoriaCompartidaPersonas::actualizarEstados(std::vector<Jugador> &jugadores_) {
    this->tomarLock();
    this->doActualizarEstados(jugadores_);
    this->liberarLock();
}