#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <random>

struct Weight
{
    double w;
    double d;
};

class Neuron;
typedef std::vector<Neuron> Layer;

class Neuron{
public:
    unsigned long long index;   // Idex of neuron in its layer
    double output;              // Value contained by neuron
    std::vector<Weight> weights; // All connetion weights of neuron
    double gradient;
    static double eta;      // Learning rate
    static double alpha;

    // Create random double value for each weight
    double randomWeight(){
        double w = static_cast<double>(rand())/RAND_MAX;
        return w;
    }

    double activationFunction(double, std::vector<double>);
    double activationFunction_derivate(double);
    // Constructor
    Neuron(unsigned long long children, unsigned long long index){
        this->index = index;
        for (unsigned i=0; i<children; i++){
            this->weights.push_back(Weight());
            this->weights.back().w = randomWeight();
            this->weights.back().d = 0;
        }
    }

    // Return value of neuron
    double getOutput(){return output;}

    // Set a double as neuron's value
    void setOutput(double d){this->output = d;}

    // Feed this neuron with values from previous layer
    void feedForward(Layer prevLayer){
        double val=0;
        for (unsigned i=0; i<(prevLayer.size()); i++){
            val += prevLayer[i].getOutput() * prevLayer[i].weights[index].w;
        }
        std::vector<double> all;
        for (unsigned i=0; i<prevLayer[0].weights.size(); i++){
            double x = 0;
            for (unsigned j=0; j<prevLayer.size(); j++){
                x += prevLayer[j].getOutput() * prevLayer[j].weights[i].w;
            }
            all.push_back(x);
        }
        this->output = activationFunction(val, all);
    }

    // Calculate gradients of neurons in output layer
    void outputGradient(double target){
        double delta = target - this->output;
        this->gradient = delta * activationFunction_derivate(this->output);
    }

    // Calculate gradients of neurons in hidden layers
    void hiddenGradient(Layer nextLayer){
        double sum=0;
        for (unsigned long long i=0; i<(nextLayer.size()); i++){
            sum += this->weights[i].w * nextLayer[i].gradient;
        }
        this->gradient = sum * activationFunction_derivate(this->output);
    }

    // update weights of neuron using gradient
    void updateWeight(Layer prevLayer){
        for (unsigned long long i=0; i<(prevLayer.size()); i++){
            Neuron neuron = prevLayer[i];
            double oldDelta = neuron.weights[this->index].d;
            double newDelta = eta * neuron.getOutput() * this->gradient + alpha * oldDelta;
            prevLayer[i].weights[this->index].d = newDelta;
            prevLayer[i].weights[this->index].w += newDelta;
        }
    }

    // Print out all weights of neuron
    void getWeight(){
        for(unsigned i=0; i<this->weights.size(); i++){
            std::cout << weights[i].w << " ";
        }
    }
};

double Neuron::eta = 1;
double Neuron::alpha = 0.5;

// Softmax as activation function
double Neuron::activationFunction(double val, std::vector<double> all){
    double sum = 0;
    for (unsigned i=0; i<all.size(); i++){
        sum += exp(all[i]);
    }
    return exp(val) / sum;
}

// Derivate of activation funtion
double Neuron::activationFunction_derivate(double x){
    return x * (1 - x);
}

#endif // NEURON_H
