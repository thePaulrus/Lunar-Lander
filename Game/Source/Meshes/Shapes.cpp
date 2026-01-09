//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "VertexFormats.h"
#include "Shapes.h"

#include <stdio.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"




//=============================================================================================================================================================================================================================================
//                                                                                                   2D SHAPES
//=============================================================================================================================================================================================================================================

//=======================
// Triangle
//=======================
static const VertexFormat_PosColor g_TriangleVerts[] =
{
    { vec2( 0.0f, 0.5f), 255, 0, 0, 255 }, // Top
    { vec2(-0.5f,-0.5f), 0, 255, 0, 255 }, // Bottom-left
    { vec2( 0.5f,-0.5f), 0, 0, 255, 255 }, // Bottom-right
};
static const uint16 g_TriangleIndices[] =
{
    
    0, 2, 1,
};
fw::Mesh* CreateTriangleMesh()
{
    return new fw::Mesh( VertexFormat_PosColor::format, g_TriangleVerts, sizeof(g_TriangleVerts), g_TriangleIndices, sizeof(g_TriangleIndices) );
}

//=======================
// Square
//=======================
static const VertexFormat_PosColor g_SquareVerts[] =
{
    { vec2(-0.5f, 0.5f), 0, 255, 0, 255 }, // Top-left
    { vec2(-0.5f,-0.5f), 0,   0, 0, 255 }, // Bottom-left
    { vec2( 0.5f,-0.5f), 0,   0, 0, 255 }, // Bottom-right
    { vec2( 0.5f, 0.5f), 0, 255, 0, 255 }, // Top-right
};
static const uint16 g_SquareIndices[] =
{
    //indecies must be clockwise relatave to the camera
    0,2,1, 0,3,2
};
fw::Mesh* CreateSquareMesh()
{
    return new fw::Mesh( VertexFormat_PosColor::format, g_SquareVerts, sizeof(g_SquareVerts), g_SquareIndices, sizeof(g_SquareIndices) );
}



//=======================
// circle
//=======================


fw::Mesh* CreateCircleMesh(int numVerts) {
    std::vector<VertexFormat_PosColor> verts;
    std::vector<uint16> indecies;

    float radius = 0.5;
    float angle = 0.0f;

    float radiansPerSide = 2.0f * 3.1415926 / (float)numVerts;

    for (int i = 0; i < numVerts; i++)
    {
        angle = i * radiansPerSide;
        verts.push_back({vec2(cos(angle) * radius, sin(angle) * radius), 0, 200, 50, 255 });

    }
    for(int i = 1; i < numVerts; i++) {
        indecies.push_back(0);
        indecies.push_back(i+1);
        indecies.push_back(i);

    }


    int vertBytes = sizeof(VertexFormat_PosColor) * numVerts;
    int indeciesBytes = sizeof(uint16) * indecies.size();
    return new fw::Mesh(VertexFormat_PosColor::format, verts.data(), vertBytes, indecies.data(), indeciesBytes);
}




//=======================
// Sprite
//=======================
static const VertexFormat_PosUV g_SpriteVerts[] =
{
    { vec2(-0.5f, 0.5f), vec2(0,1) }, // Top-left
    { vec2(-0.5f,-0.5f), vec2(0,0) }, // Bottom-left
    { vec2( 0.5f,-0.5f), vec2(1,0) }, // Bottom-right
    { vec2( 0.5f, 0.5f), vec2(1,1) }, // Top-right
};
static const uint16 g_SpriteIndices[] =
{
   0,2,1, 0,3,2
};
fw::Mesh* CreateSpriteMesh()
{
    return new fw::Mesh( VertexFormat_PosUV::format, g_SpriteVerts, sizeof(g_SpriteVerts), g_SpriteIndices, sizeof(g_SpriteIndices) );
}



//=============================================================================================================================================================================================================================================
//                                                                                                   3D SHAPES
//=============================================================================================================================================================================================================================================



//=======================
// Box
//=======================


static const uint16 g_BoxIndices[] =
{
    //indecies must be counter-clockwise relatave to the inside of the box
    //                //                 //                      /                            //                           // 
    0,2,1, 0,3,2,     4,5,6,  4,6,7,     8,9,10,   8,10,11,      12,14,13,   12,15,14,        16,19,17,   19,18,17,        20,23,21,   23,22,21
};

fw::Mesh* CreateBoxMesh(vec3 size)
{
    const VertexFormat_Pos3UV_Normal g_BoxVerts[] =
    {

        //5 
        { vec3(-0.5f, 0.5f,-0.5f) * size, vec3(0,0,-1), vec2(0.5,1)}, // Top-left     0
        { vec3(-0.5f,-0.5f,-0.5f) * size, vec3(0,0,-1), vec2(0.5,0.666) }, // Bottom-left  1
        { vec3(0.5f,-0.5f,-0.5f) * size, vec3(0,0,-1), vec2(0.75,0.666) }, // Bottom-right 2
        { vec3(0.5f, 0.5f,-0.5f) * size, vec3(0,0,-1), vec2(0.75,1) }, // Top-right    3

        // left 4
        { vec3(-0.5f, 0.5f,-0.5f) * size, vec3(-1,0,0), vec2(0.75,0.666) }, // Top-left      4
        { vec3(-0.5f,-0.5f,-0.5f) * size, vec3(-1,0,0), vec2(0.75,0.333) }, // Bottom-left    5
        { vec3(-0.5f,-0.5f,0.5f) * size, vec3(-1,0,0), vec2(1,0.333) }, // Bottom-right   6
        { vec3(-0.5f, 0.5f,0.5f) * size, vec3(-1,0,0), vec2(1,0.666) }, // Top-right     7

        //right 3
        { vec3(0.5f, -0.5f,0.5f) * size, vec3(1,0,0), vec2(0.25,0.666) }, // Top-left      4
        { vec3(0.5f,-0.5f,-0.5f) * size, vec3(1,0,0), vec2(0.25,0.333) }, // Bottom-left    5
        { vec3(0.5f,0.5f,-0.5f) * size, vec3(1,0,0), vec2(0.5,0.333) }, // Bottom-right   6
        { vec3(0.5f, 0.5f,0.5f) * size, vec3(1,0,0), vec2(0.5,0.666) }, // Top-right     7

        //back 2
        { vec3(0.5f, 0.5f,0.5f) * size, vec3(0,0,1), vec2(0.5,0.333) }, // Top-left      8
        { vec3(0.5f,-0.5f,0.5f) * size, vec3(0,0,1), vec2(0.5,0) }, // Bottom-left   9
        { vec3(-0.5f,-0.5f,0.5f) * size, vec3(0,0,1), vec2(0.75,0) }, // Bottom-right   10
        { vec3(-0.5f, 0.5f,0.5f) * size, vec3(0,0,1), vec2(0.75,0.333) }, // Top-right      11

        //1
        { vec3(-0.5f, -0.5f,-0.5f) * size, vec3(0,-1,0), vec2(0.5,0.666) }, // Top-left     12
        { vec3(-0.5f,-0.5f,0.5f) * size, vec3(0,-1,0), vec2(0.5,0.333) }, // Bottom-left   13
        { vec3(0.5f,-0.5f,0.5f) * size, vec3(0,-1,0), vec2(0.75,0.333) }, // Bottom-right  14
        { vec3(0.5f, -0.5f,-0.5f) * size, vec3(0,-1,0), vec2(0.75,0.666) }, // Top-right    15

        //6
        { vec3(-0.5f, 0.5f,0.5f) * size, vec3(0,1,0), vec2(0,0.666) }, // Top-left      16
        { vec3(-0.5f,0.5f,-0.5f) * size, vec3(0,1,0), vec2(0,0.333) }, // Bottom-left   17
        { vec3(0.5f,0.5f,-0.5f) * size, vec3(0,1,0), vec2(0.25,0.333) }, // Bottom-right   18
        { vec3(0.5f, 0.5f,0.5f) * size, vec3(0,1,0), vec2(0.25,0.666) }, // Top-right      19

        // 4
        { vec3(-0.5f, -0.5f,0.5f) * size, vec3(0,-1,0), vec2(0.75,0.666) }, // Top-left     20
        { vec3(-0.5f,-0.5f,-0.5f) * size, vec3(0,-1,0), vec2(0.75,0.333) }, // Bottom-left   21
        { vec3(0.5f,-0.5f,-0.5f) * size, vec3(0,-1,0), vec2(1,0.333) }, // Bottom-right 22
        { vec3(0.5f, -0.5f,0.5f) * size, vec3(0,-1,0), vec2(1,0.666) }, // Top-right     23
    };
    //return new fw::Mesh(VertexFormat_Pos3UV::format, g_BoxVerts, sizeof(g_BoxVerts), g_BoxIndices, sizeof(g_BoxIndices));
    return new fw::Mesh(VertexFormat_Pos3UV_Normal::format, g_BoxVerts, sizeof(g_BoxVerts), g_BoxIndices, sizeof(g_BoxIndices));
}


//=======================
// Imported Mesh
//=======================

fw::Mesh* ImportOBJMesh(const char* objfilename)
{

    std::vector<VertexFormat_Pos3UV_Normal> verts;
    std::vector<uint16> indecies;
    int fvalx;
    int fvaly;
    int fvalz;
    std::vector<vec3> vertPos;
    vec3 pos;
    std::vector<vec2> UVs;
    vec2 UV;
    std::vector<vec3> Normals;
    vec3 Normal;

    uint32 length = 0;
    char* buffer = fw::LoadCompleteFile(objfilename, &length);
    if (buffer == 0 || length == 0)
    {
        delete[] buffer;
        return nullptr;
    }

    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);
    while (line)
    {
        fw::OutputMessage("%s\n", line);

        //break the lines into peices now


        if (line[0] == 'v' && line[1] == ' ') {// Match
            sscanf_s(line, "%*s %f %f %f", &pos.x, &pos.y, &pos.z);
            vertPos.push_back(pos);
        }
        if (line[0] == 'v' && line[1] == 't') {// Match
            sscanf_s(line, "%*s %f %f ", &UV.x, &UV.y);
            UVs.push_back(UV);
        }
        if (line[0] == 'v' && line[1] == 'n') {// Match
            sscanf_s(line, "%*s %f %f %f", &Normal.x, &Normal.y, &Normal.z);
            Normals.push_back(Normal);
        }
        if (line[0] == 'f' && line[1] == ' ') {// Match
            sscanf_s(line, "%*s %d/%d/%d", &fvalx, &fvaly, &fvalz);
            verts.push_back(VertexFormat_Pos3UV_Normal({ vertPos[fvalx - 1], Normals[fvalz - 1],UVs[fvaly - 1] }));

            sscanf_s(line, "%*s %*d/%*d/%*d %d/%d/%d", &fvalx, &fvaly, &fvalz);
            verts.push_back(VertexFormat_Pos3UV_Normal({ vertPos[fvalx - 1], Normals[fvalz - 1], UVs[fvaly - 1] }));

            sscanf_s(line, "%*s %*d/%*d/%*d %*d/%*d/%*d %d/%d/%d", &fvalx, &fvaly, &fvalz);
            verts.push_back(VertexFormat_Pos3UV_Normal({ vertPos[fvalx - 1], Normals[fvalz - 1], UVs[fvaly - 1] }));
        }

        /*fw::OutputMessage("%s -> %f %f %f\n", Type, x,y,z);*/

        //dummy indecy list
        for (int i = 0; i < verts.size(); i++) {
            indecies.push_back(i);
        }


        line = strtok_s(0, "\n", &next_token);
    }

    int vertBytes = sizeof(VertexFormat_Pos3UV_Normal) * verts.size();
    int indeciesBytes = sizeof(uint16) * indecies.size();


    //find noramls

   // Mesh(const bgfx::VertexLayout & vertexFormat, const void* verts, uint32 vertsSize, const void* indices, uint32 indicesSize);
    return new fw::Mesh(VertexFormat_Pos3UV_Normal::format, verts.data(), vertBytes, indecies.data(), indeciesBytes);
}

//=======================
// Plane
//=======================


fw::Mesh* CreatePlaneMesh(vec2 numVerts, vec2 worldSize) {
    std::vector<VertexFormat_Pos3UV_Normal> verts;
    std::vector<uint16> indecies;
    vec2 UV;
    vec3 pos;
    int bottomLeft;
   
            pos.x = worldSize.x / (numVerts.x - 1);
            pos.y = worldSize.y / (numVerts.y - 1);
            pos.z = 0;
  
    for (int y = 0; y < numVerts.y; y++)
    {
        for (int x = 0; x < numVerts.x; x++) {
           
            UV.x = 1 * x / (numVerts.x - 1);
            UV.y = 1 * y / (numVerts.y - 1);


            vec3 vertPos = vec3(pos.x * x, pos.z, pos.y * y);

            verts.push_back({ vertPos , vec3(0, 1,0), UV });  
        }
    }

    for (int y = 0; y < numVerts.y -1; y++)
    {
        for (int x = 0; x < numVerts.x -1; x++) {

            bottomLeft = y * numVerts.x + x;

            indecies.push_back(bottomLeft);
            indecies.push_back(bottomLeft + numVerts.x);
            indecies.push_back(bottomLeft + numVerts.x + 1);

            indecies.push_back(bottomLeft);
            indecies.push_back(bottomLeft + numVerts.x + 1);
            indecies.push_back(bottomLeft + 1);

        }
    }


    int vertBytes = sizeof(VertexFormat_Pos3UV_Normal) * verts.size();
    int indeciesBytes = sizeof(uint16) * indecies.size();
    return new fw::Mesh(VertexFormat_Pos3UV_Normal::format, verts.data(), vertBytes, indecies.data(), indeciesBytes);
}

//=======================
// Hight map
//=======================


fw::Mesh* CreateHightMap( vec2 worldSize, const char* FileName) {
    std::vector<VertexFormat_Pos3UV_Normal> verts;
    std::vector<uint16> indecies;
    vec2 UV;
    vec3 pos;
    int bottomLeft;

    // Load the file contents.
    uint32 length;
    char* fileContents = fw::LoadCompleteFile(FileName, &length);

    // Have stb_image decompress png from memory into a raw color array.
    int width;
    int height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load_from_memory((unsigned char*)fileContents, length, &width, &height, &channels, 4);
    assert(pixels != nullptr);

    int pixelIndex = 0;

    pos.x = worldSize.x / (width - 1);
    pos.y = worldSize.y / (height - 1);
    pos.z = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++) {

            UV.x = 1 * x / ((float)width - 1);
            UV.y = 1 * y / ((float)height - 1);

            //color of 0 = 0 hight, colour of 255 = 5... so uhhhhhhhhhh divide by 51.0f?
            pos.z = pixels[pixelIndex] / 51.0f;


            vec3 vertPos = vec3(pos.x * x, pos.z, pos.y * y);

            verts.push_back({ vertPos , vec3(0, 1,0), UV });
            //we want to get the r value from each, so were're skipping over g,b, and a
            pixelIndex+=4;
        }
    }

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < width - 1; x++) {

            bottomLeft = y * width + x;

            indecies.push_back(bottomLeft);
            indecies.push_back(bottomLeft + width);
            indecies.push_back(bottomLeft + width + 1);

            indecies.push_back(bottomLeft);
            indecies.push_back(bottomLeft + width + 1);
            indecies.push_back(bottomLeft + 1);

        }
    }


    int vertBytes = sizeof(VertexFormat_Pos3UV_Normal) * verts.size();
    int indeciesBytes = sizeof(uint16) * indecies.size();
    return new fw::Mesh(VertexFormat_Pos3UV_Normal::format, verts.data(), vertBytes, indecies.data(), indeciesBytes);
}