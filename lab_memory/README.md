# Lab Memory: Malevolent Memories

> Due: Sunday, February 4 at 11:59 PM


## Assignment Description

In this lab, you will learn about two memory checking utilities: **Valgrind** and **AddressSanitizer** (aka ASAN).

The first utility you will learn about is Valgrind. Valgrind will help you detect memory errors and practice implementing the big three. Valgrind is an extremely useful tool for debugging memory problems and for fixing segfaults or other crashes. This lab is also particularly important because we will be checking for memory errors and leaks on your assignments. You will lose points for memory leaks and/or memory errors (we will also teach you the difference between a memory leak and a memory error). You should check your code with Valgrind/ASAN before handing it in. You should also be aware that Valgrind/ASAN will only detect a leak if your program allocates memory and then fails to deallocate it. It cannot find a leak unless the code containing the leak is executed when the program runs. Thus, you should be sure to test your code thoroughly and check these tests with Valgrind/ASAN.
