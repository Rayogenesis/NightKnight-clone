#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderCtrl.h"

#include "Shader.h"


void ShaderCtrl::init()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	vShader.free();
	fShader.free();
}

void ShaderCtrl::render()
{
	glm::mat4 modelview;
	texProgram.use();	
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
}

ShaderProgram& ShaderCtrl::getTexProgram()
{
	return texProgram;
}

void ShaderCtrl::setTranslateModelview()
{
	glm::mat4 modelview = glm::mat4(1.0f);
	modelview = glm::translate(modelview, TRANSLATE);
	texProgram.setUniformMatrix4f("modelview", modelview);
}