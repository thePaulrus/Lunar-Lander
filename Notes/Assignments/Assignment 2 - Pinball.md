
**Submission**
- Commit your work
- Mark it complete on Brightspace

**Overview**
This isn't meant to be a game. Just a "Toy", let the user play for as long as it's interesting to them, so don't let it end and don't let your shapes just pile up in a corner (Unless that's somehow interesting?!?)

**Scene**
- Create a new scene
- This scene should have a Box2D physics world

**Camera**
- Setup a camera that's looking at the "machine" from an angle
- Update your camera with eye/up/at vectors. Up can stay hard-coded to 0,1,0 but keep it a variable in case you want to change it later

**Machine**
- This doesn't need to be literal pinball machine, just spawn some balls that bounce around, are affected by gravity and other forces, even some based on inputs if you want
- Setup a bunch of static objects that other objects can bounce off of
	- Make use of different materials, some with texture, some solid color, some vertex color
- Create some objects that actively bounce the balls away when they collide
	- i.e. when a ball hits these "bumpers", they will apply a force to the ball away from their circle
	- This should make use of the contact listener
	- If you want to do something different than a "bumper" that makes use of contacts and similar, or more complex, math, feel free to do that instead
- Add some flippers that react to keyboard presses, one key to flip all paddles at the same time is fine
	- Put rotational limits on the paddle's joint
- Create some "obstacles" that use joints
	- Use 3 or more joint types in your machine (including the revolute for the flippers)
	- Make at least 1 of them (other than the paddle) use a motor
		- but, a motor here might also be useful to push in back into place quickly
- Have different colored balls that have different filter properties and can pass through different "gates" of some kind. i.e. Red balls pass through red blocks, Blue through blue or something along those lines.

**Subjective Mark for Polish/Uniqueness**
- I rarely do this since the focus is meant to be on the code but I'm putting 1 of the 10 marks on making this look and behave nicely and/or in an interesting way
- It's completely subjective, so you might have to live with a 0 even if you do a ton of work and I simply don't see it that way
- Try to do something unique
- Feel free to make it a bit more of a game if you'd like
