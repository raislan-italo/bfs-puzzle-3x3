#include <SFML/Graphics.hpp>
#include "PuzzleState.hpp"
#include "BFS.hpp"
#include "Visualizer.hpp"
#include <thread>
#include <iostream>

using namespace std;

int main() {
    array<array<int, 3>, 3> tabuleiroInicial {{
        {2, 5, 6},
        {3, 4, 1},
        {8, 7, 0}
    }};

    // Cria uma janela 400x400
    sf::RenderWindow window(sf::VideoMode(400, 400), "Quebra-Cabeca 3x3 - BFS");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1; // Se a fonte não carregar, o programa sai

    // Exibe o estado inicial e espera pelo clique
    PuzzleState inicial(tabuleiroInicial);
    drawState(window, inicial, font); // Desenha o estado inicial uma vez

    std::cout << "Clique na janela para iniciar a resolução..." << std::endl;

    bool clicked = false;
    while (window.isOpen() && !clicked) { // Loop para esperar pelo clique
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) { // Verifica se um botão do mouse foi pressionado
                clicked = true; // Define clicked como true para sair do loop de espera
            }
        }
    }

    if (!window.isOpen()) { // Se a janela foi fechada antes do clique, sai do programa
        return 0;
    }

    // Inicia a resolução BFS após o clique
    std::cout << "Iniciando busca BFS..." << std::endl;
    auto caminho = bfs(inicial); // O BFS retorna o caminho como um vetor de PuzzleState

    // Parte para imprimir a solução inicial e configurar o contador de movimentos
    if (caminho.empty()) {
        std::cout << "Nenhuma solução encontrada para este tabuleiro" << std::endl;
    } else {
        std::cout << "Solução encontrada em " << caminho.size() - 1 << " movimentos!" << std::endl;
        std::cout << "Iniciando visualização passo a passo..." << std::endl;
    }

    int contadorMovimentos = 0; // Inicializa um contador para os movimentos

    for (const auto& estado : caminho) {                                // Loop que itera pelos estados da solução
        drawState(window, estado, font);                                // Desenha o estado atual na janela
        std::this_thread::sleep_for(std::chrono::milliseconds(600));    // Pausa para a visualização

        // Impressão em tempo real
        if (contadorMovimentos == 0) { // O primeiro estado é o inicial
            std::cout << "Estado Inicial (0 movimentos)" << std::endl;
        } else {
            std::cout << "Movimento " << contadorMovimentos << ": " << estado.move << std::endl; // Imprime o número do movimento e o nome do movimento
        }
        contadorMovimentos ++; // Incrementa o contador para o próximo movimento

        sf::Event event;
        while (window.pollEvent(event)) { // Processa eventos da janela, como fechamento
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    // Loop final para manter a janela aberta após a animação
    std::cout << "Visualização completa. Clique na janela para fechar." << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
    }

    return 0;
}