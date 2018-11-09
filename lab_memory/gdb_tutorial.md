# GDB (GDB Resources)

## Getting Started with GDB

To launch your program using gdb, run the following command:

```
gdb [program name]
```

To run your program with optional command line arguments:

```
(gdb) run [arguments]
```

Alternatively, you can do this in one line with the following command:

```
gdb --args ./program_name [optional] [args] [here]
```

This allows you to simply type

```
(gdb) run
```

to start your program.

## Note

Throughout the lab, we'll use the notation

```
(gdb) command...
```

to indicate that the command should be run from within GDB.

## Tip

GDB will provide several helpful features. First, it will output similar debugging information as Valgrind upon errors such as segmentation faults. Second, and more important, it allows you to stop the program execution, move around, and view the state of the running program at any point in time.

To do that, we will use the following common commands (see more details in the slides). We’ll also define the abbreviations of these commands, so you don’t have to type the full names of these commands when you want to use them.

- **Walking through your code.**
    - `break [file:line number]`
        - Example usage: `break skipList.cpp:40`
        - Create a breakpoint at the specified line. This will stop the program’s execution when it is being ran. (See `run`).
        - When your program is stopped (by a previous use of `break`) in a certain file, `break n` will create a breakpoint at line `n` in that same file.
        - Note: There are other variations on how to use `break` here. One variation is breaking at a function belonging to a class. *Example*: `break SkipList::insert`.
        - Abbreviation: `b`. Example usage: `b skipList.cpp:40`
    - `clear [file:line number]`
        - Removes a breakpoint designated by `break`.
    - `run (arguments)`
        - Runs the program, starting from the main function.
        - Abbreviation: `r`.
    - `list`
        - Shows the next few lines where the program is stopped.
    - `layout src`
        - Shows an updating window with your source code and the current line of execution.
        - Usually easier than type `list` every line or referring back to your open code
    - `next`
        - Continues to the next line executed. This does not enter any functions. (See step for this).
        - Abbreviation: `n`.
    - `step`
        - Continues to the next line executed. Unlike `next`, this will step into any proceeding functions
        - Abbreviation: `s`.
    - `finish`
        - Steps out of a function.
        - Abbreviation: `fin`.
    - `continue`
        - Continues the execution of the program after it's already started to run. `continue` is usually used after you hit a breakpoint.
        - Abbreviation: `c`.
- **Viewing the state of your code.**
    - `info args`
        - Shows the current arguments to the function.
        - If you are stopped within a class's function, the this variable will appear.
    - `info locals`
        - Shows the local variables in the current function.
    - `print [variable]`
        - Prints the value of a variable or expression. *Example*: `print foo(5)`
        - The functionality of print is usually superseded by `info locals` if you are looking to print local variables. But if you want to view object member variables, `print` is the way to go.
        - *Example*: `print list->head`. Or `print *integer_ptr`.
        - Abbreviation: `p`.
    - [backtrace](ftp://ftp.gnu.org/old-gnu/Manuals/gdb/html_node/gdb_42.html)
        - Shows the call stack of your program
        - The list of which function has called the function you are in, recursively
    - [frame [n]](https://sourceware.org/gdb/onlinedocs/gdb/Frames.html)
        - Used to go to the frame numbers as seen in backtrace
- **Other useful commands.**
    - `ctrl-l` (clears the screen)
    - `ctrl-a` (moves cursor to beginning of prompt)
    - `ctrl-e` (moves cursor to end of prompt)
