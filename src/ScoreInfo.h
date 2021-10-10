//
// Created by idime on 10/10/2021.
//

#ifndef TARGET___SCOREINFO_H
#define TARGET___SCOREINFO_H

# include "SDL.h"
# include "SDL_ttf.h"

class ScoreInfo {
public:
    SDL_Texture *texture;
    bool isEnd;
    double x, y;

    ScoreInfo(SDL_Renderer* render, double x, double y, int value);
    void update();

private:
    SDL_Surface *surface;
    double velocityY;
    int timer;
};


#endif //TARGET___SCOREINFO_H
