### Download binary
``scp -P4242 level06@192.168.31.33:/home/users/level06/level06 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (refer to source code)

Upon inspection, it is evident that the program prompts for a login, then a serial number. The program then performs calculations on the provided login to derive an expected serial number. It subsequently compares the user-provided serial number with the derived one. If they match, it executes **system("/bin/sh");**, providing the user with a shell.

----

### Create a keygen

To automate the process of obtaining valid serial numbers, we isolate the section of the code responsible for encoding the login into its verification serial. We then craft a keygen based on this logic (see resources/keygen.c).

All that's left is to compile our keygen:

``gcc /tmp/keygen.c -std=c99 -o /tmp/keygen``

----

### Bypassing security

W launch our keygen, with the username we want :

``./keygen jbertin``
>Serial for jbertin is: 6233795


``level06@OverRide:~$ ./level06``

>-> Enter Login: **jbertin**
>     NEW ACCOUNT DETECTED
>-> Enter Serial: **6233795**   
>Authenticated!

``$ cat /home/users/level07/.pass``
>GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
