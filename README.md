# Boolean Minimization
Simplifying boolean function is one of the basics in digital electronics. Quinine McClunskey also known as tabulation method helps to minimize booleans with large number of variables, where the number of variables acts as a limitation in K-map. This method helps in simplifying. 


## Output

Enter the number of variables:
4Enter the minterms(RANGE=0-15) separated by comma:
0,1,2,6,7,8,9,10,14,15
0000
0001
0010
1000
0110
1001
1010
0111
1110
1111

000- 0000 0001
00-0 0000 0010
-000 0000 1000
-------------------------------
-001 0001 1001
0-10 0010 0110
-010 0010 1010
100- 1000 1001
10-0 1000 1010
-------------------------------
011- 0110 0111
-110 0110 1110
1-10 1010 1110
-------------------------------
-111 0111 1111
111- 1110 1111
-------------------------------

-00- 000- 100-
-0-0 00-0 10-0
-------------------------------
--10 0-10 1-10
-------------------------------
-11- 011- 111-
-------------------------------

-00-    unchecked
-0-0    unchecked
--10    unchecked
-11-    unchecked

The reduced boolean expression in SOP form before table reduced:
b'c'+b'd'+cd'+bc

        b'c'    b'd'    cd'     bc
0       x       x
1       x
2               x       x
8       x       x
6                       x       x
9       x
10              x       x        
7                               x
14                      x       x
15                              x

b'd'+b'c'+bc
Would you like to enter another expression? (y/n)
