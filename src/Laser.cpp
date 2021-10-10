//
// Created by MPA on 26/09/2021.
//

# include <cstdio>

#include "Laser.h"

extern int screenWidth;
extern int screenHeight;

Laser::Laser(SDL_Renderer *render, double x, double y, int angle) :
//-------declaration usuelle-------
x{x}, y{y}, width{50}, height{13}, angle{angle}, speed{10},
toDestroy{false},
//----------declaration graphic--------
laserImg{IMG_Load("../data/images/laser.png")}
{
    //------affectation graphic----------
    SDL_GetRendererOutputSize(render, &screenWidth, &screenHeight);
    texture = SDL_CreateTextureFromSurface(render, laserImg);
    //---------Affectation ussuelle----------
    Sprite::rayon = 0;
}
//lance le laser
void Laser::go()
{
    x += cos(angle * (M_PI/180)) * speed;
    y += sin(angle * (M_PI/180)) * speed;

    Sprite::centerX = (x + width/2.0) + cos(angle * (M_PI/180))*(width/2.0);
    Sprite::centerY = (y + height/2.0) + sin(angle * (M_PI/180))*(height/2.0);

}

void Laser::overScreen()
{
    if (x > screenWidth || x < 0 || y > screenHeight || y < 0) {
        toDestroy = true;
    }
}