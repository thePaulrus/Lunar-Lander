
see [Box2D - !Overview](../Files/Physics%20Engines/Box2D/Box2D%20-%20!Overview.md)

**Submission**
- Commit your work to main
- Mark it complete on Brightspace

**Overview**
Create a Lunar Lander style game.
This game can be written with either Box2d or Jolt physics.

**Scene**
- Create a new scene
- This scene should have a physics world (either box2d or Jolt)

**Ship**
Make a ship with this sort of layout
- ![LunarLanderShip](LunarLanderShip.png)
- 1 engine per side of ship
- 4 images: No engines on, left on, right on, both on
	- Alternatively make 1 sprite for the ship and draw the "fire" separately
- Collision-wise it can be a single body as wide as the legs
	- Don't make the collision the width of the image otherwise corners will catch on the ground shapes

**Controls**
- 2 button gameplay
- 'A' fires left thruster
- 'D' fires right thruster
	- Thrusters should apply force off center to cause some torque
- 'R' resets the ship, teleporting its body, zeroing out velocity, etc.

**Ground**
- Make some landing spots and some obstacles
- Suggestion:
	- Use an unrotated cube for a single landing spot
	- Place a bunch of rotated shapes that you can't land on to fill the space
- Feel free to try other options, like chain shapes

**Camera**
- Smoothly zoom the camera in as you approach the ground
- Don't zoom too close in

**Game**
- Hitting the ground at an angle or with too much speed or force will cause you to crash
	- Collision response should come from events sent through the event manager
- Print some messages based on the state of the game
	- "Too Fast"
	- "Bad Angle"
	- "Crash"
	- "Safe Landing"
- Lock the controls when you land safely or crash (other than reset)

**Tips**
- Restricting rotation
	- Box2D will naturally be restricted to the XY plane and only be allowed to rotate on the Z-axis. Jolt is a 3d physics engine and has full freedom of movement/rotation. This can be artificially limited with the `EAllowedDOFs mAllowedDOFs` member of `JPH::BodyCreationSettings`

- Sleeping bodies
	- Box2D and Jolt both allow objects to fall asleep for performance reasons.
	- Box2D has an option to take up the body when you apply force
	- Jolt doesn't have this option, but you can set the body to never fall asleep when it's created.

- World space position for forces
	- Box2D and Jolt have methods to apply forces at world space locations
	- Box2D has a convenient method inside the body to convert a local space position into the world space position called `GetWorldPoint`
	- Jolt doesn't have this method, so you'll have to transform a local space position into world space manually, this can be done by multiplying a local space position through your object's `world matrix`

- World space direction for forces
	- Similar to the last point, the force direction needs to be rotated.
	- Box2D has another helpers called `GetWorldVector` in the body class, this will rotate a direction vector for you.
	- For Jolt (or Box2d without helpers), since this is 2d, you can get away with a `vec2(cos,sin)` to figure out the direction, or you can setup a rotation matrix and transform the direction vector by the matrix
```c++
// Pseudo-code'ish
mat4 rot;
rot.CreateRotation( EulerAngles );
vec3 worldDir = rot * localDir;
```

- Damping
	- Both Box2d and Jolt have methods to dampen linear and angular velocities
	- Angular damping can be very handy to control the rotation on a body, making it harder to turn
		- The docs suggest values between 0 and 1, but feel free to experiment with much higher values to help control the spin of the ship
	- Linear damping can also be helpful to simulate "air resistance" and make the game a bit easier to control

- Gravity
	- Lower gravity means less forces overall and a ship that falls more slowly
	- This game is meant to be a "lunar lander" to make sure to reduce gravity
	- Find a value that works for you, you don't need literal moon gravity
