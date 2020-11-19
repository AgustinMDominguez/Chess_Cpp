#include <stdlib.h>
#include <stdio.h>
#include <set>

/*
Regardless of how they are called and depicted, team1 will be the team that
starts from the bottom of the console and that makes the first move.
*/

class Condition {
public:
    std::set<int> emptyCells; // Signals the board which cells must be empty
    int t1present;  // Signals the board which cells must have a piece of team 1
    int t2present;  // Signals the board which cells must have a piece of team 2
    int t1absent;   // Signals the board which cells must not have a piece of team 1
    int t2absent;   // Signals the board which cells must not have a piece of team 2
    // -1 for non signals
    Condition() : t1present(-1), t2present(-1), t1absent(-1), t2absent(-1) {}
};

class Piece {
protected:
    int firstp;
    int secondp;
    bool teamOne;
public:
    Piece(int f, int s, bool t) : firstp(f), secondp(s), teamOne(t) {}

    bool team() {
        return teamOne;
    }

    virtual int type() =0; // Returns which piece this one is

    virtual Condition move(int ax, int ay, int bx, int by) =0;

    inline bool inbounds(int f, int s) {
        return (f>0 && s>0 && f<8 && s<8);
    }
};

class King : public Piece {
public:
    Condition move(int ax, int ay, int bx, int by) {
        bool possible;
        Condition cond;
        possible = abs(ax-bx)<2 & abs(ay-by)<2;
        if(!possible) {
            cond.t1absent = 10*ax + ay;
            cond.t2absent = cond.t1absent;
        } else if (teamOne) cond.t1absent = 10*bx + by;
        else cond.t2absent = 10*bx + by;
        return cond;
    }
};

class Pawn : public Piece {
public:
    Condition move(int ax, int ay, int bx, int by) {
        Condition cond;
        if(teamOne) {
            if(ax!=bx+1 || abs(ay-by)>1) {
                cond.t1absent = 10*ax + ay;
                cond.t2absent = cond.t1absent;
            } else if (ay==by) cond.emptyCells.insert(10*bx + by);
            else cond.t2present = 10*bx + by;
        } else { // Team 2
            if(ax+1!=bx || abs(ay-by)>1) {
                cond.t1absent = 10*ax + ay;
                cond.t2absent = cond.t1absent;
            } else if (ay==by) cond.emptyCells.insert(10*bx + by);
            else cond.t1present = 10*bx + by;
        }
    }
};


int main() {
    return EXIT_SUCCESS;
}