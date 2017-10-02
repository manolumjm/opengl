//**************************************************************************
// Práctica 2
// Class to read .ply files
//**************************************************************************


#ifndef _MODELO_PLY_H_
#define _MODELO_PLY_H_

#include "file_ply_stl.h"
#include "objetos.h"
#include <vector>

class modelo_ply : public _triangulos3D
{

    public:
        modelo_ply();
        void leer_ply(char * file);
};



#endif