//
//  Expression.cpp
//  MoodDrawing
//
//  Created by Jake Pyne on 23/07/2012.
//
#include "Cinder/xml.h"
#include "Expression.h"
using namespace ci;

Expression::Expression() {
    mDescription    = std::string("");
    
    mMouthWidth     = 
    mMouthHeight    = 
    mEyebrowLeft    = 
    mEyebrowRight   = 
    mEyeLeft        = 
    mEyeRight       = 
    mJaw            = 
    mNostrils       = 0.0f;
}

Expression::Expression(std::string description,
           float mouthWidth,
           float mouthHeight,
           float eyebrowLeft,
           float eyebrowRight,
           float eyeLeft,
           float eyeRight,
           float jaw,
           float nostrils) {
    
    mDescription    = description;
    mMouthWidth     = mouthWidth;
    mMouthHeight    = mouthHeight;
    mEyebrowLeft    = eyebrowLeft;
    mEyebrowRight   = eyebrowRight;
    mEyeLeft        = eyeLeft;
    mEyeRight       = eyeRight;
    mJaw            = jaw;
    mNostrils       = nostrils;
    
}

void Expression::setDescription(char* description) {
    mDescription = description;
}

std::string Expression::getDescription() {
    return mDescription;
}

void Expression::save() {
    XmlTree exp("expression", "");
    exp.push_back(XmlTree("mouthWidth",     boost::lexical_cast<std::string>(mMouthWidth)));
    exp.push_back(XmlTree("mouthHeight",    boost::lexical_cast<std::string>(mMouthHeight)));
    exp.push_back(XmlTree("eyebrowLeft",    boost::lexical_cast<std::string>(mEyebrowLeft)));
    exp.push_back(XmlTree("eyebrowRight",   boost::lexical_cast<std::string>(mEyebrowRight)));
    exp.push_back(XmlTree("eyeLeft",        boost::lexical_cast<std::string>(mEyeLeft)));
    exp.push_back(XmlTree("eyeRight",       boost::lexical_cast<std::string>(mEyeRight)));
    exp.push_back(XmlTree("jaw",            boost::lexical_cast<std::string>(mJaw)));
    exp.push_back(XmlTree("nostrils",       boost::lexical_cast<std::string>(mNostrils)));
    exp.write( writeFile(std::string("./Expressions/") + mDescription + std::string(".xml")));
}