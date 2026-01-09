writting code with generic data types

## Function Templates

can make a function that works with multiple data types without having to overload


add template <typename T> at the begining of a function signature

when calling a function template add the file tupe you are passing right after the function name. (eg. BubbleSort<int>(values, 5))

when the function is runs it turns the T into whatever data type you told it to use





## class templates //the markdown shit stpped working when I added chevrons 

a class that can have generic type member veriables

to make one just add template <typename T> right above the declaration of the class

if you have methods in the class that call other methods, the object type you pass it has to have that method
to make sure this happens it's good to have a base class that has all the nessisary methods, and only call the template class with objects that inherit from the base class. (base class is usually GameObject)
you can accoplish this by having this line right below the first { of your class:
static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from BaseObject");

when using a class template pass the object type you're using 
(eg.ObjectPool<Asteroid> m_AsteroidPool(20);//but asteroid must inherit from GameObject)


