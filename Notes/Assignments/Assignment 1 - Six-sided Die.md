
see [Scenes](../Files/Engine/Scenes.md), [Transforms](../Files/Graphics/Transforms.md), [View And Projection Matrices](../Files/Graphics/View%20And%20Projection%20Matrices.md), [bgfx Shaders](../Files/Graphics/bgfx%20Shaders.md), [UV Coordinates](../Files/Graphics/UV%20Coordinates.md)

**Submission**
- Commit your work
- Mark it complete on Brightspace

**Scene**
- Create a `Scene` class as described in [Scenes](../Files/Engine/Scenes.md)
- Create a new `Scene` subclass for your cube scene
- In `Game` add an imgui scene selector window
	- You can use a series of ImGui::Button calls
		- but feel free to make your interface however you like
	- Either create/destory scenes when the button is pressed
		- or keep a list of scenes already made and switch which one is active
- Make the cube scene the default when you commit your assignment
- As you derive more scene subclasses, you might start to see the need to put more functionality into `fw::Scene`
- Keep your scenes minimal
	- i.e. Don't leave leftover code from a cut and paste of a previous scene

**Setup for 3D vertex positions**
- Take these changes slow, one misstep and nothing will render
	- Do one change, compile and test
	- Always know what you're expecting as a result of each step
- Make a_position a vec3
	- Attribute properties are defined in "varying.def.sc" in the DataRaw/Shaders folder
	- Changing the attribute type to vec3 won't prevent our meshes from rendering, the graphics pipeline will just fill the 'z' values with 0 for each 2d vertex
	- You'll need to immediate adapt all the vertex shaders since this line:
		- `vec2 objectSpacePosition = a_position` is no longer valid
		- It's assigning a vec3 to a vec2
- Adapt all .vert files to use matrices (World, View, and Projection)
	- Start with just the world matrix and in just one shader
	- Once that works, clean up the code, always verifying if it still works
		- rip out the scale, rot, pos uniforms
	- see [bgfx Shaders](../Files/Graphics/bgfx%20Shaders.md) for the formatting of uniforms, matrix multiplies, and more
- When you have all 3 matrices being sent in, clean up
	- Rip out all the old transform uniforms (scale, rot, pos, camPos, projScale) and code related to them
	- There's an `#include <bgfx_shader.sh>` missing in VertexColor.vert
		- Make sure you add that back in, otherwise the mul() function will cause errors

**Vertex Format**
- Create a new vertex format with 3D positions
	- or adapt one of the vertex format structs to have 3D positions

**Die**
- Before attempting this, make sure the circle from week 1 renders
	- You can find the code below
	- Look at [Exercise - Project Setup](../Files/Exercises/Exercise%20-%20Project%20Setup.md) for a fix to Mesh related to `bgfx::makeRef`
- Create or download a texture with 6 faces of a die on it
	- Load it, create a material, etc
- Make a create cube function in Shapes.cpp
    - You'll need 24 vertices and 36 indices
	    - 4 verts and 6 indices per side of the cube
	- Pass in a size, so we can make any size of rectangle in the future without changing the object scale
	    - Create a cube the requested size centered around 0,0,0
		- Add multiple cubes to your scene, some uniform size, some non-uniform
			- i.e. make it taller than it is wide or similar
	    - Setup the UVs so it shows the 6 faces of a die
- Render at least one of the dice rotating so we see all 6 sides over time
	- optionally, also add some imgui controls to control the rotation

**Small Fix**
This might not be needed for the cube, but it will be needed later on.

In `Material::GetBGFXRenderState()`, set the Z-Write bit flag for all materials. Without this depth values are not being written to the depth buffer and objects, or parts of objects, might appear in the wrong order.

```c++
    bgfxRenderState |= BGFX_STATE_WRITE_Z;
```

**Circle creation code**
```c++
fw::Mesh* CreateCircleMesh()
{
    int numPoints = 32;

    std::vector<VertexFormat_PosColor> verts;
    std::vector<uint16> indices;

    float angleInc = 2*PI / numPoints;
    float radius = 5.0f;

    for( int i=0; i<numPoints; i++ )
    {
        float angle = angleInc * i;
        vec2 pos = vec2( cos(angle), sin(angle) ) * radius;
        verts.push_back( { pos, 0, 255, 0, 255 } );
    }

    for( int i=1; i<numPoints-1; i++ )
    {
        indices.push_back( 0 );
        indices.push_back( i+1 );
        indices.push_back( i );
    }

    int vertBytes = sizeof(VertexFormat_PosColor) * (int)verts.size();
    int indicesBytes = sizeof(uint16) * (int)indices.size();

    return new fw::Mesh( VertexFormat_PosColor::format,
                         verts.data(), vertBytes,
                         indices.data(), indicesBytes );
}
```