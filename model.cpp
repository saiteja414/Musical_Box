#include "model.hpp"

#include "texture.hpp"
#include "parameters.cpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
const int num_vertices = 36;

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};


//// arguments are radius1 for lower circle plane,radius2 for upper circle plane,height, vertices and colors array that will be given to vbo and vao; origin at center of lower circle;
 void makecylinder(int mode, double radius1,double radius2,double height,glm::vec4 positions_cylinder[],glm::vec4 colors_cylinder[],glm::vec4 normals_cylinder[], glm::vec2 tex_cylinder[], double r, double g, double b, double a)
{
  int total_vertices = 2*3*360 + 6*360;
  int idx = 0;
  int idx1 = 0;
  int idx2 = 0;
  int idx3 = 0;
  /// lower circle
  for (int i = 0; i < 360; ++i)
  {
    ////// positions
    positions_cylinder[idx] = glm::vec4(  0.0,  0.0,  0.0, 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1 * cos(i*(M_PI / 180)), 0,radius1 * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1 * cos((i+1)*(M_PI / 180)), 0,radius1 * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    ////// colors
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;

    if (mode == 1) 
    {
      tex_cylinder[idx2] = glm::vec2(0.5, 0.5); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
    }

    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;

  }
  /// upper circle
  for (int i = 0; i < 360; ++i)
  {
    ////// positions
    positions_cylinder[idx] = glm::vec4(  0.0,  height,  0.0, 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2 * cos(i*(M_PI / 180)), height,radius2 * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2 * cos((i+1)*(M_PI / 180)), height,radius2 * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    ////// colors
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;

    if (mode == 1) 
    {
      tex_cylinder[idx2] = glm::vec2(0.5, 0.5); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
    }

    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;

  }
  /// vertical quads
  for (int i = 0 + 360 + 360; i < 360 + 360 + 360; ++i)
  {
    ////// positions
    positions_cylinder[idx] = glm::vec4(  radius1 * cos(i*(M_PI / 180)), 0,radius1 * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2 * cos(i*(M_PI / 180)), height,radius2 * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2 * cos((i+1)*(M_PI / 180)), height,radius2 * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1 * cos(i*(M_PI / 180)), 0,radius1 * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1 * cos((i+1)*(M_PI / 180)), 0,radius1 * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2 * cos((i+1)*(M_PI / 180)), height,radius2 * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    ////// colors
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    ////// texture
    if(mode == 1){
    tex_cylinder[idx2] = glm::vec2(0, 1); idx2++;  
    tex_cylinder[idx2] = glm::vec2(0, 0); idx2++;  
    tex_cylinder[idx2] = glm::vec2(1, 0); idx2++;  
    tex_cylinder[idx2] = glm::vec2(0, 1); idx2++;  
    tex_cylinder[idx2] = glm::vec2(1, 0); idx2++;  
    tex_cylinder[idx2] = glm::vec2(1, 1); idx2++;
  }
    ////// normal
    normals_cylinder[idx3] = glm::vec4(cos(i*(M_PI / 180)),0,sin(i*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos(i*(M_PI / 180)),0,sin(i*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos((i+1)*(M_PI / 180)),0,sin((i+1)*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos(i*(M_PI / 180)),0,sin(i*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos((i+1)*(M_PI / 180)),0,sin((i+1)*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos((i+1)*(M_PI / 180)),0,sin((i+1)*(M_PI / 180)),1);idx3++;

  }
		
}
////
void makeellipsecylinder(int mode,double radius1a,double radius1b,double radius2a,double radius2b,double height,glm::vec4 positions_cylinder[],glm::vec4 colors_cylinder[],glm::vec4 normals_cylinder[],glm::vec2 tex_cylinder[], double r, double g, double b, double a)
{
  int total_vertices = 2*3*360 + 6*360;
  int idx = 0;
  int idx1 = 0;
  int idx2 = 0;
  int idx3 = 0;
  /// lower circle
  for (int i = 0; i < 360; ++i)
  {
    ////// positions
    positions_cylinder[idx] = glm::vec4(  0.0,  0.0,  0.0, 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1a * cos(i*(M_PI / 180)), 0,radius1b * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1a * cos((i+1)*(M_PI / 180)), 0,radius1b * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    ////// colors
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    ////// textures
    if (mode == 1) 
    {
      tex_cylinder[idx2] = glm::vec2(0.5, 0.5); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
    }
    ////// normals
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
  }
  /// upper circle
  for (int i = 0; i < 360; ++i)
  {
    ////// positions
    positions_cylinder[idx] = glm::vec4(  0.0,  height,  0.0, 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2a * cos(i*(M_PI / 180)), height,radius2b * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2a * cos((i+1)*(M_PI / 180)), height,radius2b * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    ////// colors
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    ////// textures
    if (mode == 1) 
    {
      tex_cylinder[idx2] = glm::vec2(0.5, 0.5); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
      tex_cylinder[idx2] = glm::vec2(0.5 + 0.5 * cos(i*(M_PI / 180)), 0.5 + 0.5 * sin(i*(M_PI / 180)) ); idx2++;  
    }
    ///// normals
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
    normals_cylinder[idx3] = glm::vec4(0,-1,0,1);idx3++;
  }
  /// vertical quads
  for (int i = 0 + 360 + 360; i < 360 + 360 + 360; ++i)
  {
    ////// positions
    positions_cylinder[idx] = glm::vec4(  radius1a * cos(i*(M_PI / 180)), 0,radius1b * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2a * cos(i*(M_PI / 180)), height,radius2b * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2a * cos((i+1)*(M_PI / 180)), height,radius2b * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1a * cos(i*(M_PI / 180)), 0,radius1b * sin(i*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius1a * cos((i+1)*(M_PI / 180)), 0,radius1b * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    positions_cylinder[idx] = glm::vec4(  radius2a * cos((i+1)*(M_PI / 180)), height,radius2b * sin((i+1)*(M_PI / 180)), 1.0);idx++;
    ////// colors
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    colors_cylinder[idx1] = glm::vec4(r,g,b,a);idx1++;
    ////// textures
    if(mode == 1){
    tex_cylinder[idx2] = glm::vec2(0, 1); idx2++;  
    tex_cylinder[idx2] = glm::vec2(0, 0); idx2++;  
    tex_cylinder[idx2] = glm::vec2(1, 0); idx2++;  
    tex_cylinder[idx2] = glm::vec2(0, 1); idx2++;  
    tex_cylinder[idx2] = glm::vec2(1, 0); idx2++;  
    tex_cylinder[idx2] = glm::vec2(1, 1); idx2++;
    
  }
  ////// normals
    normals_cylinder[idx3] = glm::vec4(cos(i*(M_PI / 180)),0,sin(i*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos(i*(M_PI / 180)),0,sin(i*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos((i+1)*(M_PI / 180)),0,sin((i+1)*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos(i*(M_PI / 180)),0,sin(i*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos((i+1)*(M_PI / 180)),0,sin((i+1)*(M_PI / 180)),1);idx3++;
    normals_cylinder[idx3] = glm::vec4(cos((i+1)*(M_PI / 180)),0,sin((i+1)*(M_PI / 180)),1);idx3++;
  }
}

//// arguments are radius of sphere , vertex and  color array that will be given to vbo and vao; origin at center of the sphere;
void makesphere(int mode, double radius,glm::vec4 positions_sphere[],glm::vec4 colors_sphere[],glm::vec4 normals_sphere[],glm::vec2 tex_sphere[], double r,double g,double b,double a)
{
  int idx = 0;
  int idx1 = 0;
  int idx2 = 0;
  int idx3 = 0;
  for (int i = 0; i < 180; ++i)
  {
    for (int j = 0; j < 360; ++j)
    {
      /// 1st tri
      positions_sphere[idx] = glm::vec4( radius * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius * 1.0 * cos(i*(M_PI / 180)), radius * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius * sin(i*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius * 1.0 * cos(i*(M_PI / 180)), radius * sin(i*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius * 1.0 * cos((i+1)*(M_PI / 180)), radius * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx++;
      /// 2nd tri
      positions_sphere[idx] = glm::vec4( radius * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius * 1.0 * cos(i*(M_PI / 180)), radius * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius * sin((i+1)*(M_PI / 180)) * cos(j*(M_PI / 180)),radius * 1.0 * cos((i+1)*(M_PI / 180)), radius * sin((i+1)*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius * 1.0 * cos((i+1)*(M_PI / 180)), radius * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx++;
      /// 1st color
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      /// 2nd color
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      /// textures
      if(mode == 1){
        tex_sphere[idx2] = glm::vec2(0, 1); idx2++;  
        tex_sphere[idx2] = glm::vec2(0, 0); idx2++;  
        tex_sphere[idx2] = glm::vec2(1, 0); idx2++;  
        tex_sphere[idx2] = glm::vec2(0, 1); idx2++;  
        tex_sphere[idx2] = glm::vec2(1, 0); idx2++;  
        tex_sphere[idx2] = glm::vec2(1, 1); idx2++;
    }
    /// normals
      /// 1st tri
      normals_sphere[idx3] = glm::vec4( radius * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius * 1.0 * cos(i*(M_PI / 180)), radius * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius * sin(i*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius * 1.0 * cos(i*(M_PI / 180)), radius * sin(i*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius * 1.0 * cos((i+1)*(M_PI / 180)), radius * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx3++;
      /// 2nd tri
      normals_sphere[idx3] = glm::vec4( radius * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius * 1.0 * cos(i*(M_PI / 180)), radius * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius * sin((i+1)*(M_PI / 180)) * cos(j*(M_PI / 180)),radius * 1.0 * cos((i+1)*(M_PI / 180)), radius * sin((i+1)*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius * 1.0 * cos((i+1)*(M_PI / 180)), radius * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx3++;
      /// 1st color
    } 
  }
}


void makeellipse(int mode,double radius1,double radius2,double radius3,glm::vec4 positions_sphere[],glm::vec4 colors_sphere[],glm::vec4 normals_sphere[],glm::vec2 tex_sphere[], double r,double g,double b,double a)
{
  int idx = 0;
  int idx1 = 0;
  int idx2 = 0;
  int idx3 = 0;
  for (int i = 0; i < 180; ++i)
  {
    for (int j = 0; j < 360; ++j)
    {
      /// 1st tri
      positions_sphere[idx] = glm::vec4( radius1 * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius2 * 1.0 * cos(i*(M_PI / 180)), radius3 * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius1 * sin(i*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius2 * 1.0 * cos(i*(M_PI / 180)), radius3 * sin(i*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius1 * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius2 * 1.0 * cos((i+1)*(M_PI / 180)), radius3 * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx++;
      /// 2nd tri
      positions_sphere[idx] = glm::vec4( radius1 * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius2 * 1.0 * cos(i*(M_PI / 180)), radius3 * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius1 * sin((i+1)*(M_PI / 180)) * cos(j*(M_PI / 180)),radius2 * 1.0 * cos((i+1)*(M_PI / 180)), radius3 * sin((i+1)*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx++;
      positions_sphere[idx] = glm::vec4( radius1 * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius2 * 1.0 * cos((i+1)*(M_PI / 180)), radius3 * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx++;
      /// 1st color
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      /// 2nd color
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      colors_sphere[idx1] = glm::vec4(r,g,b,a);idx1++;
      /// texture
      if(mode == 1){
        tex_sphere[idx2] = glm::vec2(0, 1); idx2++;  
        tex_sphere[idx2] = glm::vec2(0, 0); idx2++;  
        tex_sphere[idx2] = glm::vec2(1, 0); idx2++;  
        tex_sphere[idx2] = glm::vec2(0, 1); idx2++;  
        tex_sphere[idx2] = glm::vec2(1, 0); idx2++;  
        tex_sphere[idx2] = glm::vec2(1, 1); idx2++;
    }
    /// normals
      /// 1st tri
      normals_sphere[idx3] = glm::vec4( radius1 * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius2 * 1.0 * cos(i*(M_PI / 180)), radius3 * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius1 * sin(i*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius2 * 1.0 * cos(i*(M_PI / 180)), radius3 * sin(i*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius1 * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius2 * 1.0 * cos((i+1)*(M_PI / 180)), radius3 * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx3++;
      /// 2nd tri
      normals_sphere[idx3] = glm::vec4( radius1 * sin(i*(M_PI / 180)) * cos(j*(M_PI / 180)),radius2 * 1.0 * cos(i*(M_PI / 180)), radius3 * sin(i*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius1 * sin((i+1)*(M_PI / 180)) * cos(j*(M_PI / 180)),radius2 * 1.0 * cos((i+1)*(M_PI / 180)), radius3 * sin((i+1)*(M_PI / 180)) * sin(j*(M_PI / 180)), 1.0);idx3++;
      normals_sphere[idx3] = glm::vec4( radius1 * sin((i+1)*(M_PI / 180)) * cos((j+1)*(M_PI / 180)),radius2 * 1.0 * cos((i+1)*(M_PI / 180)), radius3 * sin((i+1)*(M_PI / 180)) * sin((j+1)*(M_PI / 180)), 1.0);idx3++;
    } 
  }
}


void cuboidwithoutlid(double height, double length, double width, glm::vec4 positions_cwl[], glm::vec4 colors_cwl[], glm::vec4 normals_cwl[], glm::vec2 tex_cwl[], double r,double g,double b,double a)
{
  int idx1 = 0;
  int idx2 = 0;
  int idx3 = 0;
  int idx4 = 0;
  //front face
  positions_cwl[idx1] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 0.0, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx1++;
  //color front face
  normals_cwl[idx3] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, 0.0, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx3++;
  //color front face
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  //back face
  positions_cwl[idx1] = glm::vec4(length/2, 0.0, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 0.0, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, 0.0, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  //color back face
  normals_cwl[idx3] = glm::vec4(length/2, 0.0, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, 0.0, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, 0.0, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx3++;
  //
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  colors_cwl[idx2] = glm::vec4(r,g,b,a);idx2++;
  //bottom face
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  //color bottom face
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx3++;
  //color bottom face
  colors_cwl[idx2] = glm::vec4(g,b,r,a);idx2++;
  colors_cwl[idx2] = glm::vec4(g,b,r,a);idx2++;
  colors_cwl[idx2] = glm::vec4(g,b,r,a);idx2++;
  colors_cwl[idx2] = glm::vec4(g,b,r,a);idx2++;
  colors_cwl[idx2] = glm::vec4(g,b,r,a);idx2++;
  colors_cwl[idx2] = glm::vec4(g,b,r,a);idx2++;
  //left face
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 0.0, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 0.0, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 0.0, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  //color left face
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, 0.0, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, 0.0, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, 0.0, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, 0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx3++;
  //color left face
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  //right face
  positions_cwl[idx1] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, 0.0, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  //color right face
  normals_cwl[idx3] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, 0.0, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, 0.0, 0.0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, 0, 1.0);idx3++;
  normals_cwl[idx3] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx3++;
  //color right face
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
  colors_cwl[idx2] = glm::vec4(b,r,g,a);idx2++;
}


void cuboid(double height, double length, double width, glm::vec4 positions_cwl[], glm::vec4 colors_cwl[], glm::vec4 normals_cwl[], glm::vec2 tex_cwl[],double r,double g,double b,double a)
{
  int idx1 = 0;
  int idx2 = 0;
  int idx3 = 0;
  int idx4 = 0;
  height = height / 2;
  //front face
  positions_cwl[idx1] = glm::vec4(length/2, height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx1++;
  //color front face
  normals_cwl[idx3] = glm::vec4(0,0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,1.0,1);idx3++;
  //color front face
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  //
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[0];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[3];idx4++;
 
  //back face
  positions_cwl[idx1] = glm::vec4(length/2, height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  //color back face
  normals_cwl[idx3] = glm::vec4(0,0,-1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,-1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,-1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,-1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,-1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,0,-1.0,1);idx3++;
  //color back face
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  //
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[0];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[3];idx4++;
  //bottom face
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  //color bottom face
  normals_cwl[idx3] = glm::vec4(0,-1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,-1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,-1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,-1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,-1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0,-1.0,0.0,1);idx3++;
  //color bottom face
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
 //
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[0];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[3];idx4++;
  //left face
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, 0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, -1.0 * height, -width, 1.0);idx1++;
  //color left face
  normals_cwl[idx3] = glm::vec4(-1.0,0.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0,0.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0,0.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0,0.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0,0.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(-1.0,0.0,0.0,1);idx3++;
  //color left face
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  //
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[0];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[3];idx4++;
  //right face
  positions_cwl[idx1] = glm::vec4(length/2, height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, 0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, -1.0 * height, -width, 1.0);idx1++;
  //color right face
  normals_cwl[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
  //color right face
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  //
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[0];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[3];idx4++;
  //top face
  positions_cwl[idx1] = glm::vec4(length/2, 1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, 1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 1.0 * height, -width, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(length/2, 1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 1.0 * height, 0.0, 1.0);idx1++;
  positions_cwl[idx1] = glm::vec4(-1.0 * length/2, 1.0 * height, -width, 1.0);idx1++;
  //color bottom face
  normals_cwl[idx3] = glm::vec4(0.0,1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,1.0,0.0,1);idx3++;
  normals_cwl[idx3] = glm::vec4(0.0,1.0,0.0,1);idx3++;
  //color bottom face
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  colors_cwl[idx2] = glm::vec4(r, g, b, a);idx2++;
  //
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[0];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[1];idx4++;
  tex_cwl[idx4] = t_coords[2];idx4++;
  tex_cwl[idx4] = t_coords[3];idx4++;
}

//origin at the center of base of triangle having height in + y axis 
void maketriangle(double length, double height, glm::vec4 positions_tri[], glm::vec4 colors_tri[], glm::vec4 normals_tri[], glm::vec2 tex_tri[],double r,double g,double b,double a)
{
    int idx1 = 0;
    int idx2 = 0;
    int idx3 = 0;
    int idx4 = 0;

    positions_tri[idx1] = glm::vec4(-1 * length/2, 0.0, 0.0, 1.0);idx1++;
    positions_tri[idx1] = glm::vec4(1 * length/2, 0.0, 0.0, 1.0);idx1++;
    positions_tri[idx1] = glm::vec4(0.0, height, 0.0, 1.0);idx1++;
    
    normals_tri[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tri[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tri[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;

    //
    tex_tri[idx4] = t_coords[1];idx4++;
    tex_tri[idx4] = t_coords[0];idx4++;
    tex_tri[idx4] = t_coords[2];idx4++;

    colors_tri[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tri[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tri[idx2] = glm::vec4(r, g, b, a);idx2++;
}

void maketie(double width, double height, glm::vec4 positions_tie[], glm::vec4 colors_tie[], glm::vec4 normals_tie[], glm::vec2 tex_tie[],double r,double g,double b,double a)
{
    int idx1 = 0;
    int idx2 = 0;
    int idx3 = 0;
    int idx4 = 0;

    positions_tie[idx1] = glm::vec4(-1 * width/4, 0.0, 0.0, 1.0);idx1++;
    positions_tie[idx1] = glm::vec4(width/4, 0.0, 0.0, 1.0);idx1++;
    positions_tie[idx1] = glm::vec4(0.0, -1 * height/8, 0.0, 1.0);idx1++;

    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    
    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;

    tex_tie[idx4] = t_coords[1];idx4++;
    tex_tie[idx4] = t_coords[0];idx4++;
    tex_tie[idx4] = t_coords[2];idx4++;
    
    positions_tie[idx1] = glm::vec4(0.0, -1 * height/8, 0.0, 1.0);idx1++;
    positions_tie[idx1] = glm::vec4(-width/2,-3 * height/4, 0.0, 1.0);idx1++;
    positions_tie[idx1] = glm::vec4(width/2,-3 * height/4, 0.0, 1.0);idx1++;

    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;

    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;

    tex_tie[idx4] = t_coords[1];idx4++;
    tex_tie[idx4] = t_coords[0];idx4++;
    tex_tie[idx4] = t_coords[2];idx4++;

    positions_tie[idx1] = glm::vec4(-width/2,-3 * height/4, 0.0, 1.0);idx1++;
    positions_tie[idx1] = glm::vec4(width/2,-3 * height/4, 0.0, 1.0);idx1++;
    positions_tie[idx1] = glm::vec4(0.0,-1 * height, 0.0, 1.0);idx1++;

    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;
    normals_tie[idx3] = glm::vec4(0.0,0.0,1.0,1);idx3++;

    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;
    colors_tie[idx2] = glm::vec4(r, g, b, a);idx2++;

    tex_tie[idx4] = t_coords[1];idx4++;
    tex_tie[idx4] = t_coords[0];idx4++;
    tex_tie[idx4] = t_coords[2];idx4++;
}

//-----------------------------------------------------------------
const int num_cylinder = 2*3*360 + 6*360;
glm::vec4 positions_cylinder[num_cylinder];
glm::vec4 colors_cylinder[num_cylinder];

const int num_sphere = 180 * 360 * 6;
glm::vec4 positions_sphere[num_sphere];
glm::vec4 colors_sphere[num_sphere];

glm::vec2 texture_present = glm::vec2(1.0,1.0);
glm::vec2 texture_absent = glm::vec2(0.0,0.0);

const int num_room = 36 + 4*3 + 6*3;

const int num_bwl = 5 * 6;
const int num_room_vertices = 16 ; 
const double rh = 70, rw = 120, rl = 120 ;
const double dh = 35, dw = 15, dd = 20 ;
const double wh = 10, ww = 10, wdz = 10, wdy = 10 ;

glm::vec4 positions_room[num_room_vertices] = {
  glm::vec4(0,0,0,1.0),
  glm::vec4(0,rh,0,1.0),
  glm::vec4(rw,rh,0,1.0),
  glm::vec4(rw,0,0,1.0),
  glm::vec4(rw, 0, -rl, 1.0),
  glm::vec4(rw,rh, -rl, 1.0),
  glm::vec4(0,rh, -rl, 1.0),
  glm::vec4(0,0, -rl, 1.0),
  glm::vec4(dd,0, 0, 1.0),
  glm::vec4(dd,dh, 0, 1.0),
  glm::vec4(dd+dw,dh, 0, 1.0),
  glm::vec4(dd+dw,0, 0, 1.0),
  glm::vec4(rw,wdy, -wdz, 1.0),
  glm::vec4(rw,wdy + wh, -wdz, 1.0),
  glm::vec4(rw,wdy + wh, -wdz-ww, 1.0),
  glm::vec4(rw,wdy, -wdz-ww, 1.0)
};

glm::vec4 positions_hands[8] = {
  glm::vec4(  -0.2,  0.0,  0.2, 1.0),
  glm::vec4(  0.2,   0.0,  0.2, 1.0),
  glm::vec4(  0.05,   -0.5,  0.2, 1.0),
  glm::vec4(  -0.05,  -0.5,  0.2, 1.0),
  glm::vec4(  -0.05,  -0.5, -0.2, 1.0),
  glm::vec4(  0.05,   -0.5, -0.2, 1.0),
  glm::vec4(  0.2,   0.0, -0.2, 1.0),
  glm::vec4(  -0.2,  0.0, -0.2, 1.0) 
};

glm::vec4 positions_ears[8] = {
  glm::vec4(  -0.1,  0.0,  0.2, 1.0),
  glm::vec4(  0.1,   0.0,  0.2, 1.0),
  glm::vec4(  0.01,   -0.5,  0, 1.0),
  glm::vec4(  -0.01,  -0.5,  0, 1.0),
  glm::vec4(  -0.01,  -0.5, -0, 1.0),
  glm::vec4(  0.01,   -0.5, -0, 1.0),
  glm::vec4(  0.1,   0.0, -0.2, 1.0),
  glm::vec4(  -0.1,  0.0, -0.2, 1.0) 
};

glm::vec4 positions_feet[8] = {
  glm::vec4(  -0.2,  0.0,  0.2, 1.0),
  glm::vec4(  0.2,   0.0,  0.2, 1.0),
  glm::vec4(  0.05,   -0.75,  0.2, 1.0),
  glm::vec4(  -0.05,  -0.75,  0.2, 1.0),
  glm::vec4(  -0.05,  -0.75, -0.2, 1.0),
  glm::vec4(  0.05,   -0.75, -0.2, 1.0),
  glm::vec4(  0.2,   0.0, -0.2, 1.0),
  glm::vec4(  -0.2,  0.0, -0.2, 1.0) 
};

double hx1=1 , hy1=209.0/256, hz1=190.0/256 ; 
double ex1=1 , ey1=0.0      , ez1=0         ; 
glm::vec4 colors_hands[8] = {
  glm::vec4(hx1, hy1, hz1, 1.0),
  glm::vec4(hx1, hy1, hz1, 1.0),
  glm::vec4(hx1, hy1, hz1, 1.0),
  glm::vec4(hx1, hy1, hz1, 1.0),
  glm::vec4(hx1, hy1, hz1, 1.0),
  glm::vec4(hx1, hy1, hz1, 1.0),
  glm::vec4(hx1, hy1, hz1, 1.0),
  glm::vec4(hx1, hy1, hz1, 1.0)
};

glm::vec4 colors_room[num_room_vertices] = {
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(1, 0.2, 0.3, 1.0),
  glm::vec4(1, 0.7, 0.3, 1.0),
  glm::vec4(1, 0.3, 0.1, 1.0),
  glm::vec4(0, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0),
  glm::vec4(0.3, 0.3, 0.3, 1.0)
};

glm::vec4 colors_ears[8] = {
  glm::vec4(ex1, ey1, ez1, 1.0),
  glm::vec4(ex1, ey1, ez1, 1.0),
  glm::vec4(ex1, ey1, ez1, 1.0),
  glm::vec4(ex1, ey1, ez1, 1.0),
  glm::vec4(ex1, ey1, ez1, 1.0),
  glm::vec4(ex1, ey1, ez1, 1.0),
  glm::vec4(ex1, ey1, ez1, 1.0),
  glm::vec4(ex1, ey1, ez1, 1.0)
};

glm::vec4 colors_feet[8] = {
  glm::vec4(1.0, 0.1, 0.5, 1.0),
  glm::vec4(1.0, 0.1, 0.5, 1.0),
  glm::vec4(1.0, 0.1, 0.5, 1.0),
  glm::vec4(1.0, 0.1, 0.5, 1.0),
  glm::vec4(1.0, 0.1, 0.5, 1.0),
  glm::vec4(1.0, 0.1, 0.5, 1.0),
  glm::vec4(1.0, 0.1, 0.5, 1.0),
  glm::vec4(1.0, 0.1, 0.5, 1.0),
};


int tri_idx=0;
int tri_idx_feet=0;
int tri_idx_hands=0;
int tri_idx_ears=0;
int tri_idx_neck=0;
int tri_idx_room=0;

glm::vec4 v_positions_control_point [num_sphere];
glm::vec4 v_colors_control_point    [num_sphere];
glm::vec4 v_positions_lb        [num_bwl      ];
glm::vec4 v_colors_lb           [num_bwl      ];
glm::vec4 v_positions_ub        [num_bwl      ];
glm::vec4 v_colors_ub           [num_bwl      ];
glm::vec4 v_positions_uarms     [num_cylinder ];
glm::vec4 v_positions_larms     [num_cylinder ];
glm::vec4 v_colors_uarms        [num_cylinder ];
glm::vec4 v_colors_larms        [num_cylinder ];
glm::vec4 v_positions_hands     [num_cylinder ];
glm::vec4 v_colors_hands        [num_cylinder ];
glm::vec4 v_positions_ears      [num_vertices ];
glm::vec4 v_colors_ears         [num_vertices ];
glm::vec4 v_positions_torso1    [num_cylinder ];
glm::vec4 v_colors_torso1       [num_cylinder ];
glm::vec4 v_positions_torso2    [num_sphere   ];
glm::vec4 v_colors_torso2       [num_sphere   ];
glm::vec4 v_positions_torso3    [num_cylinder ];
glm::vec4 v_colors_torso3       [num_cylinder ];
glm::vec4 v_positions_torso4    [num_sphere   ];
glm::vec4 v_colors_torso4       [num_sphere   ];
glm::vec4 v_positions_ulegs     [num_cylinder ];
glm::vec4 v_colors_ulegs        [num_cylinder ];
glm::vec4 v_positions_llegs     [num_cylinder ];
glm::vec4 v_colors_llegs        [num_cylinder ];
glm::vec4 v_positions_neck      [num_cylinder ];
glm::vec4 v_colors_neck         [num_cylinder ];
glm::vec4 v_positions_jointSmall[num_sphere   ];
glm::vec4 v_colors_jointSmall   [num_sphere   ];
glm::vec4 v_positions_jointBig  [num_sphere   ];
glm::vec4 v_colors_jointBig     [num_sphere   ];
glm::vec4 v_positions_head      [num_sphere   ];
glm::vec4 v_colors_head         [num_sphere   ];
glm::vec4 v_positions_tie       [9            ];
glm::vec4 v_colors_tie          [9            ];
glm::vec4 v_positions_eye       [num_sphere   ];
glm::vec4 v_colors_eye          [num_sphere   ];
glm::vec4 v_positions_mouth     [3            ];
glm::vec4 v_colors_mouth        [3            ]; 
glm::vec4 v_colors_feet         [num_vertices ]; 
glm::vec4 v_positions_feet      [num_vertices ]; 
glm::vec4 v_positions_lens      [num_cylinder ];
glm::vec4 v_colors_lens         [num_cylinder ];
glm::vec4 v_positions_joint     [num_cylinder ];
glm::vec4 v_colors_joint        [num_cylinder ];
glm::vec4 v_positions_frame     [num_cylinder ];
glm::vec4 v_colors_frame        [num_cylinder ];
glm::vec4 v_positions_box       [num_vertices ];
glm::vec4 v_colors_box          [num_vertices ];
glm::vec4 v_positions_room      [num_room ] ;
glm::vec4 v_colors_room         [num_room ] ;
glm::vec4 v_positions_table     [num_sphere  ] ; // table positions
glm::vec4 v_colors_table        [num_sphere  ] ; // table 
glm::vec4 v_positions_tableTop  [num_cylinder] ; // tabletop positions
glm::vec4 v_colors_tableTop     [num_cylinder] ; // tabletop 
glm::vec4 v_positions_tableL    [num_cylinder] ; // table leg positions
glm::vec4 v_colors_tableL       [num_cylinder] ; // table leg colors
glm::vec4 v_positions_chair[num_vertices] ;
glm::vec4 v_colors_chair   [num_vertices] ;
glm::vec4 v_positions_chair_rest[num_vertices] ;
glm::vec4 v_colors_chair_rest   [num_vertices] ;
glm::vec4 v_positions_cupboard   [num_vertices] ;
glm::vec4 v_colors_cupboard      [num_vertices] ;
glm::vec4 v_positions_cupboard_door   [num_vertices] ;
glm::vec4 v_colors_cupboard_door      [num_vertices] ;
glm::vec4 v_positions_door   [num_vertices] ;
glm::vec4 v_colors_door      [num_vertices] ;
glm::vec4 v_positions_door_knob   [num_sphere] ;
glm::vec4 v_colors_door_knob      [num_sphere] ;
glm::vec4 v_positions_bed   [num_vertices] ;
glm::vec4 v_colors_bed      [num_vertices] ;
glm::vec4 v_positions_bed_leg1   [num_vertices] ;
glm::vec4 v_colors_bed_leg1      [num_vertices] ;
glm::vec4 v_positions_bed_leg2   [num_vertices] ;
glm::vec4 v_colors_bed_leg2      [num_vertices] ;
glm::vec4 v_positions_chair_leg[num_cylinder] ;
glm::vec4 v_colors_chair_leg   [num_cylinder] ;
glm::vec2 v_tex_control_point [num_sphere];
glm::vec2 v_tex_lb        [num_bwl      ];
glm::vec2 v_tex_ub        [num_bwl      ];
glm::vec2 v_tex_uarms     [num_cylinder ];
glm::vec2 v_tex_larms     [num_cylinder ];
glm::vec2 v_tex_hands     [num_cylinder ];
glm::vec2 v_tex_ears      [num_vertices ];
glm::vec2 v_tex_torso1    [num_cylinder ];
glm::vec2 v_tex_torso2    [num_sphere   ];
glm::vec2 v_tex_torso3    [num_cylinder ];
glm::vec2 v_tex_torso4    [num_sphere   ];
glm::vec2 v_tex_ulegs     [num_cylinder ];
glm::vec2 v_tex_llegs     [num_cylinder ];
glm::vec2 v_tex_neck      [num_cylinder ];
glm::vec2 v_tex_jointSmall[num_sphere   ];
glm::vec2 v_tex_jointBig  [num_sphere   ];
glm::vec2 v_tex_head      [num_sphere   ];
glm::vec2 v_tex_tie       [9            ];
glm::vec2 v_tex_eye       [num_sphere   ];
glm::vec2 v_tex_mouth     [3            ];
glm::vec2 v_tex_feet      [num_vertices ]; 
glm::vec2 v_tex_lens      [num_cylinder ];
glm::vec2 v_tex_joint     [num_cylinder ];
glm::vec2 v_tex_frame     [num_cylinder ];
glm::vec2 v_tex_box       [num_vertices ];
glm::vec2 v_tex_room      [num_room ] ;
glm::vec2 v_tex_table     [num_sphere  ] ; // table tex
glm::vec2 v_tex_tableTop  [num_cylinder] ; // tabletop tex
glm::vec2 v_tex_tableL    [num_cylinder] ; // table leg tex
glm::vec2 v_tex_chair[num_vertices] ;
glm::vec2 v_tex_chair_rest[num_vertices] ;
glm::vec2 v_tex_cupboard   [num_vertices] ;
glm::vec2 v_tex_cupboard_door   [num_vertices] ;
glm::vec2 v_tex_door   [num_vertices] ;
glm::vec2 v_tex_door_knob   [num_sphere] ;
glm::vec2 v_tex_bed   [num_vertices] ;
glm::vec2 v_tex_bed_leg1   [num_vertices] ;
glm::vec2 v_tex_bed_leg2   [num_vertices] ;
glm::vec2 v_tex_chair_leg[num_cylinder] ;
glm::vec4 v_normals_control_point [num_sphere];
glm::vec4 v_normals_lb        [num_bwl      ];
glm::vec4 v_normals_ub        [num_bwl      ];
glm::vec4 v_normals_uarms     [num_cylinder ];
glm::vec4 v_normals_larms     [num_cylinder ];
glm::vec4 v_normals_hands     [num_cylinder ];
glm::vec4 v_normals_ears      [num_vertices ];
glm::vec4 v_normals_torso1    [num_cylinder ];
glm::vec4 v_normals_torso2    [num_sphere   ];
glm::vec4 v_normals_torso3    [num_cylinder ];
glm::vec4 v_normals_torso4    [num_sphere   ];
glm::vec4 v_normals_ulegs     [num_cylinder ];
glm::vec4 v_normals_llegs     [num_cylinder ];
glm::vec4 v_normals_neck      [num_cylinder ];
glm::vec4 v_normals_jointSmall[num_sphere   ];
glm::vec4 v_normals_jointBig  [num_sphere   ];
glm::vec4 v_normals_head      [num_sphere   ];
glm::vec4 v_normals_tie       [9            ];
glm::vec4 v_normals_eye       [num_sphere   ];
glm::vec4 v_normals_mouth     [3            ];
glm::vec4 v_normals_feet      [num_vertices ]; 
glm::vec4 v_normals_lens      [num_cylinder ];
glm::vec4 v_normals_joint     [num_cylinder ];
glm::vec4 v_normals_frame     [num_cylinder ];
glm::vec4 v_normals_box       [num_vertices ];
glm::vec4 v_normals_room      [num_room ] ;
glm::vec4 v_normals_table     [num_sphere  ] ; // table normal
glm::vec4 v_normals_tableTop  [num_cylinder] ; // tabletop normal
glm::vec4 v_normals_tableL    [num_cylinder] ; // table leg normal
glm::vec4 v_normals_chair[num_vertices] ;
glm::vec4 v_normals_chair_rest[num_vertices] ;
glm::vec4 v_normals_cupboard   [num_vertices] ;
glm::vec4 v_normals_cupboard_door   [num_vertices] ;
glm::vec4 v_normals_door   [num_vertices] ;
glm::vec4 v_normals_door_knob   [num_sphere] ;
glm::vec4 v_normals_bed   [num_vertices] ;
glm::vec4 v_normals_bed_leg1   [num_vertices] ;
glm::vec4 v_normals_bed_leg2   [num_vertices] ;
glm::vec4 v_normals_chair_leg[num_cylinder] ;


glm::vec4 ccolors_belly             [num_cylinder   ];
glm::vec4 ccolors_j             [num_sphere   ];
glm::vec4 ccolors_leg           [num_cylinder ];
glm::vec4 ccolors_paw           [num_vertices ];
glm::vec4 ccolors_t1            [num_cylinder ];
glm::vec4 ccolors_j2            [num_sphere   ];
glm::vec4 ccolors_t2            [num_cylinder ];
glm::vec4 ccolors_t3            [num_cylinder ];
glm::vec4 ccolors_cbum          [num_sphere   ];
glm::vec4 ccolors_ceye          [num_sphere   ];
glm::vec4 ccolors_ears          [3            ];
glm::vec4 ccolors_mouth         [3            ];
glm::vec4 cpos_belly            [num_cylinder ];
glm::vec4 cpos_j                [num_sphere   ];
glm::vec4 cpos_leg              [num_cylinder ];
glm::vec4 cpos_paw              [num_vertices ];
glm::vec4 cpos_t1               [num_cylinder ];
glm::vec4 cpos_j2               [num_sphere   ];
glm::vec4 cpos_t2               [num_cylinder ];
glm::vec4 cpos_t3               [num_cylinder ];
glm::vec4 cpos_cbum             [num_sphere   ];
glm::vec4 cpos_ceye             [num_sphere   ];
glm::vec4 cpos_ears             [3            ];
glm::vec4 cpos_mouth            [3            ];

glm::vec2 ctex_belly            [num_cylinder ];
glm::vec2 ctex_j                [num_sphere   ];
glm::vec2 ctex_leg              [num_cylinder ];
glm::vec2 ctex_paw              [num_vertices ];
glm::vec2 ctex_t1               [num_cylinder ];
glm::vec2 ctex_j2               [num_sphere   ];
glm::vec2 ctex_t2               [num_cylinder ];
glm::vec2 ctex_t3               [num_cylinder ];
glm::vec2 ctex_cbum             [num_sphere   ];
glm::vec2 ctex_ceye             [num_sphere   ];
glm::vec2 ctex_ears             [3            ];
glm::vec2 ctex_mouth            [3            ];
glm::vec4 cnormals_belly            [num_cylinder ];
glm::vec4 cnormals_j                [num_sphere   ];
glm::vec4 cnormals_leg              [num_cylinder ];
glm::vec4 cnormals_paw              [num_vertices ];
glm::vec4 cnormals_t1               [num_cylinder ];
glm::vec4 cnormals_j2               [num_sphere   ];
glm::vec4 cnormals_t2               [num_cylinder ];
glm::vec4 cnormals_t3               [num_cylinder ];
glm::vec4 cnormals_cbum             [num_sphere   ];
glm::vec4 cnormals_ceye             [num_sphere   ];
glm::vec4 cnormals_ears             [3            ];
glm::vec4 cnormals_mouth            [3            ];

glm::vec4 v_positions_lamp [num_cylinder] ;
glm::vec4 v_colors_lamp [num_cylinder] ;
glm::vec4 v_normals_lamp [num_cylinder] ;
glm::vec2 v_tex_lamp [num_cylinder] ;

glm::vec4 v_positions_lamp_base [num_cylinder] ;
glm::vec4 v_colors_lamp_base [num_cylinder] ;
glm::vec4 v_normals_lamp_base [num_cylinder] ;
glm::vec2 v_tex_lamp_base [num_cylinder] ;

void quad_feet(int a, int b, int c, int d)
{
  v_colors_feet[tri_idx_feet] = colors_feet[a]; v_positions_feet[tri_idx_feet] = positions_feet[a]; v_tex_feet[tri_idx_feet] = t_coords[1]; tri_idx_feet++;
  v_colors_feet[tri_idx_feet] = colors_feet[b]; v_positions_feet[tri_idx_feet] = positions_feet[b]; v_tex_feet[tri_idx_feet] = t_coords[0]; tri_idx_feet++;
  v_colors_feet[tri_idx_feet] = colors_feet[c]; v_positions_feet[tri_idx_feet] = positions_feet[c]; v_tex_feet[tri_idx_feet] = t_coords[2]; tri_idx_feet++;
  v_colors_feet[tri_idx_feet] = colors_feet[a]; v_positions_feet[tri_idx_feet] = positions_feet[a]; v_tex_feet[tri_idx_feet] = t_coords[1]; tri_idx_feet++;
  v_colors_feet[tri_idx_feet] = colors_feet[c]; v_positions_feet[tri_idx_feet] = positions_feet[c]; v_tex_feet[tri_idx_feet] = t_coords[2]; tri_idx_feet++;
  v_colors_feet[tri_idx_feet] = colors_feet[d]; v_positions_feet[tri_idx_feet] = positions_feet[d]; v_tex_feet[tri_idx_feet] = t_coords[3]; tri_idx_feet++;
 }

void quad_hands(int a, int b, int c, int d)
{
  v_colors_hands[tri_idx_hands] = colors_hands[a]; v_positions_hands[tri_idx_hands] = positions_hands[a]; v_tex_hands[tri_idx_hands] = t_coords[1]; tri_idx_hands++;
  v_colors_hands[tri_idx_hands] = colors_hands[b]; v_positions_hands[tri_idx_hands] = positions_hands[b]; v_tex_hands[tri_idx_hands] = t_coords[0]; tri_idx_hands++;
  v_colors_hands[tri_idx_hands] = colors_hands[c]; v_positions_hands[tri_idx_hands] = positions_hands[c]; v_tex_hands[tri_idx_hands] = t_coords[2]; tri_idx_hands++;
  v_colors_hands[tri_idx_hands] = colors_hands[a]; v_positions_hands[tri_idx_hands] = positions_hands[a]; v_tex_hands[tri_idx_hands] = t_coords[1]; tri_idx_hands++;
  v_colors_hands[tri_idx_hands] = colors_hands[c]; v_positions_hands[tri_idx_hands] = positions_hands[c]; v_tex_hands[tri_idx_hands] = t_coords[2]; tri_idx_hands++;
  v_colors_hands[tri_idx_hands] = colors_hands[d]; v_positions_hands[tri_idx_hands] = positions_hands[d]; v_tex_hands[tri_idx_hands] = t_coords[3]; tri_idx_hands++;
 }

 void quad_ears(int a, int b, int c, int d)
{
  v_colors_ears[tri_idx_ears] = colors_ears[a]; v_positions_ears[tri_idx_ears] = positions_ears[a]; v_tex_ears[tri_idx_ears] = t_coords[1]; tri_idx_ears++;
  v_colors_ears[tri_idx_ears] = colors_ears[b]; v_positions_ears[tri_idx_ears] = positions_ears[b]; v_tex_ears[tri_idx_ears] = t_coords[0]; tri_idx_ears++;
  v_colors_ears[tri_idx_ears] = colors_ears[c]; v_positions_ears[tri_idx_ears] = positions_ears[c]; v_tex_ears[tri_idx_ears] = t_coords[2]; tri_idx_ears++;
  v_colors_ears[tri_idx_ears] = colors_ears[a]; v_positions_ears[tri_idx_ears] = positions_ears[a]; v_tex_ears[tri_idx_ears] = t_coords[1]; tri_idx_ears++;
  v_colors_ears[tri_idx_ears] = colors_ears[c]; v_positions_ears[tri_idx_ears] = positions_ears[c]; v_tex_ears[tri_idx_ears] = t_coords[2]; tri_idx_ears++;
  v_colors_ears[tri_idx_ears] = colors_ears[d]; v_positions_ears[tri_idx_ears] = positions_ears[d]; v_tex_ears[tri_idx_ears] = t_coords[3]; tri_idx_ears++;
 }

 void quad_room(int a, int b, int c, int d)
{
  v_colors_room[tri_idx_room] = colors_room[a]; v_positions_room[tri_idx_room] = positions_room[a]; v_tex_room[tri_idx_room] = t_coords[1]; tri_idx_room++;
  v_colors_room[tri_idx_room] = colors_room[b]; v_positions_room[tri_idx_room] = positions_room[b]; v_tex_room[tri_idx_room] = t_coords[0]; tri_idx_room++;
  v_colors_room[tri_idx_room] = colors_room[c]; v_positions_room[tri_idx_room] = positions_room[c]; v_tex_room[tri_idx_room] = t_coords[2]; tri_idx_room++;
  v_colors_room[tri_idx_room] = colors_room[a]; v_positions_room[tri_idx_room] = positions_room[a]; v_tex_room[tri_idx_room] = t_coords[1]; tri_idx_room++;
  v_colors_room[tri_idx_room] = colors_room[c]; v_positions_room[tri_idx_room] = positions_room[c]; v_tex_room[tri_idx_room] = t_coords[2]; tri_idx_room++;
  v_colors_room[tri_idx_room] = colors_room[d]; v_positions_room[tri_idx_room] = positions_room[d]; v_tex_room[tri_idx_room] = t_coords[3]; tri_idx_room++;
 }


void colorcube_feet(void)
{
    quad_hands( 0,1 ,2, 3);
    quad_hands( 4,5 ,6, 7);
    quad_hands( 1, 2, 5, 6);
    quad_hands( 0,3 ,4, 7);
    quad_hands( 0,1 ,6, 7);
    quad_hands( 2,3 ,4, 5);
}

void colorcube_hands(void)
{
    quad_hands( 0,1 ,2, 3);
    quad_hands( 4,5 ,6, 7);
    quad_hands( 1, 2, 5, 6);
    quad_hands( 0,3 ,4, 7);
    quad_hands( 0,1 ,6, 7);
    quad_hands( 2,3 ,4, 5);
}

void colorcube_ears(void)
{
    quad_ears( 0,1 ,2, 3);
    quad_ears( 4,5 ,6, 7);
    quad_ears( 1, 2, 5, 6);
    quad_ears( 0,3 ,4, 7);
    quad_ears( 0,1 ,6, 7);
    quad_ears( 2,3 ,4, 5);
}

void colorcube_room(void)
{
    quad_room( 0,8 ,9, 1); //front
    quad_room( 1,9 ,10, 2); //front
    quad_room( 2,10 ,11, 3); //front
    quad_room( 4,5 ,6, 7); //back
    quad_room( 1, 2, 5, 6); // top
    quad_room( 0,3 ,4, 7); //bottom
    quad_room( 0,1 ,6, 7); //side
    quad_room( 2,13 ,12, 3); //side
    quad_room( 3,12 ,15, 4); //side
    quad_room( 4,15 ,14, 5); //side
    quad_room( 5,14 ,13, 2); //side
}

void fill_ncr(int n){
  for (int i=0;i<=n;i++) ncr.push_back(0.0);
  ncr[0] = 1.0 ;
  for (int k = 0; k < n; ++ k)
    ncr[k+1] = 1.0 * (ncr[k] * (n-k)) / (k+1) ;
  ncr[n] = 0.0 ; 

}

std::vector<double> get_bezier_point(double &t){

  std::vector<double> out(3) ; 
  int n = controlPoints.size() ;
  if (ncr.size()==0) fill_ncr(n-1) ;
  // double tr = 1, tr1 = pow(1-t,n-1);
  for (int i=0;i<n;i++){
    double tr = pow(t,i);
    double tr1 = pow(t,n-1-i) ;
    out[0] += ncr[i] * tr * tr1 * controlPoints[i][0]; 
    out[1] += ncr[i] * tr * tr1 * controlPoints[i][1]; 
    out[2] += ncr[i] * tr * tr1 * controlPoints[i][2]; 
  }
  // std::cerr << "These are the points " << out[0] << " " << out[1] << " " << out[2] << "\n" ;
  return out ; 
}

void get_camera_positions(){
  double i=0;
  while (i<=1){
    cameraPositions.push_back(get_bezier_point(i)) ;
    i+=TIME_INTERVAL;
  }
}


std::string get_string_from_vec(std::vector <double> &v )
{
  std::string out = "" ;

  for (int i=0;i<v.size();i++)
  {
    out += std::to_string(v[i]) + " " ;
  }

  return out ; 
}

int are_not_equal(std::vector<double> v1, std::vector<double> v2) 
{
  if (v1.size() != v2.size()) return 1 ;
  for (int i=0;i<v1.size();i++)
    if (v1[i] != v2[i]) return 1 ;

  return 0 ; 
}

// getting frame from string ; 
void get_frame_from_string(std::vector<std::vector<double> > &prevFrame, std::string &s)
{

  std::istringstream input(s);
  std::string str,str2 ; 
  std::vector <std::vector<double> > frame = prevFrame;

  std::getline(input,str,' ') ;
  keylight1.push_back(std::stoi(str));
  std::getline(input,str,' ') ;
  keylight2.push_back(std::stoi(str));

  while(std::getline(input, str, ' ')) {
      std::vector <double> point(6) ; 
      for (int j=0;j<6;j++){
        std::getline(input,str2,' ') ;
        point[j] = (std::stod(str2));
      }
      frame[std::stoi(str)] = point ; 
  }

  keyframes.push_back(frame) ; 
}


std::vector<std::vector<double> > get_frame_average(std::vector < std::vector <double> > &v1, std::vector< std::vector<double> > &v2, double n)
{

  std::vector <std::vector< double> > out(NUM_NODES, std::vector<double> (6))  ;
  // std::cerr << out.size() ;
  if (v1.size() == v2.size()){
    for (int i=0;i<v1.size();i++){
        for (int j=0;j<6;j++){
          // std::cerr << v1[0].size() << " "<< v2[0].size() <<"\n"; 
          // Linearly interpolating coords
          out[i][j] = v1[i][j] * n + v2[i][j] * (1 - n) ;
        }
      }
    }
  else {
    std::cerr << "Frame lengths are different\n" ;
    exit(1) ;
    // std::cerr << v1.size() << " "<< v2.size() <<"\n"; 
    }
  return out ; 
}

// interpolating keyframes to get the frames of the animation
void interpolate_frames()
{
  // for (int i=0;i<keyframes.size();i++) std::cout<<keyframes[i].size() << " " ;
    // std::cout<<"\n" ;
  for (int i=1;i<keyframes.size();i++)
  {
    allframes.push_back(keyframes[i-1]) ;
    for (int j=1;j<NUM_FRAMES;j++){
      alllight1.push_back(keylight1[i-1]) ;
      alllight2.push_back(keylight2[i-1]) ;
      allframes.push_back(get_frame_average(keyframes[i-1],keyframes[i], 1.0*j/NUM_FRAMES)) ;
    }
  }
  std::cerr << "Done interpolation of frames\n" ;
  allframes.push_back(keyframes[keyframes.size()-1]) ;

  for (int i=0;i<allframes.size();i++){
    for (int j=0;j<allframes[i].size();j++){
      for (int k=0;k<6;k++)
      if (allframes[i][j][k] != 0) std::cerr << allframes[i][j][k] <<" " ;
    }
    std::cerr<<"\n" ;
  }
}

// get keyframes from the keyframes.txt file and interpolate them 
void get_all_frames()
{

  // clean all the vectors
  keyframes.clear() ;
  allframes.clear() ;
  prevFrame.clear() ;
  keylight1.clear() ; 
  keylight2.clear() ;

  std::vector<double> v(6) ;

  for (int i=0;i<NUM_NODES;i++) prevFrame.push_back(v) ;

  std::string cur_frame ; 
  std::ifstream infile("keyframes.txt");
  if (infile.is_open()) {
    while (getline(infile, cur_frame)){
      // printf("%s\n" , cur_frame.c_str()) ;
      get_frame_from_string(prevFrame,cur_frame) ;
    }
    infile.close();
    printf("Done getting %lu keyframes\n", keyframes.size()) ;
    // std::cout << keyframes.size() << " " << keylight1.size() << " " << keylight2.size() << "\n" ; 
    interpolate_frames() ; 
  } 
}

// to save Frae to keyframes.txt
void saveFrame(){

  std::ofstream outfile;
  outfile.open("keyframes.txt", std::ios::app);
  if( !outfile ) {
    std::cerr << "Cannot open file\n" ;
    exit(1) ; 
  }
  
  outfile << std::to_string(LIGHT1) << " " << std::to_string(LIGHT2) << " " ;

  // saving only those parameters that are required
  if (prevFrame.size() == 0 )
  {

    for (int i=0;i<model_vec.size();i++)
    {
      prevFrame.push_back(model_vec[i]->get_parameters()) ;
    }
    // saving the keyframes
    // as this is the first keyframe, we store whole frame data
    for (int i=0;i<prevFrame.size();i++)
        outfile << std::to_string(i) << " " << get_string_from_vec(prevFrame[i]) ;

  }
  else
  {
    for (int i=0;i<prevFrame.size();i++)
    {
      if (are_not_equal(model_vec[i]->get_parameters(), prevFrame[i])) {
        prevFrame[i] = model_vec[i]->get_parameters() ; 
        outfile << std::to_string(i) << " " << get_string_from_vec(prevFrame[i]) ;
      }
    }
  }
  outfile << "\n" ;
  outfile.close() ;
  // save_frame_to_image_file(12) ;
}
void initBuffersGL(void)
{


  std::string vertex_shader_file("vshader.glsl");
  std::string fragment_shader_file("fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  GLuint tex_room = LoadTexture("images/jeans.bmp",256,256);
  GLuint tex_belly = LoadTexture("images/grass.bmp",256,256);
  GLuint tex_cjoint = LoadTexture("images/grass.bmp",256,256);
  GLuint tex_torso1 = LoadTexture("images/grass.bmp",256,256);
  GLuint tex_cbum = LoadTexture("images/grass.bmp",256,256);
  GLuint tex_bed = LoadTexture("images/all1.bmp",256,256);
  GLuint tex_wood = LoadTexture("images/boot1.bmp",256,256);


  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  normalMatrix = glGetUniformLocation( shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
  tex_present = glGetAttribLocation( shaderProgram, "tex_present" );
  SWITCH1 = glGetUniformLocation( shaderProgram, "light1" );
  SWITCH2 = glGetUniformLocation( shaderProgram, "light2" );

  //*********************************** Making box geometry **********************************************//
  cuboidwithoutlid(lbh,lbl,lbw,v_positions_lb,v_colors_lb,v_normals_lb,v_tex_lb,lcr,lcg,lcb,lca);    // first  box
  cuboidwithoutlid(ubh,ubl,ubw,v_positions_ub,v_colors_ub,v_normals_ub,v_tex_ub,ucr,ucg,ucb,uca);    // second box
  
  //********************************************** Making humanoid geometry **********************************************//

  makecylinder (0,lens_radius,lens_radius,.1,v_positions_lens,v_colors_lens,v_normals_lens,v_tex_lens,culr,culg,culb,0.3) ;             // sunglasses
  makecylinder (0,0.05,0.05,joint_length, v_positions_joint,v_colors_joint ,v_normals_joint,v_tex_joint,culr,culg,culb,cula) ;             // joint
  makecylinder (0,0.05,0.05,1.5,v_positions_frame,v_colors_frame,v_normals_frame,v_tex_frame, culr , culg,culb,cula) ;                       // frame

  makeellipsecylinder (0,rt11,rt11/2,rt12,rt12/2,ht1,v_positions_torso1,v_colors_torso1,v_normals_torso1,v_tex_torso1,ct1r,ct1g,ct1b,ct1a) ; // torso1
  makeellipsecylinder (0,rt31,rt31/2,rt32,rt32/2,ht3,v_positions_torso3,v_colors_torso3,v_normals_torso3,v_tex_torso3,ct1r,ct1g,ct1b,ct1a) ; // torso3
  makeellipsecylinder (0,nr1/1.3,nr1,nr2/1.3,nr2,hn,v_positions_neck,v_colors_neck,v_normals_torso2,v_tex_torso2,hx,hy,hz,1.0 ) ;            // neck

  makecylinder (0,rua1,rua2,hua,v_positions_uarms,v_colors_uarms,v_normals_uarms,v_tex_uarms,ct1r,ct1g,ct1b,ct1a) ;                        // upper arms
  makecylinder (0,rul1,rul2,hul,v_positions_ulegs,v_colors_ulegs,v_normals_ulegs,v_tex_ulegs,culr,culg,culb,cula) ;                        // upper legs
  makecylinder (0,rll1,rll2,hll,v_positions_llegs,v_colors_llegs,v_normals_llegs,v_tex_llegs,culr,culg,culb,cula) ;                        // lower legs
  makecylinder (0,rla1,rla2,hla,v_positions_larms,v_colors_larms,v_normals_larms,v_tex_larms,hx,hy,hz,1.0 ) ;                              // lower arms

  makeellipse  (0,rt2,rt2/2.0,rt2/2.0,v_positions_torso2,v_colors_torso2,v_normals_torso2,v_tex_torso2,ct1r,ct1g,ct1b,ct1a) ;                // torso2
  makeellipse  (0,rt4,rt4/3.0,rt4/2.0,v_positions_torso4,v_colors_torso4,v_normals_torso4,v_tex_torso4,ct1r,ct1g,ct1b,ct1a) ;                // torso4
  makeellipse  (0,nr2/1.3,nr2/1.3,nr2+0.1,v_positions_head,v_colors_head,v_normals_head,v_tex_head,0.1,0.1,0.1,1.0) ;                    // head

  makesphere   (0,rsj1,v_positions_jointSmall, v_colors_jointSmall,v_normals_jointSmall,v_tex_jointSmall,hx,hy,hz,1.0)  ;                            // small joint
  makesphere   (0,rbj1,v_positions_jointBig, v_colors_jointBig,v_normals_jointBig,v_tex_jointBig,ct1r,ct1g,ct1b,ct1a) ;                          // big joint
  makesphere   (0,0.15,v_positions_eye,v_colors_eye,v_normals_eye,v_tex_eye,8.0/255,160.0/255,165.0/255,ct1a) ;                        // eyes
  
  colorcube_hands();                                                                                         // hands
  colorcube_ears();                                                                                         // hands
  colorcube_room();                                                                                         // hands


  maketriangle(.5,.3,v_positions_mouth,v_colors_mouth,v_normals_mouth,v_tex_mouth,8.0/255,160.0/255,165.0/255,1);                        // mouth
  cuboid(0.5,.5,1,v_positions_feet,v_colors_feet,v_normals_feet,v_tex_feet,1,0.5,1,1.0);                                             // feet
  maketie(1,3,v_positions_tie,v_colors_tie,v_normals_tie,v_tex_tie,1,0.5,0.5,1.0);                                                   // tie

  //*********************************** Size constants ********************************************************//

  int scp = sizeof ( v_positions_torso1) ;
  int ssp = sizeof ( v_positions_torso2) ; 
  int scc = sizeof ( v_colors_torso1   ) ;
  int ssc = sizeof ( v_colors_torso2   ) ; 
  int sbp = sizeof ( v_positions_lb    ) ;
  int sbc = sizeof ( v_colors_lb       ) ;
  int shc = sizeof ( v_colors_hands    ) ;
  int shp = sizeof ( v_positions_hands ) ;
  int sxc = sizeof ( v_colors_box      ) ;
  int sxp = sizeof ( v_positions_box   ) ;
  int smp = sizeof ( v_positions_mouth ) ;
  int smc = sizeof ( v_colors_mouth    ) ;
  int stp = sizeof ( v_positions_tie   ) ;
  int stc = sizeof ( v_colors_tie      ) ;
  int srp = sizeof ( v_positions_room  ) ;
  int src = sizeof ( v_colors_room     ) ;


  home       = new csX75::HNode(NULL       ,0             , NULL                  , NULL               ,  NULL                , NULL  ,0  ,0  ,0  ,0,texture_absent,0) ; model_vec.push_back(home       ) ;
  boxcentr   = new csX75::HNode(home       ,0             ,v_positions_lb         ,v_colors_lb         , v_normals_lb         , NULL  ,sbp,sbc,sbp,0,texture_absent,0) ; model_vec.push_back(boxcentr   ) ;
  lbox       = new csX75::HNode(boxcentr   ,num_bwl       ,v_positions_lb         ,v_colors_lb         , v_normals_lb         , NULL  ,sbp,sbc,sbp,0,texture_absent,0) ; model_vec.push_back(lbox       ) ;
  ubox       = new csX75::HNode(lbox       ,num_bwl       ,v_positions_ub         ,v_colors_ub         , v_normals_ub         , NULL  ,sbp,sbc,sbp,0,texture_absent,0) ; model_vec.push_back(ubox       ) ;
  torso1     = new csX75::HNode(home       ,num_cylinder  ,v_positions_torso1     ,v_colors_torso1     , v_normals_torso1     , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(torso1     ) ;
  torso2     = new csX75::HNode(torso1     ,num_sphere    ,v_positions_torso2     ,v_colors_torso2     , v_normals_torso2     , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(torso2     ) ;
  torso3     = new csX75::HNode(torso2     ,num_cylinder  ,v_positions_torso3     ,v_colors_torso3     , v_normals_torso3     , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(torso3     ) ;
  torso4     = new csX75::HNode(torso1     ,num_sphere    ,v_positions_torso4     ,v_colors_torso4     , v_normals_torso4     , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(torso4     ) ;
  neckJoint  = new csX75::HNode(torso4     ,num_sphere    ,v_positions_jointBig   ,v_colors_jointBig   , v_normals_jointBig   , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(neckJoint  ) ;
  neck       = new csX75::HNode(neckJoint  ,num_cylinder  ,v_positions_neck       ,v_colors_neck       , v_normals_neck       , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(neck       ) ;
  head       = new csX75::HNode(neck       ,num_sphere    ,v_positions_head       ,v_colors_head       , v_normals_head       , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ;  model_vec.push_back(head       ) ;
  shoulderL  = new csX75::HNode(torso1     ,num_sphere    ,v_positions_jointBig   ,v_colors_jointBig   , v_normals_jointBig   , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(shoulderL  ) ;
  shoulderR  = new csX75::HNode(torso1     ,num_sphere    ,v_positions_jointBig   ,v_colors_jointBig   , v_normals_jointBig   , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(shoulderR  ) ;
  uArmL      = new csX75::HNode(shoulderL  ,num_cylinder  ,v_positions_uarms      ,v_colors_uarms      , v_normals_uarms      , NULL  ,scp,scc,scp,0,texture_absent,0) ;         model_vec.push_back(uArmL      ) ;
  uArmR      = new csX75::HNode(shoulderR  ,num_cylinder  ,v_positions_uarms      ,v_colors_uarms      , v_normals_uarms      , NULL  ,scp,scc,scp,0,texture_absent,0) ;         model_vec.push_back(uArmR      ) ;
  elbowL     = new csX75::HNode(uArmL      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(elbowL     ) ;
  elbowR     = new csX75::HNode(uArmR      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(elbowR     ) ;
  lArmL      = new csX75::HNode(elbowL     ,num_cylinder  ,v_positions_larms      ,v_colors_larms      , v_normals_larms      , NULL  ,scp,scc,scp,0,texture_absent,0) ;         model_vec.push_back(lArmL      ) ;
  lArmR      = new csX75::HNode(elbowR     ,num_cylinder  ,v_positions_larms      ,v_colors_larms      , v_normals_larms      , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(lArmR      ) ;
  hipL       = new csX75::HNode(torso3     ,num_sphere    ,v_positions_jointBig   ,v_colors_jointBig   , v_normals_jointBig   , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(hipL       ) ;
  hipR       = new csX75::HNode(torso3     ,num_sphere    ,v_positions_jointBig   ,v_colors_jointBig   , v_normals_jointBig   , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(hipR       ) ;
  uLegL      = new csX75::HNode(hipL       ,num_cylinder  ,v_positions_ulegs      ,v_colors_ulegs      , v_normals_ulegs      , NULL  ,scp,scc,scp,0,texture_absent,0) ;         model_vec.push_back(uLegL      ) ;
  uLegR      = new csX75::HNode(hipR       ,num_cylinder  ,v_positions_ulegs      ,v_colors_ulegs      , v_normals_ulegs      , NULL  ,scp,scc,scp,0,texture_absent,0) ;     model_vec.push_back(uLegR      ) ;
  kneeL      = new csX75::HNode(uLegL      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(kneeL      ) ;
  kneeR      = new csX75::HNode(uLegR      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(kneeR      ) ;
  lLegL      = new csX75::HNode(kneeL      ,num_cylinder  ,v_positions_llegs      ,v_colors_llegs      , v_normals_llegs      , NULL  ,scp,scc,scp,0,texture_absent,0) ;         model_vec.push_back(lLegL      ) ;
  lLegR      = new csX75::HNode(kneeR      ,num_cylinder  ,v_positions_llegs      ,v_colors_llegs      , v_normals_llegs      , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(lLegR      ) ;
  ankleL     = new csX75::HNode(lLegL      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(ankleL     ) ;
  ankleR     = new csX75::HNode(lLegR      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(ankleR     ) ;
  wristL     = new csX75::HNode(lArmL      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(wristL     ) ;
  wristR     = new csX75::HNode(lArmR      ,num_sphere    ,v_positions_jointSmall ,v_colors_jointSmall , v_normals_jointSmall , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(wristR     ) ;
  handL      = new csX75::HNode(wristL     ,num_vertices  ,v_positions_hands      ,v_colors_hands      , v_normals_hands      , NULL  ,shp,shc,shp,0,texture_absent,0) ;         model_vec.push_back(handL      ) ;
  handR      = new csX75::HNode(wristR     ,num_vertices  ,v_positions_hands      ,v_colors_hands      , v_normals_hands      , NULL  ,shp,shc,shp,0,texture_absent,0) ;         model_vec.push_back(handR      ) ;
  footL      = new csX75::HNode(ankleL     ,num_vertices  ,v_positions_feet       ,v_colors_feet       , v_normals_feet       , NULL  ,shp,shc,shp,0,texture_absent,0) ; model_vec.push_back(footL      ) ;
  footR      = new csX75::HNode(ankleR     ,num_vertices  ,v_positions_feet       ,v_colors_feet       , v_normals_feet       , NULL  ,shp,shc,shp,0,texture_absent,0) ; model_vec.push_back(footR      ) ;
  eyeL       = new csX75::HNode(neck       ,num_sphere    ,v_positions_eye        ,v_colors_eye        , v_normals_eye        , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(eyeL       ) ;
  eyeR       = new csX75::HNode(neck       ,num_sphere    ,v_positions_eye        ,v_colors_eye        , v_normals_eye        , NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(eyeR       ) ;
  mouth      = new csX75::HNode(neck       ,3             ,v_positions_mouth      ,v_colors_mouth      , v_normals_mouth      , NULL  ,smp,smc,smp,0,texture_absent,0) ; model_vec.push_back(mouth      ) ;
  tie        = new csX75::HNode(torso4     ,9             ,v_positions_tie        ,v_colors_tie        , v_normals_tie        , NULL  ,stp,stc,stp,0,texture_absent,0) ; model_vec.push_back(tie        ) ;
  slr        = new csX75::HNode(neck       ,num_cylinder  ,v_positions_lens       ,v_colors_lens       , v_normals_lens       , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(slr        ) ;
  sjoint     = new csX75::HNode(slr        ,num_cylinder  ,v_positions_joint      ,v_colors_joint      , v_normals_joint      , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(sjoint     ) ;
  sll        = new csX75::HNode(sjoint     ,num_cylinder  ,v_positions_lens       ,v_colors_lens       , v_normals_lens       , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(sll        ) ;
  sfl        = new csX75::HNode(sll        ,num_cylinder  ,v_positions_frame      ,v_colors_frame      , v_normals_frame      , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(sfl        ) ;
  sfr        = new csX75::HNode(slr        ,num_cylinder  ,v_positions_frame      ,v_colors_frame      , v_normals_frame      , NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(sfr        ) ;

  //*********************************** Setting initial parameters **********************************************//
  boxcentr   -> change_parameters(bxc) ;
  lbox       -> change_parameters(lbx) ;
  ubox       -> change_parameters(ubx) ;
  torso1     -> change_parameters(t1x) ;
  torso2     -> change_parameters(t2x) ;
  torso3     -> change_parameters(t3x) ;
  torso4     -> change_parameters(t4x) ;
  neckJoint  -> change_parameters(njx) ;
  neckJoint  -> set_rrx() ;
  neckJoint  -> set_rry() ;
  neckJoint  -> set_rrz() ;
  neck       -> change_parameters(nx) ;
  head       -> change_parameters(hdx) ;
  shoulderL  -> change_parameters(slx) ;
  shoulderR  -> change_parameters(srx) ;
  uArmL      -> change_parameters(ualx) ;      
  uArmR      -> change_parameters(uarx) ;      
  elbowL     -> change_parameters(elx) ;
  elbowR     -> change_parameters(erx) ;
  hipL       -> change_parameters(hlx) ;
  hipR       -> change_parameters(hrx) ;
  lArmL      -> change_parameters(lalx) ;      
  lArmR      -> change_parameters(larx) ;      
  uLegL      -> change_parameters(ullx) ;      
  uLegR      -> change_parameters(ulrx) ;    
  kneeL      -> change_parameters(klx) ;
  kneeR      -> change_parameters(krx) ;
  lLegL      -> change_parameters(lllx) ;     
  lLegR      -> change_parameters(llrx) ;
  ankleL     -> change_parameters(alx) ;
  ankleR     -> change_parameters(arx) ;
  wristL     -> change_parameters(wlx) ;
  wristR     -> change_parameters(wrx) ;
  footL      -> change_parameters(footLx) ;
  footR      -> change_parameters(footRx) ;
  shoulderR  -> set_rrz();
  shoulderL  -> set_rrz();
  eyeL       -> change_parameters(eyeLx) ;
  eyeR       -> change_parameters(eyeRx) ;
  mouth      -> change_parameters(mx) ;
  tie        -> change_parameters(tx) ;
  slr        -> change_parameters(0.45, 0.9, 0.9, 90, 0, 180) ;
  sjoint     -> change_parameters(lens_radius, 0.1, 0, 0, 0, -90) ;
  sll        -> change_parameters(0, joint_length + lens_radius, 0, 0, 0, -90) ;
  sfl        -> change_parameters(-1 * lens_radius, .1, 0, 0, 0, -180) ;
  sfr        -> change_parameters(-1 * lens_radius, 0, 0, 0, 0, 0) ;
  

  //*********************************** Making cat geometry **********************************************//

  makecylinder (0, cbe[0],cbe[1],cbe[2], cpos_belly, ccolors_belly,cnormals_belly,ctex_belly, 1,0.5,0.5 , 1.0 ) ;       // belly
  makecylinder (0, cle[0],cle[1],cle[2] , cpos_leg, ccolors_leg,cnormals_leg,ctex_leg, cx,cy,cz, 1.0 ) ;            // legs
  makecylinder (0, ctail1[0],ctail1[1],ctail1[2], cpos_t1 ,ccolors_t1,cnormals_t1,ctex_t1, 0 , 0 , 1 , 1.0 ) ;   // tail1
  makecylinder (0, ctail2[0],ctail2[1],ctail2[2] , cpos_t2, ccolors_t2,cnormals_t2,ctex_t2, 0 , 1, 0 , 1.0 ) ;    // tail2
  makecylinder (0, ctail3[0],ctail3[1],ctail3[2] , cpos_t3,ccolors_t3,cnormals_t3,ctex_t3,  1 , 0 , 0 , 1.0 ) ;   // tail3
  makesphere  (0,cbj, cpos_j, ccolors_j,cnormals_j,ctex_j, cx,cy,cz , 0 );                                      // big joint
  makesphere (0,csj, cpos_j2, ccolors_j2,cnormals_j2,ctex_j2, cx,cy,cz , 0 );                                     // small joint
  makesphere (0,0.2, cpos_ceye, ccolors_ceye,cnormals_ceye,ctex_ceye, 0, 0, 1 , 1.0 );                                // eye
  makeellipse (0,cbe[0],cbe[0]/3,cbe[0],cpos_cbum,ccolors_cbum,cnormals_cbum,ctex_cbum,cx,cy,cz,1.0) ;                // bum
  cuboid(0.2,0.5,0.2,cpos_paw,ccolors_paw,cnormals_paw,ctex_paw,1,0.5,0.5,1.0);                                   // paw
  maketriangle(el,eh,cpos_ears,ccolors_ears,cnormals_ears,ctex_ears,1,0.2,0.1,1.0);                                 // ears
  maketriangle(ml,mh,cpos_mouth,ccolors_mouth,cnormals_mouth,ctex_mouth,1,0.2,0.1,1.0);                               // mouth

  //*********************************** CAT Hierarchy Nodes **********************************************//

  ccentroid  = new csX75::HNode(home       ,0             , NULL      , NULL          , NULL      ,NULL  ,0  ,0  ,0  ,0,texture_absent,0) ; model_vec.push_back(ccentroid);  // belly centroid
  cbelly     = new csX75::HNode(ccentroid  ,num_cylinder  ,cpos_belly ,ccolors_belly  ,cnormals_belly ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(cbelly);  // belly
  cl1j1      = new csX75::HNode(cbelly     ,num_sphere    ,cpos_j     ,ccolors_j      ,cnormals_j     ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl1j1);  // leg1-joint1
  cl2j1      = new csX75::HNode(cbelly     ,num_sphere    ,cpos_j     ,ccolors_j      ,cnormals_j     ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl2j1);  // leg2-joint1
  cl3j1      = new csX75::HNode(cbelly     ,num_sphere    ,cpos_j     ,ccolors_j      ,cnormals_j     ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl3j1);  // leg3-joint1
  cl4j1      = new csX75::HNode(cbelly     ,num_sphere    ,cpos_j     ,ccolors_j      ,cnormals_j     ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl4j1);  // leg4-joint1
  cl1        = new csX75::HNode(cl1j1      ,num_cylinder  ,cpos_leg   ,ccolors_leg    ,cnormals_leg   ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(cl1);  // leg1
  cl2        = new csX75::HNode(cl2j1      ,num_cylinder  ,cpos_leg   ,ccolors_leg    ,cnormals_leg   ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(cl2);  // leg2
  cl3        = new csX75::HNode(cl3j1      ,num_cylinder  ,cpos_leg   ,ccolors_leg    ,cnormals_leg   ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(cl3);  // leg3
  cl4        = new csX75::HNode(cl4j1      ,num_cylinder  ,cpos_leg   ,ccolors_leg    ,cnormals_leg   ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(cl4);  // leg4
  cl1j2      = new csX75::HNode(cl1        ,num_sphere    ,cpos_j2    ,ccolors_j2     ,cnormals_j2    ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl1j2);  // leg1-joint2
  cl2j2      = new csX75::HNode(cl2        ,num_sphere    ,cpos_j2    ,ccolors_j2     ,cnormals_j2    ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl2j2);  // leg2-joint2
  cl3j2      = new csX75::HNode(cl3        ,num_sphere    ,cpos_j2    ,ccolors_j2     ,cnormals_j2    ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl3j2);  // leg3-joint2
  cl4j2      = new csX75::HNode(cl4        ,num_sphere    ,cpos_j2    ,ccolors_j2     ,cnormals_j2    ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cl4j2);  // leg4-joint2
  ct1j1      = new csX75::HNode(cbelly     ,num_sphere    ,cpos_j2    ,ccolors_j2     ,cnormals_j2    ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(ct1j1);  // tail-joint1
  ct1        = new csX75::HNode(ct1j1      ,num_cylinder  ,cpos_t1    ,ccolors_t1     ,cnormals_t1    ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(ct1);  // tail1
  ct1j2      = new csX75::HNode(ct1        ,num_sphere    ,cpos_j2    ,ccolors_j2     ,cnormals_j2    ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(ct1j2);  // tail-joint2
  ct2        = new csX75::HNode(ct1j2      ,num_cylinder  ,cpos_t2    ,ccolors_t2     ,cnormals_t2    ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(ct2);  // tail2
  ct1j3      = new csX75::HNode(ct2        ,num_sphere    ,cpos_j2    ,ccolors_j2     ,cnormals_j2    ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(ct1j3);  // tail-joint3
  ct3        = new csX75::HNode(ct1j3      ,num_cylinder  ,cpos_t3    ,ccolors_t3     ,cnormals_t3    ,NULL  ,scp,scc,scp,0,texture_absent,0) ; model_vec.push_back(ct3);  // tail3
  cbum       = new csX75::HNode(cbelly     ,num_sphere    ,cpos_cbum  ,ccolors_cbum   ,cnormals_cbum  ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cbum);  // bum
  chd        = new csX75::HNode(cbelly     ,num_sphere    ,cpos_cbum  ,ccolors_cbum   ,cnormals_cbum  ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(chd);  // head
  cleye      = new csX75::HNode(chd        ,num_sphere    ,cpos_ceye  ,ccolors_ceye   ,cnormals_ceye  ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(cleye);  // left eye
  creye      = new csX75::HNode(chd        ,num_sphere    ,cpos_ceye  ,ccolors_ceye   ,cnormals_ceye  ,NULL  ,ssp,ssc,ssp,0,texture_absent,0) ; model_vec.push_back(creye);  // right eye
  cpaw1      = new csX75::HNode(cl1j2      ,num_vertices  ,cpos_paw   ,ccolors_paw    ,cnormals_paw   ,NULL  ,shp,shc,shp,0,texture_absent,0) ; model_vec.push_back(cpaw1);  // paw1
  cpaw2      = new csX75::HNode(cl2j2      ,num_vertices  ,cpos_paw   ,ccolors_paw    ,cnormals_paw   ,NULL  ,shp,shc,shp,0,texture_absent,0) ; model_vec.push_back(cpaw2);  // paw2
  cpaw3      = new csX75::HNode(cl3j2      ,num_vertices  ,cpos_paw   ,ccolors_paw    ,cnormals_paw   ,NULL  ,shp,shc,shp,0,texture_absent,0) ; model_vec.push_back(cpaw3);  // paw3
  cpaw4      = new csX75::HNode(cl4j2      ,num_vertices  ,cpos_paw   ,ccolors_paw    ,cnormals_paw   ,NULL  ,shp,shc,shp,0,texture_absent,0) ; model_vec.push_back(cpaw4);  // paw4
  cmouth     = new csX75::HNode(chd        ,3             ,cpos_mouth ,ccolors_mouth  ,cnormals_mouth ,NULL  ,smp,smc,smp,0,texture_absent,0) ; model_vec.push_back(cmouth);  // mouth
  cearL      = new csX75::HNode(chd        ,num_vertices  ,v_positions_ears  ,v_colors_ears , v_normals_ears, NULL   ,sizeof(v_positions_ears),sizeof(v_colors_ears),sizeof(v_normals_ears),0,texture_absent,0) ; model_vec.push_back(cearL); // left ear
  cearR      = new csX75::HNode(chd        ,num_vertices  ,v_positions_ears  ,v_colors_ears , v_normals_ears,NULL   ,sizeof(v_positions_ears),sizeof(v_colors_ears),sizeof(v_normals_ears),0,texture_absent,0) ; model_vec.push_back(cearR); // right ear

  //*********************************** Setting initial parameters **********************************************//

  ccentroid ->change_parameters(centroid) ; 
  cbelly ->change_parameters(cbellyx) ; 
  cl1j1  ->change_parameters(cl1j1x ) ; 
  cl1j1  ->set_rrx();
  cl1j1  ->set_rry();
  cl1j1  ->set_rrz();
  cl2j1  ->change_parameters(cl2j1x ) ; 
  cl2j1  ->set_rrx();
  cl2j1  ->set_rry();
  cl2j1  ->set_rrz();
  cl3j1  ->change_parameters(cl3j1x ) ;
  cl3j1  ->set_rrx();
  cl3j1  ->set_rry();
  cl3j1  ->set_rrz();
  cl4j1  ->change_parameters(cl4j1x ) ;
  cl4j1  ->set_rrx();
  cl4j1  ->set_rry();
  cl4j1  ->set_rrz();
  cl1    ->change_parameters(cl1x  ) ;
  cl2    ->change_parameters(cl2x  ) ;
  cl3    ->change_parameters(cl3x  ) ;
  cl4    ->change_parameters(cl4x  ) ;
  cl1j2  ->change_parameters(cl1j2x) ;
  cl1j2  ->set_rrx();
  cl1j2  ->set_rry();
  cl1j2  ->set_rrz();
  cl2j2  ->change_parameters(cl2j2x) ;
  cl2j2  ->set_rrx();
  cl2j2  ->set_rry();
  cl2j2  ->set_rrz();
  cl3j2  ->change_parameters(cl3j2x) ;
  cl3j2  ->set_rrx();
  cl3j2  ->set_rry();
  cl3j2  ->set_rrz();
  cl4j2  ->change_parameters(cl4j2x) ;
  ct1j1  ->change_parameters(ct1j1x) ;        
  ct1    ->change_parameters(ct1x  ) ;
  ct1j2  ->change_parameters(ct1j2x) ;
  ct2    ->change_parameters(ct2x  ) ;
  ct1j3  ->change_parameters(ct1j2x) ;
  ct3    ->change_parameters(ct3x  ) ;
  cbum   ->change_parameters(cbumx ) ;
  cpaw1  ->change_parameters(cpaw1x) ;
  cpaw2  ->change_parameters(cpaw2x) ;
  cpaw3  ->change_parameters(cpaw3x) ;
  cpaw4  ->change_parameters(cpaw4x) ;
  cleye  ->change_parameters(cleyex) ;
  creye  ->change_parameters(creyex) ;
  cearR  ->change_parameters(-1.0,0.0,-0.33,0,-10,-90);
  cearL  ->change_parameters(-1.0,0,0.33,0,10,-90);
  cmouth ->change_parameters(0.2,-0.7,0,-90,-180,90);


  //*********************************** Making room and furniture geometry **********************************************//

  // cupboard
  cuboidwithoutlid(dcb[0],dcb[1],dcb[2],v_positions_cupboard,v_colors_cupboard ,v_normals_cupboard, v_tex_cupboard,ccb[0] ,ccb[1] ,ccb[2] ,ccb [3]);                      //lid
  cuboid(dcbl[0],dcbl[1],dcbl[2],v_positions_cupboard_door,v_colors_cupboard_door,v_normals_cupboard_door,v_tex_cupboard_door,ccbl[0],ccbl[1],ccbl[2],ccbl[3]);                      //lid

  //bed
  cuboid(db[0],db[1],db[2],v_positions_bed,v_colors_bed,v_normals_bed,v_tex_bed,cb[0],cb[1],cb[2],cb[3]);                      //bed
  cuboid(dbl1[0],dbl1[1],dbl1[2],v_positions_bed_leg1,v_colors_bed_leg1,v_normals_bed_leg1,v_tex_bed_leg1,cbl1[0],cbl1[1],cbl1[2],cbl1[3]);                      //lid
  cuboid(dbl2[0],dbl2[1],dbl2[2],v_positions_bed_leg2,v_colors_bed_leg2,v_normals_bed_leg2,v_tex_bed_leg2,cbl2[0],cbl2[1],cbl2[2],cbl2[3]);                      //lid

  // table
  makecylinder (1,dtableTop[0],dtableTop[1],dtableTop[2],v_positions_tableTop,v_colors_tableTop,v_normals_tableTop,v_tex_tableTop,ctableTop[0],ctableTop[1],ctableTop[2],ctableTop[3]) ;             // table
  makecylinder (1,dtableL[0],dtableL[1],dtableL[2],v_positions_tableL,v_colors_tableL,v_normals_tableL,v_tex_tableL,ctableL[0],ctableL[1],ctableL[2],ctableL[3]) ;    
  makesphere   (0,0.3,v_positions_table, v_colors_table,v_normals_table,v_tex_table,1,0.2,0.3,1.0)  ;  

  // of chair
  cuboid(dchair[0],dchair[1],dchair[2],v_positions_chair,v_colors_chair,v_normals_chair,v_tex_chair,cchair[0],cchair[1],cchair[2],cchair[3]);                                          
  cuboid(dchairr[0],dchairr[1],dchairr[2],v_positions_chair_rest,v_colors_chair_rest,v_normals_chair_rest,v_tex_chair_rest,cchair[0],cchair[1],cchair[2],cchair[3]);                                           
  makecylinder (0,dchairl[0],dchairl[1],dchairl[2],v_positions_chair_leg,v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,cchairl[0],cchairl[1],cchairl[2],cchairl[3]) ;    

  //door
  cuboid(ddoor[0],ddoor[1],ddoor[2],v_positions_door,v_colors_door,v_normals_door,v_tex_door,cdoor[0],cdoor[1],cdoor[2],cdoor[3]);                      //bed
  makesphere (0,1.5,v_positions_door_knob, v_colors_door_knob,v_normals_door_knob,v_tex_door_knob,1,0.2,0.3,1.0)  ;  
  makesphere (0,4,v_positions_control_point, v_colors_control_point,v_normals_control_point,v_tex_control_point,1,0.2,0.3,1.0)  ;  

  makecylinder (0,dlamp[0],dlamp[1],dlamp[2],v_positions_lamp,v_colors_lamp,v_normals_lamp,v_tex_lamp,clamp[0],clamp[1],clamp[2],clamp[3]) ;    
  makecylinder (0,dlamp_base[0],dlamp_base[1],dlamp_base[2],v_positions_lamp_base,v_colors_lamp_base,v_normals_lamp_base,v_tex_lamp_base,clamp_base[0],clamp_base[1],clamp_base[2],clamp_base[3]) ;    


  room     = new csX75::HNode( NULL  ,num_room,v_positions_room ,v_colors_room,v_normals_room,v_tex_room, srp,src,srp,sizeof(v_tex_room),texture_present,tex_room) ; model_vec.push_back(room) ;  // belly

  table    = new csX75::HNode( NULL ,num_sphere,v_positions_table  ,v_colors_table,v_normals_table,v_tex_table ,ssp,ssc,sizeof(v_normals_table),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(table) ;    // table top
  tableTop = new csX75::HNode(table ,num_cylinder,v_positions_tableTop  ,v_colors_tableTop,v_normals_tableTop,v_tex_tableTop ,scp,scc, sizeof(v_normals_tableTop),sizeof(v_tex_tableL),texture_present, tex_wood) ; model_vec.push_back(tableTop) ;    // table top
  tableL1  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL1) ;  // table legs
  tableL2  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL2) ;  // table legs
  tableL3  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL3) ;  // table legs
  tableL4  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL4) ;  // table legs
  tableL5  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL5) ;  // table legs
  tableL6  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL6) ;  // table legs
  tableL7  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL7) ;  // table legs
  tableL8  = new csX75::HNode(table ,num_cylinder,v_positions_tableL ,v_colors_tableL,v_normals_tableL,v_tex_tableL,scp,scc,sizeof(v_normals_tableL),sizeof(v_tex_tableL),texture_present,tex_wood) ; model_vec.push_back(tableL8) ;  // table legs

  chair1  = new csX75::HNode(NULL, num_vertices, v_positions_chair, v_colors_chair,v_normals_chair,v_tex_chair, shp, shc,sizeof(v_normals_chair),0,texture_absent,0) ; model_vec.push_back(chair1) ;

  chair1L1  = new csX75::HNode(chair1, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair1L1) ;
  chair1L2  = new csX75::HNode(chair1, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair1L2) ;
  chair1L3  = new csX75::HNode(chair1, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair1L3) ;
  chair1L4  = new csX75::HNode(chair1, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair1L4) ;
 
  chair1A1  = new csX75::HNode(chair1, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair1A1) ;
  chair1A2  = new csX75::HNode(chair1, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair1A2) ;

  chair1R  = new csX75::HNode(chair1A1, num_vertices, v_positions_chair_rest, v_colors_chair_rest,v_normals_chair_rest,v_tex_chair_rest,shp,shc,sizeof(v_normals_chair_rest),0,texture_absent,0)  ; model_vec.push_back(chair1R) ;
                                                                                                                
  chair2  = new csX75::HNode(NULL, num_vertices, v_positions_chair, v_colors_chair,v_normals_chair,v_tex_chair, shp, shc,sizeof(v_normals_chair),0,texture_absent,0) ; model_vec.push_back(chair2) ;            
  chair2L1  = new csX75::HNode(chair2, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair2L1) ;  
  chair2L2  = new csX75::HNode(chair2, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair2L2) ;  
  chair2L3  = new csX75::HNode(chair2, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair2L3) ;  
  chair2L4  = new csX75::HNode(chair2, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair2L4) ;  
  chair2A1  = new csX75::HNode(chair2, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair2A1) ;
  chair2A2  = new csX75::HNode(chair2, num_cylinder, v_positions_chair_leg, v_colors_chair_leg,v_normals_chair_leg,v_tex_chair_leg,scp,scc,sizeof(v_normals_chair_leg),0,texture_absent,0) ; model_vec.push_back(chair2A2) ;
  chair2R  = new csX75::HNode(chair2A1, num_vertices, v_positions_chair_rest, v_colors_chair_rest,v_normals_chair_rest,v_tex_chair_rest,shp,shc,sizeof(v_normals_chair_rest),0,texture_absent,0) ; model_vec.push_back(chair2R) ;

  cupboard      = new csX75::HNode(NULL, num_bwl, v_positions_cupboard, v_colors_cupboard,v_normals_cupboard,v_tex_cupboard,sbp,sbc,sizeof(v_normals_cupboard),0,texture_absent,0) ; model_vec.push_back(cupboard) ;
  cupboard_door  = new csX75::HNode(cupboard, num_vertices, v_positions_cupboard_door, v_colors_cupboard_door,v_normals_cupboard_door,v_tex_cupboard_door, shp,shc,sizeof(v_normals_cupboard_door),0,texture_absent,0) ; model_vec.push_back(cupboard_door) ;

  bed  = new csX75::HNode(NULL, num_vertices, v_positions_bed, v_colors_bed,v_normals_bed,v_tex_bed,shp,shc,sizeof(v_normals_bed),sizeof(v_tex_bed),texture_present,tex_bed) ; model_vec.push_back(bed) ;
  bedLeg1  = new csX75::HNode(bed, num_vertices, v_positions_bed_leg1, v_colors_bed_leg1,v_normals_bed_leg1,v_tex_bed_leg1, shp,shc,sizeof(v_normals_bed_leg1),0,texture_absent,0) ; model_vec.push_back(bedLeg1) ;
  bedLeg2  = new csX75::HNode(bed, num_vertices, v_positions_bed_leg2, v_colors_bed_leg2,v_normals_bed_leg2,v_tex_bed_leg2, shp,shc,sizeof(v_normals_bed_leg2),0,texture_absent,0) ; model_vec.push_back(bedLeg2) ;

  door  = new csX75::HNode(room, num_vertices, v_positions_door, v_colors_door,v_normals_door,v_tex_door, shp,shc,sizeof(v_normals_door),0,texture_absent,0) ; model_vec.push_back(door) ;
  doorKnob  = new csX75::HNode(door, num_sphere, v_positions_door_knob, v_colors_door_knob,v_normals_door_knob,v_tex_door_knob, ssp,ssc,sizeof(v_normals_door_knob),0,texture_absent,0) ; model_vec.push_back(doorKnob) ;

  lamp_base    = new csX75::HNode( NULL ,num_cylinder,v_positions_lamp_base  ,v_colors_lamp_base,v_normals_lamp_base,v_tex_lamp_base ,scp,scc,sizeof(v_normals_lamp_base),0,texture_absent,0) ; model_vec.push_back(lamp_base) ;    // lamp_base top
  lamp    = new csX75::HNode( lamp_base ,num_cylinder,v_positions_lamp  ,v_colors_lamp,v_normals_lamp,v_tex_lamp ,scp,scc,sizeof(v_normals_lamp),0,texture_absent,0) ; model_vec.push_back(lamp) ;    // lamp top


  //*********************************** Setting initial parameters *********************************************//
  tableTop-> change_parameters(ptableTop) ;
  tableL1 -> change_parameters(ptableL1) ;
  tableL2 -> change_parameters(ptableL2) ;
  tableL3 -> change_parameters(ptableL3) ;
  tableL4 -> change_parameters(ptableL4) ;
  tableL5 -> change_parameters(ptableL5) ;
  tableL6 -> change_parameters(ptableL6) ;
  tableL7 -> change_parameters(ptableL7) ;
  tableL8 -> change_parameters(ptableL8) ;
  
  room -> change_parameters(proom) ;

  // chair
  table->change_parameters(0,-5,0,0,0,0) ;
  chair1->change_parameters(15,0,15,0,45,0) ;
  chair2->change_parameters(-15,0,15,0,-45,0) ;


  chair1L1 -> change_parameters(pchairL1) ;
  chair1L2 -> change_parameters(pchairL2) ;
  chair1L3 -> change_parameters(pchairL3) ;
  chair1L4 -> change_parameters(pchairL4) ;
  chair1A1 -> change_parameters(pchairA1) ;
  chair1A2 -> change_parameters(pchairA2) ;
  chair1R  -> change_parameters(pchairR)  ;
  chair2L1 -> change_parameters(pchairL1) ;
  chair2L2 -> change_parameters(pchairL2) ;
  chair2L3 -> change_parameters(pchairL3) ;
  chair2L4 -> change_parameters(pchairL4) ;
  chair2A1 -> change_parameters(pchairA1) ;
  chair2A2 -> change_parameters(pchairA2) ;
  chair2R  -> change_parameters(pchairR)  ;

  cupboard  -> change_parameters(pcb)  ;
  cupboard_door  -> change_parameters(pcbl)  ;

  bed  -> change_parameters(pb)  ;
  bedLeg1  -> change_parameters(pbl1)  ;
  bedLeg2  -> change_parameters(pbl2)  ;

  door -> change_parameters(pd)  ;
  doorKnob  -> change_parameters(pdk)  ;

  lamp->change_parameters(plamp);
  lamp_base->change_parameters(plamp_base) ;

  // cupboard

  root_node = curr_node = cbelly;

}

void drawCP(){
  for (int i=0;i<controlPoints_HN.size();i++){
    controlPoints_HN[i] = new csX75::HNode(NULL, num_sphere, v_positions_control_point, v_colors_control_point,v_normals_control_point,v_tex_control_point,sizeof(v_positions_control_point),sizeof(v_colors_control_point),sizeof(v_normals_control_point),0,texture_absent,0);
  }
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0,10.0,0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    // projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.01,500.0);
  else
    projection_matrix = glm::ortho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

  view_matrix = projection_matrix*lookat_matrix;

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  matrixStack.push_back(view_matrix);

  if(LIGHT1 > 0)
    glUniform1f(SWITCH1, 1.0);
  else
    glUniform1f(SWITCH1, 0.0);
  if(LIGHT2 > 0)
    glUniform1f(SWITCH2, 1.0);
  else
    glUniform1f(SWITCH2, 0.0);

  room->render_tree();
  table->render_tree() ; 
  chair1->render_tree() ; 
  chair2->render_tree() ; 
  cupboard->render_tree() ; 
  boxcentr->render_tree() ; 
  torso1->render_tree() ; 
  ccentroid->render_tree() ; 
  lamp_base->render_tree() ; 

  for (int i=0;i<controlPoints_HN.size();i++) controlPoints_HN[i]->render() ;
  bed->render_tree() ; 
 //home->render_tree();
}

void save_frame_to_image_file(int frame_id) {

    unsigned int width = 512 ;
    unsigned int height = 512 ;
    unsigned int color_max = 255 ;
    unsigned int pixel_nbytes = 4 ;
    glReadBuffer(GL_BACK) ;
    GLubyte * pixels = new unsigned char [4 * (width+1) * (height + 1) ]; 

    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    size_t i, j, k, cur;
    enum Constants { max_filename = 4096 };
    char filename[max_filename];
    snprintf(filename, max_filename, "%s%d.ppm", "output/frame_", frame_id);
    FILE *f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cur = pixel_nbytes * ((height - i - 1) * width + j);
            fprintf(f, "%3d %3d %3d ", pixels[cur], pixels[cur + 1], pixels[cur + 2]);
        }
        fprintf(f, "\n");
    }
    fclose(f);



}


int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "The Music Box", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  int frame_num = 0 , donecam = 0, ft = 1  ; 
  time_t time1, time2 ; 
  // Loop until the user closes the window

  std::vector<double> v1(3) ; v1[0] = 20 ; v1[1] = 20 ; v1[2] = 20 ; 
  std::vector<double> v2(3) ; v2[0] = 10 ; v2[1] = 11 ; v2[2] = 13 ; 
  std::vector<double> v3(3) ; v3[0] = 15 ; v3[1] = 10 ; v3[2] = 10 ; 
  std::vector<double> v4(3) ; v4[0] = 10 ; v4[1] = 10 ; v4[2] = -10 ; 
  controlPoints.push_back(v4) ; 
  controlPoints.push_back(v3) ; 
  controlPoints.push_back(v2) ; 
  controlPoints.push_back(v1) ; 
  // controlPoints.push_back(vs) ; 

  // std::cerr << "Drawing control points\n" ;
  drawCP() ; 

  // for (int i=0;i<controlPoints.size();i++) std::cerr << controlPoints[i][0]<< controlPoints[i][1]<< controlPoints[i][2]<<"\n" ;

  get_camera_positions() ;
// 
  // std::cerr << "Got camera positions " << cameraPositions.size() << "\n" ;

  while (glfwWindowShouldClose(window) == 0)
    {
      // std::cerr << shouldAnimateObjects<<" "<<frame_num<<" " <<donecam<<" "<<allframes.size()<<"\n";
      if (ft && shouldAnimateCamera) {time1 = glfwGetTime() ; ft = 0 ; std::cerr<<"Animating camera\n" ;}

      if (shouldAnimateCamera && frame_num < cameraPositions.size() && !donecam && glfwGetTime()>frame_num*fps - time1){
          c_xpos = cameraPositions[frame_num][0] ;
          c_ypos = cameraPositions[frame_num][1] ;
          c_zpos = cameraPositions[frame_num][2] ;
          std::cerr<<cameraPositions.size() ; 
          frame_num++ ; 
      }

      // switch to 
      if (frame_num == cameraPositions.size()){shouldAnimateCamera = 0 ; donecam = 1; frame_num = 0 ; time2 = glfwGetTime() ;}
      if (shouldAnimateObjects && !shouldAnimateCamera) {donecam = 1;  time2 = glfwGetTime() ;}
      if (donecam && shouldAnimateObjects && frame_num < allframes.size() && glfwGetTime()>frame_num*fps - time2){
        // std::cerr << "Doing animation \n" ;
        for (int j=0;j<allframes[frame_num].size();j++){
          model_vec[j] -> change_parameters(allframes[frame_num][j]);
        }
        frame_num++ ; 
      }
      
      if (donecam && shouldAnimateCamera && frame_num == allframes.size()) { donecam = 0 ; shouldAnimateObjects = 0 ;  shouldAnimateCamera = 0 ; frame_num = 0 ; ft = 1 ; } 

      if (shouldAnimateCamera || shouldAnimateObjects || donecam)
        save_frame_to_image_file(frame_num);

      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------
