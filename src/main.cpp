/*
 * a game which I hope that will work
 * so far, everything is fine !!!
 * (so far...)
 */
# include <iostream>
# include <vector>
# include <algorithm>
# include <cstdlib>
# include <ctime>

# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_image.h"

# include "Ship.h"
# include "Laser.h"
# include "Target.h"
# include "Asteroide.h"

int screenWidth = 1000;
int screenHeight = 500;

int mainSpeed = 3;

/*
 * a function to calculate circular collision
 * @param some Sprite
 * @return if collision
 * */
bool circularColision(Sprite obj1, Sprite obj2)
{
    return sqrt(pow(abs(obj1.centerX - obj2.centerX),2) + pow(abs(obj1.centerY - obj2.centerY),2)) < obj1.rayon + obj2.rayon;
}

int main(int argc, char* argv[])
{
    std::srand(time(NULL));
    //------------declaration primaire-------------
    bool programRunning = true, createLaser = false, readyLaser = true, reset=false;
    SDL_Event evt;
    SDL_Rect rect;
                                                                    // a diviser par 60//
    int laserRelease = 5, laserTimer = laserRelease, debriTimer = 0, debriFrequence = 30, targetSize, score = 0;

    //-----------start graphic renderer-----------
    SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2
    IMG_Init(IMG_INIT_PNG); //initialize SDL_image
    SDL_Window* window = SDL_CreateWindow("Target++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    // ----Check that the window was successfully created------
    if (window == nullptr) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    //--------------------------------------------------------//

    // --------------SDL_mixer --------------------------
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    //----------------------------------------------------//
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    // ---------------declaration des images -----------------

    //SDL_Surface* image = SDL_Load("../data/images/background.bmp");
    SDL_Surface* image = IMG_Load("../data/images/background.png");
    SDL_Texture* background = nullptr;
    if (image != nullptr)
    {
        background = SDL_CreateTextureFromSurface(render, image);
    }
    else{

        printf(SDL_GetError()); // a laisser
    }
    // ---------------declaration des musique -------------------------
    Mix_AllocateChannels(10); //aloue cannaux
    Mix_Music *musique = Mix_LoadMUS("../data/music/TargetSong.wav"); //LOAD UNE MUSIQUE
    Mix_Chunk *laserSong = Mix_LoadWAV("../data/music/lazer.wav");  //LOAD UN SON
    Mix_Chunk *targetSong = Mix_LoadWAV("../data/music/break.wav");
    Mix_Chunk *spark = Mix_LoadWAV("../data/music/spark.wav");
    //------------------Déclaration des object-----------------
    Ship ship(render);
    std::vector<Laser> lasers = {};
    std::vector<Target> targets = {};
    std::vector<Asteroide> cailloux = {};
    //-----------------------------------------------
    Mix_PlayMusic(musique, -1); //JOUE UNE MUSIQUE
    while(programRunning)
    {
        //--------------------events----------------
        while(SDL_PollEvent(&evt))
        {
            // --------------quite le program-----------
            if (evt.type == SDL_QUIT)
            {
                programRunning = false;
            }
            //--------------evenement clavier----------
            //--------------key pressed---------
            if (evt.type == SDL_KEYDOWN)
            {
                //go
                if (evt.key.keysym.sym == SDLK_z)
                {
                    ship.fireOn = true;
                }

                //tourne +
                if (evt.key.keysym.sym == SDLK_q)
                {
                    ship.rotationDirection = '+';
                }

                //tourne -
                if (evt.key.keysym.sym == SDLK_d)
                {
                    ship.rotationDirection = '-';
                }

                //shoot laser
                if (evt.key.keysym.sym == SDLK_TAB)
                {
                    if (readyLaser)
                    {
                        createLaser = true;
                        readyLaser = false;
                    }
                }
                //--------------------

            }
            if (evt.type == SDL_KEYUP){
                if (evt.key.keysym.sym == SDLK_z)
                {
                    ship.fireOn = false;
                }

                //-------stop rotation---------
                if (evt.key.keysym.sym == SDLK_q)
                {
                    if (ship.rotationDirection == '+')
                    {
                        ship.rotationDirection = NULL;
                    }
                }

                if (evt.key.keysym.sym == SDLK_d)
                {
                    if (ship.rotationDirection == '-')
                    {
                        ship.rotationDirection = NULL;
                    }
                }
                //-----------------------

                //get laser ready
                if (evt.key.keysym.sym == SDLK_TAB)
                {
                    createLaser = false;
                    readyLaser = true;
                }
            }
            //-----------------------------------------
        }
        //--------------update-------------
        //----update de ship-------------
        if (!ship.isBlow) {
            if (ship.isDamaged) {
                ship.damaged();
            }
            if (!ship.isStunt) {
                ship.go();
                ship.velocity();
            }
            ship.tourne();
            ship.collide();
            ship.battery();
        } else {
            reset = ship.blowUp();
        }
        //----------------------------lasers-------------
        if (createLaser)
        {
            if (laserTimer >= laserRelease && ship.energie > 0)
            {
                laserTimer = 0;
                ship.energie -= 1;
                lasers.emplace_back(Laser(render,
                                          ship.x + (ship.size / 2.0) - (50 / 2.0),
                                          ship.y + (ship.size / 2.0) - (13 / 2.0),
                                          ship.angle));
                Mix_PlayChannel(-1, laserSong, 0);
            } else {
                laserTimer += 1; //timer
            }
        } else
        {
            laserTimer = laserRelease; //reinitialise le timer
        }

        for(Laser& laser:lasers)
        {
            laser.go();
            laser.overScreen();
        }

        //--------------cretation de truc----------------
        debriTimer += 1; //timer
        if (debriTimer > debriFrequence)
        {
            debriTimer = 0;
            if (rand()%10< 1)//frequence modulable
            {
                //creation de cible
                targetSize = rand()%100 +50;
                targets.emplace_back(Target(render, rand() % (500-targetSize), targetSize, rand() % 9));
            }
            if (rand()%10 < 8)
            {
                //creation de cailloux
                int newSize = rand()%100 +40;
                cailloux.emplace_back(Asteroide(render,
                                                rand() % (500 - newSize),
                                                newSize,
                                                rand() % 4,
                                                rand()% 359,
                                                rand() % 2));
            }
        }
        for (Target& target:targets)
        {
            target.move();
        }
        for (Asteroide& caillou:cailloux)
        {
            caillou.move();
        }

        //--------------------Collision générales-----------------
        //moi et les cailloux
        if (!ship.isDamaged && !ship.isBlow)
        {
            for (Asteroide& caillou : cailloux)
            {
                if (circularColision(ship, caillou))
                {
                    ship.HP -= 1;
                    if (ship.HP > 0)
                    {
                        ship.isDamaged = true;
                        ship.isStunt = true;
                        Mix_PlayChannel(-1, spark, 0);
                    } else
                    {
                        ship.isBlow = true;
                        createLaser = false;
                        //melee.stop();
                        //ship.blow.play();
                    }
                    break;
                }
            }
        }

        //laser et target
        for (Target& target:targets) {
            for (Laser& laser:lasers) {
                if (circularColision(target, laser) && !laser.toDestroy)

                {
                    laser.toDestroy = true;
                    target.toDestroy = true;
                    score += target.value;
                    //ScoreInfo newScoreInfo = new ScoreInfo(target.centerX, target.centerY, target.value, windows);
                    //scoresInfos.add(newScoreInfo);
                }
            }
        }

        //laser et caillou
        for (Asteroide& caillou:cailloux)
        {
            for (Laser& laser:lasers)
            {
                if (circularColision(caillou, laser) && !laser.toDestroy)
                {
                    laser.toDestroy = true;
                }
            }
        }
        //------------------------actualisation de liste------------------
        //liste de laser
        for (Laser& laser : lasers) {
            if (laser.toDestroy) {
                lasers.erase(
                        remove_if(lasers.begin(), lasers.end() - 1, [](Laser laser) { return laser.toDestroy; }));
            }
        }
        //liste de Targets
        for (Target& target : targets) {
            if (target.toDestroy) //destroy with song
            {
                Mix_PlayChannel(-1, targetSong, 0);
                targets.erase(
                        remove_if(targets.begin(), targets.end() - 1, [](Target target) { return target.toDestroy; }));
            }
            if (target.outScreen) { //destroy without song
                targets.erase(
                        remove_if(targets.begin(), targets.end() - 1, [](Target target) { return target.outScreen; }));
            }
        }
        //liste de Cailloux
        for (Asteroide& caillou : cailloux) {
            if (caillou.toDestroy) {
                cailloux.erase(
                        remove_if(cailloux.begin(), cailloux.end() - 1, [](Asteroide caillou) { return caillou.toDestroy; }));
            }
        }
        //--------------------------------------------------------------------

        // ------drawing test----------
        //background
        rect = {}; //reset
        SDL_QueryTexture(background, nullptr, nullptr, &rect.w, &rect.h);
        SDL_RenderCopy(render, background, nullptr, &rect);

        //---------------player----------------
        //ship
        rect = {static_cast<int>(ship.x), static_cast<int>(ship.y)}; //reset
        SDL_QueryTexture(ship.body, nullptr, nullptr, &rect.w, &rect.h);
        SDL_RenderCopyEx(render, ship.body, nullptr, &rect, ship.angle, nullptr, SDL_FLIP_NONE);

        //fire
        if (ship.fireOn)
        {
            rect = {static_cast<int>(ship.x), static_cast<int>(ship.y)}; //reset
            SDL_QueryTexture(ship.fire, nullptr, nullptr, &rect.w, &rect.h);
            SDL_RenderCopyEx(render, ship.fire, nullptr, &rect, ship.angle, nullptr, SDL_FLIP_NONE);
        }
        //----------------animations-------------------
        rect = {static_cast<int>(ship.x), static_cast<int>(ship.y)}; //reset
        SDL_QueryTexture(ship.currentGifFrame, nullptr, nullptr, &rect.w, &rect.h);
        SDL_RenderCopyEx(render, ship.currentGifFrame, nullptr, &rect, ship.angle, nullptr, SDL_FLIP_NONE);
        //--------------------------------
        //lasers
        for (Laser laser:lasers)
        {
            rect = {static_cast<int>(laser.x), static_cast<int>(laser.y)};
            SDL_QueryTexture(laser.texture, nullptr, nullptr, &rect.w, &rect.h);
            SDL_RenderCopyEx(render, laser.texture, nullptr, &rect, laser.angle, nullptr, SDL_FLIP_NONE);
        }

        //targets
        for (Target target:targets)
        {
            rect = {static_cast<int>(target.x), static_cast<int>(target.y)}; //reset
            SDL_QueryTexture(target.texture, nullptr, nullptr, &rect.w, &rect.h);
            SDL_RenderCopy(render, target.texture, nullptr, &rect);
        }

        //Cailloux
        for (Asteroide caillou:cailloux)
        {
            rect = {static_cast<int>(caillou.x), static_cast<int>(caillou.y)};
            SDL_QueryTexture(caillou.texture, nullptr, nullptr, &rect.w, &rect.h);
            SDL_RenderCopyEx(render, caillou.texture, nullptr, &rect, caillou.angle, nullptr, SDL_FLIP_NONE);
        }

        //la vie
        for (int i=0; i < ship.HP; i++)
        {
            rect = {static_cast<int>(i*45), static_cast<int>(0)};
            SDL_QueryTexture(ship.lifeTexture, nullptr, nullptr, &rect.w, &rect.h);
            SDL_RenderCopy(render, ship.lifeTexture, nullptr, &rect);
        }
        SDL_RenderPresent(render);
        // ----------// Cap to 60 FPS //-----------------
        SDL_Delay(floor(16.666f));
    }
    // Clean up
    SDL_DestroyRenderer(render);
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
