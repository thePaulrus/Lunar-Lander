```c++
//memory box 1 holds the number 5
int value = 5;

// puts the memory box's adress into memory box 2
//a pointer has more memory allocation than an int, so you can't set an int to an
//adress
//the & here doesn't mean refrence. in this senario it means adress
int* pValue = &value;
//now memory box 1 holds the number 5, and memory box 2 holds the number(adress) 1


//this is bad, because it it trying to have pValue hold 5 as an adress,
//which is garbage
//int* pValue = value;

//setting the number held in memory box 1 to 6
*pValue = 6;

//this is bad, because it is trying to set the adress held in memory box 2 to 6,
//memory box 6 is garbage
//pValue = 6;
//refrences know when they are being initialized or used, 
//pointers don't
```

a pointer to a member variable uses a -> instead of a .




