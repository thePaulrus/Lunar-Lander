#containter 
[[pointers]]


```c++
vector<int> intlist; 
//creating an array of size 0

intlist.push_back(1); 
//if the capacity is smaller than 1, creates an array of size 1, copies the last array into this one, puts a new value in that last empty slot, deletes //the old array, and ups the capacity
//if the capacity is large anough it just increces the size, and just doesn't really //care

intlist.pop_back(); 
//decreaces the size by 1, deleting the last value in the vector
//does not decreace capacity

intlist.begin(); 
//returns a pointer to the first value of the vector
*intlist.begin() = 10; //changes the value of the first element of the vector
//dereference

intlist.erase(intlist.begin()); 
//erases the first value, decreases size by 1,
//shifts everything forward

intlist.erase(intlist.begin() +1); 
//erases the second value, decreases size by 1,
//shifts everything after index 1 forward

intlist.end(); 
//returns a pointer to the memory 1 past the last index of the vector

intlist.insert(intlist.begin+3, 40); 
//puts value 40 at index 3, pushes everything else back, increases size, and allat

sort(intlist.begin(), intlist.end()); 
// sorts the vector from the first element to ther last element. make sure to include <algorithm>

sort(intlist.begin(), intlist.end()-1); 
// sorts the vector from the first elemeny to the second last element, because sort() sorts up to, but not including the second argument passed. make sure to include <algorithm>


```
push_back is costly, so it's a good idea to allocate a certain amount of memory first
```c++
vector<int> intlist(5); //creating an array of size 5
intlist[0] = 5; //same  syntax as arrays

vector<int> intlist(5, 100); // array of 5 ints, each of them have value 100

vector<int> intlist = {1,2,3,4,5}; // array of 5 ints. same syntax as array
```
also, don't make pointers to elements in a vector, cause that shit is always on the move.

vecotrs have size and capacity. size is how many workable spots it has, and capacity is how many spots it can fill before it has to reallocate memory.
the puter pretty much goes "allat memory allocation you're specificly telling me to do?... I ain't doin allat" the computer thinks it's better than you, and allocate's it's own shit cause fuck you, and sets it's own capacity.

```c++
vector<int> intlist(5); 
intlist.reserve(20); //sets the capacity to 20, not the size;
```

a vector is just a nicly packaged array, with more features, but is more expencive,,, like a sequel.


