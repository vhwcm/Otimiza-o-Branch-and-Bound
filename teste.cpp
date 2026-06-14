#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char * argv[]) {

    bool desligarCortesDeViabilidade = false;
    bool desligarCortesDeOtimalidade = false;
    bool usarFuncaoLimitanteEnunciado = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-f") {
            desligarCortesDeViabilidade = true;
        } else if (arg == "-o") {
            desligarCortesDeOtimalidade = true;
        } else if (arg == "-a") {
            usarFuncaoLimitanteEnunciado = true;
        }
    }

    std::cout << "Viabilidade: " << (desligarCortesDeViabilidade ? "ON" : "OFF") << "\n";
    std::cout << "Otimalidade: " << (desligarCortesDeOtimalidade ? "ON" : "OFF") << "\n";
    std::cout << "Limitante: " << (usarFuncaoLimitanteEnunciado ? "ON" : "OFF") << "\n";

    return 0;
}