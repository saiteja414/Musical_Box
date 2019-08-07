/*
  A program which opens a window and draws three Arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the Arms move.

  Use the keys 1,2 and 3 to switch between Arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"
/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 50 ; 
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=true;
//Shader program attribs
GLuint vPosition,vColor,texCoord,tex_present,vNormal,normalMatrix,viewMatrix,SWITCH1,SWITCH2;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

std::vector < csX75::HNode *  > model_vec  ;  


csX75::HNode* home; 			//model_vec.push_back(&home);			
	
csX75::HNode* boxcentr; 		//model_vec.push_back(&boxcentr);		
csX75::HNode* lbox; 			//model_vec.push_back(&lbox);			
csX75::HNode* ubox; 			//model_vec.push_back(&ubox);			
	
csX75::HNode* root_node; 		//model_vec.push_back(&root_node);	
csX75::HNode* curr_node; 		//model_vec.push_back(&curr_node);	
csX75::HNode* torso1; 			//model_vec.push_back(&torso1);		
csX75::HNode* torso2; 			//model_vec.push_back(&torso2);		
csX75::HNode* torso3; 			//model_vec.push_back(&torso3);		
csX75::HNode* torso4; 			//model_vec.push_back(&torso4);
csX75::HNode* shoulderL; 		//model_vec.push_back(&shoulderL);
csX75::HNode* shoulderR; 		//model_vec.push_back(&shoulderR);
csX75::HNode* wristL; 			//model_vec.push_back(&wristL);
csX75::HNode* wristR; 			//model_vec.push_back(&wristR);
csX75::HNode* hipL; 			//model_vec.push_back(&hipL);

csX75::HNode* hipR; 			//model_vec.push_back(&hipR);

csX75::HNode* handL; 			//model_vec.push_back(&handL);
csX75::HNode* handR; 			//model_vec.push_back(&handR);
csX75::HNode* elbowL; 			//model_vec.push_back(&elbowL);
csX75::HNode* elbowR; 			//model_vec.push_back(&elbowR);

csX75::HNode* kneeL; 			//model_vec.push_back(&kneeL);
csX75::HNode* kneeR; 			//model_vec.push_back(&kneeR);

csX75::HNode* ankleL; 			//model_vec.push_back(&ankleL);
csX75::HNode* ankleR; 			//model_vec.push_back(&ankleR);

csX75::HNode* uArmL; 			//model_vec.push_back(&uArmL);
csX75::HNode* lArmL; 			//model_vec.push_back(&lArmL);
csX75::HNode* uArmR; 			//model_vec.push_back(&uArmR);
csX75::HNode* lArmR; 			//model_vec.push_back(&lArmR);
csX75::HNode* uLegR; 			//model_vec.push_back(&uLegR);
csX75::HNode* lLegR; 			//model_vec.push_back(&lLegR);
csX75::HNode* uLegL; 			//model_vec.push_back(&uLegL);
csX75::HNode* lLegL; 			//model_vec.push_back(&lLegL);
csX75::HNode* neck; 			//model_vec.push_back(&neck);
csX75::HNode* neckJoint; 		//model_vec.push_back(&neckJoint);
csX75::HNode* head; 			//model_vec.push_back(&head);
csX75::HNode* eyeL; 			//model_vec.push_back(&eyeL);
csX75::HNode* eyeR; 			//model_vec.push_back(&eyeR);
csX75::HNode* mouth; 			//model_vec.push_back(&mouth);

csX75::HNode* footL; 			//model_vec.push_back(&footL);
csX75::HNode* footR; 			//model_vec.push_back(&footR);

csX75::HNode* cbelly; 			//model_vec.push_back(&cbelly);
csX75::HNode* cl1j1; 			//model_vec.push_back(&cl1j1);
csX75::HNode* cl2j1; 			//model_vec.push_back(&cl2j1);
csX75::HNode* cl3j1; 			//model_vec.push_back(&cl3j1);
csX75::HNode* cl4j1; 			//model_vec.push_back(&cl4j1);
csX75::HNode* cl1; 				//model_vec.push_back(&cl1);
csX75::HNode* cl2; 				//model_vec.push_back(&cl2);
csX75::HNode* cl3; 				//model_vec.push_back(&cl3);
csX75::HNode* cl4; 				//model_vec.push_back(&cl4);
csX75::HNode* cl1j2; 			//model_vec.push_back(&cl1j2);
csX75::HNode* cl2j2; 			//model_vec.push_back(&cl2j2);
csX75::HNode* cl3j2; 			//model_vec.push_back(&cl3j2);
csX75::HNode* cl4j2; 			//model_vec.push_back(&cl4j2);
csX75::HNode* cpaw1; 			//model_vec.push_back(&cpaw1);
csX75::HNode* cpaw2; 			//model_vec.push_back(&cpaw2);
csX75::HNode* cpaw3; 			//model_vec.push_back(&cpaw3);
csX75::HNode* cpaw4; 			//model_vec.push_back(&cpaw4);
csX75::HNode* ct1j1; 			//model_vec.push_back(&ct1j1);
csX75::HNode* ct1; 				//model_vec.push_back(&ct1);
csX75::HNode* ct1j2; 			//model_vec.push_back(&ct1j2);
csX75::HNode* ct2; 				//model_vec.push_back(&ct2);
csX75::HNode* ct1j3; 			//model_vec.push_back(&ct1j3);
csX75::HNode* ct3; 				//model_vec.push_back(&ct3);
csX75::HNode* chdj; 			//model_vec.push_back(&chdj);
csX75::HNode* chd; 				//model_vec.push_back(&chd);
csX75::HNode* cbum; 			//model_vec.push_back(&cbum);
csX75::HNode* cleye; 			//model_vec.push_back(&cleye);
csX75::HNode* creye; 			//model_vec.push_back(&creye);
csX75::HNode* cearR; 			//model_vec.push_back(&cearR);
csX75::HNode* cearL; 			//model_vec.push_back(&cearL);
csX75::HNode* ccentroid; 		//model_vec.push_back(&ccentroid);
csX75::HNode* cmouth; 			//model_vec.push_back(&cmouth);
csX75::HNode* tie; 				//model_vec.push_back(&tie);

csX75::HNode* slr; 				//model_vec.push_back(&slr);
csX75::HNode* sll; 				//model_vec.push_back(&sll);
csX75::HNode* sjoint; 			//model_vec.push_back(&sjoint);
csX75::HNode* sfl; 				//model_vec.push_back(&sfl);
csX75::HNode* sfr; 				//model_vec.push_back(&sfr);

csX75::HNode* room; 			//model_vec.push_back(&room); 

csX75::HNode* table; 			//model_vec.push_back(&table); 
csX75::HNode* tableTop; 		//model_vec.push_back(&tableTop); 
csX75::HNode* tableL1; 			//model_vec.push_back(&tableL1); 
csX75::HNode* tableL2; 			//model_vec.push_back(&tableL2); 
csX75::HNode* tableL3; 			//model_vec.push_back(&tableL3); 
csX75::HNode* tableL4; 			//model_vec.push_back(&tableL4); 
csX75::HNode* tableL5; 			//model_vec.push_back(&tableL5); 
csX75::HNode* tableL6; 			//model_vec.push_back(&tableL6); 
csX75::HNode* tableL7; 			//model_vec.push_back(&tableL7); 
csX75::HNode* tableL8; 			//model_vec.push_back(&tableL8);

csX75::HNode* chair1; 			//model_vec.push_back(&chair1); 
csX75::HNode* chair1L1; 		//model_vec.push_back(&chair1L1); 
csX75::HNode* chair1L2; 		//model_vec.push_back(&chair1L2); 
csX75::HNode* chair1L3; 		//model_vec.push_back(&chair1L3); 
csX75::HNode* chair1L4; 		//model_vec.push_back(&chair1L4); 
csX75::HNode* chair1A1; 		//model_vec.push_back(&chair1A1); 
csX75::HNode* chair1A2; 		//model_vec.push_back(&chair1A2); 
csX75::HNode* chair1R; 			//model_vec.push_back(&chair1R); 

csX75::HNode* chair2; 			//model_vec.push_back(&chair2); 
csX75::HNode* chair2L1; 		//model_vec.push_back(&chair2L1); 
csX75::HNode* chair2L2; 		//model_vec.push_back(&chair2L2); 
csX75::HNode* chair2L3; 		//model_vec.push_back(&chair2L3); 
csX75::HNode* chair2L4; 		//model_vec.push_back(&chair2L4); 
csX75::HNode* chair2A1; 		//model_vec.push_back(&chair2A1); 
csX75::HNode* chair2A2; 		//model_vec.push_back(&chair2A2); 
csX75::HNode* chair2R; 			//model_vec.push_back(&chair2R); 


csX75::HNode* cupboard; 		//model_vec.push_back(&cupboard); 
csX75::HNode* cupboard_door; 	//model_vec.push_back(&cupboard_door); 
csX75::HNode* cupboard_knob; 	//model_vec.push_back(&cupboard_knob); 

csX75::HNode* bed; 				//model_vec.push_back(&bed); 
csX75::HNode* bedLeg1; 			//model_vec.push_back(&bedLeg1); 
csX75::HNode* bedLeg2; 			//model_vec.push_back(&bedLeg2); 

csX75::HNode* door; 			//model_vec.push_back(&door); 
csX75::HNode* doorKnob; 		//model_vec.push_back(&doorKnob); 

csX75::HNode * lamp ; 
csX75::HNode * lamp_base ; 

std::vector <std::vector <double> > prevFrame  ; 
std::vector <std::vector < std::vector <double> > > keyframes,allframes ; 
std::vector <int> keylight1,keylight2,alllight1,alllight2 ; 
std::vector <std::vector <double> > controlPoints,cameraPositions  ; 
std::vector <double> ncr ; 

int LIGHT1 = 1 ; 
int LIGHT2 = 0 ; 
int save_mode = 0 ; 
int NUM_NODES = 111 ; 
int NUM_FRAMES = 24 ; 
int NUM_LIGHTS = 2 ; 
double fps = 1.0/24 ; 
double TIME_INTERVAL = 0.005 ; 
int shouldAnimateCamera = 0 ;
int shouldAnimateObjects = 0 ;
std::vector<csX75::HNode*> controlPoints_HN ; 

void save_frame_to_image_file(int) ; 

int DRAWING_MODE = 0 ; 
//-------------------------------------------------------------------------



// void openFile();
// std::string get_string_from_vec(std::vector <double> v );
// int are_not_equal(std::vector<double> &v1, std::vector<double> &v2) ;
// // getting frame from string ; 
// std::vector<double> get_frame_from_string(std::string &s);
// std::vector<double> get_frame_average(std::vector <double> &v1, std::vector<double> &v2, int n);
// // interpolating keyframes to get the frames of the animation
// void interpolate_frames();
// // get keyframes from the keyframes.txt file and interpolate them 
// void get_all_frames();
// // to save Frae to keyframes.txt
// void saveFrame() ;
// std::vector<double> get_bezier_point(int t);
// void get_camera_positions();

#endif
