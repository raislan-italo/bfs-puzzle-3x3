#pragma once                    // Garante que esse arquivo seja incluído apenas uma vez durante a compilação
// Importa
#include "PuzzleState.hpp"      // A estrutura do estado do tabuleiro
#include <queue>                // Para usar std::queue, essencial para BFS.
#include <set>                  // Para registrar os estados visitados
#include <vector>               // Para armazenar o caminho solução

using namespace std;

//  Retorna um vetor de estados do tipo PuzzleState, representando o caminho até a solução final.
vector<PuzzleState> bfs(PuzzleState start) {
    queue<shared_ptr<PuzzleState>> fila;        // Contém os nós ainda não explorados (BFS usa fila FIFO).
    vector<PuzzleState> caminho;               // Guarda o caminho do estado inicial até o final.
    set<array<array<int, 3>, 3>> visitados;    // Impede visitar o mesmo estado mais de uma vez.

    // Coloca o estado inicial na fila.
    fila.push(make_shared<PuzzleState>(start));

    // Enquanto houver estados a explorar
    while (!fila.empty()) {
        auto atual = fila.front(); fila.pop();          // Pega o proximo estado da fila
        if (visitados.count(atual->board)) continue;    // Ignora estados já visitados

        visitados.insert(atual->board); // Se for novo, marca como visitado.

        // Se o estado for o objetivo final
        if (atual->isGoal()) {
            //  Reconstrói o caminho do objetivo até o início, voltando pelos pais
            while (atual != nullptr) {
                caminho.push_back(*atual);
                atual = atual->parent;
            }
            // Depois inverte para ficar na ordem correta.
            std::reverse(caminho.begin(), caminho.end());
            return caminho;
        }

        // Adiciona todos os vizinhos (movimentos válidos) à fila, se ainda não visitados
        for (auto& prox : atual->getSuccessors()) {
            if (!visitados.count(prox->board))
                fila.push(prox);
        }
    }

    return caminho;
}
