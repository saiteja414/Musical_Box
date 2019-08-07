#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz;
		bool rrx,rry,rrz;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;
		std::size_t tex_buffer_size;
		std::size_t normal_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo,tex;

		glm::mat3 normal_matrix;

		
		glm::vec2 tex_p;
		glm::mat4 rotation;
		glm::mat4 translation;
		
		std::vector<HNode*> children;
		HNode* parent;


		void update_matrices();

	  public:
		HNode(HNode*, GLuint, glm::vec4*,  glm::vec4*,  glm::vec4*, glm::vec2*, std::size_t, std::size_t, std::size_t, std::size_t,glm::vec2 , GLuint);
		//actualHNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec2* a_texCoord, std::size_t v_size, std::size_t c_size, std::size_t t_size, GLuint texture)
		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void change_parameters(double v[] );
		void change_parameters(GLfloat * );
		void change_parameters(std::vector<double> a);
		void render_tree();
		void inc_rx(int);
		void inc_ry(int);
		void inc_rz(int);
		void dec_rx(int);
		void dec_ry(int);
		void dec_rz(int);
		void set_rrx();
		void set_rry();
		void set_rrz();
		double get_tx(){return tx;} 
		double get_ty(){return ty;} 
		double get_tz(){return tz;} 
		double get_rx(){return rx;} 
		double get_ry(){return ry;} 
		double get_rz(){return rz;} 
		std::vector <double> get_parameters() ; //{return std::vector(tx,ty,tz,rx,ry,rz) ;} 
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif