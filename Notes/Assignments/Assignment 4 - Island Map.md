
**Submission**
- Commit your work to main
- Mark it complete on Brightspace

**Overview**
Create a heightmap island with some trees on it surrounded by water

**Scene**
- Create a new scene
- This scene does not need physics
- Position a camera to nicely frame all of the objects below
	- The water can extend offscreen

**Cubes**
- Add 4 cubes at the following locations
	- (0,0)
	- (10,0)
	- (0,10)
	- (10,10)
- Make them large enough to always be seen

**Heightmap Island**
- Add a new plane mesh constructor that takes in a png filename
	- Create 1 vertex for each pixel in the png
		- i.e. a 32x32 texture will generate a heightmap with 32x32 vertices
		- Keep the png file low res, like 32x32 or 64x64. Due to the uint16 index format we're using, we're limited to 65535 vertices, so 256x256 is as large as we can go
	- Set the "Y" values of each vertex based on the color of the pixel in the texture
	- Make a color value of 0 a world height of 0
	- Make a color value of 255 a world height of 5
- Create a heightmap that's 10x10 world units large
	- i.e. It should touch all 4 cubes
- Give it the min height around the edges and max height at some points in the center
	- i.e. make an island

**Water**
- Create a plane that's at least 20x20 world units large
	- Center is so it extends in all directions surrounding the island
- Place it at a same world height as the 4 cubes
- Have any form of simple water deformation applied by a shader

**Trees**
- Create a tree mesh in a 3d editor of your choice that can export .obj files
	- I recommend MagicaVoxel or Blender since they're free
	- Place the pivot point on the bottom of the trunk
	- It must be a single mesh with a material that colors the trunk and leaves different colors
- Place 10+ trees around your map
	- Place them exactly on vertices in your heightmap so their positions match up with the heights
	- Give them random Y rotations
	- Give them random scale between 0.8 and 1.2
