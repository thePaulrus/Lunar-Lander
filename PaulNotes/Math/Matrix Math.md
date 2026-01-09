don't touch w for now.
0001 means the object can be translated
0000 means the object cannot be translated
pretty sure the first 3 ALWAYS have to be 0s

identity matrix // equivalent of multiplying a matrix by one
|1000|   |x|   |x|
|0100|   |y|   |y|
|    | * | | = | |
|0010|   |z|   |z|
|0001|   |w|   |w|

scaling // diagonal
|2000|   |x|   |2x|
|0400|   |y|   |4y|
|    | * | | = |  |
|0070|   |z|   |7z|
|0001|   |w|   |w |

translation // right coloumn
|0008|   |x|   |x+8|
|0006|   |y|   |y+6|
|    | * | | = |   |
|0003|   |z|   |z+3|
|0001|   |w|   |w+1|//but the end result of w doesn't matter

scaling and translation
|1004|   |x|   |1x+4|
|0205|   |y|   |2y+5|
|    | * | | = |    |
|0036|   |z|   |3z+6|
|0001|   |w|   |w+1 |//but the end result of w doesn't matter


dot product
