#ifndef NCP_COMPUTING_H
#define NCP_COMPUTING_H

#include "UniversalTuringMachine.h"
//#include <Eigen/Dense>

class Computing {
private:
    UniversalTuringMachine t;

private:


public:
    Computing();

    /**
     * Methods regarding polynomials
     * @param p1 polynomial 1
     * @param p2 polynomial 2
     * @return solutions
     */
    std::vector<double> addPolynomials(std::vector<double> p1, std::vector<double> p2);
    std::vector<double> subtractPolynomials(std::vector<double> p1, std::vector<double> p2);
    std::vector<double> multiplyPolynomials(std::vector<double> p1, std::vector<double> p2);
    std::vector<double> divide_polynomials(const std::vector<double> &p1, const std::vector<double> &p2);
    std::vector<double> derive(const std::vector<double>& coefs);
    std::vector<double> integrate(const std::vector<double>& coefs);

    /**
     * Methods regarding matrices
     * @param mat1 Matrix 1
     * @param mat2 Matrix 2
     * @return solutions
     */
    std::vector<std::vector<double>> add_matrices(const std::vector<std::vector<double>>& mat1, const std::vector<std::vector<double>>& mat2);
    std::vector<std::vector<double>> subtract_matrices(const std::vector<std::vector<double>>& mat1, const std::vector<std::vector<double>>& mat2);
    std::vector<std::vector<double>> multiply_matrices(const std::vector<std::vector<double>>& mat1, const std::vector<std::vector<double>>& mat2);
    std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> matrix);
    // inverse wss Eigen/Dense library

    /**
     * Methods regarding vectors
     */
    std::vector<double> add_vectors(std::vector<double> vec1, std::vector<double> vec2);
    std::vector<double> subtract_vectors(std::vector<double> vec1, std::vector<double> vec2);
    std::vector<double> multiply_vectors(std::vector<double> vec1, std::vector<double> vec2);
    double length_vector(std::vector<double> vec1);

    /**
     * Basic operations
     * @param x integer variable 1
     * @param y integer variable 2
     * @return solution
     */
    int multiply(int x, int y);
    int divide(int x, int y);
    int add(int x, int y);
    int subtract(int x, int y);



};


#endif //NCP_COMPUTING_H
