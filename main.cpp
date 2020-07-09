
// Emrullah Arseven 
// emrullaharseven@yandex.com

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;
long double toplamerror,sigma1, sigma2,   sigma3, sigma4, sigma, sigma5, sigma6, sigma7;
long double c = 0.1, ol, oll, bet = 0.6;
long double neth1, neth2, neth3, neth4, neth5, outh5, outh1, outh2, outh3, outh4, neto1, neto2, outo1, outo2, e01, e02, temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17;


//Value range of a, b, c
//ax^2 + bx + c
long double a1[4] = { 1.0,2.0,3.0,4.0 };
long double b1[6] = { -2.0,-1.0,0,1.0,2.0,3.0 };
long double c1[] = { -4,-3,-2 };


int bayrak = 0;
long double ts[2];

//random weight values
long double w[] = { 0.5,0.2,0.3,0.5,0.23,0.32,0.74,0.21,0.66,0.12,0.53,0.052,0.9,0.31,0.23,0.42,0.7,0.2,0.1,0.33,0.23,0.21,0.1,0.2,0.9 };
int t12;
long double weski[25];
//random weight values
long double b[] = { 0.81,0.76,0.82131,0.213,0.61,0.12,0.64 };
long double beski[] = { 0,0,0,0,0,0,0 };

int kac_bir[72], bir_sayisi = 0;

//finding the stinks of the equation
void kok_bulma(long double de, long double e, long double f) {
	long double a, b, c, x1, x2, discriminant;
	a = de;
	b = e;
	c = f;
	bayrak = 0;
	discriminant = b * b - 4 * a * c;

	if (discriminant > 0) {
		x1 = (-b + sqrt(discriminant)) / (2 * a);
		x2 = (-b - sqrt(discriminant)) / (2 * a);

		ts[0] = x1;
		ts[1] = x2;
	}
	if (discriminant <= 0) {
		exit(1);
	}

}



int main() {



	for (int i = 0; i < 25; i++) {
		weski[i] = 0;
	}

	while (1) {
		int x;
		cout << "Click 0 to start training" << endl;
		cout << "Click 1 to use the previous learn" << endl;
		cin >> x;

		if (x == 0)
		{
			cout << "How many equations are trained?" << endl;
			cin >> temp17;

			for (int i = 0; i < 72; i++) {
				kac_bir[i] = 0;
			}


			while (1) {
				bir_sayisi = 0;
				t12 = 0;
				t12--;

				for (int i = 0; i < 4; i++) {
					for (int t = 0; t < 6; t++) {
						for (int k = 0; k < 3; k++) {
							kok_bulma(a1[i], b1[t], c1[k]);

							t12++;

							if (i == 0 && t == 0 && k == 0) {
								cout << "----------- Learning ---------------------" << endl;
							}
							cout << w[0] << endl;
							cout << "aa" << endl;
							neth1 = a1[i] * w[0] + b1[t] * w[5] + c1[k] * w[10] + b[0];
							neth2 = a1[i] * w[1] + b1[t] * w[6] + c1[k] * w[11] + b[1];
							neth3 = a1[i] * w[2] + b1[t] * w[7] + c1[k] * w[12] + b[2];
							neth4 = a1[i] * w[3] + b1[t] * w[8] + c1[k] * w[13] + b[3];
							neth5 = a1[i] * w[4] + b1[t] * w[9] + c1[k] * w[14] + b[4];


							outh1 = (2 / (1 + exp(-2 * neth1))) - 1;
							outh2 = (2 / (1 + exp(-2 * neth2))) - 1;
							outh3 = (2 / (1 + exp(-2 * neth3))) - 1;
							outh4 = (2 / (1 + exp(-2 * neth4))) - 1;
							outh5 = (2 / (1 + exp(-2 * neth5))) - 1;



							cout << outh1 << endl;

							neto1 = outh1 * w[15] + outh2 * w[17] + outh3 * w[19] + outh4 * w[21] + outh5 * w[23] + b[5];
							neto2 = outh1 * w[16] + outh2 * w[18] + outh3 * w[20] + outh4 * w[22] + outh5 * w[24] + b[6];

							outo1 = (2 / (1 + exp(-2 * neto1))) - 1;
							outo2 = (2 / (1 + exp(-2 * neto2))) - 1;


							kok_bulma(a1[i], b1[t], c1[k]);

							ts[0] = (2 / (1 + exp(-2 * ts[0]))) - 1;
							ts[1] = (2 / (1 + exp(-2 * ts[1]))) - 1;


							//error=ts[0]-outo1;
							e01 = ts[0] - outo1;
							e02 = ts[1] - outo2;

							toplamerror = sqrt(pow(e01, 2) + pow(e02, 2)) * 0.5;

							kok_bulma(a1[i], b1[t], c1[k]);

							cout << "ilk kok " << ts[0] << endl;
							cout << "ikinci kok " << ts[1] << endl;
							cout << "sistemin buldugu " << neto1 << endl;
							cout << "sistemin buldugu 2 " << neto2 << endl;

							if (toplamerror <= 0.008 && toplamerror >= -0.008) {//tolerance

								kac_bir[t12] = 1;
								continue;
							}


							sigma1 = (1 - pow((2 / (1 + exp(-2 * outo1))) - 1, 2)) * e01;
							sigma2 = (1 - pow((2 / (1 + exp(-2 * outo2))) - 1, 2)) * e02;

							sigma3 = (1 - pow((2 / (1 + exp(-2 * outh1))) - 1, 2)) * (sigma1 * w[15] + sigma2 * w[16]);
							sigma4 = (1 - pow((2 / (1 + exp(-2 * outh2))) - 1, 2)) * (sigma1 * w[17] + sigma2 * w[18]);
							sigma5 = (1 - pow((2 / (1 + exp(-2 * outh3))) - 1, 2)) * (sigma1 * w[19] + sigma2 * w[20]);
							sigma6 = (1 - pow((2 / (1 + exp(-2 * outh4))) - 1, 2)) * (sigma1 * w[21] + sigma2 * w[22]);
							sigma7 = (1 - pow((2 / (1 + exp(-2 * outh5))) - 1, 2)) * (sigma1 * w[23] + sigma2 * w[24]);



							weski[15] = c * sigma1 * outh1 + bet * weski[15];
							weski[16] = c * sigma2 * outh1 + bet * weski[16];

							weski[17] = c * sigma1 * outh2 + bet * weski[17];
							weski[18] = c * sigma2 * outh2 + bet * weski[18];

							weski[19] = c * sigma1 * outh3 + bet * weski[19];
							weski[20] = c * sigma2 * outh3 + bet * weski[20];
							weski[21] = c * sigma1 * outh4 + bet * weski[21];
							weski[22] = c * sigma2 * outh4 + bet * weski[22];
							weski[23] = c * sigma1 * outh5 + bet * weski[23];
							weski[24] = c * sigma2 * outh5 + bet * weski[24];
							beski[5] = c * sigma1 + bet * beski[5];
							beski[6] = c * sigma2 + bet * beski[6];



							w[15] = w[15] + weski[15];
							w[16] = w[16] + weski[16];
							w[17] = w[17] + weski[17];
							w[18] = w[18] + weski[18];
							w[19] = w[19] + weski[19];
							w[20] = w[20] + weski[20];
							w[21] = w[21] + weski[21];
							w[22] = w[22] + weski[22];
							w[23] = w[23] + weski[23];
							w[24] = w[24] + weski[24];
							b[5] = b[5] + beski[5];
							b[6] = b[6] + beski[6];




							weski[0] = c * sigma3 * a1[i] + bet * weski[0];
							weski[1] = c * sigma4 * a1[i] + bet * weski[1];
							weski[2] = c * sigma5 * a1[i] + bet * weski[2];
							weski[3] = c * sigma6 * a1[i] + bet * weski[3];
							weski[4] = c * sigma7 * a1[i] + bet * weski[4];

							weski[5] = c * sigma3 * b1[t] + bet * weski[5];
							weski[6] = c * sigma4 * b1[t] + bet * weski[6];
							weski[7] = c * sigma5 * b1[t] + bet * weski[7];
							weski[8] = c * sigma6 * b1[t] + bet * weski[8];
							weski[9] = c * sigma7 * b1[t] + bet * weski[9];

							weski[10] = c * sigma3 * c1[k] + bet * weski[10];
							weski[11] = c * sigma4 * c1[k] + bet * weski[11];
							weski[12] = c * sigma5 * c1[k] + bet * weski[12];
							weski[13] = c * sigma6 * c1[k] + bet * weski[13];
							weski[14] = c * sigma7 * c1[k] + bet * weski[14];

							beski[0] = c * sigma3 + bet * beski[0];
							beski[1] = c * sigma4 + bet * beski[1];
							beski[2] = c * sigma5 + bet * beski[2];
							beski[3] = c * sigma6 + bet * beski[3];
							beski[4] = c * sigma7 + bet * beski[4];

							w[0] = w[0] + weski[0];
							w[1] = w[1] + weski[1];
							w[2] = w[2] + weski[2];
							w[3] = w[3] + weski[3];
							w[4] = w[4] + weski[4];
							w[5] = w[5] + weski[5];
							w[6] = w[6] + weski[6];
							w[7] = w[7] + weski[7];
							w[8] = w[8] + weski[8];
							w[9] = w[9] + weski[9];
							w[10] = w[10] + weski[10];
							w[11] = w[11] + weski[11];
							w[12] = w[12] + weski[12];
							w[13] = w[13] + weski[13];
							w[14] = w[14] + weski[14];
							b[0] = b[0] + beski[0];
							b[1] = b[1] + beski[1];
							b[2] = b[2] + beski[2];
							b[3] = b[3] + beski[3];
							b[4] = b[4] + beski[4];


							cout << w[0] << endl;
						}

					}
				}
				for (int i = 0; i < 72; i++) {
					bir_sayisi += kac_bir[i];
					cout << bir_sayisi << endl;
				}
				if (bir_sayisi >= temp17) {
					cout << bir_sayisi << endl;
					goto aga;
				}

				for (int i = 0; i < 72; i++) {
					kac_bir[i] = 0;
				}

			}
		aga:
			ofstream myfile;
			myfile.open("sa.txt");
			myfile << " w[0]=" << w[0] << ";\n";
			myfile << "w[1]=" << w[1] << ";\n";
			myfile << "w[2]=" << w[2] << ";\n";
			myfile << "w[3]=" << w[3] << ";\n";
			myfile << "w[4]=" << w[4] << ";\n";
			myfile << "w[5]=" << w[5] << ";\n";
			myfile << "w[6]=" << w[6] << ";\n";
			myfile << "w[7]=" << w[7] << ";\n";
			myfile << "w[8]=" << w[8] << ";\n";
			myfile << "w[9]=" << w[9] << ";\n";
			myfile << "w[10]=" << w[10] << ";\n";
			myfile << "w[11]=" << w[11] << ";\n";
			myfile << "w[12]=" << w[12] << ";\n";
			myfile << "w[13]=" << w[13] << ";\n";
			myfile << "w[14]=" << w[14] << ";\n";
			myfile << "w[15]=" << w[15] << ";\n";
			myfile << "w[16]=" << w[16] << ";\n";
			myfile << "w[17]=" << w[17] << ";\n";
			myfile << "w[18]=" << w[18] << ";\n";
			myfile << "w[19]=" << w[19] << ";\n";
			myfile << "w[20]=" << w[20] << ";\n";
			myfile << "w[21]=" << w[21] << ";\n";
			myfile << "w[22]=" << w[22] << ";\n";
			myfile << "w[23]=" << w[23] << ";\n";
			myfile << "w[24]=" << w[24] << ";\n";
			myfile << "b[0]=" << b[0] << ";\n";
			myfile << "b[1]=" << b[1] << ";\n";

			myfile << "b[2]=" << b[2] << ";\n";
			myfile << "b[3]=" << b[3] << ";\n";

			myfile << "b[4]=" << b[4] << ";\n";
			myfile << "b[5]=" << b[5] << ";\n";
			myfile << "b[6]=" << b[6] << ";\n";

			myfile.close();



		}


		else if (x == 1) {

			long double  a1, b1, c1;

			w[0] = 0.568408;
			w[1] = 0.606266;
			w[2] = 1.41234;
			w[3] = 0.11824;
			w[4] = 0.329883;
			w[5] = -0.389336;
			w[6] = 0.449357;
			w[7] = -0.622878;
			w[8] = 0.3173;
			w[9] = -0.198989;
			w[10] = 0.586835;
			w[11] = 0.260728;
			w[12] = 0.402314;
			w[13] = 0.518389;
			w[14] = 1.10326;
			w[15] = 0.0161172;
			w[16] = 0.381493;
			w[17] = -0.97265;
			w[18] = -0.0289887;
			w[19] = 0.0106353;
			w[20] = 0.92806;
			w[21] = -0.334701;
			w[22] = -0.157553;
			w[23] = -0.141663;
			w[24] = 1.14276;
			b[0] = 0.280136;
			b[1] = 0.494323;
			b[2] = 0.293008;
			b[3] = 0.428905;
			b[4] = -0.495247;
			b[5] = 1.49414;
			b[6] = -0.913098;




			cout << "a,b,c gir" << endl;
			cin >> a1 >> b1 >> c1;
			neth1 = a1 * w[0] + b1 * w[5] + c1 * w[10] + b[0];
			neth2 = a1 * w[1] + b1 * w[6] + c1 * w[11] + b[1];
			neth3 = a1 * w[2] + b1 * w[7] + c1 * w[12] + b[2];
			neth4 = a1 * w[3] + b1 * w[8] + c1 * w[13] + b[3];
			neth5 = a1 * w[4] + b1 * w[9] + c1 * w[14] + b[4];

			outh1 = (2 / (1 + exp(-2 * neth1))) - 1;
			outh2 = (2 / (1 + exp(-2 * neth2))) - 1;
			outh3 = (2 / (1 + exp(-2 * neth3))) - 1;
			outh4 = (2 / (1 + exp(-2 * neth4))) - 1;
			outh5 = (2 / (1 + exp(-2 * neth5))) - 1;



			cout << outh1 << endl;

			neto1 = outh1 * w[15] + outh2 * w[17] + outh3 * w[19] + outh4 * w[21] + outh5 * w[23] + b[5];
			neto2 = outh1 * w[16] + outh2 * w[18] + outh3 * w[20] + outh4 * w[22] + outh5 * w[24] + b[6];

			outo1 = (2 / (1 + exp(-2 * neto1 + b[5]))) - 1;
			outo2 = (2 / (1 + exp(-2 * neto2 + b[6]))) - 1;




			kok_bulma(a1, b1, c1);
			cout << "ilk kok " << ts[0] << endl;
			cout << "ikinci kok " << ts[1] << endl;

			ts[0] = (2 / (1 + exp(-2 * outo1))) - 1;
			ts[1] = (2 / (1 + exp(-2 * outo2))) - 1;


			cout << "the result of the system 1- " << neto1 << endl;
			cout << "the result of the system 2- " << neto2 << endl;

		}
	}
}
