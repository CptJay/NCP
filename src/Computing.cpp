#include <iostream>
#include "Computing.h"

Computing::Computing() = default;

std::vector<double> Computing::addPolynomials(std::vector<double> p1, std::vector<double> p2) {
    std::vector<double> sum;

    std::vector<unsigned long > test;
    bool testLong = false;

    int size1 = p1.size();
    int size2 = p2.size();
    int size = std::max(size1, size2);
    for (int i = 0; i < size; i++) {
        if (i < size1 && i < size2) {
            sum.push_back(add(p1[i], p2[i]));
            test.push_back(add(p1[i], p2[i]));
            //sum.push_back(p1[i] + p2[i]);
        } else if (i >= size1) {
            sum.push_back(p2[i]);
        } else {
            sum.push_back(p1[i]);
        }
    }

    if (testLong){
        for (auto i : test) {
            cout << "Testing accuracy: " << i << endl;
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
            difference.push_back(subtract(p1[i],p2[i])); //difference.push_back(p1[i] - p2[i]);
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
            product[i + j] += multiply(p1[i], p2[j]); //p1[i] * p2[j];
        }
    }
    return product;
}

std::vector<double> Computing::divide_polynomials(const vector<double> &p1, const vector<double> &p2) {
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
    // 5 3 2
    if (coefs.empty()){
        std::cout << "Error: No coefficients found." << std::endl;
        return {};
    }

    std::vector<double> result;

    for (int i = 0; i < coefs.size()-1; i++){
        result.push_back(multiply(coefs[i], coefs.size()-1-i));
    }

    return result;
}

std::vector<double> Computing::integrate(const vector<double> &coefs) {

    if (coefs.empty()){
        std::cout << "Error: No coefficients found." << endl;
    }

    std::vector<double> result;

    for (int i = 0; i < coefs.size()-1; i++) {
//        result[i+1] = divide(coefs[i],i+1).size();
        result.push_back(divide(coefs[i], coefs.size()-i));
    }
    result.push_back(coefs[coefs.size()-1]);
    return result;
}

std::vector<std::vector<double>> Computing::transpose(std::vector<std::vector<double>> matrix) {

    /**
     * Example: std::vector<std::vector<double>> matrix = {{1.2, 2.3}, {3.4, 4.5}, {5.6, 6.7}};
     */
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (rows == 0 || cols == 0){
        std::cout << "Error: Either rows or columns of matrix has size 0." << std::endl;
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

    if (mat1.size() != mat2.size()){
        cout << "Error: Matrix dimensions not correct for addition" << endl;
        return result;
    }

    if (mat1[0].size() != mat2[0].size()){
        cout << "Error: Matrix dimensions not correct for addition" << endl;
        return result;
    }

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat1[i].size(); j++) {
            result[i][j] = add(mat1[i][j], mat2[i][j]);
        }
    }

    return result;
}

std::vector<std::vector<double>>
Computing::subtract_matrices(const vector<std::vector<double>> &mat1, const vector<std::vector<double>> &mat2) {
    std::vector<std::vector<double>> result(mat1.size(), std::vector<double>(mat1[0].size()));

    if (mat1.size() != mat2.size()){
        cout << "Error: Matrix dimensions not correct for subtraction" << endl;
        return result;
    }

    if (mat1[0].size() != mat2[0].size()){
        cout << "Error: Matrix dimensions not correct for subtraction" << endl;
        return result;
    }

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat1[i].size(); j++) {
            result[i][j] = subtract(mat1[i][j], mat2[i][j]);
        }
    }
    return result;
}

std::vector<std::vector<double>>
Computing::multiply_matrices(const vector<std::vector<double>> &mat1, const vector<std::vector<double>> &mat2) {
    std::vector<std::vector<double>> result(mat1.size(), std::vector<double>(mat2[0].size()));

    //check for dimensie [[2, 3, 5], [2, 4, 3]]
    if (mat1[0].size() != mat2.size()){
        cout << "Error: Matrix dimensions not correct for multiplication" << endl;
        return result;
    }

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat2[0].size(); j++) {
            for (int k = 0; k < mat1[0].size(); k++) {
                result[i][j] += multiply(mat1[i][k], mat2[k][j]);
            }
        }
    }

    return result;
}

int Computing::add(int x, int y) {
    int result {};
    if (abs(x) < abs(y)) {
        swap(x, y);
    }
    if ((x >= 0 and y >= 0) or (x < 0 and y < 0)) {
        result = t.add(x, y);
    }
    else {
        result = t.subtract(x, y);
    }
    if (x < 0) {
        return -result;
    }
    return result;
}

int Computing::subtract(int x, int y) {
    int result {};
    if (abs(x) < abs(y)) {
        swap(x, y);
    }
    if ((x >= 0 and y >= 0) or (x < 0 and y < 0)) {
        result = t.subtract(x, y);
    }
    else {
        result = t.add(x, y);
    }
    if (y-x < 0) {
        return -result;
    }
    return result;
}

int Computing::multiply(int x, int y) {
    int result = t.multiply(x, y);
    if ((x >= 0 and y >= 0) or (x < 0 and y < 0)) {
        return result;
    }
    return -result;
}

int Computing::divide(int x, int y) {
    int result = t.divide(x, y);
    if (x >= 0 and y >= 0 or x < 0 and y < 0) {
        return result;
    }
    return -result;
}

std::vector<double> Computing::subtract_vectors(const std::vector<double> vec1, const std::vector<double> vec2) {

    std::vector<double> result(vec1.size());

    if (vec1.size() != vec2.size()) {
        std::cout << "Error: vectors have different sizes!" << std::endl;
        return result;
    }

    for (int i = 0; i < vec1.size(); i++) {
        result[i] = subtract(vec1[i], vec2[i]);
    }

    return result;
}

std::vector<double> Computing::add_vectors(const std::vector<double> vec1, const std::vector<double> vec2) {
    std::vector<double> result {};
    for (int i = 0; i < vec1.size(); i++) {
        result.push_back(this->add(vec1[i], vec2[i]));
    }
    return result;
}

std::vector<double> Computing::multiply_vectors(std::vector<double> vec1, std::vector<double> vec2) {
    std::vector<double> result(vec1.size());

    if (vec1.size() != vec2.size()) {
        std::cout << "Error: vectors have different sizes!" << std::endl;
        return result;
    }

    for (int i = 0; i < vec1.size(); i++) {
        result[i] = this->multiply(vec1[i], vec2[i]);
    }

    return result;
}

double Computing::length_vector(std::vector<double> vec1) {
    return vec1.size();
}












