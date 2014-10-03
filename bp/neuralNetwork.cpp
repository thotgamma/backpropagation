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

//重みをランダムに決定
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

//前向き計算
void neuralNetwork::advanceCalc(){
    
    /*
    //値のセット
    for (int i=1; i < CC_numberOfCoreIn; i++) {
        inputCore[i] = input[i-1];
    }
    */
    
    //入力層 -> 隠れ層
    for (int i=0; i < CC_numberOfCoreIn; i++) {
        for (int j=0; j < CC_numberOfCoreHidd; j++) {
            hiddenCore[j] = hiddenCore[j] + inputCore[i] * netIn2Hidd[i][j];
        }
    }
    
    //隠れ層の値をシグモイド関数に通す
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        hiddenCore[i] = sigmoid(hiddenCore[i]);
    }
    
    //隠れ層->出力層
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        for (int j=0; j < CC_numberOfCoreOut; j++) {
            outputCore[j] = outputCore[j] + hiddenCore[i] * netHidd2Out[i][j];
        }
    }
    
    //出力層の値をシグモイド関数に通す
    for (int i=0; i < CC_numberOfCoreOut; i++) {
        outputCore[i] = sigmoid(outputCore[i]);
    }
}

void neuralNetwork::resetCores(){
    //隠れ層の値を消去
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        hiddenCore[i] = 0;
    }
    //出力層の値を消去
    for (int i=0; i < CC_numberOfCoreOut; i++) {
        outputCore[i] = 0;
    }
}


//後ろ向き計算
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
            }
            
            advanceCalc();
            backwardCalc(answer,learningRate);
            diff = diff + pow(outputCore[0]-answer, 2);
            resetCores();
        }
        
        
        teachFile.clear();
        teachFile.seekg(0, std::fstream::beg);
        std::cout << i <<":"<< diff << std::endl;
        
    }
    //return diff;
}

void neuralNetwork::save(std::string filename){
    std::ofstream network_scc(filename);
    
    network_scc << "[core]\n";
    network_scc << CC_numberOfCoreIn;
    network_scc << " ";
    network_scc << CC_numberOfCoreHidd;
    network_scc << " ";
    network_scc << CC_numberOfCoreOut;
    network_scc << "\n";
    
    network_scc << "[net]\n";
    
    //coreIN -> coreHidden
    for (int i=0; i < CC_numberOfCoreIn; i++) {
        for (int j=0; j < CC_numberOfCoreHidd; j++) {
            network_scc << "0";
            network_scc << " ";
            network_scc << i;
            network_scc << " ";
            network_scc << j;
            network_scc << " ";
            network_scc << netIn2Hidd[i][j];
            network_scc << "\n";
        }
    }
    
    //coreHidden -> coreOut
    for (int i=0; i < CC_numberOfCoreHidd; i++) {
        for (int j=0; j < CC_numberOfCoreOut; j++) {
            network_scc << "1";
            network_scc << " ";
            network_scc << i;
            network_scc << " ";
            network_scc << j;
            network_scc << " ";
            network_scc << netIn2Hidd[i][j];
            network_scc << "\n";
        }
    }
    
    network_scc.close();
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