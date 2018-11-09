# Lab Memory: Malevolent Memories

> Due: Sunday, February 4 at 11:59 PM


## Assignment Description

In this lab, you will learn about two memory checking utilities: **Valgrind** and **AddressSanitizer** (aka ASAN).

The first utility you will learn about is Valgrind. Valgrind will help you detect memory errors and practice implementing the big three. Valgrind is an extremely useful tool for debugging memory problems and for fixing segfaults or other crashes. This lab is also particularly important because we will be checking for memory errors and leaks on your assignments. You will lose points for memory leaks and/or memory errors (we will also teach you the difference between a memory leak and a memory error). You should check your code with Valgrind/ASAN before handing it in. You should also be aware that Valgrind/ASAN will only detect a leak if your program allocates memory and then fails to deallocate it. It cannot find a leak unless the code containing the leak is executed when the program runs. Thus, you should be sure to test your code thoroughly and check these tests with Valgrind/ASAN.

```
$ valgrind ./test
==24734== Memcheck, a memory error detector
==24734== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==24734== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==24734== Command: ./test
==24734==
===============================================================================
===============================================================================
You may want to run these test cases in valgrind!
valgrind --leak-check=full ./test
OR:
valgrind --leak-check=full ./test "[valgrind]"
===============================================================================
===============================================================================

===============================================================================
All tests passed (10 assertions in 5 test cases)

==24734==
==24734== HEAP SUMMARY:
==24734==     in use at exit: 0 bytes in 0 blocks
==24734==   total heap usage: 4,935 allocs, 4,935 frees, 511,192 bytes allocated
==24734==
==24734== All heap blocks were freed -- no leaks are possible
==24734==
==24734== For counts of detected and suppressed errors, rerun with: -v
==24734== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
