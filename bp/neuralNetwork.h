//
//  neuralNetwork.h
//  bp
//
//  Created by thotgamma on 2014/10/03.
//  Copyright (c) 2014年 thotgamma. All rights reserved.
//

#ifndef __bp__neuralNetwork__
#define __bp__neuralNetwork__

#include "const.h"

#include <stdio.h>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "math.h"

class neuralNetwork{
public:
    
    int individualID;
    double score;
    
    double inputCore[CC_numberOfCoreIn];
    double hiddenCore[CC_numberOfCoreHidd];
    double outputCore[CC_numberOfCoreOut];
    
    double fixTmp[CC_numberOfCoreHidd];
    
    double netIn2Hidd[CC_numberOfCoreIn][CC_numberOfCoreHidd];
    double netHidd2Out[CC_numberOfCoreHidd][CC_numberOfCoreOut];
    
    neuralNetwork();
    void makeNewNetwork();
    void load(std::string filename);
    void save(std::string filename);
    void discard();
    void advanceCalc();
    void backwardCalc(double answer,double learningRate);
    double sigmoid(double input);
    void resetCores();
    void learn(std::string filename,double learningRate,int roops);
    std::vector<std::string> split(std::string input,char separator);
};


#endif /* defined(__bp__neuralNetwork__) */
