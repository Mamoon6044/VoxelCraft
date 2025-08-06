#pragma once
#include "Entity.h"
#include "GUITexture.h"
#include "Loader.h"


struct inventorySlot {
    int slot;
    GUITexture texture;
    int count;

    inventorySlot(int slot, GUITexture tex, int count): slot(slot), texture(tex), count(count) {}
};

class Player {
    
    public:

        Player(Entity& head, Entity& body, Loader& loader);

        Entity& getBody();
        Entity& getHead();
        int getHealth();
        void changeHealth(int value);
        void changeHearts();
        void dead();

        std::vector<GUITexture>& getHearts();
        std::vector<inventorySlot>& getInventory();
        void addInventory(GUITexture iso, int c, int slot);

    private:

        int health = 20;
        Loader& loader;

        std::vector<inventorySlot> inventory;
        std::vector<GUITexture> hearts;
        std::vector<GUITexture> hand;

        Entity& body;
        Entity& head;
};