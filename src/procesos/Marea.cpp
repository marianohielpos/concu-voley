//
// Created by Mariano Hielpos on 9/23/17.
//

#include "Marea.h"
#include "Logger.h"


Marea::Marea(Logger* logger) {

    this->logger = logger;

}

void Marea::run() {
    this->logger->info("Marea incializada");

}