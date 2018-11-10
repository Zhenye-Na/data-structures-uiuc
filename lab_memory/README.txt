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