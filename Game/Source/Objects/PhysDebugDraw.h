#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "Meshes/VertexFormats.h"
#include "Game.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

class PhysDebugDraw : public b2Draw
{
public:
    bgfx::ProgramHandle m_ShaderHandle;
    fw::Uniforms* m_pUniforms;

    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {}
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override 
    {
        VertexFormat_PosColor g_SquareVerts[] =
        {
            { vec2(vertices[0].x, vertices[0].y), 0, 255, 0, 128}, // Top-left
            { vec2(vertices[1].x, vertices[1].y), 0, 255, 0, 128 }, // Bottom-left
            { vec2(vertices[2].x, vertices[2].y), 0, 255, 0, 128 }, // Bottom-right
            { vec2(vertices[3].x, vertices[3].y), 0, 255, 0, 128 }, // Top-right
        };
        uint16 g_SquareIndices[] =
        {
            //indecies must be clockwise relatave to the camera
            0,2,1, 0,3,2
        };
        DrawShape(g_SquareVerts, g_SquareIndices, 4,6);
    }

    virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override 
    {
        int b = 1;
    }
    virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override {
        int b = 1;
    
    }
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override {}
    virtual void DrawTransform(const b2Transform& xf) override {}
    virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override {}

    void DrawShape(VertexFormat_PosColor* triangleVerts, uint16* triangleIndices, uint32_t numVertices, uint32_t numIndices)
    {
        bgfx::TransientVertexBuffer tvb;
        bgfx::TransientIndexBuffer tib;

        int maxVerts = bgfx::getAvailTransientVertexBuffer(numVertices, VertexFormat_PosColor::format);
        int maxIndices = bgfx::getAvailTransientIndexBuffer(numIndices);
        if ((numVertices != maxVerts) || (numIndices != maxIndices))
        {
            // Not enough space in transient buffer, quit drawing the rest...
            return;
        }

        fw::mat4 worldMatrix;
        worldMatrix.SetIdentity();
        bgfx::setUniform(m_pUniforms->GetUniform("u_OBJtoWorld"), &worldMatrix);

        bgfx::allocTransientVertexBuffer(&tvb, numVertices, VertexFormat_PosColor::format);
        bgfx::allocTransientIndexBuffer(&tib, numIndices);

        VertexFormat_PosColor* vertData = (VertexFormat_PosColor*)tvb.data;
        memcpy(vertData, triangleVerts, numIndices * sizeof(VertexFormat_PosColor::format));
        uint16* indexData = (uint16*)tib.data;
        memcpy(indexData, triangleIndices, numIndices * sizeof(uint16));

        uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA |
            BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);

        bgfx::setState(state);
        bgfx::setVertexBuffer(0, &tvb, 0, numVertices);
        bgfx::setIndexBuffer(&tib, 0, numIndices);
        bgfx::submit(EditorViews::EditorView_Game, m_ShaderHandle);
    }
};
