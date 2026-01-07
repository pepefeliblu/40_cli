# 40_cli - Cuarenta

A C++ CLI implementation of the traditional Ecuadorian card game **Cuarenta**.

## Description

"Cuarenta" (Forty) is the national card game of Ecuador. This C++ project simulates the game in the terminal, allowing a human player ("Usuario") to play against a computer opponent ("Cortana").

### Rules Implemented
*   **Caída**: Capturing a card by playing one of the same rank (2 points).
*   **Limpia**: Clearing the table (2 points).
*   **Ronda**: Initial hand bonus combinations.
*   **Suma**: Capturing cards by summing their values.
*   **Winning**: The first player to reach 40 points wins.

## Building

You can build the project using a C++14 compliant compiler (e.g., `clang++` or `g++`).

### Quick Build (clang++)
```bash
clang++ -std=c++14 -o 40_cli main.cpp Carta40.cpp Cortana.cpp Jugador.cpp Usuario.cpp
```

## Usage

Run the executable to start the game:

```bash
./40_cli
```

### Controls
Follow the on-screen prompts. Common commands include:
*   `lanzar [Card]` (e.g., `lanzar AC` for invalid throw, `lanzar`) - *Note: The game prompts for action then card.*
*   `robar` - Capture a card.
*   `caida` - Claim a "caída".
*   `sumar` - Capture by sum.

## Author

**Juan José Rueda**
CMP-320 Programación para ciencias e ingeniería 2
Profesor: Aldo Cassola

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
