//
// Created by MPA on 22/09/2021.
//

#ifndef TARGET___SHIP_H
#define TARGET___SHIP_H

# include <vector>
# include "SDL.h"
# include "SDL_image.h"
# include "Sprite.h"


enum sens {
    RIEN, DROITE, GAUCHE
};

class Ship : public Sprite{
public:
    Ship(SDL_Renderer* render);
    SDL_Texture *body, *fire, *lifeTexture, *currentGifFrame;
    std::vector<SDL_Texture*> sparkGif, blowGif;
    int size, angle, HP, energie, maxEnergie, chargeTime, chargeTimer;
    double x, y, velocityX, velocityY;
    bool fireOn, canRecharge, isVisible, isDamaged, isBlow, isStunt;
    int rotationDirection;

    void go(); //calcule velocity
    void velocity(); // ad velocity
    void tourne(double newAngle); //tourne (manette)
    void tourne(); //legacy
    void collide(); //make collide
    void damaged(); //damaged
    bool blowUp(); //return true when end
    void battery();

    void playGif(std::vector<SDL_Texture*> gifVector, int delay);

private:
    SDL_Texture *blankGif;
    SDL_Surface *sheet, *bodyImg, *fireImg, *tempLife, *lifeImg, *tempImg, *tempGif, *IMGblankGif;
    int rotationSpeed, damagedTime, damagedTimer, blinkTime, blinkTimer, sparkTime, sparkTimer, blowTime, blowTimer;
    float jetPower, speedMax;
};


#endif //TARGET___SHIP_H
