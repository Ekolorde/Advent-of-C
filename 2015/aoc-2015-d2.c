/* Advent of Code 2015 Day 2: I Was Told There Would Be No Math.
1: Determine how much wrapping paper to order via math:
    - Read a very long file consisting of strings like 10x3x28 and 8x4x11, each on it's own line.
    - Split each line into three integers, somehow.
    - Determine which of those integers is the smallest, add it to a result variable.
    - Add each integer together, then multiply that by 2, add to the result variable.
2: Determine how much ribbon to order via even more math:
    - Do the first two steps of the first part.
    - Add the first two integers to a second result variable twice.
    - multiply all three integers, then add the result of that to the second result variable.
This program requires a file named aoc-2015-d2.txt to function properly, text file must contain 1000 line puzzle input.
If successful, the output should be 1598415 for 1, and 3812909 for 2.
*/
/* Things I need to learn in order to do this:

[x] How to read through a file, line by line.
[x] How to split a line into three parts, while tossing the x's.
[x] How to convert a string into an integer
[ ] why the hell doesn't this work god damn it

Other than that I have a pretty good idea of what I need to do.
I'm just going to write around the stuff I don't know how to do and then come back to that later.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* fptr;
    int paper = 0;
    int ribbon = 0;
    int first, second, third, i, i2;
    int lines = 1000;
    const int buflen = 9;
    char buf[buflen];

    fptr = fopen("aoc-2015-d2.txt", "r");

    for (i = 0; i < lines; i++) {
        fgets(buf, buflen, fptr);
        printf("%s", buf);
        char* token = strtok(buf, "x");
        i2 = 0;
        while (token != NULL) {
            if (i2 == 0) {
                first = atoi(token);
                printf("%d ", first);
            }
            else if (i2 == 1) {
                second = atoi(token);
                printf("%d ", second);
            }
            else if (i2 == 2) {
                third = atoi(token);
                printf("%d\n", third);
            }
            token = strtok(NULL, "x");
            i2 += 1;
        }

        if (first <= second && first <= third) {
            paper += first;
        }
        else if (second <= first && second <= third) {
            paper += second;
        }
        else if (third <= first && third <= second) {
            paper += third;
        }
        paper += first * 2;
        paper += second * 2;
        paper += third * 2;
        printf("%d ", paper);

        ribbon += first * 2;
        ribbon += second * 2;
        ribbon += first * second * third;
        printf("%d\n", ribbon);
    }
    printf("\nPaper: %d\n", paper);
    printf("Ribbon: %d", ribbon);

    return 0;
}
/*
Okay I've actually made an attempt at debugging now and I've found a few issues:

1: My compiler outputs .exe files to a subfolder of where the .c file is stored, while the program assumes the needed txt file will be in the exact same folder as it. That was fixed by temporarily moving the text file.
2: My fgets stops fgetting at line 750 for some reason.
3: (now that the line splitter should be working properly) paper is way too low and ribbon is way too high. Like if it were just that they were both a little too low I'd pin it on the thing stopping at 750, but ribbon is *millions* above the correct answer, and paper is at a hundred thousand when it should be 1.5 million.

I really don't know where the issue is with this thing, but I think it can be blamed on the fact that I have no idea what I'm doing or how half the code in this actually works.

The above no longer applies, I've made a few changes and this seems fully functional outside of the part where it always stops at line 750, which I still have no explanation for. Gonna come back to this thing tomorrow.
*/