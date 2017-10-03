//**************************************************************************
// Práctica 4
// Class to read files with extension .ply to transform them into figures
//**************************************************************************


#include "modelo_ply.h"

modelo_ply:: modelo_ply()
{

}

void modelo_ply::leer_ply(char * file)
{
    vector<float> read_vertex;
    vector<int> read_faces;
    _file_ply ply;
    int n_vertices,n_caras,j;    

    /*apertura archivo .ply*/
    ply.open(file);

    /*Lectura archivo .ply*/
    ply.read(read_vertex, read_faces);

    /*Asignación del nº de caras y vértices al objeto*/
    
    
    n_vertices = read_vertex.size() / 3;
    n_caras = read_faces.size() / 3;

    /*Reserva de tamaño para caras y vértices*/
    vertices.resize(n_vertices);
    caras.resize(n_caras);

    j = 0;
    /*Asignación de vértices al objeto*/
    for (int i = 0; i < read_vertex.size(); i += 3)
    {
        vertices[j].x = read_vertex[i];
        vertices[j].y = read_vertex[i+1];
        vertices[j].z = read_vertex[i+2];
        j++;
    }

    j = 0;

    /*Asignación de caras al objeto*/
    for (int i = 0; i < read_faces.size(); i += 3)
    {
        caras[j]._0 = read_faces[i];
        caras[j]._1 = read_faces[i + 1]; 
        caras[j]._2 = read_faces[i + 2];
        j++;
    }


    ply.close();
}

