#include "MenuScene.h"
#include "ModelScene.h"
#include "ColorScene.h"
#include "PyramidInterpolationScene.h"
#include "CameraScene.h"
#include "TextureScene.h"
#include "AmbientLightScene.h"
#include "CircleScene.h"
#include "DiffuseLightScene.h"
#include "SpecularLightScene.h"
#include "SphereScene.h"
#include "PointLightScene.h"
#include "SpotLightScene.h"
#include "ShaderCircleScene.h"

MenuScene::MenuScene(std::shared_ptr<SceneData> data)
	:_data(data)
{
}

void MenuScene::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MenuScene::imGuiRender()
{
	if (ImGui::Button("Background Color"))
	{
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<ColorScene>(_data)), false);
	}

	if (ImGui::Button("Circle"))
	{
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<CircleScene>(_data)), false);
	}

	if (ImGui::Button("Shader Circle"))
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<ShaderCircleScene>(_data)), false);
	}

	if (ImGui::Button("Pyramid Interpolation"))
	{
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<PyramidInterpolationScene>(_data)), false);
	}
	
	if (ImGui::Button("Camera"))
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<CameraScene>(_data)), false);
	}
	
	if (ImGui::Button("Texture"))
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<TextureScene>(_data)), false);
	}
	
	if (ImGui::Button("Ambient Light"))
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<AmbientLightScene>(_data)), false);
	}

	if (ImGui::Button("Diffuse Light"))
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<DiffuseLightScene>(_data)), false);
	}	
	
	if (ImGui::Button("Specular Light"))
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<SpecularLightScene>(_data)), false);
	}	
	
	if (ImGui::Button("Sphere")) 
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<SphereScene>(_data)), false);
	}	
	
	if (ImGui::Button("Point Light")) 
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<PointLightScene>(_data)), false);
	}

	if (ImGui::Button("Spot Light")) 
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<SpotLightScene>(_data)), false);
	}

	if (ImGui::Button("Model"))
	{
		_data->window.reset();
		_data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<ModelScene>(_data)), false);
	}

}
