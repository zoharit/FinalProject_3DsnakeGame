#include  <iostream>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

void LLSsolver(MatrixXd A, VectorXd b, MatrixXd C, VectorXd d)
{
	
	A = MatrixXd::Random(3, 2);
	cout << "Here is the matrix A:\n" << A << endl;
	b = VectorXd::Random(3);
cout << "Here is the right hand side b:\n" << b << endl;
cout << "The least-squares solution is:\n"
<< A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b) << endl;
}