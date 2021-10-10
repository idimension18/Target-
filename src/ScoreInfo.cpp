//
// Created by idime on 10/10/2021.
//

#include <string>
#include "ScoreInfo.h"


ScoreInfo::ScoreInfo(SDL_Renderer* render,double x,double y,int value) :
x{x}, y{y}, velocityY{10}, isEnd{false}, timer{0}
{
    //---------------declaration graphiques---------------------
    TTF_Font* font = TTF_OpenFont("../data/fonts/m5x7.ttf", 27);
    SDL_Color white{0,255,0};
    surface = TTF_RenderText_Solid(font, std::to_string(value).c_str(), white);
    printf(SDL_GetError());
    texture = SDL_CreateTextureFromSurface(render, surface);
}

void ScoreInfo::update() {
    timer +=1;
    if (timer < 120) {
        y -= velocityY;
        velocityY /= 1.5;
    } else {
        isEnd = true;
    }
}

