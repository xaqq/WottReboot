#include "Triangle.hpp"
#include "Translation.hpp"
#include "Scale.hpp"
#include "Rotation.hpp"

Triangle::Triangle()
{
}

void Triangle::init(Window *win)
{
	_fs = new SimpleFragmentShader();
	_vs = new SimpleVertexShader();
	_program = new Program();
	_win = win;
	_geometry.add(glm::vec3(-1.0f, -1.0f, 0.0f));
	_geometry.add(glm::vec3(1.0f, -1.0f, 0.0f));
	_geometry.add(glm::vec3(0.0f, 1.0f, 0.0f));
}

void Triangle::load()
{
	_fs->compile();
	_vs->compile();
	_program->attach(*_fs);
	_program->attach(*_vs);
	_program->link();
	_va = new VertexAttrib(*_program, "vertexPosition_modelspace");
	_vao.bind();
	_vbo.bind();
	_vbo.data(_geometry.getVectorBufferData());
	_va->enable();
	_va->pointer(_geometry.getVectorBufferData());
	_va->disable();
	_vbo.unbind();
	_vao.unbind();
	setScale(0.1, 0.1, 0.1);
}

void Triangle::update()
{
	rotate(0, 0, 0.9);
	translate(0.01, 0, 0);
	applyTransformations();
	_vao.bind();
	_vbo.bind();
	_vbo.data(_geometry.getVectorBufferData());
	_vbo.unbind();
	_vao.unbind();
}

void Triangle::draw()
{
	_program->useProgram();
	_vao.bind();
	_va->enable();
	VertexArray::drawArrays(VertexArray::LINE_LOOP, 3);
	_va->disable();
	_vao.unbind();
	_program->stopUseProgram();
}

void Triangle::unload()
{
}

I3DObject &Triangle::applyMatrix(const I3DMatrix &matrix)
{
	_geometry.applyMatrix(matrix);
	return *this;
}

Triangle::~Triangle()
{
	delete _va;
	delete _vs;
	delete _fs;
	delete _program;
}