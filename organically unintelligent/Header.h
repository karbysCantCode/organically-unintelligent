#pragma once
#include <vector>
#include <iostream>
#include "randomNumbers.h"
#include "mathFunctions.h"

struct connection {
	double weight = 0;
};

class neuron {
public:
	std::vector<connection> connections;
	std::vector<double> activationContribution;
	std::vector<neuron>* layerBehind;
	int layer;
	int id;
	double bias = 0;
	double activation = 0;

	void getActivation(std::vector<neuron>& lastLayer) {
		layerBehind = &lastLayer;
		activationContribution.clear();
		activation += bias;
		for (const neuron& currentNeuron : lastLayer) {
			const double result = currentNeuron.activation * connections[currentNeuron.id - 1].weight;
			activationContribution.push_back(result);
			activation += result;
			
		}
		activation = relu(activation);
	}

	void analyseContributions() {
		std::vector<double> activationPower;

	}
};

class brain {
public:
	int layerCount;
	int inputNeurons;
	int outputNeurons;
	int internalNeurons;
	std::vector<std::vector<neuron>> layers;

	brain(int LayerCount, int input, int output, int Internal) : 
		layerCount(LayerCount),
		layers(LayerCount+2),
		inputNeurons(input),
		outputNeurons(output),
		internalNeurons(Internal) {
		//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
		for (int i = 0; i < layerCount+2; ++i) {
			std::cout << "initilizing layer: " << i;
			layers[i] = std::vector<neuron>();
			std::cout << " success\n";
		}


	}

	void setInputNeurons(std::vector<double> &inputArray) {
		for (neuron& currentNeuron : layers[0]) {
			currentNeuron.activation = inputArray[currentNeuron.id - 1];
		}
	}

	void initLayers() {
		for (int i = 0; i < inputNeurons; ++i) {
			neuron n;
			n.activation = 0;
			n.bias = randomDouble(-1, 1);
			n.layer = 0;
			n.id = i+1;
			layers[0].push_back(n);
			std::cout << "added neuron: " << n.id << " to layer: " << 0 << '\n';
		}
		for (int l = 0; l < layerCount; ++l) {
			for (int i = 0; i < internalNeurons; ++i) {
				neuron n;
				n.activation = 0;
				n.bias = randomDouble(-1, 1);
				n.layer = l+1;
				n.id = i + 1;
				planConnections(n);
				layers[l+1].push_back(n);
				std::cout << "added neuron: " << n.id << " to layer: " << l+1 << '\n';
			}
		}

		for (int i = 0; i < outputNeurons; ++i) {
			neuron n;
			n.activation = 0;
			n.bias = randomDouble(-1, 1);
			n.layer = layerCount+1;
			n.id = i + 1;
			
			planConnections(n);
			layers[layerCount+1].push_back(n);
			std::cout << "added neuron: " << n.id << " to layer: " << layerCount + 1 << '\n';
		}
	}

	void passLayers() {
		for (int currentLayer = 1; currentLayer < layerCount+2; ++currentLayer) {
			for (neuron& currentNeuron : layers[currentLayer]) {
				currentNeuron.getActivation(layers[currentLayer - 1]);
			}
		}

		for (const neuron& currentNeuron : layers[layerCount+1]) {
			std::cout << "Neuron: " << currentNeuron.id << " Bias: " << currentNeuron.bias << " Activation: " << currentNeuron.activation << '\n';
		}
	}

	void trainLayers(std::vector<double> &desiredOutputs) {

	}

	void printLayers() {
		for (int layer = 0; layer < layers.size(); ++layer) {
			std::cout << "Layer: " << layer + 1 << '\n';
			for (const auto& currentNeuron : layers[layer]) {
				std::cout << "	Neuron: " << currentNeuron.id << '\n';
				std::cout << "		Activation: " << currentNeuron.activation << '\n';
				std::cout << "		Bias: " << currentNeuron.bias << '\n';
			}
		}
	}
	void printLayers(int layerToPrint) {
		std::cout << "Layer: " << layerToPrint << '\n';
		for (const neuron& currentNeuron : layers[layerToPrint]) {
			std::cout << "	Neuron: " << currentNeuron.id << '\n';
			std::cout << "		Activation: " << currentNeuron.activation << '\n';
			std::cout << "		Bias: " << currentNeuron.bias << '\n';
		}
	}
private:

	int getNeuronsInLastLayer(int layer) {
		if (layer == 1) {
			return inputNeurons;
		}
		else if (layer == 0) {
			return 0;
		}
		else {
			return internalNeurons;
		}

	}
	void planConnections(neuron &currentNeuron) {
		int neuronsInLastLayer = getNeuronsInLastLayer(currentNeuron.layer);
		if (neuronsInLastLayer == 0) return;
		
		for (int i = 0; i < neuronsInLastLayer; ++i) {
			connection c;
			c.weight = randomDouble(-1, 1);
			currentNeuron.connections.push_back(c);
		}
	}
};