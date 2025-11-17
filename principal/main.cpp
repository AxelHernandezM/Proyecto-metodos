#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <limits> 

double derivada_2_puntos_desiguales(double x0, double f_x0, double x1, double f_x1) {
    if (x1 == x0) {
        throw std::invalid_argument("Los puntos x deben ser diferentes.");
    }
    return (f_x1 - f_x0) / (x1 - x0);
}

double derivada_3_puntos_desiguales(double x0, double f_x0, double x1, double f_x1, double x2, double f_x2) {
    if (x0 == x1 || x0 == x2 || x1 == x2) {
        throw std::invalid_argument("Los puntos x deben ser distintos entre sí.");
    }

    double c0 = (x1 - x2) / ((x0 - x1) * (x0 - x2));
    double c1 = (2.0 * x1 - x0 - x2) / ((x1 - x0) * (x1 - x2));
    double c2 = (x1 - x0) / ((x2 - x1) * (x2 - x0));

    return f_x0 * c0 + f_x1 * c1 + f_x2 * c2;
}

// --- Gestión de la Entrada de Usuario ---

void limpiar_entrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int mostrar_menu() {
    int opcion = -1;
    std::cout << "\n--------------------------------------------------------" << std::endl;
    std::cout << "  Menu: Diferenciacion numerica (Puntos desiguales)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "1. Aproximacion con 2 Puntos" << std::endl;
    std::cout << "2. Aproximacion con 3 Puntos (en el punto central x1)" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Opción: ";

    if (!(std::cin >> opcion)) {
        limpiar_entrada();
        return -1;
    }
    return opcion;
}

void ejecutar_2_puntos() {
    double x_a, f_a, x_b, f_b;
    std::cout << "\n--- Método de 2 Puntos ---" << std::endl;

    std::cout << "Ingrese x0: ";
    if (!(std::cin >> x_a)) { limpiar_entrada(); return; }
    std::cout << "Ingrese f(x0): ";
    if (!(std::cin >> f_a)) { limpiar_entrada(); return; }

    std::cout << "Ingrese x1: ";
    if (!(std::cin >> x_b)) { limpiar_entrada(); return; }
    std::cout << "Ingrese f(x1): ";
    if (!(std::cin >> f_b)) { limpiar_entrada(); return; }

    try {
        double aprox = derivada_2_puntos_desiguales(x_a, f_a, x_b, f_b);
        std::cout << "\nResultado de 2 Puntos: f'(x) ≈ " << aprox << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "\nERROR: " << e.what() << std::endl;
    }
}

void ejecutar_3_puntos() {
    double x0, f0, x1, f1, x2, f2;
    std::cout << "\n--- Método de 3 Puntos (Derivada en x1) ---" << std::endl;

    std::cout << "Ingrese x0: ";
    if (!(std::cin >> x0)) { limpiar_entrada(); return; }
    std::cout << "Ingrese f(x0): ";
    if (!(std::cin >> f0)) { limpiar_entrada(); return; }

    std::cout << "Ingrese el punto CENTRAL x1: ";
    if (!(std::cin >> x1)) { limpiar_entrada(); return; }
    std::cout << "Ingrese f(x1): ";
    if (!(std::cin >> f1)) { limpiar_entrada(); return; }

    std::cout << "Ingrese x2: ";
    if (!(std::cin >> x2)) { limpiar_entrada(); return; }
    std::cout << "Ingrese f(x2): ";
    if (!(std::cin >> f2)) { limpiar_entrada(); return; }

    try {
        double aprox = derivada_3_puntos_desiguales(x0, f0, x1, f1, x2, f2);
        std::cout << "\n Resultado de 3 Puntos (en x1=" << x1 << "): f'(x1) ≈ " << aprox << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "\nERROR: " << e.what() << std::endl;
    }
}


int main() {
    std::cout << std::fixed << std::setprecision(8);
    
    while (true) {
        int opcion = mostrar_menu();

        switch (opcion) {
            case 1:
                ejecutar_2_puntos();
                break;
            case 2:
                ejecutar_3_puntos();
                break;
            case 0:
                std::cout << "\nSaliendo del programa" << std::endl;
                return 0;
            default:
                std::cout << "\nOpción inválida." << std::endl;
                limpiar_entrada();
                break;
        }
    }
}