#include <NeuralNet.h>

int main()
{
    std::vector<unsigned> topo = {64,2};
    NeuralNet Net(topo);
    std::vector<double> target = {0,1};
    std::vector<double> input = {2,3,5,5,23};
    for (unsigned i=0; i<50; i++){
        Net.feedForward(input);
        Net.getOutput();
        Net.backPropagate(target);
    }
    //Net.trainOnce("phsd50csr.auau.31.2gev.centr.0000phsd50csr.auau.31.2gev.centr.0_event.dat", target);
    //Net.trainWithBatch("D:/Bioinfo/PRG-Pr/Milestone2/dataset_half/nqgp", 10, target);
    return 0;
}
