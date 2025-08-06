#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSource {

    public:

        LightSource(const glm::vec3& position, const glm::vec3& colour);

        const glm::vec3 getPosition()const;
        void setPosition(glm::vec3 position);

        const glm::vec3 getColour()const;
        void setColour(glm::vec3 colour);

    private:

        glm::vec3 position;
        glm::vec3 colour;
};