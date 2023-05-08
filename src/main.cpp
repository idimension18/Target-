/*
 * a game which I hope that will work
 * so far, everything is fine !!!
 * (so far...)
 */
# include <vector>
# include <algorithm>
# include <cstdlib>
# include <ctime>
# include <string>
# include <sstream>

# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>
# include "SDL_image.h"
# include "SDL_ttf.h"

# include "Ship.h"
# include "Laser.h"
# include "Target.h"
# include "Asteroide.h"
# include "ScoreInfo.h"

int screenWidth = 1000;
int screenHeight = 500;

double scaleX = 1;
double scaleY = 1;

int mainSpeed = 3;

double maxAxis = 32768.;

/*
 * a function to calculate circular collision
 * @param some Sprite
 * @return if collision
 * */
bool circularColision(Sprite obj1, Sprite obj2)
{
    return sqrt(pow(abs(obj1.centerX - obj2.centerX),2) + pow(abs(obj1.centerY - obj2.centerY),2)) < obj1.rayon + obj2.rayon;
}

void scaleRect(SDL_Rect *rect)
{
    rect->x *= scaleX;
    rect->y *= scaleY;
    rect->w *= scaleX;
    rect->h *= scaleY;
}

int main(int argc, char* argv[])
{
    std::srand(time(NULL));
    //------------declaration primaire-------------
    bool programRunning = true, createLaser = false, readyLaser = true, reset=false;
    SDL_Event evt;
    SDL_Rect rect, rect2;
                                                                    // a diviser par 60//
    int laserRelease = 5, laserTimer = laserRelease, debriTimer = 0, debriFrequence = 30, targetSize, score = 0;
    double axisX = 0, axisY = 0, axisRatio = 0, axisAngle = 0;

    //-----------start graphic renderer-----------
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);  // Initialize SDL2
    //------------------------------------------------------------
    SDL_Joystick* pJoystick = NULL;
    int numJoystick = SDL_NumJoysticks(); // Compte le nombre de joysticks
    printf("Vous avez %d joysticks sur cette machine\n",numJoystick);
    if ( numJoystick >= 1 )
    {
        // Ouvre le premier joystick présent sur la machine
        pJoystick = SDL_JoystickOpen(0);
        if ( pJoystick == NULL )
        {
            fprintf(stderr,"Erreur pour ouvrir le premier joystick\n");
        }
    }
    //--------------------------------------------------------------------------
    IMG_Init(IMG_INIT_PNG); //initialize SDL_image
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Target++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);
    // ----Check that the window was successfully created------
    if (window == nullptr) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    printf("Informations du joystick\n");
    printf("Nom : %s\n",SDL_JoystickName(0));
    printf("Nombre d'axes : %d\n",SDL_JoystickNumAxes(pJoystick));
    printf("Nombre de chapeaux : %d\n",SDL_JoystickNumHats(pJoystick));
    printf("Nombre de trackballs : %d\n",SDL_JoystickNumBalls(pJoystick));
    printf("Nombre de boutons : %d\n",SDL_JoystickNumButtons(pJoystick));
    //--------------------------------------------------------//

    // --------------SDL_mixer --------------------------
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    //----------------------------------------------------//
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    // ---------------declaration des images -----------------
    SDL_Surface* image = IMG_Load("../data/images/background.png");
    SDL_Texture* background = nullptr;
    background = SDL_CreateTextureFromSurface(render, image);

    //---------------LE SCORE------------------------
    char *scoreText{const_cast<char *>(std::string("o").c_str())};
    TTF_Font* font = TTF_OpenFont("../data/fonts/m5x7.ttf", 50);
    SDL_Color white{0,255,0};

    SDL_Surface *scoreSurface, *energySurface = TTF_RenderText_Solid(font, "Energy :", white);;
    SDL_Texture *scoreTexture, *energyTexture = SDL_CreateTextureFromSurface(render, energySurface);
    // ---------------declaration des musique -------------------------
    Mix_AllocateChannels(10); //aloue cannaux
    Mix_Music *musique = Mix_LoadMUS("../data/music/TargetSong.wav"); //LOAD UNE MUSIQUE
    Mix_Chunk *laserSong = Mix_LoadWAV("../data/music/lazer.wav");  //LOAD UN SON
    Mix_Chunk *targetSong = Mix_LoadWAV("../data/music/break.wav");
    Mix_Chunk *spark = Mix_LoadWAV("../data/music/spark.wav");
    Mix_Chunk *blow = Mix_LoadWAV("../data/music/blow.wav");
    //------------------Déclaration des object-----------------
    Ship ship(render);
    std::vector<Laser> lasers = {};
    std::vector<Target> targets = {};
    std::vector<Asteroide> cailloux = {};
    std::vector<ScoreInfo> scoreInfos={};
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
            //-------------evenemtn windows---------
            if (evt.type == SDL_WINDOWEVENT)
            {
                if (evt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    rect = {} ;//rest
                    SDL_GetWindowSize(window, &rect.w, &rect.h);
                    scaleX = rect.w*1./screenWidth;
                    scaleY = rect.h*1./screenHeight;
                }
            }
            //-------------- key board event-----------------
            if (evt.type == SDL_KEYDOWN)
            {
                if (evt.key.keysym.sym == SDLK_z)
                {
                    ship.fireOn = true;
                }

                if (evt.key.keysym.sym == SDLK_q)
                {
                    ship.rotationDirection = GAUCHE;
                }
                if (evt.key.keysym.sym == SDLK_d)
                {
                    ship.rotationDirection = DROITE;
                }

                if (evt.key.keysym.sym == SDLK_l)
                {
                    if (readyLaser)
                    {
                        createLaser = true;
                        readyLaser = false;
                    }
                }
            }

            if (evt.type == SDL_KEYUP)
            {
                if (evt.key.keysym.sym == SDLK_z)
                {
                    ship.fireOn = false;
                }

                if (evt.key.keysym.sym == SDLK_q)
                {
                    if (ship.rotationDirection == GAUCHE)
                    {
                        ship.rotationDirection = RIEN;
                    }
                }
                if (evt.key.keysym.sym == SDLK_d)
                {
                    if (ship.rotationDirection == DROITE)
                    {
                        ship.rotationDirection = RIEN;
                    }
                }

                if (evt.key.keysym.sym == SDLK_l)
                {
                    createLaser = false;
                    readyLaser = true;
                }
            }
            //-------------------- joystivk event---------------------
            if (evt.type == SDL_JOYBUTTONDOWN || evt.type == SDL_JOYBUTTONUP)
            {
                //------------------pressed------------------
                if (evt.jbutton.state == SDL_PRESSED)
                {
                    //lasers
                    if (evt.jbutton.button == 0)
                    {
                        if (readyLaser)
                        {
                            createLaser = true;
                            readyLaser = false;
                        }
                    }
                }
                //-------------------release-----------------
                if (evt.jbutton.state == SDL_RELEASED)
                {
                    //lasers
                    if (evt.jbutton.button == 0)
                    {
                        createLaser = false;
                        readyLaser = true;
                    }
                }
            }
            //-------------------- evenement stick---------------------------
            if (evt.type == SDL_JOYAXISMOTION)
            {
                //-------------- fire ------------------
                if (evt.jaxis.axis == 5)
                {
                    if (evt.jaxis.value > 0) //fire on
                    {
                        ship.fireOn = true;
                    } else //fire off
                    {
                        ship.fireOn = false;
                    }
                }
                //---------------Direction  stick ------------------
                if (evt.jaxis.axis == 0) // x axis
                {
                    axisX = round(evt.jaxis.value/maxAxis *1000)/1000;
                }
                if (evt.jaxis.axis == 1) //y axis
                {
                    axisY =  (-1) * round(evt.jaxis.value/maxAxis*1000)/1000;
                }
                axisRatio = sqrt(pow(axisX,2) + pow(axisY, 2));
                if (axisX != 0 || axisY != 0)
                {
                    axisAngle = acos(axisX / axisRatio)*(180/M_PI);
                    if (axisY > 0)
                    {
                        axisAngle += 2*(180-axisAngle);
                    }
                }
                //-----------------------------
            }
            //-----------------------------------------------------
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
            //ship.tourne(axisAngle);
            ship.tourne();
            ship.collide();
            ship.battery();
        } else {
            reset = ship.blowUp();
        }
        //---------------reset tout------------------
        if (reset) {
            reset = false;
            score = 0;
            ship = Ship{render};
            lasers.clear();
            targets.clear();
            cailloux.clear();
            Mix_PlayMusic(musique, -1);
        }
        //----------------------------lasers-------------------
        if (createLaser)
        {
            ship.canRecharge = false;
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
            if (!ship.isDamaged)
            {
                ship.canRecharge = true;
            }
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
        for (ScoreInfo& scoreInfo:scoreInfos)
        {
            scoreInfo.update();
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
                        Mix_HaltMusic();
                        Mix_PlayChannel(-1, blow, 0);
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
                    scoreInfos.emplace_back(ScoreInfo(render, target.centerX, target.centerY, target.value));
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
        for (Asteroide& caillou : cailloux)
        {
            if (caillou.toDestroy)
            {
                cailloux.erase(
                        remove_if(cailloux.begin(), cailloux.end() - 1, [](Asteroide caillou) { return caillou.toDestroy; }));
            }
        }

        //liste des score Info
        for (ScoreInfo& scoreInfo:scoreInfos)
        {
            if (scoreInfo.isEnd){
                scoreInfos.erase(remove_if(scoreInfos.begin(), scoreInfos.end()-1, [](ScoreInfo scoreInfo){return scoreInfo.isEnd;}));
            }
        }
        // -------------------------drawing stufs----------------
        //background
        rect = {}; //reset
        SDL_QueryTexture(background, nullptr, nullptr, &rect.w, &rect.h);
        scaleRect(&rect);
        SDL_RenderCopy(render, background, nullptr, &rect);

        //---------------player----------------
        if (ship.isVisible)
        {
            //ship
            rect = {static_cast<int>(ship.x), static_cast<int>(ship.y)}; //reset
            SDL_QueryTexture(ship.body, nullptr, nullptr, &rect.w, &rect.h);
            scaleRect(&rect);
            SDL_RenderCopyEx(render, ship.body, nullptr, &rect, ship.angle, nullptr, SDL_FLIP_NONE);

            //fire
            if (ship.fireOn)
            {
                rect = {static_cast<int>(ship.x), static_cast<int>(ship.y)}; //reset
                SDL_QueryTexture(ship.fire, nullptr, nullptr, &rect.w, &rect.h);
                scaleRect(&rect);
                SDL_RenderCopyEx(render, ship.fire, nullptr, &rect, ship.angle, nullptr, SDL_FLIP_NONE);
            }
        }
        //----------------animations-------------------
        rect2 = {};
        SDL_QueryTexture(ship.currentGifFrame, nullptr, nullptr, &rect2.w, &rect2.h);
        scaleRect(&rect);
        rect = {static_cast<int>((ship.x+(ship.size)/2.)-(rect2.w)/2.), static_cast<int>((ship.y+(ship.size)/2.)-(rect2.h)/2.), rect2.w, rect2.h}; //reset
        scaleRect(&rect);
        SDL_RenderCopyEx(render, ship.currentGifFrame, nullptr, &rect, ship.angle, nullptr, SDL_FLIP_NONE);
        //--------------------------------
        //lasers
        for (Laser laser:lasers)
        {
            rect = {static_cast<int>(laser.x), static_cast<int>(laser.y)};
            SDL_QueryTexture(laser.texture, nullptr, nullptr, &rect.w, &rect.h);
            scaleRect(&rect);
            SDL_RenderCopyEx(render, laser.texture, nullptr, &rect, laser.angle, nullptr, SDL_FLIP_NONE);
        }

        //targets
        for (Target target:targets)
        {
            rect = {static_cast<int>(target.x), static_cast<int>(target.y)}; //reset
            SDL_QueryTexture(target.texture, nullptr, nullptr, &rect.w, &rect.h);
            scaleRect(&rect);
            SDL_RenderCopy(render, target.texture, nullptr, &rect);
        }

        //Cailloux
        for (Asteroide caillou:cailloux)
        {
            rect = {static_cast<int>(caillou.x), static_cast<int>(caillou.y)};
            SDL_QueryTexture(caillou.texture, nullptr, nullptr, &rect.w, &rect.h);
            scaleRect(&rect);
            SDL_RenderCopyEx(render, caillou.texture, nullptr, &rect, caillou.angle, nullptr, SDL_FLIP_NONE);
        }

        //------------------------user interface----------------------------
        //Score Infos
        for (ScoreInfo& scoreInfo:scoreInfos)
        {
            rect = {static_cast<int>(scoreInfo.x), static_cast<int>(scoreInfo.y)};
            SDL_QueryTexture(scoreInfo.texture, nullptr, nullptr, &rect.w, &rect.h);
            scaleRect(&rect);
            SDL_RenderCopy(render, scoreInfo.texture, nullptr, &rect);
        }

        //energie bar
        rect = {850, 0, 50, 20};
        scaleRect(&rect);
        SDL_RenderCopy(render, energyTexture, nullptr, &rect);

        rect = {850, 20, 75, 25};
        scaleRect(&rect);
        SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
        SDL_RenderDrawRect(render, &rect);

        SDL_SetRenderDrawColor(render, 0, 255, 0, 0);
        rect = {851, 21, static_cast<int>(74.0*(ship.energie*(1.)/ship.maxEnergie)), 24};
        scaleRect(&rect);
        SDL_RenderFillRect(render, &rect);

        //la vie
        for (int i=0; i < ship.HP; i++)
        {
            rect = {static_cast<int>(i*45), static_cast<int>(0)};
            SDL_QueryTexture(ship.lifeTexture, nullptr, nullptr, &rect.w, &rect.h);
            scaleRect(&rect);
            SDL_RenderCopy(render, ship.lifeTexture, nullptr, &rect);
        }

        //le score
        sprintf(scoreText, "score : %04i", score);
        scoreSurface = TTF_RenderText_Solid(font, scoreText, white);
        scoreTexture = SDL_CreateTextureFromSurface(render, scoreSurface);

        rect = {420, 0};
        SDL_QueryTexture(scoreTexture, nullptr, nullptr, &rect.w, &rect.h);
        scaleRect(&rect);
        SDL_RenderCopy(render, scoreTexture, nullptr, &rect);
        //----------------final--------------------
        SDL_RenderPresent(render);
        // ----------// Cap to 60 FPS //-----------------
        SDL_Delay(floor(16.666f));
    }

    // Clean up
    SDL_DestroyRenderer(render);
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_JoystickClose(pJoystick);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
