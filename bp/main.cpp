//
//  main.cpp
//  bp
//
//  Created by thotgamma on 2014/10/03.
//  Copyright (c) 2014年 thotgamma. All rights reserved.
//

#include <iostream>
#include "neuralNetwork.h"


int main(int argc, const char * argv[]) {
    
    neuralNetwork nnet;
    nnet.makeNewNetwork();
    
    nnet.learn("input.txt", 0.5, 5000);
    
    nnet.inputCore[1] = 0;
    nnet.advanceCalc();
    std::cout << "calc 0:" << nnet.outputCore[0] << std::endl;
    nnet.resetCores();
    nnet.inputCore[1] = 0.5;
    nnet.advanceCalc();
    std::cout << "calc 0.5:" << nnet.outputCore[0] << std::endl;
    nnet.resetCores();
    nnet.inputCore[1] = 1;
    nnet.advanceCalc();
    std::cout << "calc 1:" << nnet.outputCore[0] << std::endl;
    nnet.resetCores();
    
    
    return 0;
}


