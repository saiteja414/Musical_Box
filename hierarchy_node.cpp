#include "hierarchy_node.hpp"

#include <iostream>

extern GLuint vPosition,vColor,uModelViewMatrix,texCoord,tex_present,normalMatrix,vNormal;

extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_normals, glm::vec2* a_texCoord, std::size_t v_size, std::size_t c_size, std::size_t n_size, std::size_t t_size,glm::vec2 tex_needed, GLuint texture){
		
		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		tex_buffer_size = t_size;
		normal_buffer_size = n_size;
		tex = texture;
		// initialize vao and vbo of the object;
		tex_p = tex_needed;

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + normal_buffer_size + tex_buffer_size + sizeof(tex_needed)*num_vertices , NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, normal_buffer_size, a_normals );
		if(tex_needed[0] == 1){
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + normal_buffer_size, tex_buffer_size, a_texCoord );
		// std::cout<<"entered"<<std::endl;
		for (int i = 0; i < num_v; ++i)
		{
			glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + normal_buffer_size + tex_buffer_size + sizeof(tex_needed)*i, sizeof(tex_needed), &tex_needed );
		}
		}
		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size));
		
		if(tex_needed[0] == 1){
		// std::cout<<"entered"<<std::endl;
		glEnableVertexAttribArray( texCoord );
		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size + normal_buffer_size));
		glEnableVertexAttribArray( tex_present );
		glVertexAttribPointer( tex_present, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size + normal_buffer_size + tex_buffer_size));
		}

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::change_parameters(double v[]){
		tx = v[0];
		ty = v[1];
		tz = v[2];
		rx = v[3];
		ry = v[4];
		rz = v[5];

		update_matrices();
	}

	void HNode::change_parameters(GLfloat *  v){
		tx = v[0];
		ty = v[1];
		tz = v[2];
		rx = v[3];
		ry = v[4];
		rz = v[5];

		update_matrices();
	}



	void HNode::change_parameters(std::vector<double> v){
		tx = v[0];
		ty = v[1];
		tz = v[2];
		rx = v[3];
		ry = v[4];
		rz = v[5];

		update_matrices();
	}


	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);
		normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));
		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glBindVertexArray (vao);
		if(tex_p[0] > .5){
		glBindTexture(GL_TEXTURE_2D, tex);
		}
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(int v){
		if((rrx && rx+v >= -90 && rx+v <= 90) || (!rrx && rx+v >= -180 && rx+v <= 180)) 
		rx+=v;
		update_matrices();
	}


	void HNode::inc_ry(int v){
		if((rry && ry+v >= -90 && ry+v <= 90) || (!rry && ry+v >= -180 && ry+v <= 180)) 
		ry+=v;
		update_matrices();
	}

	void HNode::inc_rz(int v){
		if((rrz && rz+v >= -90 && rz+v <= 90) || (!rrz && rz+v >= -180 && rz+v <= 180)) 
		rz+=v;
		update_matrices();
	}

	void HNode::dec_rx(int v){
		if((rrx && rx-v >= -90 && rx-v <= 90) || (!rrx && rx-v >= -180 && rx-v <= 180)) 
		rx-=v;
		update_matrices();
	}

	void HNode::dec_ry(int v){
		if((rry && ry-v >= -90 && ry-v <= 90) || (!rry && ry-v >= -180 && ry-v <= 180) )
		ry-=v;
		update_matrices();
	}

	void HNode::dec_rz(int v){
		if((rrz && rz-v >= -90 && rz-v <= 90) || (!rrz && rz-v >= -180 && rz-v <= 180)) 
		rz-=v;
		update_matrices();
	}

	void HNode::set_rrx(){
		rrx = true;
	}

	void HNode::set_rry(){
		rry = true;
	}

	void HNode::set_rrz(){
		rrz = true;
	}

	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

	std::vector<double> HNode::get_parameters(){
		std::vector<double> out(6) ;
		out[0] = tx ;
		out[1] = ty ; 
		out[2] = tz ; 
		out[3] = rx ;
		out[4] = ry ;
		out[5] = rz ;
		return out ; 
	}
}