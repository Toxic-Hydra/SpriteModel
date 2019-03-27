#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

int main()
{
	std::cout << "Program started" << std::endl;
	sf::RenderWindow window(sf::VideoMode(640, 480), "SpriteModel");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);
	sf::Texture model;
	model.loadFromFile("images/knight.png");
	
	sf::IntRect rectangle(0, 0, 20, 21);
	sf::Sprite modelSprite(model, rectangle);
	float rotation = 0.0f;
	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	
	char imageFile[255] = "images/knight.png";
	int layers = 14;
	int layerWidth = 20;
	int LayerHeight = 21;
	float scale = 5.0f;

	sf::Clock deltaClock;
	while (window.isOpen()) {
		if (rotation >= 360.0f) rotation = 0.0f;
		if (rotation <= -360.0f) rotation = 0.0f;
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					rotation = rotation - 10.0f;
					
					std::cout << "Rotate - 10: "<< rotation << std::endl;
					break;
				case sf::Keyboard::Right:
					rotation = rotation + 10.0f;
					std::cout << "Rotate + 10: "<< rotation << std::endl;
					break;
				}
			}
		}
	

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Model Settings"); 

		if (ImGui::ColorEdit3("Background color", color)) {

			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);

		}

		
		ImGui::InputInt("Width", &layerWidth);
		ImGui::InputInt("Length", &LayerHeight);
		ImGui::InputInt("Layers", &layers);
		ImGui::SliderFloat("Scale", &scale, 0.0f, 20.0f);

		ImGui::InputText("Image File", imageFile, 255);

		if (ImGui::Button("Update Image File")) {
			
			model.loadFromFile(imageFile);
		}
		ImGui::End(); 

		window.clear(bgColor); 
		
		
		for (int i = 0; i < layers; i++) {
	
		sf::IntRect rectangle(layerWidth * i, 0, layerWidth, LayerHeight);
		sf::Sprite modelSprite(model, rectangle);
		modelSprite.setOrigin(layerWidth/2, LayerHeight/2);
		modelSprite.scale(scale, scale);
		modelSprite.setPosition((640 / 2), (480 / 2)-(i*scale));
		modelSprite.rotate(rotation);
		window.draw(modelSprite);

		}
		
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}