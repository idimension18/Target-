//
// Created by MPA on 28/09/2021.
//

# include "SDL.h"
# include "Sprite.h"
# include "SDL_image.h"

#ifndef TARGET___ASTEROIDE_H
#define TARGET___ASTEROIDE_H


class Asteroide : public Sprite{
public:
    Asteroide(SDL_Renderer *render, double y, int size, int type, double angle, int sens);
    double x, y, angle, rotationSpeed, rayon, centerX, centerY;
    int size, speedRatio;
    bool toDestroy;
    SDL_Texture *texture;

    void move(); //move

private:
    SDL_Surface *sheet, *temp, *bodyImg;
};


#endif //TARGET___ASTEROIDE_H
