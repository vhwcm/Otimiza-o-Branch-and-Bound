#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

void printaSaida (vector<int> vetorProdutoClienteFinal);
void branchAndBound (vector<int> vetorProdutoClienteFinal, vector<int> ofertaClientes, int nClientes, int nProdutos);

int valorMaximo = 0;
int nClientes, nProdutos;
vector<int> maioresOfertasPorProduto;
vector<pair<int,int>> vetorSolucao; //par produto - cliente 
int maiorOferta = 0;

int main(int argc, char * argv[]) {
    vector<int> precoProdutos;
    vector<vector<int>> ofertaClientes;
    cin >> nProdutos >> nClientes;
    
    bool desligarCortesDeViabilidade = false;
    bool desligarCortesDeOtimalidade = false;
    bool usarFuncaoLimitanteEnunciado = false;
    bool funcaoLimitanteMurilo = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-f") {
            desligarCortesDeViabilidade = true;
        } else if (arg == "-o") {
            desligarCortesDeOtimalidade = true;
        } else if (arg == "-a") {
            usarFuncaoLimitanteEnunciado = true;
        } else if (arg == "-m") {
            funcaoLimitanteMurilo = true;
        }
    }

    for (int i = 0; i < nProdutos; i++) {
        int maior_valor_do_produto = 0;
        for (int j = 0; j < nClientes; j++) {
            int oferta;
            cin >> oferta;
            if (oferta > maior_valor_do_produto) {
                maior_valor_do_produto = oferta;
                if (maior_valor_do_produto > maiorOferta) {
                    maiorOferta = maior_valor_do_produto;
                }
            }
            
            ofertaClientes[i].push_back(oferta); // aqui a gente termina de montar as ofertas dos clientes
        }
        maioresOfertasPorProduto[i].push_back(maior_valor_do_produto);
    }

    vector<pair<int, int> vetorProdutoClienteFinal;


    branchAndBound(vetorProdutoClienteFinal, ofertaClientes, nClientes, nProdutos);
    printaSaida(vetorProdutoClienteFinal);
}

void branchAndBound (vector<int> vetorProdutoClienteFinal, vector<int> ofertaClientes,
    bool desligarCortesDeViabilidade, bool desligarCortesDeOtimalidade, bool usarFuncaoLimitanteEnunciado) {
    int nOfertas = ofertaClientes.size();
    int nProdutosRestantes = nProdutos - nOfertas;
    set<int> produtosRestantes;
    set<int> clientesQueNãoCompraramNada;
    branch(vetorProdutoClienteFinal, ofertaClientes, produtosRestantes, clientesQueNãoCompraramNada);
    // aqui vai sair setado valorMaximo e vetorProdutoClienteFinal
}

void branch(vector<int> vetorProdutoClienteFinal, vector<int> ofertaClientes, set<int> produtosRestantes,  set<pair<int,int>> clienteProdutoComprado, set<int> clientesQueNaoCompraramNada, int produtoEscolhido) {
    for (auto cliente : clientesQueNaoCompraramNada) {
        clientesQueNãoCompraramNada.erase(cliente);
        clienteProdutoComprado.insert(make_pair(cliente, produtoEscolhido));
        int valor = px(ofertaClientes, precoProdutos, clienteProdutoComprado);
        if (valor > valorMaximo) {
            valorMaximo = valor;
            for (auto cp : clienteProdutoComprado) {
                vetorSolucao.clear();
                vetorSolucao.push_back(make_pair(cp.second, cp.first));
            }
        }

        int valorFuncaoLimitante;
        if (funcaoLimitanteMurilo) {
            valorFuncaoLimitante = funcaoLimitanteMurilo(valorAtual, ofertaClientes, precoProdutos, clienteProdutoComprado, produtoEscolhido);
        } else if (funcaoLimitanteNossa) {
            valorFuncaoLimitante= funcaoLimitanteNossa(valorAtual, ofertaClientes, precoProdutos, clienteProdutoComprado, produtoEscolhido);
        }

        if (valorFuncaoLimitante < valorMaximo) {
            continue;
            clientesQueNãoCompraramNada.insert(cliente);
        }

        branch(vetorProdutoClienteFinal, ofertaClientes, produtosRestantes, clientesQueNãoCompraramNada, produtoEscolhido + 1, valorAtual);
        clienteProdutoComprado.erase(cliente);
        clientesQueNãoCompraramNada.insert(cliente);
    }
}

int px(vector<int> ofertaClientes, vector<int> precoProdutos, set<pair<int,int>> clienteProdutoComprado) {
    int sum = 0;
    for (auto cp : clienteProdutoComprado) {
        sum += precopProdutos[cp.second];
    }

    return sum;   
}

// relaxa viabilidade, relaxa mais
int funcaoLimitanteMurilo(int valorAteAgora, vector<int> ofertaClientes, vector<int> precoProdutos, set<pair<int,int>> clienteProdutoComprado, int produtoAtual) {
    int resposta = valorAteAgora;
    resposta += maiorOferta * (nProdutos - produtoAtual - 1);
}

// relaxa viabilidade, relaxa menos
int funcaoLimitanteNossa(int valorAteAgora, vector<int> ofertaClientes, vector<int> precoProdutos, set<pair<int,int>> clienteProdutoComprado, int produtoAtual) {
    int sum = valorAteAgora;
    for ( int i = produtoAtual + 1; i < nProdutos; i++) {
        sum += maioresOfertasPorProduto[i];
    }
    return sum;
}

void printaSaida (vector<int> vetorProdutoClienteFinal) {
    for (int i = 0; i < vetorProdutoClienteFinal.size(); i++) {
        cout << vetorProdutoClienteFinal[i].first << " " << vetorProdutoClienteFinal[i].second << endl;
    }
}
/*std::set container instead, its interface relies on methods like .insert(), .erase(), and .find()*/