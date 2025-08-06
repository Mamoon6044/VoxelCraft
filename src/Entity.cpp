#include "Entity.h"

Entity::Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale):model(std::move(model)){

    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
}

void Entity::increasePosition(double dx, double dy, double dz){

    this->position.x+=dx;
    this->position.y+=dy;
    this->position.z+=dz;
}

void Entity::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Entity::increaseRotation(double dx, double dy, double dz){

    this->rotX+=dx;
    this->rotY+=dy;
    this->rotZ+=dz;
}

TexturedModel& Entity::getModel(){
    return this->model;
}
void Entity::setRotX(float rotX) {
    this->rotX = rotX;
}
void Entity::setRotY(float rotY) {
    this->rotY = rotY;
}

glm::vec3 Entity::getPosition()const{
    return this->position;
}
float Entity::getRotX()const{
    return this->rotX;
}
float Entity::getRotY()const{
    return this->rotY;
}
float Entity::getRotZ()const{
    return this->rotZ;
}
float Entity::getScale()const{
    return this->scale;
}