// TowersOfHanoi.cpp
#include "TowersOfHanoi.h"
#include <iostream>

using namespace std;

TowersOfHanoi::TowersOfHanoi(int N) : pegA(N), pegB(N), pegC(N), numDisks(N), moveCount(0) {
    for (int i = N; i >= 1; --i) {
        pegA.push(i);
    }

    // Student Task: Initialize the pegs and place N disks on pegA
    // - Use a loop to push disks numbered from N down to 1 onto pegA.
    // - Each disk should be pushed in decreasing size order.
}

void TowersOfHanoi::solve() {
    displayPegs();
    moveDisks(numDisks, pegA, pegC, pegB);

    // Student Task: Implement the solve function
    // - This function should initiate the solution by calling moveDisks with the correct parameters.
    // - Use 'numDisks' as the number of disks to move.
    // - Move disks from pegA (source) to pegC (target) using pegB (auxiliary).
}

void TowersOfHanoi::moveDisks(int N, Stackt<int>& source, Stackt<int>& target, Stackt<int>& auxiliary) {
    if (N == 1) {
        target.push(source.pop());
        moveCount++;
        displayPegs();
    } else {
        moveDisks(N - 1, source, auxiliary, target);
        target.push(source.pop());
        moveCount++;
        displayPegs();
        moveDisks(N - 1, auxiliary, target, source);
    }
    // Student Task: Implement the moveDisks function
    // - This is a recursive function that moves N disks from the source peg to the target peg using the auxiliary peg.
    // - Base case: If N is 1, move a disk directly from the source to the target.
    // - Recursive case:
    //   1. Move N-1 disks from the source to the auxiliary peg using the target peg.
    //   2. Move the Nth disk from the source to the target peg.
    //   3. Move the N-1 disks from the auxiliary peg to the target peg using the source peg.
    // - After each move, increment moveCount and call displayPegs to show the current state of pegs.
}

void TowersOfHanoi::displayPegs() {
    // This function is implemented for you.
    // It prints the current state of the three pegs (A, B, C).
    cout << "Peg A: ";
    pegA.display();
    cout << "Peg B: ";
    pegB.display();
    cout << "Peg C: ";
    pegC.display();
    cout << "-------------------------" << endl;
}