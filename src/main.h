/* package */
#define PACKAGE "lavalamp"
#define PACKAGE_NAME "lavalamp"
#define PACKAGE_URL ""

#define CONFIGFILE "lavalamp.cfg"

struct image_F {
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