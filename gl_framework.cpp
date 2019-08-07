#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern GLfloat c_xpos,c_ypos,c_zpos;
extern int LIGHT1, LIGHT2;
extern bool enable_perspective;
extern csX75::HNode* torso1,* cbelly, * home, *uarmR, *larmR, *uarmL, *larmL, *lbox, *ubox, *curr_node;
extern std::vector <std::vector <double> > controlPoints ; 
extern int DRAWING_MODE ;
extern int shouldAnimateCamera ;
extern int shouldAnimateObjects ;
////
extern csX75::HNode* torso1;
extern csX75::HNode* torso2;
extern csX75::HNode* torso3;
extern csX75::HNode* shoulderL;
extern csX75::HNode* shoulderR;
extern csX75::HNode* wristL;
extern csX75::HNode* wristR;
extern csX75::HNode* hipL;

extern csX75::HNode* hipR;

extern csX75::HNode* handL;
extern csX75::HNode* handR;
extern csX75::HNode* elbowL;
extern csX75::HNode* elbowR;

extern csX75::HNode* kneeL;
extern csX75::HNode* kneeR;

extern csX75::HNode* ankleL;
extern csX75::HNode* ankleR;
extern csX75::HNode* neckJoint ;
extern csX75::HNode* head ;


extern csX75::HNode * cbelly;
extern csX75::HNode * cl1j1 ;
extern csX75::HNode * cl2j1 ;
extern csX75::HNode * cl3j1 ;
extern csX75::HNode * cl4j1 ;
extern csX75::HNode * cl1   ;
extern csX75::HNode * cl2   ;
extern csX75::HNode * cl3   ;
extern csX75::HNode * cl4   ;
extern csX75::HNode * cl1j2 ;
extern csX75::HNode * cl2j2 ;
extern csX75::HNode * cl3j2 ;
extern csX75::HNode * cl4j2 ;
extern csX75::HNode * cpaw1 ;
extern csX75::HNode * cpaw2 ;
extern csX75::HNode * cpaw3 ;
extern csX75::HNode * cpaw4 ;
extern csX75::HNode * ct1j1 ;
extern csX75::HNode * ct1   ;
extern csX75::HNode * ct1j2 ;
extern csX75::HNode * ct2   ;
extern csX75::HNode * ct1j3 ;
extern csX75::HNode * ct3   ;
extern csX75::HNode * chdj  ;
extern csX75::HNode * chd   ;
extern csX75::HNode * cbum   ;
extern csX75::HNode * cleye;
extern csX75::HNode * creye ;
extern csX75::HNode * cearR ;
extern csX75::HNode * cearL ;
extern csX75::HNode * cmouth ;
extern csX75::HNode * ccentroid;
extern csX75::HNode* boxcentr;

extern void saveFrame() ; 
extern void get_all_frames() ;
////
bool lid_open = false;
bool cam_rot = false;
int curr_mode = 1;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // enable blending
    glEnable(GL_BLEND) ;
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA) ;

  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    ypos=512-ypos;
    ypos = (unsigned int) std::min(512 - 1,(int)ypos);


    if (DRAWING_MODE && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
      // if ( action == GLFW_PRESS )
        // {
          // push back the point in the vector
          std::vector<double> p(3) ;
          p[0] = c_xpos;
          p[1] = c_ypos;
          p[2] = c_zpos; 

          std::cout << "Added point to control points list\n" ;
          controlPoints.push_back(p);
        // }
      }
  }


  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS){
     LIGHT1 = !LIGHT1;
    }
    else if (key == GLFW_KEY_X && action == GLFW_PRESS){
     LIGHT2 = !LIGHT2; 
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS){
      std::cout<<"Entering/Leaving drawing mode\n" ;
     DRAWING_MODE = 1 - DRAWING_MODE; 
    }
   else if (key == GLFW_KEY_1 && action == GLFW_PRESS){
     curr_node = home;
     curr_mode = 1;
   }
   else if (key == GLFW_KEY_0 && action == GLFW_PRESS){
     curr_node = home;
     curr_mode = 0; 
   }
   else if (key == GLFW_KEY_2 && action == GLFW_PRESS){
     curr_node = torso1;
     curr_mode = 2;
   }
   else if (key == GLFW_KEY_3 && action == GLFW_PRESS){
     curr_node = ccentroid;
     curr_mode = 3;
   }
   else if (key == GLFW_KEY_4 && action == GLFW_PRESS){
     curr_node = boxcentr;
     curr_mode = 4;
   }
   else if (key == GLFW_KEY_5 && action == GLFW_PRESS){
     saveFrame() ;
   }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS){
     get_all_frames() ;
   }

   else if (key == GLFW_KEY_7 && action == GLFW_PRESS){
      shouldAnimateCamera = 1 ;
   }

    else if (key == GLFW_KEY_8 && action == GLFW_PRESS){
      std::cerr << "Animation mode enabled\n" ;
      shouldAnimateObjects = 1 ;
   }


   else if (key == GLFW_KEY_O && action == GLFW_PRESS && !lid_open){
      ubox->dec_rx(90);
      lid_open = true;
   }
   else if (key == GLFW_KEY_O && action == GLFW_PRESS && lid_open){
      ubox->inc_rx(90);
      lid_open = false;
   }

   else if(curr_mode == 0){
      if (key == GLFW_KEY_R  && action == GLFW_PRESS)
        cam_rot = true;
      else if (key == GLFW_KEY_T  && action == GLFW_PRESS)
        cam_rot = false;
      else if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS && cam_rot)
        c_yrot -= 10.0;
      else if (key == GLFW_KEY_RIGHT  && action == GLFW_PRESS  && cam_rot)
        c_yrot += 10.0;
      else if (key == GLFW_KEY_UP  && action == GLFW_PRESS  && cam_rot)
        c_xrot -= 10.0;
      else if (key == GLFW_KEY_DOWN  && action == GLFW_PRESS  && cam_rot)
        c_xrot += 10.0;        
      else if (key == GLFW_KEY_PAGE_UP  && action == GLFW_PRESS  && cam_rot)
        c_zrot -= 10.0;
      else if (key == GLFW_KEY_PAGE_DOWN  && action == GLFW_PRESS  && cam_rot)
        c_zrot += 10.0;
      else if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS)
        c_ypos -= 2.0;
      else if (key == GLFW_KEY_RIGHT  && action == GLFW_PRESS)
        c_ypos += 2.0;
      else if (key == GLFW_KEY_UP  && action == GLFW_PRESS)
        c_xpos -= 2.0;
      else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        c_xpos += 2.0;        
      else if (key == GLFW_KEY_PAGE_UP  && action == GLFW_PRESS)
        c_zpos -= 2.0;
      else if (key == GLFW_KEY_PAGE_DOWN  && action == GLFW_PRESS)
        c_zpos += 2.0;
      }

   else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && curr_node != elbowR && curr_node != elbowL && curr_node != kneeR && curr_node != kneeL )
      curr_node->dec_ry(10);
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && curr_node != elbowR && curr_node != elbowL && curr_node != kneeR && curr_node != kneeL)
      curr_node->inc_ry(10);
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      curr_node->dec_rx(10);
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      curr_node->inc_rx(10);
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && curr_node != elbowR && curr_node != elbowL && curr_node != kneeR && curr_node != kneeL)
      curr_node->dec_rz(10);
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && curr_node != elbowR && curr_node != elbowL && curr_node != kneeR && curr_node != kneeL)
      curr_node->inc_rz(10);
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;
  //for camera
   

   /// for human
   else if(curr_mode == 2){
     // if (key == GLFW_KEY_H && action == GLFW_PRESS)
     //   curr_node = head;
     if (key == GLFW_KEY_N && action == GLFW_PRESS)
       curr_node = neckJoint;
     else if (key == GLFW_KEY_T && action == GLFW_PRESS)
       curr_node = torso1;
     
     else if (key == GLFW_KEY_S && action == GLFW_PRESS && curr_node == shoulderL)
       curr_node = shoulderR;
     else if (key == GLFW_KEY_S && action == GLFW_PRESS && curr_node == shoulderR)
       curr_node = shoulderL;
     else if (key == GLFW_KEY_S && action == GLFW_PRESS)
       curr_node = shoulderR;
                
     else if (key == GLFW_KEY_E && action == GLFW_PRESS && curr_node == elbowL)
       curr_node = elbowR;
     else if (key == GLFW_KEY_E && action == GLFW_PRESS && curr_node == elbowR)
       curr_node = elbowL;
     else if (key == GLFW_KEY_E && action == GLFW_PRESS)
       curr_node = elbowR;

     else if (key == GLFW_KEY_W && action == GLFW_PRESS && curr_node == wristL)
       curr_node = wristR;
     else if (key == GLFW_KEY_W && action == GLFW_PRESS && curr_node == wristR)
       curr_node = wristL;
     else if (key == GLFW_KEY_W && action == GLFW_PRESS)
       curr_node = wristR;

     else if (key == GLFW_KEY_K && action == GLFW_PRESS && curr_node == kneeR)
       curr_node = kneeL;
     else if (key == GLFW_KEY_K && action == GLFW_PRESS && curr_node == kneeL)
       curr_node = kneeR;
     else if (key == GLFW_KEY_K && action == GLFW_PRESS)
       curr_node = kneeL;

     else if (key == GLFW_KEY_A && action == GLFW_PRESS && curr_node == ankleR)
       curr_node = ankleL;
     else if (key == GLFW_KEY_A && action == GLFW_PRESS && curr_node == ankleL)
       curr_node = ankleR;
     else if (key == GLFW_KEY_A && action == GLFW_PRESS)
       curr_node = ankleR;

     else if (key == GLFW_KEY_H && action == GLFW_PRESS && curr_node == hipR)
       curr_node = hipL;
     else if (key == GLFW_KEY_H && action == GLFW_PRESS && curr_node == hipL)
       curr_node = hipR;
     else if (key == GLFW_KEY_H && action == GLFW_PRESS)
       curr_node = hipL;

     else if (key == GLFW_KEY_R && action == GLFW_PRESS)
       curr_node = torso2;
     else if (key == GLFW_KEY_U && action == GLFW_PRESS)
       curr_node = torso3;
 }
 /// for cat
  else if (curr_mode == 3){
     if (key == GLFW_KEY_T && action == GLFW_PRESS && curr_node == ct1j3)
       curr_node = ct1j1;
     else if (key == GLFW_KEY_T && action == GLFW_PRESS && curr_node == ct1j1)
       curr_node = ct1j2;
     else if (key == GLFW_KEY_T && action == GLFW_PRESS && curr_node == ct1j2)
       curr_node = ct1j3;
     else if (key == GLFW_KEY_T && action == GLFW_PRESS)
       curr_node = ct1j1;

     else if (key == GLFW_KEY_L && action == GLFW_PRESS && curr_node == cl4j1)
       curr_node = cl1j1;
     else if (key == GLFW_KEY_L && action == GLFW_PRESS && curr_node == cl1j1)
       curr_node = cl2j1;
     else if (key == GLFW_KEY_L && action == GLFW_PRESS && curr_node == cl2j1)
       curr_node = cl3j1;
     else if (key == GLFW_KEY_L && action == GLFW_PRESS && curr_node == cl3j1)
       curr_node = cl4j1;
     else if (key == GLFW_KEY_L && action == GLFW_PRESS)
       curr_node = cl1j1;
     
     else if (key == GLFW_KEY_F && action == GLFW_PRESS && curr_node == cl4j2)
       curr_node = cl1j2;
     else if (key == GLFW_KEY_F && action == GLFW_PRESS && curr_node == cl1j2)
       curr_node = cl2j2;
     else if (key == GLFW_KEY_F && action == GLFW_PRESS && curr_node == cl2j2)
       curr_node = cl3j2;
     else if (key == GLFW_KEY_F && action == GLFW_PRESS && curr_node == cl3j2)
       curr_node = cl4j2;
     else if (key == GLFW_KEY_F && action == GLFW_PRESS)
       curr_node = cl1j2;
   }
    /// camera mode
       
  }
};  
  


