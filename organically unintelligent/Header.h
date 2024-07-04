#pragma once
#include <vector>
#include "randomNumbers.h"

struct connection {
	double weight;
};

class neuron {
public:
	std::vector<connection> connections;
	int layer;
	int id;
	double activation;
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
		layers(LayerCount),
		inputNeurons(input),
		outputNeurons(output),
		internalNeurons(Internal) {
		//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
		for (int i = 0; i < LayerCount; ++i) {
			layers[i] = std::vector<neuron>();
		}


	}

	void initLayers() {
		for (int i = 0; i < inputNeurons; ++i) {
			layers[0][i].activation = randomDouble(-1.0,1.0);
			layers[0][i].id = i;
			layers[0][i].layer = 0;
		}
		for (int l = 0; l < layerCount; ++l) {
			for (int i = 0; i < internalNeurons; ++i) {
				layers[l + 1][i].activation = randomDouble(-1.0, 1.0);
				layers[l + 1][i].id = i;
				layers[l + 1][i].layer = l + 1;
			}
		}

		for (int i = 0; i < outputNeurons; ++i) {
			layers[layerCount][i].activation = randomDouble(-1.0, 1.0);
			layers[layerCount][i].id = i;
			layers[layerCount][i].layer = layerCount;
		}
	}

	void passLayers() {
		for (int currentLayer = 0; currentLayer < layerCount; ++currentLayer) {
			const int neuronsInNext = getNeuronsInNextLayer(currentLayer);
			for (int currentNeuron = 0; currentNeuron < neuronsInNext; ++currentNeuron) {
				if (neuronsInNext == 0) return;

			}
		}
	}
private:

	int getNeuronsInNextLayer(int layer) {
		if (layer == layerCount) {
			return 0;
		}
		else if (layer == layerCount - 1) {
			return outputNeurons;
		}
		else {
			return internalNeurons;
		}

	}
	void planConnections(neuron currentNeuron) {
		int neuronsInNextLayer = getNeuronsInNextLayer(currentNeuron.layer);
		if (neuronsInNextLayer == 0) return;
		
		for (int i = 0; i < neuronsInNextLayer; ++i) {
			currentNeuron.connections[i].weight = randomDouble(-1, 1);
		}
	}
};