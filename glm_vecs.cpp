#include "model.hpp"

const int num_cylinder = 2*3*360 + 6*360;

const int num_sphere = 180 * 360 * 6;
const int num_bwl = 5 * 6;
const int num_vertices = 36 ;

//for box
glm::vec4 v_positions_lb[num_bwl];
glm::vec4 v_colors_lb[num_bwl];


glm::vec4 v_positions_ub[num_bwl];
glm::vec4 v_colors_ub[num_bwl];

// for arms and legs
glm::vec4 v_positions_uarms[num_cylinder];
glm::vec4 v_positions_larms[num_cylinder];
glm::vec4 v_colors_uarms[num_cylinder];
glm::vec4 v_colors_larms[num_cylinder];
glm::vec4 v_positions_hands[num_cylinder];
glm::vec4 v_colors_hands[num_cylinder];
// for torso
glm::vec4 v_positions_torso1[num_cylinder];
glm::vec4 v_colors_torso1   [num_cylinder];
glm::vec4 v_positions_torso2[num_sphere];
glm::vec4 v_colors_torso2   [num_sphere];
glm::vec4 v_positions_torso3[num_cylinder];
glm::vec4 v_colors_torso3   [num_cylinder];

// for legs
glm::vec4 v_positions_ulegs  [num_cylinder];
glm::vec4 v_colors_ulegs     [num_cylinder];
glm::vec4 v_positions_llegs  [num_cylinder];
glm::vec4 v_colors_llegs     [num_cylinder];

// for neck
glm::vec4 v_positions_neck  [num_cylinder];
glm::vec4 v_colors_neck     [num_cylinder];

// for joints
glm::vec4 v_positions_jointSmall[num_sphere];
glm::vec4 v_colors_jointSmall   [num_sphere];

glm::vec4 v_positions_jointBig[num_sphere];
glm::vec4 v_colors_jointBig[num_sphere];

//for head

glm::vec4 v_positions_head[num_sphere];
glm::vec4 v_colors_head   [num_sphere];


///for tie
glm::vec4 v_positions_tie[9];
glm::vec4 v_colors_tie   [9];

// for hands
// glm::vec4 v_colors_hands[num_vertices] ; 
// glm::vec4 v_positions_hands[num_vertices] ; 

// for feet
glm::vec4 v_colors_feet[num_vertices] ; 
glm::vec4 v_positions_feet[num_vertices] ; 

// for CAT
glm::vec4 ccolors_belly[num_cylinder];
glm::vec4 ccolors_j[num_sphere]   ;
glm::vec4 ccolors_leg[num_cylinder]  ;
glm::vec4 ccolors_paw[num_vertices]  ;
glm::vec4 ccolors_t1[num_cylinder]  ;
glm::vec4 ccolors_j2[num_sphere] ;
glm::vec4 ccolors_t2[num_cylinder] ;
glm::vec4 ccolors_chd[num_sphere] ;
glm::vec4 ccolors_ceye[num_sphere];

glm::vec4 cpos_belly[num_cylinder];
glm::vec4 cpos_j[num_sphere]   ;
glm::vec4 cpos_leg[num_cylinder]  ;
glm::vec4 cpos_paw[num_vertices]  ;
glm::vec4 cpos_t1[num_cylinder]  ;
glm::vec4 cpos_j2[num_sphere] ;
glm::vec4 cpos_t2[num_cylinder] ;
glm::vec4 cpos_chd[num_sphere] ;
glm::vec4 cpos_ceye[num_sphere];

glm::vec4 v_positions_lens[num_cylinder];
glm::vec4 v_colors_lens[num_cylinder];

glm::vec4 v_positions_joint[num_cylinder];
glm::vec4 v_colors_joint[num_cylinder];

glm::vec4 v_positions_frame[num_cylinder];
glm::vec4 v_colors_frame[num_cylinder];


glm::vec4 positions_cylinder[num_cylinder];
glm::vec4 colors_cylinder[num_cylinder];
glm::vec4 positions_sphere[num_sphere];
glm::vec4 colors_sphere[num_sphere];


glm::vec4 positions_hands[8] = {
  /////// arms 
  glm::vec4(  -0.2,  0.0,  0.2, 1.0),
  glm::vec4(  0.2,   0.0,  0.2, 1.0),
  glm::vec4(  0.05,   -0.5,  0.2, 1.0),
  glm::vec4(  -0.05,  -0.5,  0.2, 1.0),
  glm::vec4(  -0.05,  -0.5, -0.2, 1.0),
  glm::vec4(  0.05,   -0.5, -0.2, 1.0),
  glm::vec4(  0.2,   0.0, -0.2, 1.0),
  glm::vec4(  -0.2,  0.0, -0.2, 1.0) 
};
  /////// torso 
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

//RGBA colors
glm::vec4 colors_hands[8] = {
  /////// arms and legs 0-7
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
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
