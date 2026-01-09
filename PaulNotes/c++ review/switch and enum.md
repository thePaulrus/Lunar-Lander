#enum
#assert

unscoped enum:
```c++
enum Colour
{
	Red,
	Green,
	Blue,
	purple,
	megenta,
	yellow,
};

Colour playerColour = Red;
//enums are treated like numbers, so you can say some dumb shit like
//in value = monday, or
//monday *= 5

switch(playerColour)
{
case Red:
	cout << "the player is red";
	break;
case Green:
	cout << "the player is red";
	break;
case Blue:
	cout << "the player is Blue";
	break;
case purple:
case megenta:
	cout << "the player is megenta";
	break;
case yellow:
	cout << "the player is yellow";
	break;
default:
	assert(false);
	break;
}
```
scoped enum:
```c++
enum class Colour
{
	Red,
	Green,
	Blue,
	purple,
	megenta,
	yellow,
};


Colour playerColour = Colour::Red;
//stops you from doing dumb shit

switch(playerColour)
{
case Colour::Red:
	cout << "the player is red";
	break;
case Colour::Green:
	cout << "the player is red";
	break;
case Colour::Blue:
	cout << "the player is Blue";
	break;
case Colour::purple:
case Colour::megenta:
	cout << "the player is megenta";
	break;
case Colour::yellow:
	cout << "the player is yellow";
	break;
default:
	assert(false);
	break;
}
```

you can declare variables inside a case if you put {} around the code inside the case statement