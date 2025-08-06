#pragma once
#include "Loader.h"
#include "RawModel.h"
#include "GUITexture.h"
#include "GUIShader.h"
#include "Maths.h"

class GUIRenderer {

    public:

        GUIRenderer(Loader& loader);

        void render(std::vector<GUITexture>& GUIs, std::vector<GUITexture>& hearts, std::vector<inventorySlot>& inventory);
        void cleanUp();

    private:

        RawModel quad;
        GUIShader shader;
        Maths maths;
};