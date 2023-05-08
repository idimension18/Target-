//
// Created by MPA on 26/09/2021.
//

#ifndef TARGET___LASER_H
#define TARGET___LASER_H
# include <SDL2/SDL.h>
# include "Sprite.h"
# include "SDL_image.h"

class Laser : public Sprite {
public:
    Laser(SDL_Renderer *render, double x, double y, int angle);
    SDL_Texture *texture;
    int width, height, angle;
    double x, y;
    bool toDestroy;

    void go(); //lance le laser
    void overScreen();
    //detruit le laser en dehors de l'ecrans

private:
    SDL_Surface *laserImg;
    double speed;
};


#endif //TARGET___LASER_H
