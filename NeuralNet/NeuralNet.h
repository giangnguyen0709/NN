#ifndef NEURALNET_H
#define NEURALNET_H

#include <Neuron.h>
#include <fstream>
#include <dirent.h>
#include <string.h>

class NeuralNet {
private:
    std::vector<unsigned> Topology;
    Layer inputLayer;
    Layer outputLayer;
    double loss;
    std::vector<Layer> layers;
public:

    // Constructer
    NeuralNet (std::vector<unsigned> Topology){
        for (unsigned i=0; i<Topology.size(); i++){
            unsigned children = i == (Topology.size() - 1) ? 0 : Topology[i + 1];
            this->layers.push_back(Layer());
            for (unsigned j=0; j<Topology[i]; j++){
                this->layers.back().push_back(Neuron(children, static_cast<unsigned long long>(j)));
            }
        }
        layers.insert(layers.begin(), Layer());
    }


    // Print out topology of neural network
    void getTopology() {
        for (unsigned i=1; i<layers.size(); i++){
            std::cout<<layers[i].size()<<' ';
        }
        std::cout<<std::endl;
    }

    // Change topology of neural network
    void setTopology(std::vector<unsigned> Topology){
        layers.clear();
        for (unsigned i=0; i<Topology.size(); i++){
            unsigned children = i == (Topology.size() - 1) ? 0 : Topology[i + 1];
            this->layers.push_back(Layer());
            for (unsigned j=0; j<=Topology[i]; j++){
                this->layers.back().push_back(Neuron(children, static_cast<unsigned long long>(j)));
            }
        }
        layers.insert(layers.begin(), Layer());
    }

    // Print out predicted result
    void getOutput(){
        std::cout<<"Prediction: ";
        for (unsigned i=0; i<layers.back().size(); i++){
            std::cout<<layers.back()[i].getOutput()<<' ';
        }
        std::cout<<std::endl;
    }


    // Set sample result
    void setTarget(std::vector<double> targetResult){
        layers.back().clear();
        for (unsigned i=0; i<targetResult.size(); i++){
            Neuron temp(0,i);
            temp.setOutput(targetResult[i]);
            layers.back().push_back(temp);
        }
    }

    // Feed-forward algorithm
    void feedForward(std::vector<double> inputVals){
        if (layers[0].size()==0) {
            for (unsigned i=0; i<inputVals.size(); i++){
                layers[0].push_back(Neuron(layers[1].size(),i));
            }
            for (unsigned i=0; i<inputVals.size(); i++) {
                layers[0][i].setOutput(inputVals[i]);
            }
        }
        else {
            for (unsigned i=0; i<inputVals.size(); i++) {
                layers[0][i].setOutput(inputVals[i]);
            }
        }
        std::cout<<"inputLayer size: "<<layers[0].size()<<std::endl;
        for (unsigned i=0; i<layers[0].size(); i++){
            std::cout<<layers[0][i].getOutput()<<' ';
        }
        std::cout<<std::endl;
        for (unsigned i=1; i<layers.size(); i++){
            for (unsigned j=0; j<layers[i].size(); j++){
                layers[i][j].feedForward(layers[i-1]);
            }
        }
    }

    // Backpropagation algorithm
    void backPropagate(std::vector<double> targetVals){
        loss = 0;
        outputLayer = layers.back();
        for (unsigned i=0; i<outputLayer.size(); i++){
            double temp = targetVals[i] - outputLayer[i].getOutput();
            loss += temp * temp;
        }
        loss = loss/2;

        // Calculate gradients in output layer
        for (unsigned i=0; i<outputLayer.size(); i++){
            outputLayer[i].outputGradient(targetVals[i]);
        }

        // Calculate gradients in hidden layers
        for (unsigned i = layers.size()-2; i>0; i--){
            for (unsigned j=0; j<layers[i].size(); j++){
                layers[i][j].hiddenGradient(layers[i+1]);
            }
        }

        // Update the connection weights
        for (unsigned i = layers.size()-1; i>0; i--){
            for (unsigned j=0; j<layers[i].size(); j++){
                layers[i][j].updateWeight(layers[i-1]);
            }
        }
    }

    // Train with one sample data
    void trainOnce(std::string dataName, std::vector<double> targetResult){
        std::ifstream data;
        data.open(dataName);
        char c;
        std::vector<double> inputVals;
        while (true){
            if (data.eof())
                break;
            data.get(c);
            if (isdigit(c)){
                inputVals.push_back(static_cast<double>(c-48));
            }
        }
        std::cout<<"input size "<<inputVals.size()<<std::endl;
        feedForward(inputVals);
        getOutput();
        backPropagate(targetResult);
    }

    // Train with batch
    void trainWithBatch(char directory[], unsigned batchSize, std::vector<double> targetResult){
        /*
        string myDirectory="";
        for(char& c : directory){
            if (c == '/')
        }
        */
        // Get a list of all data
        DIR *dir;
        struct dirent *ent;
        std::vector<std::string> dataList;
        if ((dir = opendir(directory)) != NULL) {
            // Get all data within directory
            while ((ent = readdir(dir)) != NULL) {
                std::string fileName(ent->d_name);
                if (fileName.size()>5){
                    dataList.push_back(fileName);
                }
            }
            closedir (dir);
        }
        // Could not open directory
        else {perror("");}

        std::cout<<"Training data: "<<dataList.size()<<std::endl;
        for (unsigned i=0; i<dataList.size(); i++){
            std::cout<<dataList[i]<<std::endl;
        }

        // Train using all data from list
        /*if (batchSize<=fileList.size()){
            for (unsigned i=0; i<batchSize; i++){
                trainOnce(fileList[i], targetResult);
            }
        }
        */
    }

};

#endif // NEURALNET_H
