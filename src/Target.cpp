//
// Created by MPA on 27/09/2021.
//

#include "Target.h"
#include <cstdio>

extern int screenWidth;
extern int screenHeight;
extern int mainSpeed;

Target::Target(SDL_Renderer *render, double y, int diameter, double colorID) :
//-------declaration usuelle-------
x{static_cast<double>(screenWidth)}, y{y}, size{diameter},
value{static_cast<int>(100*(1-((diameter-50.0)/100.0)))},
rayon{diameter/2.0}, toDestroy{false}, outScreen{false},
//---------declaration graphics----------
tempImg{SDL_CreateRGBSurface(0,570, 599, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)},
scaledImg{SDL_CreateRGBSurface(0,diameter, diameter, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)}
{
    //-----------Afectation graphiques------------------------
    if (colorID <= 3)
    {
        tempImg = IMG_Load("../data/images/redTarget.png");
    } else if (colorID > 3 && colorID <= 6)
    {
        tempImg = IMG_Load("../data/images/greenTarget.png");
    } else
    {
        tempImg = IMG_Load("../data/images/yellowTarget.png");
    }
    SDL_Rect scaleRect= {0, 0, diameter, diameter};
    SDL_BlitScaled(tempImg, nullptr, scaledImg, &scaleRect);
    texture = SDL_CreateTextureFromSurface(render, scaledImg);

    //-------------------Affectation usuelle----------------
    Sprite::rayon = rayon;
}

void Target::move() {
    if (x < -size) {
        outScreen = true;
    }
    x-=mainSpeed;

    Sprite::centerX = x + (size/2.0);
    Sprite::centerY = y + (size/2.0);
}
