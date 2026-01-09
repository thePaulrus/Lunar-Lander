allows pointers to sub-class objects using the type of the parent class.

though you can't use anything from the subclass, and if you try to use a function that exists in both the sub class and the parent class, it will only use the one in the parent class.

but you can put the word "virtual" in front of the method in the parent class you can use that method from the sub class instead.

while not nessesary, you can also write "override" at the end of the method in the sub class... just cause it's safe or something.

if there is a method that all sub classes have, but the parent class would have no use for it you can just set the method equal to 0 in the parent class.