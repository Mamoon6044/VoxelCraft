#include "Player.h"
#include <iostream>

Player::Player(Entity& head, Entity& body, Loader& loader)
    :body(body), head(head), loader(loader) {

        for (int i=0; i<10; ++i) {
		 GUITexture GUI(loader.loadTexture("full_heart"), glm::vec2(-0.9+((float)i/20),-0.8), glm::vec2(0.025,0.035));
		 hearts.push_back(GUI);
	    }
        //hearts.emplace_back(loader.loadTexture("full_heart"), glm::vec2(-0.4,-0.8), glm::vec2(0.025,0.035));
}

Entity& Player::getBody(){
    return body;
}
Entity& Player::getHead(){
    return head;
}

int Player::getHealth(){
    return this->health;
}
void Player::changeHealth(int value){
    this->health += value;
}
void Player::dead(){
    body.setRotX(90);
    head.setRotX(90);
}

std::vector<GUITexture>& Player::getHearts(){
    return this->hearts;
}
std::vector<inventorySlot>& Player::getInventory(){
    return this-> inventory;
}

void Player::addInventory(GUITexture iso, int c, int slot){
    iso.changePosX(slot*0.0925);
    //std::cout<<iso.getPosition().x<<std::endl;
    inventorySlot invSlot(slot, iso, c);
    inventory.push_back(invSlot);
}

void Player::changeHearts(){
    if(health % 2 == 1){
        for(int i = hearts.size()-1; i >= static_cast<int>(health/2)+1; --i){
            hearts.erase(hearts.begin()+i);
        }
        hearts[static_cast<int>(health/2)].setTextureID(loader.loadTexture("half_heart"));
    } else {
        for(int i = hearts.size()-1; i >= static_cast<int>(health/2); --i){
            hearts.erase(hearts.begin()+i);
        }
    }
}