#include "Game.h"
#include "Exceptions.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"
namespace Gaming
{
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    Game::Game()
    {
        __width=MIN_WIDTH;
        __height=MIN_HEIGHT;
        __verbose=false;
        __grid.resize(toLinear(Position(__height,__width)));
    }

    Game::Game(unsigned width, unsigned height, bool manual)
    {
        if(width<MIN_WIDTH)
        {
            std::cout<<"Specified width too small, setting to "<<MIN_WIDTH<<std::endl;
            width=MIN_WIDTH;
        }
        if(height<MIN_HEIGHT)
        {
            std::cout<<"Specified height too small, setting to "<<MIN_HEIGHT<<std::endl;
            height=MIN_HEIGHT;
        }
        __width=width;
        __height=height;
        __verbose= false;
        __grid.resize(toLinear(Position(__height,__width)));
        if(!manual)
            populate();

    }

//    Game::Game(const Game &another)
//    {
//        for(auto seeker=another.__grid.begin();seeker!=another.__grid.end();++seeker)
//        {
//            if(*seeker!= nullptr)
//            {
//                *seeker=new Piece(**seeker);
//            }
//        }
//    }

    Game::~Game()
    {
        for(auto seeker=__grid.begin();seeker!=__grid.end();++seeker)
            if(*seeker!= nullptr)
                delete *seeker;
    }

    unsigned int Game::getNumPieces() const
    {
        unsigned int numTargets=0;
        for(auto seeker=__grid.begin();seeker!=__grid.end();++seeker)
        {
            if(*seeker!= nullptr)
                numTargets++;
        }
        return numTargets;
    }

    unsigned int Game::getNumAgents() const
    {
        unsigned int numTargets=0;
        for(auto seeker=__grid.begin();seeker!=__grid.end();++seeker)
        {
            Agent* probe = dynamic_cast<Agent*>(*seeker);
            if(probe!= nullptr)
                numTargets++;
        }
        return numTargets;
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int numTargets=0;
        for(auto seeker=__grid.begin();seeker!=__grid.end();++seeker)
        {
            Agent* probe = dynamic_cast<Simple*>(*seeker);
            if(probe!= nullptr)
                numTargets++;
        }
        return numTargets;
    }

    unsigned int Game::getNumStrategic() const
    {
        unsigned int numTargets=0;
        for(auto seeker=__grid.begin();seeker!=__grid.end();++seeker)
        {
            Agent* probe = dynamic_cast<Strategic*>(*seeker);
            if(probe!= nullptr)
                numTargets++;
        }
        return numTargets;
    }

    unsigned int Game::getNumResources(){
        unsigned int numTargets=0;
        for(auto seeker=__grid.begin();seeker!=__grid.end();++seeker)
        {
            Resource* probe = dynamic_cast<Resource*>(*seeker);
            if(probe!= nullptr)
                numTargets++;
        }
        return numTargets;
    }

    void Game::checkBounds(const Position &position)
    {
        if(position.x<0||position.y<0)
            throw InsufficientDimensionsEx(MIN_WIDTH,MIN_HEIGHT,position.y,position.x);
        if(position.x>=__height||position.y>=__width)
            throw OutOfBoundsEx(__width,__height,position.y,position.x);
    }

    bool Game::addSimple(const Position &position)
    {
        try
        {
            checkBounds(position);
            int linearPos=position.x*__width+position.y;
            if(__grid[linearPos]== nullptr)
            {
                __grid[linearPos]=new Simple(*this,position,STARTING_AGENT_ENERGY);
                return true;
            }
        }
        catch (...){return false;}

        std::cout<<"Error! Position Occupied!"<<std::endl;
        return false;
    }

    bool Game::addSimple(unsigned x, unsigned y)
    {
        Position position(x,y);
        return addSimple(position);
    }

    bool Game::addStrategic(const Position &position, Strategy *s)
    {
        try
        {
            checkBounds(position);
            int linearPos=position.x*__width+position.y;
            if(__grid[linearPos]== nullptr)
            {
                __grid[linearPos]=new Strategic(*this,position,STARTING_AGENT_ENERGY,s);
                return true;
            }
        }
        catch (...){return false;}

        std::cout<<"Error! Position Occupied!"<<std::endl;
        return false;    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        Position position(x,y);
        return addStrategic(position,s);
    }

    bool Game::addFood(const Position &position)
    {
        try
        {
            checkBounds(position);
            int linearPos=position.x*__width+position.y;
            if(__grid[linearPos]== nullptr)
            {
                __grid[linearPos]=new Food(*this,position,STARTING_RESOURCE_CAPACITY);
                return true;
            }
        }
        catch (...){return false;}

        std::cout<<"Error! Position Occupied!"<<std::endl;
        return false;
    }

    bool Game::addFood(unsigned x, unsigned y)
    {
        Position position(x,y);
        return addFood(position);
    }

    bool Game::addAdvantage(const Position &position)
    {
        try
        {
            checkBounds(position);
            int linearPos=position.x*__width+position.y;
            if(__grid[linearPos]== nullptr)
            {
                __grid[linearPos]=new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);
                return true;
            }
        }
        catch (...){return false;}

        std::cout<<"Error! Position Occupied!"<<std::endl;
        return false;
    }

    bool Game::addAdvantage(unsigned x, unsigned y)
    {
        Position position(x,y);
        return addAdvantage(position);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings surroundings;
        Position testSquare;
        for(int x=-1,i=0;x<2;++x)
            for(int y=-1;y<2;++y,++i)
            {
                testSquare.x=pos.x+x;
                testSquare.y=pos.y+y;
                surroundings.array[i]=getSquare(testSquare);
            }
        surroundings.array[4]=SELF;
        return surroundings;
    }

    PieceType Game::getSquare(const Position &position)const
    {
        int linearPos=position.x*__width+position.y;
        if(linearPos<0||linearPos>=__grid.size())
            return INACCESSIBLE;
        if(__grid[linearPos]== nullptr)
            return EMPTY;
        return __grid[linearPos]->getType();
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
        Position diff(to.x-from.x,to.y-from.y);
        if(diff.x==0)
        {
            if(diff.y==0)
                return STAY;
            if(diff.y<0)
                return W;
            return E;
        }
        if(diff.x>0)
        {
            if(diff.y==0)
                return S;
            if(diff.y>0)
                return SW;
            return SE;
        }
        if(diff.y==0)
            return N;
        if(diff.y>0)
            return NW;
        return NE;
    }

    bool Game::isLegal(const ActionType &ac, const Position &position) const
    {
        Position pos=position;
        if(ac==NW||ac==N||ac==NE)
            --pos.x;
        else if(ac==SW||ac==S||ac==SE)
            ++pos.x;
        if(ac==NW||ac==W||ac==SW)
            --pos.y;
        else if(ac==NE||ac==E||ac==SE)
            ++pos.y;
        return pos.x > 0 && pos.y > 0 && pos.x < __height && pos.y > __width;
    }

    const Position Game::move(const Position &position, const ActionType &ac) const
    {
        Position pos=position;
        if(ac==NW||ac==N||ac==NE)
            --pos.x;
        else if(ac==SW||ac==S||ac==SE)
            ++pos.x;
        if(ac==NW||ac==W||ac==SW)
            --pos.y;
        else if(ac==NE||ac==E||ac==SE)
            ++pos.y;
        return pos;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        os<<"Round "<<game.getRound()<<std::endl;
        for(int x=0;x<game.getHeight();++x)
        {
            for (int y = 0; y < game.getWidth(); ++y)
            {
                unsigned int lp = x * game.getWidth() + y;
                os << "[";
                if(game.__grid[lp]!= nullptr)
                    os<<std::setw(5)<<*game.__grid[lp];
                else
                    os<<"     ";
                os<<"]";
            }
            os<<std::endl;
        }
        os<<"Status: "<<game.__status<<std::endl;
        return os;
    }


    void Game::populate()
    {
        std::default_random_engine gen;
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFood = __numInitResources - numAdvantages;

        for(int i =0; i < numStrategic; ++i)
        {
            unsigned int x = gen() % __height;
            unsigned int y = gen() % __height;
            while (__grid[x * __width + y] != nullptr)
            {
                x = gen() % __height;
                y = gen() % __height;
            }
            addStrategic(x,y);
        }

        for(int i =0; i < numSimple; ++i)
        {
            unsigned int x = gen() % __height;
            unsigned int y = gen() % __height;
            while (__grid[x * __width + y] != nullptr)
            {
                x = gen() % __height;
                y = gen() % __height;
            }
            addSimple(x,y);
        }

        for(int i =0; i < numAdvantages; ++i)
        {
            unsigned int x = gen() % __height;
            unsigned int y = gen() % __height;
            while (__grid[x * __width + y] != nullptr)
            {
                x = gen() % __height;
                y = gen() % __height;
            }
            addAdvantage(x,y);
        }

        for(int i =0; i < numFood; ++i)
        {
            unsigned int x = gen() % __height;
            unsigned int y = gen() % __height;
            while (__grid[x * __width + y] != nullptr)
            {
                x = gen() % __height;
                y = gen() % __height;
            }
            addFood(x,y);
        }
    }

    void Game::round()
    {
        for(int i=0;i<__grid.size();++i)
        {
            if(__grid[i]!= nullptr&&!__grid[i]->getTurned())
            {
                Position currPos(i/__width,i%__width);
                ActionType action =__grid[i]->takeTurn(getSurroundings(currPos));
                __grid[i]->setTurned(true);
                unsigned int newPos=toLinear(move(currPos,action));
                if(action!=STAY&&isLegal(action, currPos))
                {
                    Piece* temp= nullptr;
                    if(__grid[newPos]!= nullptr)
                    {
                        temp = &(__grid[i]->operator*(*__grid[newPos]));
                        if(__grid[newPos]->isFinished())
                        {
                            delete __grid[newPos];
                            __grid[newPos]= nullptr;
                            if(!__grid[i]->isFinished())
                            {
                                __grid[newPos]=temp;
                            }
                        }
                        if(__grid[i]->isFinished())
                        {
                            delete __grid[i];
                            __grid[i]= nullptr;
                        }

                    }
                    else
                    {
                        __grid[newPos]=__grid[i];
                        __grid[i]= nullptr;
                    }
                }
            }
            if(__verbose)
                std::cout<<*this;
        }
        ++__round;
    }

    unsigned int Game::toLinear(const Position &bi)
    {
        return (bi.x*__width+bi.y);
    }

    Position Game::toPosition(unsigned int lin)
    {
        return Position(lin/__width,lin%__width);
    }

    void Game::play(bool verbose)
    {
        __verbose=verbose;
        while(__round<50)
        {
            round();
        }
    }
}