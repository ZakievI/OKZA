#include <iostream>

#include "lib\\unit1_2\\include\\unit_1_2.hpp" // N - number of task


int main()
{
    LoadSplineDLL();

    std::string FileName = "C:/Users/gulna/Downloads/Telegram Desktop/resourse 2/resourse/s new.dat";

    std::string fileNameGCRS = "D:/Документы/информатика, математика и физика/Магистратура/ОКЗА/okzaSymm.txt";

    std::vector<double> S;
    std::vector<double> V;
    std::vector<double> Fi;

    double fi0 = 0.0;
    double fi1 = 0.0;
    double sa = 0.0;
    double G = 0.0;


    //svWriter(FileName, S, V);

    svWriterGCRS(fileNameGCRS, S, V);

    SaCompute(S, V, sa);

    FiCompute(sa, S, V, Fi, fi0, fi1);

    GCompute(fi0, fi1, G);


    size_t n = S.size();

    std::cout << "Number of elements is " << n << " " << std::endl;

    for (int i = 0; i < n; i++)
    {

        std::cout << S[i] << " " << V[i] << " " << Fi[i] << std::endl;

    }

    std::cout << "s_a = " << sa << " " << std::endl;

    std::cout << "G = " << G << " " << "fi0 = " << fi0 << " " << "fi1 = " << fi1 << std::endl;

    FreeSplineDLL();

	return 0;
}