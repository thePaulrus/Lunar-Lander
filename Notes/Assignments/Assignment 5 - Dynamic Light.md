
**Submission**
- Commit your work to your main branch
- Mark it complete on Brightspace

**Overview**
This is mainly about adding a single light to your island scene, but also requires a player that can run around the island with a light attached to it

**Scene**
- Do this work in your island scene
	- If you happen to not have one, you can work in a new scene with a few assorted cubes or other meshes. Some of the heightmap and player specific marks won't be accessible in this case
- 10x10 is quite small for the island, increase the world size to something like 50x50 to give space to run around and to flatten some of the peaks
	- Feel free to adjust sizes to make it look/feel good based on the scale/speeds of your player
- This scene does not need physics

**Light**
- The specular component of the light is optional
- Expose all the light properties as uniforms:
	- position
	- color
	- range
	- ambient percentage
	- falloff exponent
	- specular exponent (if adding specular)
- Display these properties in a new "Light Properties" ImGui window
- Adjust your shaders to use world space normal values
- The material color comes from either a texture, a vertex color, or a uniform color
- All materials in your scene should have lighting calculations
	- If you decide you want multiple shaders with lighting math (for example, a texture shader and a vertex color shader), you can put some functions in a "header" and include it from other shader files (this isn't a core feature of some graphics languages, but bgfx supports it)

**Heightmap Normals**
- Adjust your heightmap creation code to calculate a normal vector for each vertex.
- This can be an approximation
	- pick the vertex positions for the 4 surrounding vertices
		- left, right, up, down
	- calculate the normal with the cross product of the 2 directions
		- (right - left) cross (up - down)
	- Be careful around the sides of the heightmap so you don't read memory out of bounds of your array

**Trees**
- Ensure your OBJ loader loads normals properly, so the trees will be lit up properly

**Player/Camera**
- Have the player move around the heightmap with a light attached to a point above their head
	- Find the proper height for the x/z position of the player
	- See [Barycentric Coordinates - Code](../Files/Math/Barycentric%20Coordinates%20-%20Code.md) for a possible implementation
		- What does this code do if the player goes outside the heightmap?
		- You'll likely want to create a subclass of your mesh for a heightmap, this will give you a place to store a method like this and a class definition to store the extra heightmap data needed to calculate the coordinates
- The player can be any mesh, including a cube
- Setup a third person camera to follow the player and allow the user to change the angle and zoom of the camera
	- Create a subclass of your Camera class with some extra data to support the orbit camera, such as the rotation and distance
		- See [Orbit Camera - Code](../Files/Math/Orbit%20Camera%20-%20Code.md) for a possible implementation
- The player should move relative to the camera
	- i.e. W and S should move in and out
	- and A and D should strafe left and right
	- Bear in mind this is just 2d from a top-down perspective, so this mainly needs the use a of a vector based on the camera's angle. i.e. cos and sin.
