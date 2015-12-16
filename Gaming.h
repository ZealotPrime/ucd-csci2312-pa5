//
// Created by Ivo Georgiev on 11/22/15.
//

#ifndef PA5GAME_GAMING_H
#define PA5GAME_GAMING_H

#include <array>
#include <random>
#include <vector>
#include "Advantage.h"

namespace Gaming {

    // matrix convention: x indexes rows from top to bottom, y column from left to right
    struct Position {
        unsigned int x, y;
        Position() {}
        Position(unsigned int x, unsigned int y) : x(x), y(y) {}
    };

    // actions are either a motion in one of 8 directions or staying in place
    enum ActionType { NW=0, N, NE, W, STAY, E, SW, S, SE };

    // what a position on the game grid can be filled with
    enum PieceType {AGENT=0, SIMPLE, STRATEGIC,RESOURCE, FOOD, ADVANTAGE, INACCESSIBLE, SELF, EMPTY };

    // a "map" of the 8 squares adjacent to a piece
    struct Surroundings {
        // encoded as an array/vector top-left row-wise bottom-right
        // [0][1][2]
        // [3][4][5]
        // [6][7][8]
        // the piece is always at 1x1 (4(SELF))
        std::array<PieceType, 9> array;

        ActionType getMove(PieceType)const;

    };

    ActionType Surroundings::getMove(PieceType objective)const
    {
        std::vector<int> targets;
        bool special=false;
        int count=1;
        if(objective==RESOURCE||objective==AGENT)
        {
            special=true;
            count=2;
        }
        for(int y=0;y<count;++y)
        {
            if(special)
                ++objective;
            for(int x=0;x<9;++x)
            {
                if(array[x]==objective)
                {
                    targets.push_back(x);
                }
            }
        }
        if(!targets.empty())
        {
            Position destination=PositionRandomizer()(targets);
            return static_cast<ActionType>(destination.x+destination.y*3);
        }
        return STAY;
    }



    class PositionRandomizer {
        std::default_random_engine __gen;
        std::uniform_int_distribution<int> *__dist[10];
    public:
        PositionRandomizer() {
            for (int i = 0; i < 10; i++)
                __dist[i] = new std::uniform_int_distribution<int>(0, i);
        }
        ~PositionRandomizer() {
            for (int i = 0; i < 10; i++) delete __dist[i];
        }
        const Position operator()(const std::vector<int> &positionIndices) { // TODO EmptyPosVectorEx
            int posIndex = (*__dist[positionIndices.size() - 1])(__gen);
            return Position(
                    (unsigned) (positionIndices[posIndex] / 3),
                    (unsigned) (positionIndices[posIndex] % 3));
        }
    };


}

#endif // PA5GAME_GAMING_H
