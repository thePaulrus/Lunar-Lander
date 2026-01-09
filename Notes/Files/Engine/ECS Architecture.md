
# Inheritance vs Composition

#### Inheritance

Inheritance based designs imply an "is a" relationship. For example:
- Player is a GameObject
- Item is a GameObject
- Food is an Item
- Circle is a Shape

These relationships are hard-coded into your source and don't lend themselves to being modified at runtime. This is great if you're making a game, but not as good if you're making a more general game engine.

#### Composition

Composition on the other hand implies a "has a" relationship. For example:
- Player has a Transform, has a Mesh, has a Physics body, has Movement logic
- Camera has a Transform, has Camera settings
- Enemy has a Transform, has a Mesh, has a Physics body, has AI logic

# ECS Design

ECS stands for 3 things, Entities, Components, and Systems. This approach to design allows for objects to be assembled at runtime, rather than being designed at compile time. For example, if we want to create a player, we could do something like:

```c++
player = new GameObject();
player->Add( new Transform(vec3(0,0,0)) );
player->Add( new Mesh("Sprite","Blue") );
player->Add( new Script("TopDownMovement") );
```

This is still compile time of course, but you could imagine adding menu options that would call each of these line individually from an interface.

#### Entities

An entity is an object that's comprised of a bunch of components.

In some ECS implementations, entities aren't a class at all, just a number. Then each component stores which entity it belongs to.

Whether or not you have a class associated with entities, it shouldn't have any functionality.

#### Components

Components are small classes designed to hold data. Components themselves don't take any actions.

Different components will store different blocks of data. For example:
- Transforms components will store a scale, rotation and position
- Mesh components can store references to a mesh and material

This leads to one of the main benefits of this architecture. If we have an array of transform components all contiguously laid out in memory, we can write a function that can be responsible for one thing, computing matrices that would be more efficient than doing the same work where the transform info is spread amongst many objects.

#### Systems

Systems are simply a function focused on a single task using one or more components. For example:

- A Transform System will loop through all transform components and generate a matrix for each

# Class Diagram

![ECS Class Diagram](../Images/ECS%20Class%20Diagram.png)

[Exercise - Basic ECS Setup](../Exercises/Exercise%20-%20Basic%20ECS%20Setup.md)
