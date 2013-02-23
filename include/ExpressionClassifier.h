//
//  ExpressionClassifier.h
//  MoodDrawing
//
//  Created by Jake Pyne on 23/07/2012.
//  Copyright 2012 TUI Interactive Media. All rights reserved.
//

#ifndef MoodDrawing_ExpressionClassifier_h
#define MoodDrawing_ExpressionClassifier_h

#include "Expression.h"
#include <vector>

class ExpressionClassifier {
    
    public:
        ExpressionClassifier();
        void setup(std::string appPath);
        void classify(Expression *testExpression);

    protected:
        std::vector<Expression> knownExpressions;
};

#endif
