//
//  Pokitto Render - Betelgeuse
//

#include "Pokitto.h"
#include "assets.h"

Pokitto::Core app;

int main () {
    
    app.begin();
    app.display.loadRGBPalette(paletteDB8);

    while (app.isRunning()) {
        if (app.update()) {            
            app.display.drawBitmap( 0, 0, rio);
        } 
    }
}