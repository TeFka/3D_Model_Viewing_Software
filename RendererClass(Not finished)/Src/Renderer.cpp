#include "../Inc/Renderer.h"

Renderer::Renderer(){

}

Renderer::~Renderer(){

}
Renderer::Renderer(const Renderer&)
{

}

void Renderer::setupOpenGL(int* argc, char** argv){

   glutInit(argc, argv);                 // Initialize GLUT
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutInitWindowSize(320, 320);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutDisplayFunc(render); // Register display callback handler for window re-paint
}

void Renderer::setMesh(std::vector<Vector3D> newMesh){
    this->meshes.push_back(newMesh);
}

void Renderer::render() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.5f, -0.5f);    // x, y
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
   glEnd();

   glFlush();  // Render now
}

void Renderer::startRender(){
    glutMainLoop();
}
