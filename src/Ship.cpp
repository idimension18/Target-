//
// Created by MPA on 22/09/2021.
//
# include <cstdio>
# include "Ship.h"
# include <cmath>

# include <thread>

# include <filesystem>


namespace fs = std::filesystem;

extern int screenWidth;
extern int screenHeight;

Ship::Ship(SDL_Renderer* render):
//---------declaration usuelle-----------------
x{500}, y{250}, size{64},
jetPower{0.1f}, velocityX{0}, velocityY{0}, speedMax{5.0f},
angle{90}, rotationSpeed{5}, fireOn{false}, rotationDirection{NULL},
HP{5}, isVisible{true}, isDamaged{false}, isBlow{false}, isStunt{false}, damagedTime{120}, damagedTimer{0},
blinkTime{10}, blinkTimer{0}, blowTime{150}, blowTimer{0}, sparkTime{60}, sparkTimer{0},
maxEnergie{30}, energie{maxEnergie}, canRecharge{true}, chargeTime{5}, chargeTimer{0},
//------------------------------
//---------declaration graphics----------
sheet{IMG_Load("../data/images/sprites.png")},
tempLife{IMG_Load("../data/images/life.png")},
IMGblankGif{SDL_CreateRGBSurface(0,64, 64, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)},
tempImg{SDL_CreateRGBSurface(0,256, 256, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)},
bodyImg{SDL_CreateRGBSurface(0,64, 64, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)},
fireImg{SDL_CreateRGBSurface(0,64, 64, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)},
lifeImg{SDL_CreateRGBSurface(0,45, 45, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)},
sparkGif{}, blowGif{}, currentGifFrame{}
{
    //---------affectation graphics----------
    SDL_GetRendererOutputSize(render, &screenWidth, &screenHeight);
    //body
    SDL_Rect cutRect = {2048, 0, 256, 256};
    SDL_BlitSurface(sheet, &cutRect, tempImg, nullptr);
    SDL_Rect scaleRect = {0, 0, size, size};
    SDL_BlitScaled(tempImg, nullptr, bodyImg, &scaleRect);
    body = SDL_CreateTextureFromSurface(render, bodyImg);

    SDL_FillRect(tempImg, NULL, 0x000000); //temp

    //fire
    cutRect = {2048, 256, 256, 256};
    SDL_BlitSurface(sheet, &cutRect, tempImg, nullptr);
    SDL_BlitScaled(tempImg, nullptr, fireImg, &scaleRect);
    fire = SDL_CreateTextureFromSurface(render, fireImg);

    scaleRect = {0, 0,45,45};
    SDL_BlitScaled(tempLife, nullptr, lifeImg, &scaleRect);
    lifeTexture = SDL_CreateTextureFromSurface(render, lifeImg);

    //gif test
    fs::path path{"../data/images/sparkGif"};
    for (const auto& entry : fs::directory_iterator(path))
    {
        tempGif = IMG_Load(entry.path().string().c_str());
        sparkGif.emplace_back(SDL_CreateTextureFromSurface(render, tempGif));
        printf(SDL_GetError());
    }

    path = fs::path{"../data/images/blowGif"};
    for (const auto& entry : fs::directory_iterator(path))
    {
        tempGif = IMG_Load(entry.path().string().c_str());
        blowGif.emplace_back(SDL_CreateTextureFromSurface(render, tempGif));
        printf(SDL_GetError());
    }

    blankGif = SDL_CreateTextureFromSurface(render, IMGblankGif);
    currentGifFrame = blankGif;
    //--------------------------------------------
    Sprite::centerX = x + (size/2.0);
    Sprite::centerY = y + (size/2.0);
    Sprite::rayon = size/2.0;
}
//-----------go engine----------------
void Ship::go()
{
    if (fireOn)
    {
        velocityX += cos(angle * (M_PI/180)) * jetPower;
        velocityY += sin(angle * (M_PI/180)) * jetPower;

        //------speedmax------------------
        if (abs(velocityX) > speedMax) {
            velocityX = velocityX > 0 ? speedMax : -speedMax;
        }
        if (abs(velocityY) > speedMax) {
            velocityY = velocityY > 0 ? speedMax : -speedMax;
        }
        //-----------------------------
    }
}

void Ship::velocity()
{
    x += velocityX;
    y += velocityY;

    Sprite::centerX = x + (size/2.0f);
    Sprite::centerY = y + (size/2.0f);
}

//------rotation fuction----------
void Ship::tourne()
{
    if (rotationDirection == '-')
    {
        angle += rotationSpeed;
        if (angle >= 360) {
            angle -= 360;
        }
    } else if (rotationDirection == '+')
    {
        angle -= rotationSpeed;
        if (angle < 0) {
            angle += 360;
        }
    }
}

//---------------colision-----------
void Ship::collide() {
    if (x > screenWidth - size || x < 0) {
        velocityX = 0;
        if (x < 0) {
            x = 0;
        }
        if (x > screenWidth - size) {
            x = (screenWidth - size);
        }
    }
    if (y > screenHeight - size ||y <0) {
        velocityY = 0;
        if (y < 0) {
            y=0;
        }
        if (y > (screenHeight - size)) {
            y = (screenHeight - size);
        }
    }
}

void Ship::playGif(std::vector<SDL_Texture*> gifVector, int delay)
{
    for(SDL_Texture* texture:gifVector)
    {
        currentGifFrame = texture;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay * 10));
    }
    currentGifFrame = blankGif;
}

void Ship::damaged() {
    if (damagedTimer < damagedTime) {
        damagedTimer += 1;
        blinkTimer += 1;
        sparkTimer += 1;

        if (sparkTimer == 1) {
            std::thread th1(&Ship::playGif, this,sparkGif, 4);
            th1.detach();
        } else if (sparkTimer > sparkTime) {
            canRecharge = true;
        }
        if (blinkTimer > blinkTime) {
            blinkTimer = 0;
            isVisible = !isVisible;
        }
        if (damagedTimer == damagedTime/4) {
            isStunt = false;
            velocityX = 0;
            velocityY = 0;
        } else if (damagedTimer < damagedTime/4) {
            canRecharge = false;
            fireOn = false;
            velocityX += (velocityX == 0 && velocityY ==0) ? 3 : 0;
            x -= velocityX/2;
            y -= velocityY/2;
            Sprite::centerX = x + (size/2.0f);
            Sprite::centerY = y + (size/2.0f);
        }
    } else {
        isDamaged = false;
        isVisible = true;
        damagedTimer = 0;
        blinkTimer = 0;
        sparkTimer = 0;
        canRecharge = true;
    }
}

bool Ship::blowUp() {
    if (blowTimer < blowTime) {
        isVisible = false;
        blowTimer += 1;
        if (blowTimer == 1) {
            std::thread th1(&Ship::playGif, this, blowGif, 10);
            th1.detach();
        }
        x += velocityX/2;
        y += velocityY/2;
        Sprite::centerX = x + (size/2.0);
        Sprite::centerY = y + (size/2.0);
        return false;
    } else {
        //windows.getContentPane().remove(blowGIF);
        isVisible = true;
        isBlow = false;
        blowTimer = 0;
        return true;
    }
}

void Ship::battery() {
    if (canRecharge && energie < maxEnergie) {
        if (chargeTimer == chargeTime) {
            energie += 1;
            chargeTimer = 0;
        } else {
            chargeTimer += 1;
        }
    }
}