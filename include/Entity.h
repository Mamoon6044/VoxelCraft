#pragma once
#include "TexturedModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity{

    public:

        Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);

        void increasePosition(double dx, double dy, double dz);
        void setPosition(float x, float y, float z);

        void increaseRotation(double dx, double dy, double dz);

        TexturedModel& getModel();

        glm::vec3 getPosition()const;
        float getRotX()const;
        float getRotY()const;
        float getRotZ()const;
        float getScale()const;
        void setRotX(float rotX);
        void setRotY(float rotY);

    private:

        TexturedModel model;
        glm::vec3 position;
        float rotX;
        float rotY;
        float rotZ;
        float scale;
};