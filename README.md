#A* Algorithm
_I did this project as a small challenge, to get back into C++ and implement a fairly common yet not trivial algorithm. You're free to use it for whatever purpose that you might have._

Small implementation of A* in C++.

##Compile / run
Just type inside the main folder:
>make && ./build/main

## Output explanation
We're creating 4 {Node} such that
 
     /--4-> B --1-\
    A              |-> D
     \--5-> C --1-/
 
Those points have coordinates (X, Y):
A = (1, 1)
B = (2, 2)
C = (2, 0)
D = (4, 1)

So here the shortest path would be A -> B -> D (considering costs and distance), so the output should be

    1 1
    2 2
    4 1