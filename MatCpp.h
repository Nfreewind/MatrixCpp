#pragma once
#include <string.h>
#include <iostream>
using namespace std;

namespace CppToolBox {
	
	void swap(double** input, double**output, int dimension, int first_row, int second_row)
	{
		double* temp_row1 = new double[dimension];
		double* temp_row2 = new double[dimension];
		int i;
		for (i = 0; i<dimension; i++)
		{
			temp_row1[i] = input[first_row][i];
			temp_row2[i] = output[first_row][i];
		}
		for (i = 0; i<dimension; i++)
		{
			input[first_row][i] = input[second_row][i];
			output[first_row][i] = output[second_row][i];
			input[second_row][i] = temp_row1[i];
			output[second_row][i] = temp_row2[i];
		}
		delete[] temp_row1;
		delete[] temp_row2;
	}
	void reorderOutput(double** output, int dimension)
	{
		double**temp = new double*[dimension];
		for (int i = 0; i<dimension; ++i)
			temp[i] = new double[dimension];

		for (int i = 1; i<dimension; ++i)
			memcpy(temp[i - 1], output[i], sizeof(double)*dimension);
		memcpy(temp[dimension - 1], output[0], sizeof(double)*dimension);

		for (int i = 0; i<dimension; ++i)
			memcpy(output[i], temp[i], sizeof(double)*dimension);

		for (int i = 0; i<dimension; ++i)
			delete[] temp[i];
		delete[] temp;
	}
	class Vector {
	private:
		double * data;
		bool is_shared;
	public:
		int length;
		static Vector * reference_of_array(double * val, int len)
		{
			Vector * total = new Vector();
			total->length = len;
			total->data = val;
			total->is_shared = true;
			return total;
		}
		double * get_array();
		Vector();
		Vector(Vector & vec);
		Vector(int len);
		Vector(double * value, int len);
		~Vector();
		double & operator[](int index);
	};
	
	class Matrix
	{
		//private properties
	private:
		double ** data;
		Vector * current_row;
		bool is_shared;
		//public properties
	public:
		int rows;
		int cols;

		//private methods
	private:


		//public methods
	public:
		//static methods
		static Matrix eyes(int dimension)
		{
			Matrix total = Matrix(dimension, dimension);
			for (int i = 0; i < dimension; i++)total.data[i][i] = 1;
			return total;
		}
		static void LMS(const Matrix & Z, const Matrix & H, const Matrix & D, Matrix & X, Matrix & S, Matrix & V)
		{
			Matrix Ht = H.t();
			Matrix Dinv = D.inv();
			X = (Ht * Dinv * H).inv() * H * Dinv * Z;
			//²»ËãÁË
		}
		static Matrix * reference_of_array(double ** val, int rows, int cols)
		{
			Matrix * total = new Matrix();
			total->rows = rows;
			total->cols = cols;
			total->data = val;
			return total;
		}
		static Matrix * reference_of_array(double * val, int rows, int cols)
		{
			Matrix * total = new Matrix();
			total->rows = rows;
			total->cols = cols;
			total->data = new double*[rows];
			for (int i = 0; i < rows; i++) total->data[i] = val + i * cols;
			return total;
		}
		inline static Matrix zeros(int rows, int cols)
		{
			return Matrix(rows, cols);
		}
		double ** get_array();
		//constructors
		Matrix();
		Matrix(int r, int c);
		Matrix(const Matrix & obj);
		Matrix(const double ** val, int r, int c);
		Matrix(const double * val, int r, int c);
		//deconstructors
		~Matrix();
		//operators
		Matrix & operator=(const Matrix & obj);
		Matrix operator-(const Matrix & obj)const;
		Matrix operator-(const double obj)const;
		Matrix operator+(const Matrix & obj)const;
		Matrix operator+(const double obj)const;
		Matrix operator*(const Matrix & obj)const;
		Matrix operator*(const double obj)const;
		Vector & operator[](int row);
		Matrix t()const;
		Matrix inv()const;
		Matrix operator/(Matrix & obj)const;
		Matrix operator/(double obj)const;
		friend ostream & operator<<(ostream & out, Matrix & obj)
		{
			for (int i = 0; i < obj.rows; i++)
			{
				for (int j = 0; j < obj.cols; j++)
				{
					out << obj.data[i][j] << "\t";
				}
				out << endl;
			}
			return out;
		}
	};

}

