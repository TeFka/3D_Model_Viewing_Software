#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<math.h>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gl/glut.h"
#include "gl/freeglut.h"

#include "Vector3D.h"
class Renderer{

private:
    std::vector<std::vector<Vector3D>> meshes;

public:
    //Default Model class constructor
    Renderer();
    //Model class destructor
    ~Renderer();
    //Model class destructor
    Renderer(const Renderer&);

    void setupOpenGL(int*, char**);

    void setMesh(std::vector<Vector3D>);
    static void render();

    void startRender();

};

#endif // RENDERER_H_INCLUDED
