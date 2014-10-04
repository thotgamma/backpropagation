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
    nnet.learn("input_1.txt", 0.3, 5000);
    
    /*
    nnet.inputCore[1] = 0.968627;
    nnet.inputCore[2] = 0.988235;
    nnet.inputCore[3] = 0.701961;
    nnet.advanceCalc();
    std::cout << "0.155714:" << nnet.outputCore[0] << std::endl;
    nnet.resetCores();
    
    nnet.inputCore[1] = 0.105882;
    nnet.inputCore[2] = 0.356863;
    nnet.inputCore[3] = 0.823529;
    nnet.advanceCalc();
    std::cout << "0.829286:" << nnet.outputCore[0] << std::endl;
    nnet.resetCores();
    
    nnet.inputCore[1] = 0.964706;
    nnet.inputCore[2] = 0.968627;
    nnet.inputCore[3] = 0.498039;
    nnet.advanceCalc();
    std::cout << "0.0707143:" << nnet.outputCore[0] << std::endl;
    nnet.resetCores();
     */
    
    
    nnet.save("a");
    
    return 0;
}


