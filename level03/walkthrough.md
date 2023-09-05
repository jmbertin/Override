### Download binary
``scp -P4242 level03@192.168.31.33:/home/users/level03/level03 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

---

### Main function analysis (refer to source code)

By analyzing the source code we see that our goal is to enter a specific condition :

 `if (strncmp(encryptedStr, expectedStr, 17) == 0)`
 `system("/bin/sh");`

We will provide a number, and this number need to pass 2 test for us to get our bash.
First, 322424845 - our number need to be <= 21 so our number need to be < 322424835.
Then the result of this substraction must be the key to transform the string.

**"Q}|u`sfg~sf{}|a3"** to **"Congratulations!"**

We see that the code that use our key to decrypt the string is just a simple xor:

`encryptedStr[idx] = key ^ encryptedStr[idx];`

A reminder of xor truth table :

````
0 0 |    0
0 1 |    1
1 0 |    1
1 1 |    0
````

We can then take the binary representation of the first character of each string :

````
Q = ASCII : 81 = Binaire :	1010001
C = ASCII : 67 = Binaire :	1000011
XOR COMPARAISON			0010010
````

``0010010 = 18``

Our key must be equal to **18**, so our password must be equal to 322424845 - 18
-> **322424827**

----

### Bypassing security

``level03@OverRide:~$ ./level03``
>Password:**322424827**

``$ whoami``
>level04

``cat /home/users/level04/.pass``
>kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
