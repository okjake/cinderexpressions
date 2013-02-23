//
//  ExpressionClassifier.cpp
//  MoodDrawing
//
//  Created by Jake Pyne on 24/07/2012.
//

#include "ExpressionClassifier.h"
#include "cinder/CinderMath.h"
#include "cinder/Xml.h"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <map>

ExpressionClassifier::ExpressionClassifier() {
}

void ExpressionClassifier::setup(std::string appPath) {
    boost::filesystem::path expressionsFolder(appPath + "/Contents/Resources/Expressions");
    std::cout << expressionsFolder;
    boost::filesystem::directory_iterator end_iter;
    
    if ( boost::filesystem::exists(expressionsFolder) && boost::filesystem::is_directory(expressionsFolder))
    {
        std::cout << "Known expressions: " << std::endl;
        for( boost::filesystem::directory_iterator dir_iter(expressionsFolder) ; dir_iter != end_iter ; ++dir_iter)
        {
            if (boost::filesystem::is_regular_file(dir_iter->status()) && !(dir_iter->path().filename().string().compare(".DS_Store") == 0))
            {
                std::cout << *dir_iter << std::endl;
                
                ci::XmlTree doc( ci::loadFile( *dir_iter ));
                ci::XmlTree expression = doc.getChild("expression");
                
                std::map<std::string, std::string> expressionDoc; 
                
                for( ci::XmlTree::Iter child = expression.begin(); child != expression.end(); ++child )
                    expressionDoc[child->getTag()] = child->getValue();
                
                knownExpressions.push_back(Expression(dir_iter->path().filename().string(),
                                                      boost::lexical_cast<float>(expressionDoc["mouthWidth"]), 
                                                      boost::lexical_cast<float>(expressionDoc["mouthHeight"]),
                                                      boost::lexical_cast<float>(expressionDoc["eyebrowLeft"]),
                                                      boost::lexical_cast<float>(expressionDoc["eyebrowRight"]),
                                                      boost::lexical_cast<float>(expressionDoc["eyeLeft"]),
                                                      boost::lexical_cast<float>(expressionDoc["eyeRight"]),
                                                      boost::lexical_cast<float>(expressionDoc["jaw"]),
                                                      boost::lexical_cast<float>(expressionDoc["nostrils"])));
            }
        }
    }
}

/*
 * Tests a provided expression against those known
 * Returns whichever is closest
 */
void ExpressionClassifier::classify(Expression *testExpression) {
    
    float distances[knownExpressions.size()];
    short int   minIndex = 0;
    float       minimum = 90000.0f;
    for ( int i = 0; i < knownExpressions.size(); i++) {
        distances[i] = sqrtf(
                        powf(knownExpressions[i].getMouthWidth()     - testExpression->getMouthWidth(), 2) +
                        powf(knownExpressions[i].getMouthHeight()    - testExpression->getMouthHeight(), 2) +
                        powf(knownExpressions[i].getEyebrowLeft()    - testExpression->getEyebrowLeft(), 2) +
                        powf(knownExpressions[i].getEyebrowRight()   - testExpression->getEyebrowRight(), 2) +
                        powf(knownExpressions[i].getEyeLeft()        - testExpression->getEyeLeft(), 2) +
                        powf(knownExpressions[i].getEyeRight()       - testExpression->getEyeRight(), 2) +
                        powf(knownExpressions[i].getJaw()            - testExpression->getJaw(), 2) +
                        powf(knownExpressions[i].getNostrils()       - testExpression->getNostrils(), 2)
                    );
        if (distances[i] < minimum) {
            minimum = distances[i];
            minIndex = i;
        }
    }
    
    // Find lowest distance and return that expression
    if (knownExpressions.size() > 0) {
        std::cout << "CURRENT EXPRESSION: " << knownExpressions[minIndex].getDescription() << std::endl;
    }
}
