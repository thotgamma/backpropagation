//
//  neuralNetwork.cpp
//  bp
//
//  Created by thotgamma on 2014/10/03.
//  Copyright (c) 2014年 thotgamma. All rights reserved.
//

#include "neuralNetwork.h"

neuralNetwork::neuralNetwork(){
    
}

void neuralNetwork::makeNewNetwork(){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> random(0.0,1.0);
    
    for (int i=0; i < CC_numberOfCoreIn; i++) {
        for (int j=0; j < CC_numberOfCoreHidd; j++) {
            netIn2Hidd[i][j] = random(mt);
        }
    }
    
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        for (int j=0; j < CC_numberOfCoreOut; j++) {
            netHidd2Out[i][j] = random(mt);
        }
    }
    
    inputCore[0] = 1;   //バイアス

}

void neuralNetwork::advanceCalc(){
    
    /*
    //値のセット
    for (int i=1; i < CC_numberOfCoreIn; i++) {
        inputCore[i] = input[i-1];
    }
    */
    
    for (int i=0; i < CC_numberOfCoreIn; i++) {
        for (int j=0; j < CC_numberOfCoreHidd; j++) {
            hiddenCore[j] = hiddenCore[j] + inputCore[i] * netIn2Hidd[i][j];
        }
    }
    
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        hiddenCore[i] = sigmoid(hiddenCore[i]);
    }
    
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        for (int j=0; j < CC_numberOfCoreOut; j++) {
            outputCore[j] = outputCore[j] + hiddenCore[i] * netHidd2Out[i][j];
        }
    }
    
    for (int i=0; i < CC_numberOfCoreOut; i++) {
        outputCore[i] = sigmoid(outputCore[i]);
    }
    //std::cout << outputCore[0] << std::endl;
}

void neuralNetwork::resetCores(){
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        hiddenCore[i] = 0;
    }
    for (int i=0; i < CC_numberOfCoreOut; i++) {
        outputCore[i] = 0;
    }
}

void neuralNetwork::backwardCalc(double answer,double learningRate){
    
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        for (int j=0; j < CC_numberOfCoreOut; j++) {
            double fix = learningRate * (answer - outputCore[j]) * outputCore[j] * (1 - outputCore[j]) * hiddenCore[i];
            fixTmp[i] = fixTmp[i] + fix * netHidd2Out[i][j];
            netHidd2Out[i][j] = netHidd2Out[i][j] + fix;
            //std::cout << "fix:" << fix << std::endl;
            
        }
    }
    
    for (int i=0; i < CC_numberOfCoreIn; i++) {
        for (int j=0; j < CC_numberOfCoreHidd; j++) {
            double fix = learningRate * hiddenCore[j] * (1 - hiddenCore[j]) * fixTmp[j] * inputCore[i];
            netIn2Hidd[i][j] = netIn2Hidd[i][j] + fix;
        }
    }
    
    for (int i=0;i < CC_numberOfCoreHidd; i++) {
        fixTmp[i] = 0;
    }
}

void neuralNetwork::learn(std::string filename, double learningRate, int roops){
    std::vector<std::string> splitedTeachData;
    
    std::vector<std::string> answerGroupVector;
    std::vector<std::string> inputGroupVector;
    
    std::vector<std::string> answerTokenVector;
    std::vector<std::string> inputTokenVector;
    
    std::ifstream teachFile(filename);
    std::string line;
    
    double diff = 0;
    
    double answer;
    
    while (std::getline(teachFile, line)) {
        
        splitedTeachData = split(line, ':');    //学習ファイルから、入力と答えとで分離
        
        inputGroupVector.push_back(splitedTeachData[0]);
        answerGroupVector.push_back(splitedTeachData[1]);
        
    }
    
    
    for (int i = 0; i< roops; i++) {
        
        diff = 0;
        
        for (int j = 0; j < inputGroupVector.size(); j++) {
            answerTokenVector = split(answerGroupVector[j], ' ');
            inputTokenVector = split(inputGroupVector[j], ' ');
            std::stringstream(answerTokenVector[0]) >> answer;
            
            //値のセット
            for (int i=1; i < CC_numberOfCoreIn; i++) {
                std::stringstream(inputTokenVector[i-1]) >> inputCore[i];
                //std::cout << "set:" << inputCore[i] << std::endl;
            }
            advanceCalc();
            backwardCalc(learningRate, answer);
            //std::cout << "ans:" << answer << std::endl;
            diff = diff + pow(outputCore[0]-answer, 2);
            resetCores();
        }
        
        
        teachFile.clear();
        teachFile.seekg(0, std::fstream::beg);
        std::cout << i <<":"<< diff << std::endl;
        
    }
    //return diff;
}




std::vector<std::string> neuralNetwork::split(std::string input,char separator){
    
    std::vector<std::string> output;
    
    std::istringstream iss(input);
    std::string token;
    
    while(getline(iss, token, separator))
    {
        output.push_back(token);
    }
    
    return output;
}

double neuralNetwork::sigmoid(double input) {
    return 1 / (1 + exp(-input));
}