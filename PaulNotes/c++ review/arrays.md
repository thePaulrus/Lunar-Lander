#containter
```
int numbers[8];
```

```c++
const int C_size = 8;
int numbers[c_size];

numbers[0] = 5;
numbers[7] = 10;
//no numbers[8]
```

# pass array to function
```c++
int sumUpArray(int[] array, int size)
{
	int sum = 0;
	for(int i= 0; i < size; i++){
		sum += array[i];
	}
	return sum;
}

int sum = sumUpArray(numbers[], c_size);
```