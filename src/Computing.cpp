#include <iostream>
#include "Computing.h"

Computing::Computing() = default;

std::vector<double> Computing::addPolynomials(std::vector<double> p1, std::vector<double> p2) {
    std::vector<double> sum;
    int size1 = p1.size();
    int size2 = p2.size();
    int size = std::max(size1, size2);
    for (int i = 0; i < size; i++) {
        if (i < size1 && i < size2) {
            sum.push_back(t.add(p1[i], p2[i]).size()); //sum.push_back(p1[i] + p2[i]);
        } else if (i >= size1) {
            sum.push_back(p2[i]);
        } else {
            sum.push_back(p1[i]);
        }
    }
    return sum;
}

std::vector<double> Computing::subtractPolynomials(std::vector<double> p1, std::vector<double> p2) {
    std::vector<double> difference;
    int size1 = p1.size();
    int size2 = p2.size();
    int size = std::max(size1, size2);
    for (int i = 0; i < size; i++) {
        if (i < size1 && i < size2) {
            difference.push_back(t.subtract(p1[i],p2[i]).size()); //difference.push_back(p1[i] - p2[i]);
        } else if (i >= size1) {
            difference.push_back(-p2[i]);
        } else {
            difference.push_back(p1[i]);
        }
    }
    return difference;
}

std::vector<double> Computing::multiplyPolynomials(std::vector<double> p1, std::vector<double> p2) {
    int size1 = p1.size();
    int size2 = p2.size();
    std::vector<double> product(size1 + size2 - 1, 0);
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            product[i + j] += t.multiply(p1[i], p2[j]).size(); //p1[i] * p2[j];
        }
    }
    return product;
}

std::vector<double> Computing::divide_polynomials(vector<double> &p1, vector<double> &p2) {
    std::vector<double> quotient;
    std::vector<double> remainder = p1;

    while (remainder.size() >= p2.size()) {
        double coef = remainder[remainder.size() - 1] / p2[p2.size() - 1];
        std::vector<double> term(remainder.size() - p2.size() + 1);
        term[term.size() - 1] = coef;
        for (int i = 0; i < p2.size(); i++) {
            remainder[i + term.size() - 1] -= coef * p2[i];
        }
        quotient.insert(quotient.begin(), term.begin(), term.end());
        while (!remainder.empty() && remainder.back() == 0) {
            remainder.pop_back();
        }
    }
    return quotient;
}


std::vector<double> Computing::derive(const vector<double> &coefs) {
    /**
     *
     * Example: 3x^2 + 2x + 1 has vector = [3, 2, 1] as input
     */

    if (coefs.empty()){
        std::cout << "No coeffs found." << std::endl;
    }

    std::vector<double> result;

    for (int i = 1; i < coefs.size(); i++) {
        result.push_back(t.multiply(coefs[i], i).size());
    }

    return result;
}

std::vector<double> Computing::integrate(const vector<double> &coefs) {

    if (coefs.empty()){
        std::cout << "No coefficients found." << endl;
    }

    std::vector<double> result(coefs.size()+1);

    for (int i = 0; i < coefs.size(); i++) {
        result[i+1] = t.divide(coefs[i],i+1).size();
    }

    return result;
}

std::vector<std::vector<double>> Computing::transpose(std::vector<std::vector<double>> matrix) {

    /**
     * Example: std::vector<std::vector<double>> matrix = {{1.2, 2.3}, {3.4, 4.5}, {5.6, 6.7}};
     */
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (rows == 0 || cols == 0){
        std::cout << "Either rows or columns of matrix has size 0." << std::endl;
    }

    std::vector<std::vector<double>> transposedMatrix(cols, std::vector<double>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }
    return transposedMatrix;
}

std::vector<std::vector<double>>
Computing::add_matrices(const vector<std::vector<double>> &mat1, const vector<std::vector<double>> &mat2) {
    std::vector<std::vector<double>> result(mat1.size(), std::vector<double>(mat1[0].size()));

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat1[i].size(); j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>>
Computing::subtract_matrices(const vector<std::vector<double>> &mat1, const vector<std::vector<double>> &mat2) {
    std::vector<std::vector<double>> result(mat1.size(), std::vector<double>(mat1[0].size()));

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat1[i].size(); j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>>
Computing::multiply_matrices(const vector<std::vector<double>> &mat1, const vector<std::vector<double>> &mat2) {
    std::vector<std::vector<double>> result(mat1.size(), std::vector<double>(mat2[0].size()));

    //check for dimensie

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat2[0].size(); j++) {
            for (int k = 0; k < mat1[0].size(); k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}












