#pragma once

#include <cmath>
#include <vector>

#define e			2.71828
#define Euler(x)	pow(e,x)


/**
 * @class Neuron
 * @brief Represents a neuron of a specific layer
 *
 * It can hold any type of value (might be reverted later on to focus on a more intuitive solution)
 *
 * @author Simon Murier
 */
template<typename T>
class Neuron
{
public:
	/*!
	 * @brief Constructor
	 *
	 * Neuron class constructor
	 *
	 * @param val Value hold by the neuron
	 */
	Neuron<T>(T val) { this->val = val; }

	/*!
	 * @brief Destructor
	 *
	 * Neuron class destructor
	 */
	virtual ~Neuron<T>() {}

	/*!
	 * @brief Neuron activation function
	 *
	 * Sigmoïd function hardcoded, more options available later on
	 */
	virtual void Activate() = 0;

	/*!
	 * @brief Neuron derivative function
	 *
	 * Sigmoïd function hardcoded, more options available later on
	 */
	virtual void Derive() = 0;

	//Getters
	T GetVal() { return this->val; }

	virtual T GetActivatedVal() = 0;
	virtual T GetDerivedVal() = 0;

	virtual T GetWeightFromSubscript(size_t subscript) = 0;

	virtual T GetBias() = 0;

protected:
	T val;

	T activatedVal;
	T derivedVal;

	std::vector<T> weights;

	T bias;
};


template<typename T>
class InputNeuron : public Neuron<T>
{
public:
	InputNeuron<T>(T val, std::vector<T> w) : Neuron<T>(val) { this->weights = w; }

	void Activate() final { throw std::exception("Not implemented"); }

	void Derive() final { throw std::exception("Not implemented"); }

	T GetActivatedVal() final { throw std::exception("Not implemented"); }
	T GetDerivedVal() final { throw std::exception("Not implemented"); }

	T GetWeightFromSubscript(size_t subscript) final { return this->weights.at(subscript); }

	T GetBias() final { throw std::exception("Not implemented"); }
};


template<typename T>
class HiddenNeuron : public Neuron<T>
{
public:
	HiddenNeuron<T>(T val, std::vector<T> w, T b) : Neuron<T>(val) 
	{ 
		this->weights = w; this->bias = b; Activate(); Derive(); 
	}

	void Activate() final { this->activatedVal = 1 / (1 + Euler(-this->val)); }

	void Derive() final { this->derivedVal = this->activatedVal * (1 - this->activatedVal); }

	T GetActivatedVal() final { return this->activatedVal; }
	T GetDerivedVal() final { return this->derivedVal; }

	T GetWeightFromSubscript(size_t subscript) final { return this->weights.at(subscript); }

	T GetBias() final { return this->bias; }
};

template<typename T>
class OutputNeuron : public Neuron<T>
{
public:
	OutputNeuron<T>(T val, T b) : Neuron<T>(val) { this->bias = b; }

	void Activate() final { throw std::exception("Not implemented"); }

	void Derive() final { this->derivedVal = this->activatedVal * (1 - this->activatedVal); } //NEEDED ??

	T GetActivatedVal() final { throw std::exception("Not implemented"); }
	T GetDerivedVal() final { return this->derivedVal; } //NEEDED ??

	T GetWeightFromSubscript(size_t subscript) final { throw std::exception("Not implemented"); }

	T GetBias() final { return this->bias; }
};