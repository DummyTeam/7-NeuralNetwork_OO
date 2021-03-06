#include "Neuron.h"
#include "Utils.h"
#include "Layer.h"
#include "ReLU.h"
#include "Sigmoid.h"
#include <string>

Neuron::Neuron(int id)
{
	this->squishification = new Sigmoid();
	this->id = id;
	init();
}

Neuron::Neuron(Squishification* squishification)
{
	this->squishification = squishification;
	this->id = 1;
	init();
}

void Neuron::init() {
	this->setActivationValue(0);
	this->bias = 0;
}

int Neuron::getId()
{
	return this->id;
}

double Neuron::getBias() {
	return this->bias;
}

double Neuron::getActivationValue()
{
	return this->activation;
}

void Neuron::setActivationValue(double activation) {
	this->activation = activation;
}

void Neuron::setDelta(double delta)
{
	this->delta = delta;
}

double Neuron::getDelta()
{
	return this->delta;
}

std::vector<Weight*> & Neuron::getInconmingWeights() {
	return this->weights;
}

double Neuron::squish(double value)
{
	return this->squishification->squish(value);
}

void Neuron::initWeightsAndBias(std::vector<Neuron*> &sourceNeurons)
{
	this->bias = 0.5;

	for (std::vector<Neuron*>::iterator neuron = sourceNeurons.begin(); neuron != sourceNeurons.end(); neuron++)
	{
		Weight* weight = new Weight(Utils::randomNumber(-1.0, 1.0), *neuron, this);

		this->weights.push_back(weight);
		(*neuron)->outgoingWeights.push_back(weight);
	}
}

void Neuron::calculateActivation()
{
	this->activation = 0;

	for (std::vector<Weight*>::iterator weight = this->weights.begin(); weight != this->weights.end(); weight++) {
		if ((*weight)->getSourceNeuron() != nullptr)
			this->activation += ((*weight)->getSourceNeuron()->activation * (*weight)->getValue());
	}

	this->activation += this->bias;
	this->setActivationValue(this->squish(this->activation));
}

void Neuron::updateWeightAndBias(double learningRate) {
	for (std::vector<Weight*>::iterator weight = this->weights.begin(); weight != this->weights.end(); weight++) {
		(*weight)->setValue((*weight)->getValue() + (*weight)->getSourceNeuron()->getActivationValue() * this->squishification->derivative(this->activation) * learningRate * this->getDelta());
	}

	this->bias += this->squishification->derivative(this->activation) * learningRate * this->getDelta();
}

void Neuron::calculatePreviousLayerNeuronDelta() {
	this->delta = 0;

	for (std::vector<Weight*>::iterator weight = this->outgoingWeights.begin(); weight != this->outgoingWeights.end(); weight++) {
		if ((*weight)->getSourceNeuron() != nullptr && (*weight)->getDestinationNeuron() != nullptr) {
			this->delta += ((*weight)->getValue() * (*weight)->getDestinationNeuron()->getDelta());
		}
	}
}

void Neuron::calculateOutputNeuronDelta(double expected) {
	this->delta = 2 * (expected - this->activation);
}
