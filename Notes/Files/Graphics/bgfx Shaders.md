
Shaders in BGFX are a bit different to raw GLSL shaders, but very similar.

#### Debugging

The way the project is set up, shaders are compiled when you run. If there are errors in your shader code, this will often pop up a window with info.

Sometimes, you won't get a pop-up, but will instead get a crash, check the call-stack and the output window to see if you can work out what the issue is.

# Differences from GLSL

#### Attributes

In GLSL, names are arbitrary, so you can choose anything.

```glsl
In "vert" files:
	attribute vec3 a_Position
```

In bgfx, there are more restrictions, position must be called "a_position".

```
In the "varying.def.sc" file:
	vec3 a_position : POSITION;

In "vert" files:
	$input a_position
```

#### Uniforms

Uniforms work the same in shader code, with one exception. There are no `float`, `vec2`, or `vec3` uniform types. Make them `vec4` or `mat4`.

```
uniform vec4 u_Time;
uniform mat4 u_MatWorld;
```

#### Transforming Vectors by Matrices

In GLSL:

```glsl
// This is not a complete shader, just an example.

attribute vec3 a_Position;
uniform mat4 u_MatWorld;

void main()
{
	vec4 result = u_MatWorld * vec4(a_Position, 1);
}
```

In BGFX:

```bgfx shader language
// This is not a complete shader, just an example.

$input a_position;
uniform mat4 u_MatWorld;

void main()
{
	vec4 result = mul( u_MatWorld, vec4(a_position, 1) );
}
```
