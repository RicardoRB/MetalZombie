#include "../include/Builder.h"

Builder::Builder() {
    //ctor
}

Builder::Builder(char file_texture[]) : Object(file_texture) {
    //ctor father
}

Builder::~Builder() {
    //dtor
}
