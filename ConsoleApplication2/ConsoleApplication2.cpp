// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <atlsafe.h>
#include <comutil.h>
#include <list>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>

#include "Neuron.h"
#include "Helpers.h"
#include "Picture.h"
#include "Layer.h"

/*
void CopySafeArrayToMem(SAFEARRAY* psa, void* data, size_t maxdatalen, size_t offset = NULL)
{
	if (psa != NULL && data != NULL)
	{
		memset(data, 0x00, maxdatalen);

		CComSafeArray<BYTE> sa(psa);
		const LONG lb = sa.GetLowerBound();
		const LONG ub = sa.GetUpperBound();

		for (LONG i = lb; i <= ub && (i - lb) < maxdatalen; i++)
		{
			if (i < offset)
				continue;

			((unsigned char*)data)[i - offset - lb] = sa.GetAt(i);
		}

		sa.Detach();
	}
}

void CreateSafeArray(SAFEARRAY** saData)
{
	double data[10]; // some sample data to write into the created safearray
	SAFEARRAYBOUND  Bound;
	Bound.lLbound = 0;
	Bound.cElements = 10;

	*saData = SafeArrayCreate(VT_R8, 1, &Bound);

	double HUGEP *pdFreq;
	HRESULT hr = SafeArrayAccessData(*saData, (void HUGEP* FAR*)&pdFreq);
	if (SUCCEEDED(hr))
	{
		// copy sample values from data[] to this safearray
		for (DWORD i = 0; i < 10; i++)
		{
			*pdFreq++ = data[i];
		}
		SafeArrayUnaccessData(*saData);
	}
}

size_t GetSafeArraySize(SAFEARRAY* psa)
{
	if (psa == NULL)
	{
		CComSafeArray<DOUBLE> sa(psa);
		const LONG lb = sa.GetLowerBound();
		const LONG ub = sa.GetUpperBound();

		return (ub - lb)+1;
	}
	return NULL;
}

// Listes chaînées //
template <typename T>
struct Element
{
	T val;
	Element<T>* next;
};

template<typename T>
struct Liste
{
	Element<T> *First;

	void Add(T value)
	{
		Element<T>* en = new Element<T>();
		en->val = value;
		en->next = this->First;
		this->First = en;
	}

	void Delete(size_t index)
	{
		Element<T>* toDelete = new Element<T>();

		if (index == 0) //Delete first element
		{
			toDelete = this->First;
			this->First = toDelete->next;
		}
		else //Delete other elements
		{
			Element<T>* current = this->First;
			for (size_t i = 1; i < index; ++i)
			{
				if (!current->next->next)
				{
					char Msg[25];
					sprintf_s(Msg, "Index %d is out of range", index);
					throw std::out_of_range(Msg);
				}

				current = current->next;
			}

			Element<T>* toDelete = current->next;

			current->next = toDelete->next;
		}

		free(toDelete);
	}
};
// --------------- //
*/

std::vector<float> operator+(const std::vector<float>& m1, const std::vector<float>& m2)
{
	const unsigned long VECTOR_SIZE = m1.size();
	std::vector <float> sum(VECTOR_SIZE);

	for (unsigned i = 0; i != VECTOR_SIZE; ++i)
		sum[i] = m1[i] + m2[i];

	return sum;
}

std::vector<float> operator-(const std::vector<float>& m1, const std::vector<float>& m2) 
{
	const unsigned long VECTOR_SIZE = m1.size();
	std::vector<float> difference(VECTOR_SIZE);

	for (unsigned i = 0; i != VECTOR_SIZE; ++i)
		difference[i] = m1[i] - m2[i];

	return difference;
}

std::vector<float> operator*(const std::vector<float>& m1, const std::vector<float>& m2) 
{
	const unsigned long VECTOR_SIZE = m1.size();
	std::vector <float> product(VECTOR_SIZE);

	for (unsigned i = 0; i != VECTOR_SIZE; ++i)
		product[i] = m1[i] * m2[i];

	return product;
}

std::vector<float> transpose(float *m, const int C, const int R) 
{

	/*  Returns a transpose matrix of input matrix.
		Inputs:
			m: vector, input matrix
			C: int, number of columns in the input matrix
			R: int, number of rows in the input matrix
		Output: vector, transpose matrix mT of input matrix m
	*/

	std::vector <float> mT(C*R);

	for (unsigned n = 0; n != C * R; n++) 
	{
		unsigned i = n / C;
		unsigned j = n % C;
		mT[n] = m[R*j + i];
	}

	return mT;
}


std::vector <float> sigmoid_d(const std::vector <float>& m1) {

	/*  Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)),
		where f(x) is sigmoid function.
		Input: m1, a vector.
		Output: x(1 - x) for every element of the input matrix m1.
	*/

	const unsigned long VECTOR_SIZE = m1.size();
	std::vector <float> output(VECTOR_SIZE);


	for (unsigned i = 0; i != VECTOR_SIZE; ++i) 
	{
		output[i] = m1[i] * (1 - m1[i]);
	}

	return output;
}

std::vector <float> sigmoid(const std::vector <float>& m1) {

	/*  Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
		Input: m1, a vector.
		Output: 1/(1 + e^-x) for every element of the input matrix m1.
	*/

	const unsigned long VECTOR_SIZE = m1.size();
	std::vector <float> output(VECTOR_SIZE);


	for (unsigned i = 0; i != VECTOR_SIZE; ++i) 
	{
		output[i] = 1 / (1 + exp(-m1[i]));
	}

	return output;
}

std::vector <float> dot(const std::vector <float>& m1, const std::vector <float>& m2, const int m1_rows, const int m1_columns, const int m2_columns) {

	/*  Returns the product of two matrices: m1 x m2.
		Inputs:
			m1: vector, left matrix of size m1_rows x m1_columns
			m2: vector, right matrix of size m1_columns x m2_columns (the number of rows in the right matrix
				must be equal to the number of the columns in the left one)
			m1_rows: int, number of rows in the left matrix m1
			m1_columns: int, number of columns in the left matrix m1
			m2_columns: int, number of columns in the right matrix m2
		Output: vector, m1 * m2, product of two vectors m1 and m2, a matrix of size m1_rows x m2_columns
	*/

	std::vector <float> output(m1_rows*m2_columns);

	for (int row = 0; row != m1_rows; ++row) 
	{
		for (int col = 0; col != m2_columns; ++col) 
		{
			output[row * m2_columns + col] = 0.f;
			for (int k = 0; k != m1_columns; ++k) 
			{
				output[row * m2_columns + col] += m1[row * m1_columns + k] * m2[k * m2_columns + col];
			}
		}
	}

	return output;
}

void print(const std::vector <float>& m, int n_rows, int n_columns) {

	/*  "Couts" the input vector as n_rows x n_columns matrix.
		Inputs:
			m: vector, matrix of size n_rows x n_columns
			n_rows: int, number of rows in the left matrix m1
			n_columns: int, number of columns in the left matrix m1
	*/

	for (int i = 0; i != n_rows; ++i) 
	{
		for (int j = 0; j != n_columns; ++j) 
		{
			std::cout << m[i * n_columns + j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
}

int main()
{
	//Generate random inputs
	std::vector<float> values(784);
	srand(time(0));
	for (size_t i = 0; i < 784; ++i)
	{
		values.at(i) = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	std::vector<float> weights(784);
	for (size_t i = 0; i < 784; ++i)
	{
		weights.at(i) = (-5 + static_cast<float>(rand())) / static_cast<float>(RAND_MAX/13);
	}

	//Initialize Input layer
	InputLayer<float> inputs(values, weights);


	//Initialize Hidden layer
	std::vector<float> biases{ -250.0f, -248.7f, -259.2f, -250.0f, -248.7f, -259.2f, -250.0f, -248.7f, -259.2f, 542.6f };

	std::vector<float> hid(10);

	for (size_t i = 0; i < 10; ++i)
	{
		float result = 0;

		//Sum & Bias
		for (size_t j = 0; j < inputs.GetNeurons().size(); ++j)
		{
			result += (inputs.GetNeurons().at(j).GetVal() * inputs.GetNeurons().at(j).GetWeightFromSubscript(j));

			//std::cout << "Added " << (inputs.GetNeurons().at(j).GetVal() * inputs.GetNeurons().at(j).GetWeightFromSubscript(j)) << std::endl;
		}

		std::cout << "result : " << result << std::endl << "Adding bias..." << std::endl;
		result += biases.at(i);
		std::cout << "Final result : " << result << std::endl << std::endl;

		//Activation
		hid.at(i) = 1.0f / (1.0f + std::pow(2.71828f, -result));
	}

	
	//Analyze result !!
	std::vector<int> outputs(10);
	for (size_t i = 0; i < 10; ++i)
	{
		if (hid.at(i) >= 0.5)
			outputs.at(i) = 1;
		else
			outputs.at(i) = 0;
	}

	// ---> Mouais... un peu de la merde l'histoire des 1 et 0
	// ---> Va falloir ptet considérer des valeurs à la virgule pour que la rétropropagation fonctionne

	system("pause");

	//HiddenLayer<float> hiddens1(hid, 8.0f);
	//OutputLayer<float> outputs(values, 8.0f);



	return 0;

	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	///////////////////////////////////////////////


	std::vector<float> X
	{
		5.1, 3.5, 1.4, 0.2,
		4.9, 3.0, 1.4, 0.2,
		6.2, 3.4, 5.4, 2.3,
		5.9, 3.0, 5.1, 1.8
	};

	std::vector<float> y
	{
		0,
		0,
		1,
		1
	};

	std::vector<float> W
	{
		0.5,
		0.5,
		0.5,
		0.5
	};

	for (unsigned i = 0; i != 50; ++i) {

		std::vector<float> pred = sigmoid(dot(X, W, 4, 4, 1));
		std::vector<float> pred_error = y - pred;
		std::vector<float> pred_delta = pred_error * sigmoid_d(pred);
		std::vector<float> W_delta = dot(transpose(&X[0], 4, 4), pred_delta, 4, 4, 1);
		W = W + W_delta;

		if (i == 49) 
		{
			print(pred, 4, 1);
		};
	};

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
