#include "LightSource.h"

LightSource::LightSource(const glm::vec3& position, const glm::vec3& colour):position(position),colour(colour){}

const glm::vec3 LightSource::getPosition()const{
    return position;
}
void LightSource::setPosition(glm::vec3 position){
    this->position = position;
}

const glm::vec3 LightSource::getColour()const{
    return colour;
}
void LightSource::setColour(glm::vec3 colour){
    this->colour = colour;
}
