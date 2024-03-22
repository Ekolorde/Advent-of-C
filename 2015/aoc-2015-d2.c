/* Advent of Code 2015 Day 2: I Was Told There Would Be No Math.
Link: https://adventofcode.com/2015/day/2
1: Determine how much wrapping paper to order via math:
    - Read a 1000 line file consisting of strings like 10x3x28 and 8x4x11, each on its own line.
    - Split each line into three integers.
    - Determine which of those integers is the smallest, add it to a result variable called paper.
    - Add the results of (l*w + w*h + h*l)*2 to paper.
2: Determine how much ribbon to order via even more math:
    - Do the first two steps of the first part.
    - Add the smallest two integers to a result variable called ribbon twice.
    - multiply all three integers, then add the result of that to ribbon.
This program requires a file named aoc-2015-d2.txt to function properly, text file must contain 1000 line puzzle input.
If successful, using included input file, the output should be 1598415 for 1, and 3812909 for 2.
Functional when compiled with tdm-gcc using the C/C++ Compile Run extension for Visual Studio Code as of March 22, 2024.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* fptr;
    int paper = 0;
    int ribbon = 0;
    int l, w, h, i, i2;
    int lines = 1000; // Set this number to the number of lines in your input file if it's different for some reason.
    const int buflen = 15;
    char buf[15];

    fptr = fopen("aoc-2015-d2.txt", "r");

    for (i = 0; i < lines; i += 1) {
        fgets(buf, buflen, fptr);
        //printf("%d %s", i, buf); // This is just here for debugging, everything works now but I'm keeping it because it looks neat when it's uncommented.
        char* token = strtok(buf, "x");
        i2 = 0;
        while (token != NULL) {
            if (i2 == 0) {
                l = atoi(token);
            }
            else if (i2 == 1) {
                w = atoi(token);
            }
            else if (i2 == 2) {
                h = atoi(token);
            }
            token = strtok(NULL, "x");
            i2 += 1;
        }

        //  Add smallest number to paper. Multiply each number by 2, add to paper.
        if ((l * w) <= (w * h) && (l * w) <= (h * l)) {
            paper += l * w;
        }
        else if ((w * h) <= (l * w) && (w * h) <= (h * l)) {
            paper += w * h;
        }
        else if ((h * l) <= (l * w) && (h * l) <= (w * h)) {
            paper += h * l;
        }
        paper += 2 * l * w;
        paper += 2 * w * h;
        paper += 2 * h * l;

        // To ribbon: Add two smallest numbers twice, add the result of multiplying all three numbers.
        // This is a whole lot of repetitive code for something like this but I don't know how to do it differently yet.
        if (l <= w && l <= h) {
            ribbon += l * 2;
            if (w <= h) {
                ribbon += w * 2;
            }
            else {
                ribbon += h * 2;
            }
        }
        else if (w <= l && w <= h) {
            ribbon += w * 2;
            if (l <= h) {
                ribbon += l * 2;
            }
            else {
                ribbon += h * 2;
            }
        }
        else {
            ribbon += h * 2;
            if (w <= l) {
                ribbon += w * 2;
            }
            else {
                ribbon += l * 2;
            }
        }
        ribbon += l * w * h;
    }
    printf("\nPaper: %d\n", paper);
    printf("Ribbon: %d", ribbon);

    fclose(fptr);
    return 0;
}
/* How this works and what I learned:
1: Include stdio.h, stdlib.h, and string.h. stdio for printf and file reading, stdlib for atoi, and string.h for strtok.
2: Declare int main. That's gonna happen every time so I'm gonna stop mentioning it after this.
3: Set a whole ton of variables:
    - FILE* fptr is required to do anything with files it seems.
    - int paper and int ribbon to keep track of final puzzle answers.
    - ints l, w, and h to keep track of the three numbers on each line of the input file.
    - ints i and i2 for looping purposes.
    - int lines to store the length of the input in lines and stop the main loop once it reaches that point.
    - const int buflen because it's required for fgets, to set a limit to the next thing.
    - char buf[15] to store the current line of the input file.
        - I spent ~2 days trying and failing to get this thing to work, the entire time it seems the problem was that the buffer was too small. (It was at 9, which I thought was the longest one of the input lines could be) So apparently giving your buffer some extra room is necessary.
4: fopen the input file in "r" mode. "rb" apparently also works fine, even though the input is a .txt file.
    - As I was writing this I started freaking out a bit because despite having not changed anything the whole program stopped working right. The issue was that the input file was in the wrong folder. ALWAYS put the input file in the same folder or it doesn't work at all. I keep forgetting that.
5: Run a for loop that runs once for every line of the input file.
    5.1: Run fgets(buf, buflen, fptr) to get the next input line.
    Bonus thing: Uncomment that printf line and it'll print the contents of each line alongside the appropriate line number (minus one)
    5.2: I admit I don't entirely understand how this bit works, but this uses strtok to split the input line into three pieces, discarding the xs.
    5.3: Set i2 to 0, resetting it every time the for loop runs.
    5.4: Run a while loop that runs through the output of strtok until it hits NULL.
        5.4.1: Convert the three strings strtok outputs into integers, assigning them to the appropriate variables, through a lot of ifs and atoi.
            - So i2 is always going to be either 0, 1 or 2, corresponding to the 3 output strings of strtok.
            - Depending on which of those three numbers i2 is at the moment, this sets the corresponding variable to the corresponding string.
        5.4.2: Move to the next output string of strtok.
        5.4.3: Increase i2 by 1.
    5.5: Do a whole lot of math (already explained at the top of file and the top of the relevant section of code) using a whole bunch of repetitive if statements and math operators and such.
        - Reminder to always make sure you *know* what the puzzle is asking you to do. When I first wrote all the math stuff I had entirely the wrong idea in that regard, and ended up needing to rewrite the thing entirely once I finally got the file reading part to work.
        - This also got me to learn how to search + replace stuff in VSCode, because originally I had been calling l w and h first second and third respectively, which took up a lot more space.
6: Print the result variables paper and ribbon.
    - The printf for paper starts with a newline character. This is only really needed if you have the printf I mentioned earlier that prints the contents of each line uncommented, otherwise it's not needed.
7: Close the input file.
8: Return 0 to tell anything using this that it was successful.
*/