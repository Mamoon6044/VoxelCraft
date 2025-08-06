#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "DisplayManager.h"
#include "Player.h"
#include "GUITexture.h"
#include "Chunk.hpp"

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

class Camera{

    public:

        Camera(GLFWwindow* window, Player& player, std::unordered_map<std::pair<int,int>, 
            Chunk, pair_hash>& chunks, DisplayManager& display, GUITexture& hotbar_selection);

        void move();
        void motion(float cameraPosX, float cameraPosY, float cameraPosZ);

        int getInvSlotNo();

        void getChunk();

        glm::vec3 getPosition();
        float getPitch();
        float getYaw();

    private:

        float speed;
        float currentVertSpeed = 0;
        float gravity;
        bool isInAir = false;
        int initial_height = 0;
        int final_height = 0;
        int slot = 0;

        bool lastLeft = false;
        bool lastRight = false;

        int normalize(float number);
        int normalizepos(float number);

        Player& player;
        Entity& head;
        Entity& body;
        GUITexture& hotbar_selection;

        DisplayManager& display;
        Chunk& chunk;
        std::unordered_map<std::pair<int,int>, Chunk, pair_hash>& chunks;

        double lastMouseX = 0;
        double lastMouseY = 0;
        float sensitivity = 0.15f;

        GLFWwindow* window;
        glm::vec3 position;
        float pitch=0;
        float yaw=0;
};