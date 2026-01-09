a refrence is initialized to another variable's memory **NOT** it's value

```c++
//memory box 1 has the number 5
int value = 5;

//memory box 2 takes the number from memory box 1.
int value2 = value;
//now both memory box 1 and 2 have value 5

//memory box 2 has the number 10. nothing else has been touched
int value2 = 10;


//initializing refrence to look at value's storage, which is memory box 1
int& reftoValue = value;

//this is not an initialization, it is a number change. reftoValue still points at //memory box 1
reftoValue = 15;
//now memory box one holds the number 15. which means value and reftoValue both //hold the number 15
```

this is useful for changing values from main inside a funtion

```c++
void ChangeValue(int intake){
	//takes a copy of the passed number in a NEW memory box
	intake = 13
	//now memory box 3 has the number 13, but because intake only has a scope of
	//ChangeValue, the veriable that was passed was not changed
}

void ChangeValue(int& intake){
//makes a refrence to the passed variable
intake = 13
//changes the number in the passed variable's memory box
//now the passed variable has the number 13
}
```


