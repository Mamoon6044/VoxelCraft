#pragma once

class RawModel {

    public:
        RawModel(int VAOId, int vertexCount);

        int getVAOId();

        int getvertexCount();

    private:
        int VAOId;
        int vertexCount;
};