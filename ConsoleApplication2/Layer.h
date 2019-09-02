#pragma once

#include "Helpers.h"
#include "Neuron.h"
#include <exception>

/** 
 * @class Layer
 * @brief Represents a layer of your network
 * 
 * It can represent any type of layer (such as inputs, hidden layers, or outputs)
 *
 * @author Simon Murier
 */
template <typename T>
class Layer
{
public:
	/*!
	 * @brief Constructor
	 *
	 * Layer class constructor
	 *
	 * @param values Values used to initialize your Neurons
	 * @param layerLevel Level of your layer
	 */
	Layer<T>(size_t layerLevel) { m_layerLevel = layerLevel; }

	/*!
	 * @brief Destructor
	 *
	 * Layer class destructor
	 */
	virtual ~Layer<T>() {}

private:
	size_t m_layerLevel;
};



template <typename T>
class InputLayer : public Layer<T>
{
public:
	InputLayer<T>(std::vector<T> &values, std::vector<T> &weights) : Layer<T>(1) 
	{
		std::for_each(values.begin(), values.end(), [this, weights](const T &t)
		{
			this->m_neurons.push_back(InputNeuron<T>(t, weights));
		});
	}

	std::vector<InputNeuron<T>> GetNeurons() { return m_neurons; }

private:
	std::vector<InputNeuron<T>> m_neurons;
};



template <typename T>
class HiddenLayer : public Layer<T>
{
public:
	HiddenLayer<T>(std::vector<T> &values, T b) : Layer<T>(1) //TODO
	{
		std::for_each(values.begin(), values.end(), [this, values, b](const T &t)
		{
			this->m_neurons.push_back(HiddenNeuron<T>(t, values, b));
		});
	}

private:
	std::vector<HiddenNeuron<T>> m_neurons;
};



template <typename T>
class OutputLayer : public Layer<T>
{
public:
	OutputLayer<T>(std::vector<T> &values, T b) : Layer<T>(1) //TODO
	{
		std::for_each(values.begin(), values.end(), [this, b](const T &t)
		{
			this->m_neurons.push_back(OutputNeuron<T>(t, b));
		});
	}

private:
	std::vector<OutputNeuron<T>> m_neurons;
};
