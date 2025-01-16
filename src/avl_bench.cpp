#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <cstring>

using namespace std;

int bench_main() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dis;

    vector<int> exposants = {5,10,15,20,25};
    for(auto e:exposants)
    {
        uint32_t count = 1 << e;
        string str1 = "Values_" + to_string(e) + ".txt";
        string str2 = "Search_" + to_string(e) + ".txt";
        string str3 = "Delete_" + to_string(e) + ".txt";

        ofstream f1(str1);
        ofstream f2(str2);
        ofstream f3(str3);
        for (size_t i = 0; i < count; i++)
        {
            uint64_t v = dis(gen);
            f1 << v << '\n'; 
            switch (i % 10) //30% iront en search, 20% en delete et autre 10% aux deux.
            { 
                case 0 :
                case 1 :
                case 2 : f2 << v << '\n'; break;
                case 3 : 
                case 4 : f3 << v << '\n'; break;
                case 5 : f2 << v << '\n'; f3 << v << '\n'; break;
                default : break;
            }
        }
        f1.close();
        f2.close();
        f3.close();
    }
    return 0;
}