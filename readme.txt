Grundlagen der Programmierung - Praktikum

Gruppenmitgliede:

Thanh Giang Nguyen (G)
Duy Pham (D)
Thi Hoa Nguyen (H)
==============================================
Milestone 2

Exercises 1 and 2 are implemented as project "NeuralNet".
Exercises 3, 4a and 4b are implemented as separate projects.

Class Neuron (G) - Arbeitszeit: 1 Woche, ungefähr 3-4 Stunden pro Tag, insgesamt 21 bis 28 Stunden,
(nicht nur die Zeit für Code sondern auch für Lesen der Literatur und Recherieren)

Die Klasse Neuron hat diese folgende Hauptfunktion

	Constructor: 	Neuron(); Dieser Constructor nimmt 2 Argumente, stranding und name, dabei ist stranding die Nummer von der Neuronen,
			die dieses Neuron erreicht und name ist Index von diesem Neuron in der Layer

	feed_foward(): Diese Funktion nimmt als Argument ein Vector, das die Neuronen des vorherigen Layers enthält, um Output mit der Activationfunction zu berechnen

	output_gradient(): Diese Funktion nimmt eine Liste von Zielouputs als Argument, um Output Gradient zu berechnen

	hidden_gradient(): Diese Funktion nimmt das nächste Layer als Argument, um Hidden Gradient zu berechnen

	update_weight(): Diese Funktion nimmt das vorherige Layer als Argument, um weight des Neurons zu aktuallisieren

class NeuralNet (D) - 30 hours - not done (diagnose: problem with back propagation)
	NeuralNet (std::vector<unsigned> Topology) 	Takes a vector of double as topology
							and creats a NN with that topology and an emmpty input layer
	getTopology() 					Prints out topology of neural network
	setTopology(std::vector<unsigned> Topology)	Changes topology of neural network
	getOutput()					Prints out predicted result
	setTarget(std::vector<double> targetResult)	Sets sample result
	feedForward(std::vector<double> inputVals)	Uses a vector of double as input values and
							execute Feed-forward algorithm
	backPropagate(std::vector<double> targetVals)	Uses a vector of double as target values and
							execute Backpropagation algorithm
	trainOnce(std::string dataName, std::vector<double> targetResult)	Takes a data name as string and
										trains with data from it and target result.
	trainWithBatch(char directory[], unsigned batchSize, std::vector<double> targetResult)	Takes directory to a folder
							as character array, get all training data from it and  trains with 
							batch of data, whose size is given 

Exercise 3 (H) - 4 hours - not done
Create a user interface:
- Load Date Button: The user can load Data on this computer
- Analyze Button: The user can change parameter of quantity of epoch
- Neural Net Mode Box: to change the topology of the neural network: 
+FC NN without Hidden-Layer
+FC NN with one Hidden-Layer
+FC NN with two Hidden-Layer
- Draw: to display graph:
+ Histogram
+ Success Rate
+ Distribution

Exercise 4a (H) - 2 hours
Create a widget with a drawing area on which the graphs can be displayed.
Use the QCustomPlot Library.
The user can enter the axis labels themselves

Exercise 4b (H) - 2 hours
Create a possibility on the GUI to display another small graph with the loss rate per epoch 
(in parallel next to the other graphs).
Here I create 2 widget for 2 graphs, one more for Eﬃciency per epoch, and one more for Loss rate per epoch