//
//  Expression.h
//  MoodDrawing
//
//  Created by Jake Pyne on 23/07/2012.
//  Copyright 2012 TUI Interactive Media. All rights reserved.
//

#ifndef MoodDrawing_Expression_h
#define MoodDrawing_Expression_h
#include <string>

class Expression {
    
    public:
    Expression();
    Expression(std::string mDescription,
               float mMouthWidth,
               float mMouthHeight,
               float mEyebrowLeft,
               float mEyebrowRight,
               float mEyeLeft,
               float mEyeRight,
               float mJaw,
               float mNostrils);
    void save();
    void load();
    void setDescription(char* description);
    std::string getDescription();
    
    float getMouthWidth()   { return mMouthWidth; }
    float getMouthHeight()  { return mMouthHeight; }
    float getEyebrowLeft()  { return mEyebrowLeft; }
    float getEyebrowRight() { return mEyebrowRight; }
    float getEyeLeft()      { return mEyeLeft; }
    float getEyeRight()     { return mEyeRight; }
    float getJaw()          { return mJaw; }
    float getNostrils()     { return mNostrils; }
    
    void setDescription(std::string description){ mDescription = description; }
    void updateMouthWidth(float mouthWidth)     { mMouthWidth = mouthWidth; }
    void updateMouthHeight(float mouthHeight)   { mMouthHeight = mouthHeight; }
    void updateEyebrowLeft(float eyebrowLeft)   { mEyebrowLeft = eyebrowLeft; }
    void updateEyebrowRight(float eyebrowRight) { mEyebrowRight = eyebrowRight; }
    void updateEyeLeft(float eyeLeft)           { mEyeLeft = eyeLeft; }
    void updateEyeRight(float eyeRight)         { mEyeRight = eyeRight; }
    void updateJaw(float jaw)                   { mJaw = jaw; }
    void updateNostrils(float nostrils)         { mNostrils = nostrils; }
    

        std::string mDescription;
        float mMouthWidth;
        float mMouthHeight;
        float mEyebrowLeft;
        float mEyebrowRight;
        float mEyeLeft;
        float mEyeRight;
        float mJaw;
        float mNostrils;
    
};
#endif
