
# Game Half

#### Minigolf
- Create a small flat area on your heightmap
- Initialize a Jolt physics world
- Create a single small mini-putt "hole"
	- Include a few angles, some elevation change, and a hole
	- Create a model for this and import it as an obj
		- You're free to make multiple models with multiple materials if you prefer
	- Turn the obj into a static collision shape using a MeshShape
	- This will sit on the heightmap. The heightmap itself doesn't need a collision shape
- Attach an orbit camera to the ball
- Have some input give the ball a push forward, depending on the camera angle
	- Add some form of swing strength, it could be a small bar on screen or even the numbers 1-9, it's all good
- If the ball goes in the hole, display a win message and show the number of strokes needed
- Pressing R will reset the game

#### Lights
- Add support for multiple lights
- Adjust the shaders to support arrays of uniforms
	- All light properties will have to come from arrays
	- Hard-code a upper limit for the number of lights in both your shader and game code
	- Modify Uniforms::CreateUniform to expose the 3rd parameter of bgfx::createUniform
	- Put your lighting math into a function, call it multiple times, once per light
		- Shaders support loops as well, so use one
	- Lights are additive, so add up the results for all lights
	- Again, hard-code the number of lights
		- Pass in "black" for the color of unused lights, in any

# Other Half

Many of the topics we cover during this class aren't necessary for assignments. Instead, they will contribute to this grade.

This list will grow as we go through the semester and other requirements will be added as well.

Most of these are architectural requirements and will need to be used consistently throughout your final codebase.

- Event Listeners
	- [Event Management](../Files/Engine/Event%20Management.md)
	- Events will only be sent to listener objects that register for a specific event type
- ECS
	- [ECS Architecture](../Files/Engine/ECS%20Architecture.md)
	- Ideally, all data would be in components, but this can be limited to:
		- Transforms
		- Meshes
		- Physics Bodies
		- Lights
	- Ideally, all functionality should be done through systems, but this can be limited to:
		- Updating transforms
		- Rendering meshes
		- Syncing physics bodies
		- Finding and created arrays of light properties
	- Other functionality, like scene specific player movement, pinball controls, everything to do with joints, cameras, scene specific game logic can remain in each individual scene class
- Physics Abstraction
	- [Abstraction Layers](../Files/Concepts/Abstraction%20Layers.md)
	- The Game project shouldn't be aware of either box2d or Jolt
	- Create a "PhysicsDemoScene" with a box falling that hits another box and lands on a larger block of "ground"
	- This scene should be able to switch between Jolt and box2d physics with a change of 1 line of code that chooses which physics world type is created

- Maintain the following scenes throughout the semester
	- Pinball
	- Lunar Lander Scene
	- Island/Minigolf Scene

- Good git commit messages (for the most part)
- No Memory Leaks
- No Warnings during build
	- These are warning produced by the compiler
	- This doesn't include the static code analysis tool
