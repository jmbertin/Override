### Download binary
``scp -P4242 level00@192.168.31.33:/home/users/level00/level00 ~/Bureau/``

### Decompile binary

1. To ASM
``gdb -batch -q -ex 'file level00' -ex 'disassemble main' > main.asm``
2. Or with Ghidra

---

### Main function analysis (refer to source code)

1 - User input for the variable **local_14** :
``scanf("%d", &local_14);``

2 - Condition -> if the first value of **local_14** array is different from 5276:
````
if (local_14[0] != 5276)
	puts("\nInvalid Password!");
else
	system("/bin/sh");
````

----

### Bypassing security

````
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276
````

>Authenticated!

``$ cat /home/users/level01/.pass``
>uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL

