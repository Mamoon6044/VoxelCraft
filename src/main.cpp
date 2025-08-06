#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include<chrono>
#include "Camera.h"
#include "LightSource.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"
#include "GUIRenderer.h"
#include "RawModel.h"
#include "Loader.h"
#include "MousePicker.h"
#include "Entity.h"
#include "TexturedModel.h"
#include "ModelTexture.h"
#include "GUITexture.h"
#include "Chunk.hpp"
#include "ChunkMeshBuilder.hpp"
#include "OBJLoader.h"

int main() {

    DisplayManager myWindow;
    myWindow.createDisplay();

    Loader loader;
	OBJLoader objLoader;
    StaticShader shader;
    MasterRenderer renderer(shader);
	GUIRenderer guiRenderer(loader);
	std::vector<Entity>entities;
	std::vector<GUITexture> GUIs;
	std::unordered_map<std::pair<int,int>, Chunk, pair_hash> chunks;

	for (int cx = 0; cx < 5; ++cx) {
    	for (int cz = 0; cz < 5; ++cz) {

			auto result = chunks.emplace(std::pair<int, int>(cx,cz), Chunk(cx,cz));
			Chunk& chunk = result.first->second;

			MeshData mesh = ChunkMeshBuilder::generateChunkMesh(chunk);

			RawModel rawModel = loader.loadToVAO(
								mesh.vertices.data(),
								mesh.vertices.size() * sizeof(float),

								mesh.texCoords.data(),
								mesh.texCoords.size() * sizeof(float),

								mesh.normals.data(),
								mesh.normals.size() * sizeof(float),

								mesh.indices.data(),
								mesh.indices.size() * sizeof(unsigned int) );

			ModelTexture texture = loader.loadTexture("textures");
			TexturedModel texturedModel(rawModel, texture);

			entities.emplace_back(texturedModel, glm::vec3((cx) * 16, 0, (cz) * 16), 0, 0, 0, 1);
    	}
	}
	float xf, yf, zf = 0;

	float inhandCube_vertices[] = {
		xf,     yf + 1, zf,
        xf,     yf + 1, zf + 1,
        xf + 1, yf + 1, zf + 1,
	    xf + 1, yf + 1, zf,

		xf,     yf, zf + 1,
        xf,     yf, zf,
        xf + 1, yf, zf,
        xf + 1, yf, zf + 1,

		xf + 1, yf + 1, zf,
        xf + 1, yf,     zf,
        xf,     yf,     zf,
        xf,     yf + 1, zf,

		xf,     yf + 1, zf + 1,
        xf,     yf,     zf + 1,
        xf + 1, yf,     zf + 1,
        xf + 1, yf + 1, zf + 1,

		xf, yf + 1, zf,
        xf, yf,     zf,
        xf, yf,     zf + 1,
        xf, yf + 1, zf + 1,

		xf + 1, yf + 1, zf + 1,
        xf + 1, yf,     zf + 1,
        xf + 1, yf,     zf,
        xf + 1, yf + 1, zf
	};
	float inhandCube_texCoords[] = {
		0,1,
		0,0.5,
		0.5,0.5,
		0.5,1,

		0.5,0.5,
		0.5,0,
		1,0,
		1,0.5,

		0,0.5,
		0,0,
		0.5,0,
		0.5,0.5,

		0,0.5,
		0,0,
		0.5,0,
		0.5,0.5,

		0,0.5,
		0,0,
		0.5,0,
		0.5,0.5,

		0,0.5,
		0,0,
		0.5,0,
		0.5,0.5
	};
	float inhandCube_normals[] = {
		0,1,0,
		0,-1,0,
		0,0,-1,
		0,0,1,
		-1,0,0,
		1,0,0
	};
	unsigned int inhandCube_indices[] = {
		0,1,2,
		0,2,3,
		4,5,6,
		4,6,7,
		8,9,10,
		8,10,11,
		12,13,14,
		12,14,15,
		16,17,18,
		16,18,19,
		20,21,22,
		20,22,23
	};
	
	for (int i=0; i<10; ++i) {
		GUITexture GUI(loader.loadTexture("heart_container"), glm::vec2(-0.9+((float)i/20),-0.8), glm::vec2(0.025,0.035));
		GUIs.push_back(GUI);
	}
	GUIs.emplace_back(loader.loadTexture("hotbar"), glm::vec2(0,-0.8), glm::vec2(0.42,0.08));


	GUITexture air(loader.loadTexture("air"), glm::vec2(-0.37,-0.795), glm::vec2(0.045,0.075));
	GUITexture iso_stone(loader.loadTexture("iso_stone"), glm::vec2(-0.37,-0.795), glm::vec2(0.045,0.075));
	GUITexture iso_bedrock(loader.loadTexture("iso_bedrock"), glm::vec2(-0.37,-0.795), glm::vec2(0.045,0.075));
	GUITexture iso_oak_log(loader.loadTexture("iso_oak_log"), glm::vec2(-0.37,-0.795), glm::vec2(0.045,0.075));
	GUITexture iso_grass(loader.loadTexture("iso_grass"), glm::vec2(-0.37,-0.795), glm::vec2(0.045,0.075));
	GUITexture iso_dirt(loader.loadTexture("iso_dirt"), glm::vec2(-0.37,-0.795), glm::vec2(0.045,0.075));


	GUIs.emplace_back(loader.loadTexture("hotbar_selection"), glm::vec2(-0.37,-0.795), glm::vec2(0.05,0.08));
	GUITexture& hotbar_selection = GUIs.back();

	ModelTexture steveTexture = loader.loadTexture("steve");
	
	RawModel headRawModel = objLoader.loadObjModel("head", loader);
	//std::cout<<headRawModel.getVAOId()<<","<<headRawModel.getvertexCount()<<std::endl;
	TexturedModel headModel(headRawModel, steveTexture);
	entities.emplace_back(headModel, glm::vec3(7.5, 40, 3.5), 0, 0, 0, 1);
	Entity& head = entities.back();

	RawModel bodyRawmodel = objLoader.loadObjModel("body", loader);
	//std::cout<<bodyRawmodel.getVAOId()<<","<<bodyRawmodel.getvertexCount()<<std::endl;
	TexturedModel bodyModel(bodyRawmodel, steveTexture);
	entities.emplace_back(bodyModel, glm::vec3(7.5, 40, 3.5), 0, 0, 0, 1);
	Entity& body = entities.back();

	Player player(head, body, loader);

	player.addInventory(air, 1, 0);player.addInventory(iso_bedrock, 1, 1);player.addInventory(iso_dirt, 1, 2);player.addInventory(iso_oak_log, 1, 3);
	player.addInventory(iso_grass, 1, 4);player.addInventory(air, 1, 5);player.addInventory(iso_dirt, 1, 6);player.addInventory(iso_bedrock, 1, 7);
	player.addInventory(iso_grass, 1, 8);

	RawModel inhandrawModel = loader.loadToVAO(inhandCube_vertices, sizeof(inhandCube_vertices), inhandCube_texCoords,
	sizeof(inhandCube_texCoords), inhandCube_normals, sizeof(inhandCube_normals),  inhandCube_indices, sizeof(inhandCube_indices));
	ModelTexture inhandtex = loader.loadTexture("grassAtlas");
	TexturedModel inhandTexturedModel(inhandrawModel, inhandtex);

	entities.emplace_back(inhandTexturedModel, glm::vec3(7, 17, 3), 0,0,0,0.5);

	LightSource light(glm::vec3(48, 11, 52), glm::vec3(1,1,1));
	Camera camera(myWindow.getWindow(), player, chunks, myWindow, hotbar_selection);
	MousePicker picker(camera, myWindow.getWindow(), myWindow, renderer.getProjectionMatrix());

	for(Entity& entity : entities) {

		renderer.processEntity(entity);
	}

	double last = glfwGetTime();

    while(!myWindow.shouldClose()) {
		double current = glfwGetTime();

		if(current - last >= 1.0/60.0) {
			last = current;

			camera.getChunk();

			if(player.getHealth()!= 0){
				camera.move();
				int slot = camera.getInvSlotNo();
			}else{
				GUIs.emplace_back(loader.loadTexture("You_Died"), glm::vec2(0, 0), glm::vec2(1,1));
			}

			picker.update();
			std::cout<<picker.getCurrentRay().x<<","<<picker.getCurrentRay().y<<","<<picker.getCurrentRay().z<<std::endl;

			renderer.render(camera);
			guiRenderer.render(GUIs, player.getHearts(), player.getInventory());

			myWindow.updateDisplay();
		}
    }

	guiRenderer.cleanUp();
    shader.cleanUp();
	loader.cleanUp();
    myWindow.closeDisplay();
    return 0;
}