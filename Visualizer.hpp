#pragma once                     // Garante que esse arquivo seja incluído apenas uma vez durante a compilação
#include <SFML/Graphics.hpp>    // Inclui SFML para construção de interfaces gráficas
#include "PuzzleState.hpp"      // Inclui a estrutura para criar o tabuleiro

// Função desenha o estado atual na window usando a font
void drawState(sf::RenderWindow& window, const PuzzleState& state, sf::Font& font) {
    window.clear(sf::Color(30, 30, 30));    // Limpa a janela com um cinza escuro.

    // Percorre cada célula da matriz 3x3.
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            sf::RectangleShape rect(sf::Vector2f(100, 100)); // Cria um quadrado de 100x100 pixels
            rect.setPosition(j * 110 + 50, i * 110 + 50);   // Espaçamento de 10px entre os blocos e margem de 50px da borda da janela.
            rect.setFillColor(state.board[i][j] == 0 ? sf::Color(70, 70, 70) : sf::Color::White);   //  Se for o "0" (espaço vazio), o bloco é cinza. Senão, branco.
            rect.setOutlineThickness(2);            // Desenha a espessura da borda do quadrado
            rect.setOutlineColor(sf::Color::Black); // Desenha a cor da borda do quadrado

            window.draw(rect); // Desenha o quadrado na janela.

            // Se não for "0", desenha o número no centro do quadrado com a fonte fornecida.
            if (state.board[i][j] != 0) {
                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(48);
                text.setFillColor(sf::Color::Black);
                text.setString(std::to_string(state.board[i][j]));
                text.setPosition(j * 110 + 80, i * 110 + 65);
                window.draw(text);
            }
        }

    window.display();   // Atualiza a janela e mostra todos os desenhos feitos.
}
