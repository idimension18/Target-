//
// Created by MPA on 28/09/2021.
//

#include "Asteroide.h"
# include <cstdio>

extern int screenWidth;
extern int screenHeight;
extern int mainSpeed;

Asteroide::Asteroide(SDL_Renderer *render,double y, int size, int type, double angle, int sens) :
//---------Declaration usuelle-------------
x{static_cast<double>(screenWidth)}, y{y}, size{size}, angle{angle}, rayon{size/2.0}, speedRatio{60},
rotationSpeed{sens == 0 ? speedRatio/rayon : -speedRatio/rayon}, toDestroy{false},
//---------Declaration graphiques---------------
sheet{IMG_Load("../data/images/asteroide.png")},
temp{SDL_CreateRGBSurface(0,128, 128, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)},
bodyImg{SDL_CreateRGBSurface(0,size, size, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)}
{
    //----------------Afectation graphic-------------------
    SDL_GetRendererOutputSize(render, &screenWidth, &screenHeight);
    SDL_Rect cutRect = {0, 0, 0, 0};
    SDL_Rect scaleRect = {0, 0, size, size};
    if (type == 0) {
        cutRect = {0, 0, 128, 128};
    } else if (type == 1) {
        cutRect = {128, 0, 128, 128};
    } else if (type == 2) {
        cutRect = {0, 128, 128, 128};
    } else {
        cutRect = {128, 128, 128, 128};
    }
    SDL_BlitSurface(sheet, &cutRect, temp, nullptr);
    SDL_BlitScaled(temp, nullptr, bodyImg, &scaleRect);
    texture = SDL_CreateTextureFromSurface(render, bodyImg);
    //---------------affectaton usuelles---------------
    Sprite::rayon = rayon;
    Sprite::centerX = x + (size/2.0);
    Sprite::centerY = y + (size/2.0);
}

void Asteroide::move() {
    toDestroy = x < -size;
    angle += rotationSpeed;
    if (angle >= 360) {
        angle -= 360;
    }
    x -= mainSpeed;

    Sprite::centerX = x + (size/2.0);
    Sprite::centerY = y + (size/2.0);

}