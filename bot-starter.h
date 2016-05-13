// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __BOT_STARTER_H
#define __BOT_STARTER_H

#include <cstdlib>
#include <vector>

#include "bot-state.h"
#include "move.h"
#include "FinalPositionFinder.h"

using namespace std;

/**
 * This class is where the main logic should be. Implement getMoves() to
 * return something better than random moves.
 */
class BotStarter {

private:

    int d = 8;


public:

    /**
     * Returns a random amount of random moves
     * @param state : current state of the bot
     * @param timeout : time to respond
     * @return : a list of moves to execute
     */
    vector<Move::MoveType> GetMoves(BotState &state,
                                    long long timeout) {

        int* positionAndOrt;
        positionAndOrt=state.getDecidedPosition();
        int lastPos = positionAndOrt[0];
        int rotation = positionAndOrt[1];
        int thisPiecePosition = (*(state.getThisPiecePosition()));
        int x = lastPos - thisPiecePosition;
        vector<Move::MoveType> moves;
        moves.empty();
        switch (rotation) {
            case 1:
                moves.push_back(Move::MoveType::TURNRIGHT);
                break;
            case 2:
                moves.push_back(Move::MoveType::TURNRIGHT);
                moves.push_back(Move::MoveType::TURNRIGHT);
                break;
            case 3:
                moves.push_back(Move::MoveType::TURNLEFT);
                break;
        }
        if (x > 0) {
            for (; x > 0; x--) {
                moves.push_back(Move::MoveType::RIGHT);
            }
        }
        if (x < 0) {
            for (; x < 0; x++) {
                moves.push_back(Move::MoveType::LEFT);
            }
        }

        moves.push_back(Move::MoveType::DROP);

        return moves;
    }


};


#endif  //__BOT_STARTER_H
