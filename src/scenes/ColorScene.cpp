#include "ColorScene.h"
#include "MenuScene.h"
ColorScene::ColorScene(std::shared_ptr<SceneData> data)
	:_data(data)
{
}

void ColorScene::render()
{
	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ColorScene::imGuiRender()
{

	ImGui::ColorEdit3("Clear Color", backgroundColor);
}
