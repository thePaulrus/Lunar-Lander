
See [ECS Architecture](../Engine/ECS%20Architecture.md)

![ECS Class Diagram](../Images/ECS%20Class%20Diagram.png)

# Note

The entire ECS setup can coexist with your existing code. This won't be as easy to test as you go since you won't see results until you're done. So, always keep the code compiling, take this in stages, and make sure you know what you're trying to achieve at each step.

Read through all the steps before starting.

Once you have the ECS setup in place, you can remove the calls to `GameObject::Draw` and everything should continue to render through your new setup.

# Steps

**Scene**
- Create a new `Scene` subclass to test this
- Only use `GameObject` and `Camera` instances, not the `Player` class

**Component classes**
- Create a `Component` base class
	- Each `Component` subclass will have a unique Type
		- The `GetType()`, `GetStaticType()` approach in the `Event` class is quite flexible and easy to extend, but feel free to do it differently
			- Avoid enums, they're too limited, if you define one in `Framework`, you can't cleanly extend it with new component types in `Game`
	- Give it a `GameObject*` for convenience
- Create two subclasses to start
	- You'll be moving the variables from the `GameObject` class into these components a bit later
	- Transform
		- Holds 3 vec3's for scale, rotation and position
		- Holds a mat4 for the combined transform
	- Mesh Rendering
		- Holds a Mesh* and a Material*

**ComponentManager**
- You need one `ComponentManager` instance in each `Scene`
- The manager will need to store a list of component pointers for each component type
- Drop in methods to do the following:
	- Add a component
	- Remove a component
	- Get a list of all registered components of a specific type
		- If passing back an existing list, don't return it by value, that will make a full copy of the vector

**Systems**
- You need at least the following systems:
	- One to update all the transforms
	- One to render all the meshes
- "System" functions can be part of the `ComponentManager` for these 2 core component types
	- We'll eventually make `Game` specific ones for new component types

**GameObject**
- The `GameObject` will hold a list of components
	- This is for convenience, for example:
		- Grabbing the transform component from another component
	- You should rarely, if ever, loop through these, other than finding a specific component, enabling/disabling a `GameObject` or saving/loading
- Allow for `GameObject` instances that have no components
	- i.e. don't create components in the `GameObject` constructor
- Creating a new component of any given type will need to add it to the `GameObject` component list as well as to the appropriate `ComponentManager` list
- Create helper functions to enable/disable a specific `GameObject`
	- i.e. Remove all of the `GameObject` components from the `ComponentManager` and re-add them
	- Write the following code to test this:
		- Add an imgui button or checkbox to enable/disable any object
		- When disabled, the object should stop rendering
	- Consider sharing some of this code with the `GameObject` destructor

**All of the above**
- Add any members, methods, etc, that will make the Game code simpler and easier to use when making a new `GameObject` with a variety of components or when writing new "systems"

**Make it all work**
- Have the `Game` call each of your systems from the right place and in the right order to keep the game working
	- i.e. Update transforms before Rendering objects

**Cleanup**
- Remove the old `GameObject::Draw` method
	- Drawing should now happen through the 2 "system" calls for updating transforms and rendering objects
- Make sure you delete all allocations when shutting down

**Next Steps**
- Create a component for your player movement logic
- Create a matching "system"
- Call this system before you update transforms since we need it to update positions and rotations first
