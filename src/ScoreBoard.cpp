#include "ScoreBoard.h"


void ScoreBoard::init()
{
    gfx->begin();
    gfx->fillScreen(BLACK);

#ifdef GFX_BL
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
#endif

    gfx->setCursor(10, 10);
    gfx->setFont(&FreeMono8pt7b);
    gfx->setTextColor(RED);
    gfx->println("Hello World!");

    delay(5000); // 5 seconds
}

void ScoreBoard::update(byte scoreRed, byte scoreBlue, long matchTime)
{
    gfx->setCursor(random(gfx->width()), random(gfx->height()));
    gfx->setTextColor(random(0xffff));
    uint8_t textSize = random(3);
    switch (textSize)
    {
    case 1:
        gfx->setFont(&FreeMono8pt7b);
        break;
    case 2:
        gfx->setFont(&FreeSansBold10pt7b);
        break;
    default:
        gfx->setFont(&FreeSerifBoldItalic12pt7b);
        break;
    }

    

    gfx->println("Hello World!");

    delay(1000); // 1 second
}

ScoreBoard::ScoreBoard(/* args */)
{
}

ScoreBoard::~ScoreBoard()
{
}