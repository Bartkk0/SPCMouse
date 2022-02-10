//
// Created by bartkk on 1/2/22.
//

#ifndef SPCMOUSE_MOUSEDATA_H
#define SPCMOUSE_MOUSEDATA_H

struct Color{
    unsigned char r=0xff,g=0x00,b=0xff;
};

enum EffectType: unsigned char{
    COLORFUL_STREAMING = 1,
    STEADY,
    BREATHING,
    TAIL,
    NEON,
    COLORFUL_STEADY,
    FLICKER,
    STARS_TWINKLE,
    WAVE,
    OFF
};

enum Speed: unsigned char{
    SLOW = 0x41,
    MEDIUM = 0x42,
    FAST = 0x43
};

/*
 04 - Report type
 11 - Packet type
 007b0000000064068436c00303070709090e0e13131d1d00000000ff000000ff000000ffffff00ff00ff00ffff000000000000
 01 - Effect type

 43 - Colorful stream speed
 00 - Colorful stream direction

 40 - Steady brightness
 ff ff ff - Steady color

 43 - Breathing speed
 07 - Breathing color amount
 ff 00 00 - Breathing color 1
 00 00 ff - Breathing color 2
 00 ff 00 - Breathing color 3
 80 00 ff - Breathing color 4
 fa c6 03 - Breathing color 5
 fa 03 6a - Breathing color 6
 80 00 80 - Breathing color 7

 43 - Tail speed

 43 - Neon speed

 4e - IDK
 ff0000
 0000ff
 fa00fa
 ffffff
 000000
 000000
 000000
 000000
 aeaeaeaeae - IDK

 41

 41 - Flicker speed
 ff 00 00 - Flicker color 1
 00 00 ff - Flicker color 2

 41 - Stars twinkle speed
 41 - Wave speed

 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
 */


struct LightingData{
    unsigned char reportType = 4;
    unsigned char packetType = 0x12;
    const unsigned char data1[51] = {
            0x00, 0x7b, 0x00, 0x00, 0x00, 0x00, // 0x00000000
            0x64, 0x06, 0x04, 0x36, 0xc0, 0x03, 0x07, 0x09, // 0x00000008
            0x0e, 0x13, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x00000010
            0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, // 0x00000018
            0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, // 0x00000020
            0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, // 0x00000028
            0x00, 0x00, 0x00, 0x00, 0x00};
    EffectType effectType = EffectType::COLORFUL_STEADY;

    Speed colorfulStreamSpeed = Speed::SLOW;
    unsigned char colorfulStreamDirection = 0x01;

    unsigned char steadyBrightness = 0x40; //0x10, 0x20, 0x30, 0x40
    Color steadyColor;

    Speed breathingSpeed = Speed::SLOW;
    unsigned char breathingColorAmount = 7; // Max 7
    Color breathingColors[7];

    Speed tailSpeed = Speed::SLOW;

    Speed neonSpeed = Speed::SLOW;

    unsigned char data11 = 0x4e;
    Color colorfulSteadyColors[8];
    unsigned char data2[5] = {0xae,0xae,0xae,0xae,0xa};
    unsigned char data3[1] = {0x41};

    Speed flickerSpeed = Speed::SLOW;
    Color flickerColors[2];

    Speed starsTwinkleSpeed = Speed::SLOW;

    Speed waveSpeed = Speed::SLOW;

    unsigned char padding[790] = { 0x00 };
};

struct ButtonData{
    unsigned char report = 4;
    unsigned char type = 0x12;
};

struct ParameterData{
    unsigned char report = 5;
    unsigned char type = 0x1b;
    unsigned char LOD = 0x01; // 0x01 = 2mm, 0x02 = 3mm
    unsigned char clickLatency = 0x02; // 0x02-0x08 = 4-16ms
    unsigned char data[3] = {0};
};

#endif //SPCMOUSE_MOUSEDATA_H
