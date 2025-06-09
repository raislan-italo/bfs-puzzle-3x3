#pragma once        // Garante que esse arquivo seja incluido apenas uma vez durante a compilação

// Bibliotecas padrão
#include <array>        // Para criar arrays (matriz fixas 3x3)
#include <vector>       // Para criar listas dinâmicas (próximo estado)
#include <memory>       // Para usar shared_ptr (ponteiros inteligentes).
#include <string>       // Para armazenar textos
#include <algorithm>    // Para usar std::swap e outras funções utilitárias.

// Estado do tabuleiro
struct PuzzleState : public std::enable_shared_from_this<PuzzleState> {
    std::array<std::array<int, 3>, 3> board;    // Array o tabuleiro (3x3) Ex: {{2,3,4}, {1,6,7}, {5,8,0}}
    std::shared_ptr<PuzzleState> parent;        // Ponteiro inteligente para o estado pai
    std::string move;                           // Guarda o movimento que gerou o estado

    // Construtor da struct
    PuzzleState(std::array<std::array<int, 3>, 3> b, std::shared_ptr<PuzzleState> p = nullptr, std::string m = "")
        : board(b), parent(p), move(m) {}

    // Método usado para verificar se o tabuleiro está no estado final
    bool isGoal() const {
        int expected = 1;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (i == 2 && j == 2) return board[i][j] == 0;
                else if (board[i][j] != expected++) return false;
        return true;
    }

    // Método usado para gerar todos os estados possíveis a partir do estado atual
    std::vector<std::shared_ptr<PuzzleState>> getSuccessors() {
        std::vector<std::shared_ptr<PuzzleState>> successors;   // Lista dos estados gerados
        int x, y;   // Coordenadas da célula onde está o 0

        // Localiza onde está a posição vazia do tabuleiro
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == 0) { x = i; y = j; }

        // Define os deslocamentos válidos
        const std::array<std::pair<int, int>, 4> moves = {{
            {-1, 0},    // Cima
            {1, 0},     // Baixo
            {0, -1},    // Esquerda
            {0, 1}      // Direita
        }};
        // Nomeia cada movimento
        const std::array<std::string, 4> moveNames = {"cima", "baixo", "esquerda", "direita"};

        // Calcula as novas coordenadas do espaço vazio após a iteração
        for (int i = 0; i < 4; ++i) {
            int nx = x + moves[i].first;
            int ny = y + moves[i].second;
            // Verifica se o novo movimento está dentro dos limites do tabuleiro.
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) { 
                // Cria uma cópia do tabuleiro atual e faz a troca entre 0 e a peça vizinha.
                auto newBoard = board;
                std::swap(newBoard[x][y], newBoard[nx][ny]);

                // Cria um novo estado e adiciona à lista de sucessores
                successors.push_back(std::make_shared<PuzzleState>(newBoard, std::static_pointer_cast<PuzzleState>(shared_from_this()), moveNames[i]));
            }
        }
        return successors;
    }

    // Compara dois estados do tabuleiro
    bool operator==(const PuzzleState& other) const {
        return board == other.board;
    }
};
