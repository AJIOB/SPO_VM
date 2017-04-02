//
// Created by alex on 02.04.17.
//

#include "ParserManager.h"

ParserManager::ParserManager(const std::string &rootWay) {
    this->rootWay = rootWay;
}

void ParserManager::run() {
    DIR* dir = opendir(rootWay.c_str());

    //todo
}
