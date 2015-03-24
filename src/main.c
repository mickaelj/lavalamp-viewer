/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2013 mika <mickael.j@gmail.com>
 *
 * lavalamp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lavalamp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include <getopt.h>
#include <libconfig.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>

#include "main.h"
#include "../config.h"



// TODO (mck#1#): find why struct do not share variable. To change ...
int Applied;
float zoomApplied;
//

void quit()
{

    TTF_Quit();
    SDL_Quit();
    exit(0);

}

void info()
{

    printf("version : %s \n",PACKAGE_VERSION);
    printf("Usage: %s [FILE]\n",PACKAGE);
    printf("Esc to quit.\n");

}

void wait_event()
{

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            quit();
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                quit();
                break;
            case SDLK_SPACE:
                quit();
                break;
            case SDLK_f:
        		break;
            case SDLK_h:
                break;
            case SDLK_RIGHT:
                image.imageRotate=image.imageRotate+90;
                image.image = IMG_Load(image.imageName);
                image.image = rotozoomSurface(image.image,image.imageRotate,1, 1);
                // TODO (mck#1#): make a function
                image.rectW = image.image->w+image.rectSize;
                image.rectH = image.image->h+image.rectSize;
                if (image.activeWindow==1) {
                    image.screen = SDL_SetVideoMode(image.rectW, image.rectH, image.image->format->BitsPerPixel, SDL_HWSURFACE|SDL_DOUBLEBUF );
                } else {
                    image.screen = SDL_SetVideoMode(image.rectW, image.rectH, image.image->format->BitsPerPixel,SDL_NOFRAME|SDL_HWSURFACE|SDL_DOUBLEBUF );
                }
                viewImage(image);struct image_F {
    // Font
    const char *fontFile;
    int fontSize;
    TTF_Font *fontName;
    int fontColorR;
    int fontColorG;
    int fontColorB;
    int textVisible;
    int fontX;
    int fontY;
    // Border
    int rectColorR;
    int rectColorG;
    int rectColorB;
    int rectSize;
    int rectH;
    int rectW;
    // For SDL
    SDL_Rect imageXY, fontXY;
    SDL_Surface * screen, *image, *text;
    const SDL_VideoInfo *videoInfo;
    const char *imageName;
    int imageW;
    int imageH;
    int activeWindow;
    int fullScreen;
    // Transform
    int imageRotate;
    float imageRatio;
    int zoom;
    int unzoom;


};
struct image_F image;
                break;
            case SDLK_LEFT:
                break;
            default:
                break;
            }
		case SDL_MOUSEBUTTONDOWN:
				quit();
				break;
        case SDL_MOUSEBUTTONUP:
            // TODO (mck#1#): Add zoom unzoom function wifenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);th SDL_gfx (rotozoom).
            image.image = IMG_Load(image.imageName);
            if(event.button.button==SDL_BUTTON_WHEELUP) {
                //image.imageRatio=image.imageRatio+0.1;
                //image.image = rotozoomSurface (image.image, 0, 1.1, 0);
                //printf("Zoom image\n");
              
            }

           if(event.button.button==SDL_BUTTON_WHEELDOWN) {
                //image.imageRatio=image.imageRatio-0.1;
                //image.image = zoomSurface(image.image,2,2, 1);
                //image.image = rotozoomSurface (image.image, 0, 0.9, 0);
                //printf("Unzoom image\n");              
            }

			//image.rectW = image.image->w+image.rectSize;
            //image.rectH = image.image->h+image.rectSize;
            //zoomImage(image);
		}
    }

}


void viewImage(struct image_F image)
{
	
    printf("image size  w:%d * h:%d - ",image.imageW,image.imageH);
    printf("screen size  w:%d * h:%d\n",image.videoInfo->current_w,image.videoInfo->current_h);

	// only one size test, to improved.
	if (image.imageW>=image.videoInfo->current_w-50) {
		if (Applied==0) {
			float zoomRatio =(float)image.imageW/image.videoInfo->current_w;
			float zoomApplied=((int)zoomRatio+1)-zoomRatio;
			printf("zoom %f\n",zoomApplied);
			image.image = rotozoomSurface(image.image, 0, zoomApplied, 1);
		}

		
	}
		if (image.imageH>=image.videoInfo->current_h-50) {
			if (Applied==0) {
				float zoomRatio =(float)image.imageH/image.videoInfo->current_h;
				float zoomApplied=((int)zoomRatio+1)-zoomRatio;
				printf("zoom %f\n",zoomApplied);
				image.image = rotozoomSurface(image.image, 0, zoomApplied, 1);
			}
		}
  
    // Get image size
    image.imageW= image.image->w;
    image.imageH= image.image->h;

    image.rectW=image.imageW+image.rectSize;
    image.rectH=image.imageH+image.rectSize;
	printf("new image size : %d %d \n",image.imageW,image.imageH);

	// Replace by  switch/case in futur
	
    if (image.activeWindow==1) {
        image.screen = SDL_SetVideoMode(image.rectW, image.rectH, image.image->format->BitsPerPixel, SDL_RESIZABLE|SDL_HWSURFACE|SDL_DOUBLEBUF );
    } else {
        image.screen = SDL_SetVideoMode(image.rectW, image.rectH, image.image->format->BitsPerPixel,SDL_NOFRAME|SDL_HWSURFACE|SDL_DOUBLEBUF );
    }
    
    if (image.fullScreen==1){
		image.screen = SDL_SetVideoMode(image.rectW, image.rectH, image.image->format->BitsPerPixel,SDL_FULLSCREEN|SDL_HWSURFACE|SDL_DOUBLEBUF );
    }
    
    char title[250];
    strcpy(title,"lavalamp : ");
    strcat(title,image.imageName);
    SDL_WM_SetCaption(title, NULL);

    SDL_FillRect(image.screen, NULL, SDL_MapRGB(image.screen->format, image.rectColorR, image.rectColorG, image.rectColorB));
    SDL_BlitSurface(image.image, NULL, image.screen, &image.imageXY);
    // create text (if TRUE in config file and font declared)
    if(image.textVisible==1) {
        if(image.fontFile) {
            SDL_Color fontColor= {image.fontColorR, image.fontColorG, image.fontColorB};
            image.fontXY.x = image.fontX;
            image.fontXY.y = image.fontY;
            image.fontName = TTF_OpenFont(image.fontFile, image.fontSize);
            image.text = TTF_RenderUTF8_Blended(image.fontName, image.imageName,fontColor);
            SDL_BlitSurface(image.text, NULL, image.screen, &image.fontXY);
            TTF_CloseFont(image.fontName);
        }
    }

    // View image1

    SDL_Flip(image.screen);

    // Free surfaces
    SDL_FreeSurface(image.image);
    SDL_FreeSurface(image.screen);

    // Wait mouse or keyboard events
    wait_event();

    // Par ici la sortie... En français dans le texte.
    quit();
}

int main (int argc, char *argv[])
{
    // TODO (mck#1#): Add command line options (getopt)

    // For config file & libconfig
    char *homedir = getenv("HOME");
    char *configfile =homedir;
    strcat(configfile,"/");
    strcat(configfile,CONFIGFILE);
    config_t cfg, *cf;

    // Default values font (view struct cfgFile in main.h)

	image.fullScreen = 0;
    image.activeWindow = 1;
    image.fontFile = "";
    image.fontSize = 12;
    image.fontColorR = 200;
    image.fontColorG = 200;
    image.fontColorB = 200;
    image.fontX=5;
    image.fontY=5;
    image.textVisible = 0;
    // Defaut values border
    image.rectColorR = 150 ;
    image.rectColorG = 150 ;
    image.rectColorB = 150 ;
    image.rectSize = 15;
    

    // Init SDL & SDL_TTF
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error : %s",SDL_GetError());//on affiche l'erreur
        return EXIT_FAILURE;//on sort du programme pour éviter de plus gros problèmes
    }
    TTF_Init();

    // Init config file parser
    cf = &cfg;
    config_init(cf);

    // Config file test
    if (!config_read_file(&cfg, configfile)) {
        //printf("...Problem with config file, fix it please.\n");
        config_destroy(&cfg);
        return 0;
    }
	
	config_lookup_int(cf, "FullScreen",&image.fullScreen);
    config_lookup_int(cf, "Active_Window",&image.activeWindow);
    config_lookup_int(cf, "Rect_ColorR", &image.rectColorR);
    config_lookup_int(cf, "Rect_ColorG", &image.rectColorG);
    config_lookup_int(cf, "Rect_ColorB", &image.rectColorB);
    config_lookup_int(cf, "Rect_Size", &image.rectSize);
    config_lookup_int(cf, "Text", &image.textVisible);
    config_lookup_string(cf, "Font_Name", &image.fontFile);
    config_lookup_int(cf, "Font_Size", &image.fontSize);
    config_lookup_int(cf, "Font_ColorR", &image.fontColorR);
    config_lookup_int(cf, "Font_ColorG", &image.fontColorG);
    config_lookup_int(cf, "Font_ColorB", &image.fontColorB);
    config_lookup_int(cf, "Font_X", &image.fontX);
    config_lookup_int(cf, "Font_Y", &image.fontY);


    // TODO (mck#1#):  make some tests (existing font, size, color, etc.)

    // Create rect border
    image.imageXY.x=image.rectSize/2;
    image.imageXY.y=image.rectSize/2;

    // print info
    info();

    // Get image name
    image.imageName = argv[1];

    // If image name is null
    if (image.imageName == NULL) {
		exit(1);
    }

    image.image = IMG_Load(image.imageName);
    SDL_putenv("SDL_VIDEO_CENTERED=center");

    // If file is not a picture file
    if ( image.image == NULL ) {
        fprintf(stderr, "Echec de chargement du fichier %s \n",image.imageName);
        return 1;
    }
    // get size
    image.imageW= image.image->w;
    image.imageH= image.image->h;

    // Get screen size
    image.videoInfo=SDL_GetVideoInfo();

    viewImage(image);
    return 0;
}