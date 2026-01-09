# access specifier
- public
- private

# member variables
- must have a prefix. like "m_"
- should be private

# methods
- helper methods should be private


```c++
class player
{
private:
	int m_ID;
	int m_positionX;
	int m_positionY;
public:
	void setPosition(int x, int y);
}
```