#include "Level0.h"

Level0::Level0(){}

Level0::~Level0(){}

Level0 *Level0::createGame(int difficulty)
{
    auto layer =new Level0();
    if(layer && layer->initWithDifficulty(difficulty)){
        layer->autorelease();
        return layer;
    }
    return nullptr;
}

bool Level0::initWithDifficulty(int difficulty)
{
     difficulty_ = difficulty;
     setLevel(0);
     initMap();
    return true;
}
