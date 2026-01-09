#assert
```c++
void Inventory::DropItem(int itemNumber)
{
	//if the condition is not met the program shuts down
	assert(itemNumber < m_NumberOfItemsHeld);
	
	//code to drop item
}



```