//
//  main.cpp
//  bp
//
//  Created by thotgamma on 2014/10/03.
//  Copyright (c) 2014年 thotgamma. All rights reserved.
//

#include <iostream>
#include "neuralNetwork.h"

neuralNetwork nnet;
bool nnetLauncher(std::vector<std::string> inputVector);


int main(int argc, const char * argv[]) {
    
    nnet.makeNewNetwork();
    
    
    std::vector<std::string> inputVector;
    while (true) {
        std::cout << ">>";
        std::string token;
        std::getline(std::cin, token);
        inputVector = nnet.split(token, ' ');
        if (inputVector[0] == "exit") {
            break;
        }
        nnetLauncher(inputVector);
    }
     
    
    nnet.learn("input_1.txt", 0.5, 5000);
    
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
    
    nnet.save("korena");
    
    
    return 0;
}

bool nnetLauncher(std::vector<std::string> inputVector){
    
#pragma mark command:new
    if (inputVector[0] == "new") {
        if (inputVector.size() != 1) {
            std::cout << "構文エラー:[new 入力層の数 中間層の数 出力層の数]" << std::endl;
            return false;
        }
        nnet.makeNewNetwork();
        return true;;
        
#pragma mark command:load
    }else if (inputVector[0] == "load"){
        if (inputVector.size() != 2) {
            std::cout << "構文エラー:[load ファイル名]" << std::endl;
            return false;
        }
        //nnet.load(inputVector[1]);
        return true;
        
#pragma mark command:save
    }else if (inputVector[0] == "save"){
        if (inputVector.size() != 2) {
            std::cout << "構文エラー:[save ファイル名]" << std::endl;
            return false;
        }
        nnet.save(inputVector[1]);
        return true;
        
#pragma mark command:learn
    }else if(inputVector[0] == "learn" ){
        if (inputVector.size() != 4) {
            std::cout << "構文エラー:[learn　教師ファイル名 学習係数 回数]" << std::endl;
            return false;
        }
        
        std::string filename = inputVector[1];
        double learningRate;
        std::stringstream(inputVector[2])>>learningRate;
        int roops;
        std::stringstream(inputVector[3])>>roops;
        nnet.learn(filename, learningRate, roops);
        return true;
        
#pragma mark command:calc
    }else if(inputVector[0] == "calc"){
        if (inputVector.size() < 2) {
            std::cout << "構文エラー:[calc 入力1 入力2...]" << std::endl;
            return false;
        }
        
        for (int i = 1; i < CC_numberOfCoreIn; i++) {
            double setter;
            std::stringstream(inputVector[i]) >> setter;
            nnet.inputCore[i] = setter;
        }
        
        nnet.advanceCalc();
        
        for (int i = 0; i < CC_numberOfCoreOut; i++) {
            std::cout   << "output"
            << i
            << ":"
            << nnet.outputCore[i]
            << std::endl;
        }
        nnet.resetCores();
        return true;
        
#pragma mark command:discard
    }else if(inputVector[0] == "discard"){
        if (inputVector.size() != 1) {
            std::cout << "構文エラー:[discard]" << std::endl;
            return false;
        }
        
        //nnet.discard();
        return true;
        
    }else if(inputVector[0] == "help"){
        std::cout << "" << std::endl;
        return true;
    }
    std::cout << "そのようなコマンドはありません。" << std::endl;
    std::cout << "コマンド\"help\"でコマンド一覧を表示できます。" << std::endl;
    
    return false;
}
