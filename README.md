# Memory-Management


Christopher Ta      |       CPSC 351-01       |       cta002@csu.fullerton.edu

Gilbert Paderogo    |       CPSC 351-01       |       gspaderogo@csu.fullerton.edu

Bryan Cuevas        |       CPSC 351-01       |       bcuevas8@csu.fullerton.edu

Sean Yu             |       CPSC 351-01       |       sean.yu@csu.fullerton.edu


Programming Language: C++

Operating System: Linux

NO EXTRA CREDIT

Main Files:

    •   main.cpp

    •   frame.h

    •   process.h

    •   memory_manager.h

    •   Makefile

How to run the project:

    1. In your Memory-Management directory open a terminal.
        NOTE: Make sure you are in the appropropriate directory when operning the terminal. ../Memory-Management

    1a. (Optional) Before you continue, look into the Memory-Management
    directory and see if there are existing mm.o and mm.
        If those files exist in the directory, delete those files or type "make clean" in to the terminal and press ENTER.
        If those files do not exist in the directory, continue to step 2.

    2. Type: 
    
        make

        into the terminal and press ENTER. This compiles the main.cpp

    3. Type:

        ./mm

        into the terminal and press ENTER. This will run the Memory Management program.

    4. Terminal will prompt you to enter a Physical(Main) Memory Size.
        NOTE: Program will only work if value entered is a multiple of
        100, 200, or 400.
    Once input is entered press ENTER to proceed.

    5. Terminal will prompt you to enter a Page Size. Options are:

    •   1   (100)

    •   2   (200)

    •   3   (400)

    After inputting 1, 2, or 3, press ENTER to continue.

    6. Terminal will prompt you to enter an input file.
    (Default input file is "in1.txt" without quotes.)
    Once input is entered press ENTER to proceed.

    7. Output will show the following occurring at specific times:

    •   Process Arrival

    •   Input Queue containing processes

    •   Memory Manager moving process to Main Memory

    •   Display of Memory Map and Frames

    7a. Once all of the processes executed completely. The terminal will
    display:

    •   Each processes' turnaround time

    •   The average turnaround time of all the processes

Test Run Sreenshot:

[![Screen-Shot-2019-12-02-at-9-57-53-PM.png](https://i.postimg.cc/6q4GzQr0/Screen-Shot-2019-12-02-at-9-57-53-PM.png)](https://postimg.cc/bS8JwpFD)

Team Collaborators

    Christopher Ta: Coding, Testing, How-To-Run Documentation, Documentation editing and review

    Gilbert Paderogo: Data Flow Documentation, Testing 

    Bryan Cuevas: Glossary Definitions Documentation, Testing

    Sean Yu: Step Process Documentation (Trace), Testing