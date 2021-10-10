//
// Created by MPA on 27/09/2021.
//

# include "SDL.h"
#include "Sprite.h"
# include "SDL_image.h"

#ifndef TARGET___TARGET_H
#define TARGET___TARGET_H

class Target : public Sprite {
public:
    Target(SDL_Renderer *render, double y, int diameter, double colorID); //
    int size, value;
    double x, y, rayon;
    bool toDestroy, outScreen;
    SDL_Texture *texture;

    void move();

private:
    SDL_Surface *tempImg, *scaledImg;
};


#endif //TARGET___TARGET_H
