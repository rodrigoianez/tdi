#include <string>
#include <limits>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <sys/stat.h>
#include "C_Image.hpp"
#include "C_Matrix.hpp"
#include <iostream>

// Función para solicitar ruta de archivo
std::string pedirRuta(bool esEntrada) {
    std::string ruta;
    std::string baseDir = "C:/Users/rodri/Desktop/TDI/practicaTDI/Run/";
    if (esEntrada) {
        std::cout << "Nombre del archivo de entrada (debe estar en " << baseDir << "): ";
        std::getline(std::cin, ruta);
        return baseDir + ruta;
    } else {
        std::cout << "Nombre del archivo de salida (se guardará en " << baseDir << "): ";
        std::getline(std::cin, ruta);
        return baseDir + ruta;
    }
}

// Función para verificar si un archivo existe
bool archivoExiste(const std::string& ruta) {
    struct stat buffer;
    return (stat(ruta.c_str(), &buffer) == 0);
}

// Función para generar ruta única de salida
std::string generarRutaSalida(const std::string& rutaEntrada, const std::string& metodo) {
    std::string baseDir = "C:/Users/rodri/Desktop/TDI/practicaTDI/Run/";
    // Extraer solo el nombre del archivo sin la ruta base
    size_t posBaseDir = rutaEntrada.find(baseDir);
    std::string nombreArchivo = (posBaseDir != std::string::npos) ? 
                               rutaEntrada.substr(posBaseDir + baseDir.length()) : 
                               rutaEntrada;
    
    size_t posPunto = nombreArchivo.find_last_of('.');
    std::string base = nombreArchivo.substr(0, posPunto);
    std::string ext = nombreArchivo.substr(posPunto);
    
    std::string nuevaRuta = baseDir + base + "_" + metodo + ext;
    int contador = 1;
    
    while (archivoExiste(nuevaRuta)) {
        nuevaRuta = baseDir + base + "_" + metodo + "_" + std::to_string(contador++) + ext;
    }
    return nuevaRuta;
}

// Función para copiar la paleta de colores
void copiarPaleta(C_Image& origen, C_Image& destino) {
    for (long i = 0; i < origen.PaletteSize(); i++) {
        destino.palette(i, C_RED) = origen.palette(i, C_RED);
        destino.palette(i, C_GREEN) = origen.palette(i, C_GREEN);
        destino.palette(i, C_BLUE) = origen.palette(i, C_BLUE);
    }
}

// Interpolación del vecino más cercano
void redimensionarVecinoMasCercano(C_Image& origen, C_Image& destino) {
    double escalaX = static_cast<double>(origen.ColN()) / destino.ColN();
    double escalaY = static_cast<double>(origen.RowN()) / destino.RowN();

    for (long y = destino.FirstRow(); y <= destino.LastRow(); y++) {
        for (long x = destino.FirstCol(); x <= destino.LastCol(); x++) {
            long origenX = static_cast<long>(x * escalaX + 0.5);
            long origenY = static_cast<long>(y * escalaY + 0.5);
            origenX = std::max(origen.FirstCol(), std::min(origen.LastCol(), origenX));
            origenY = std::max(origen.FirstRow(), std::min(origen.LastRow(), origenY));
            destino(y, x) = origen(origenY, origenX);
        }
    }
    copiarPaleta(origen, destino);
}

// Interpolación Bilineal
void redimensionarBilineal(C_Image& origen, C_Image& destino) {
    double escalaX = static_cast<double>(origen.ColN()) / destino.ColN();
    double escalaY = static_cast<double>(origen.RowN()) / destino.RowN();

    for (long y = destino.FirstRow(); y <= destino.LastRow(); y++) {
        for (long x = destino.FirstCol(); x <= destino.LastCol(); x++) {
            double origenX = x * escalaX;
            double origenY = y * escalaY;
            
            // Asegurar que los índices estén dentro de los límites
            long x1 = std::max(origen.FirstCol(), std::min(origen.LastCol(), static_cast<long>(origenX)));
            long y1 = std::max(origen.FirstRow(), std::min(origen.LastRow(), static_cast<long>(origenY)));
            long x2 = std::max(origen.FirstCol(), std::min(origen.LastCol(), x1 + 1));
            long y2 = std::max(origen.FirstRow(), std::min(origen.LastRow(), y1 + 1));
            
            double dx = origenX - x1;
            double dy = origenY - y1;
            
            double interpX1 = (1 - dx) * origen(y1, x1) + dx * origen(y1, x2);
            double interpX2 = (1 - dx) * origen(y2, x1) + dx * origen(y2, x2);
            destino(y, x) = (1 - dy) * interpX1 + dy * interpX2;
        }
    }
    copiarPaleta(origen, destino);
}

// Función auxiliar para el kernel cúbico
double kernelCubico(double x) {
    x = std::fabs(x);
    if (x < 1.0) {
        return (1.5 * x - 2.5) * x * x + 1.0;
    } else if (x < 2.0) {
        return ((-0.5 * x + 2.5) * x - 4.0) * x + 2.0;
    }
    return 0.0;
}

void redimensionarBicubico(C_Image& origen, C_Image& destino) {
    double escalaX = static_cast<double>(origen.ColN()) / destino.ColN();
    double escalaY = static_cast<double>(origen.RowN()) / destino.RowN();
    
    for (long y = destino.FirstRow(); y <= destino.LastRow(); y++) {
        for (long x = destino.FirstCol(); x <= destino.LastCol(); x++) {
            double origenX = x * escalaX;
            double origenY = y * escalaY;
            
            // Obtener las coordenadas del píxel base
            int x0 = static_cast<int>(std::floor(origenX));
            int y0 = static_cast<int>(std::floor(origenY));
            
            double valorInterpolado = 0.0;
            double pesoTotal = 0.0;
            
            // Iterar sobre la ventana 4x4
            for (int dy = -1; dy <= 2; dy++) {
                for (int dx = -1; dx <= 2; dx++) {
                    int px = x0 + dx;
                    int py = y0 + dy;
                    
                    // Comprobar si el píxel está dentro de los límites
                    if (px >= origen.FirstCol() && px <= origen.LastCol() && 
                        py >= origen.FirstRow() && py <= origen.LastRow()) {
                        
                        // Calcular la distancia para el kernel
                        double distX = origenX - px;
                        double distY = origenY - py;
                        
                        // Aplicar el kernel cúbico directamente a las distancias
                        double pesoX = kernelCubico(distX);
                        double pesoY = kernelCubico(distY);
                        double peso = pesoX * pesoY;
                        
                        valorInterpolado += origen(py, px) * peso;
                        pesoTotal += peso;
                    }
                }
            }
            
            // Normalizar solo si el peso total es significativo
            if (pesoTotal > 0.001) {
                valorInterpolado /= pesoTotal;
            } else {
                // Si el peso es muy bajo, usar el valor del píxel más cercano
                long px = static_cast<long>(std::round(origenX));
                long py = static_cast<long>(std::round(origenY));
                px = std::max(origen.FirstCol(), std::min(origen.LastCol(), px));
                py = std::max(origen.FirstRow(), std::min(origen.LastRow(), py));
                valorInterpolado = origen(py, px);
            }
            
            // Asegurar que el valor esté dentro del rango válido
            valorInterpolado = std::max(0.0, std::min(255.0, valorInterpolado));
            destino(y, x) = static_cast<long>(valorInterpolado);
        }
    }
    copiarPaleta(origen, destino);
}

// Función para obtener un número entero positivo
int pedirEnteroPositivo(const std::string& mensaje) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor && valor > 0) break;
        std::cout << "Error: Ingrese un numero positivo.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

// Función para obtener las dimensiones de la imagen
void obtenerDimensiones(int anchoOriginal, int altoOriginal, int& ancho, int& alto) {
    std::cout << "\nMODO DE REDIMENSIONAMIENTO\n";
    std::cout << "|----------------------------------------|\n";
    std::cout << "| 1. Manual (dimensiones exactas)        |\n";
    std::cout << "| 2. Automatico (factor de escala)       |\n";
    std::cout << "|----------------------------------------|\n";
    
    int opcion = pedirEnteroPositivo("Seleccione una opción (1-2): ");
    
    if (opcion == 1) {
        std::cout << "\n DIMENSIONES MANUALES\n";
        std::cout << "   Dimensiones actuales: " << anchoOriginal << "x" << altoOriginal << "\n";
        ancho = pedirEnteroPositivo("   Ancho objetivo: ");
        alto = pedirEnteroPositivo("   Alto objetivo: ");
    } else {
        std::cout << "\n⚖️ FACTOR DE ESCALA\n";
        std::cout << "|----------------------------------------|\n";
        std::cout << "| 1. Mitad (0.5x)                        |\n";
        std::cout << "| 2. Doble (2x)                          |\n";
        std::cout << "| 3. Personalizado                       |\n";
        std::cout << "|----------------------------------------|\n";
        
        int factorOpcion = pedirEnteroPositivo("Seleccione una opción (1-3): ");
        double factor;
        
        switch (factorOpcion) {
            case 1: 
                factor = 0.5; 
                std::cout << "   Aplicando factor: 0.5x\n";
                break;
            case 2: 
                factor = 2.0; 
                std::cout << "   Aplicando factor: 2.0x\n";
                break;
            default:
                while (true) {
                    std::cout << "   Factor (ejemplo: 0.5 o 2.0): ";
                    if (std::cin >> factor && factor > 0) break;
                    std::cout << "   Error: Ingrese un numero positivo.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        ancho = static_cast<int>(anchoOriginal * factor);
        alto = static_cast<int>(altoOriginal * factor);
        std::cout << "   Nuevas dimensiones: " << ancho << "x" << alto << "\n";
    }
}

// Función para seleccionar el algoritmo
std::string seleccionarAlgoritmo() {
    std::cout << "\n    ALGORITMO DE INTERPOLACION\n";
    std::cout << "|----------------------------------------|\n";
    std::cout << "| 1. Vecino mas cercano                  |\n";
    std::cout << "|      Mas rapido                        |\n";
    std::cout << "|      Calidad básica                    |\n";
    std::cout << "| 2. Bilineal                            |\n";
    std::cout << "|      Balance velocidad/calidad         |\n";
    std::cout << "|      Buena para fotos                  |\n";
    std::cout << "| 3. Bicubico                            |\n";
    std::cout << "|      Mejor calidad                     |\n";
    std::cout << "|      Mas lento                         |\n";
    std::cout << "|----------------------------------------|\n";
    
    int seleccion = pedirEnteroPositivo("Seleccione un algoritmo (1-3): ");
    switch (seleccion) {
        case 1: return "vecino";
        case 2: return "bilineal";
        default: return "bicubico";
    }
}

int main() {
    try {
        std::cout << "                                         |----------------------------------------|\n";
        std::cout << "                                         |     REDIMENSIONADOR DE IMAGENES        |\n";
        std::cout << "                                         |----------------------------------------|\n\n";
        
        std::cout << "  INSTRUCCIONES:\n";
        std::cout << "   - Solo necesitara ingresar el nombre del archivo\n";
        std::cout << "   - La imagen resultante se guardara en la carpeta Run\n\n";
        
        std::string rutaEntrada = pedirRuta(true);
        if (rutaEntrada.empty()) return 0;
        
        C_Image imagenOrigen;
        try {
            std::cout << "\n Cargando imagen...\n";
            imagenOrigen.Read(rutaEntrada.c_str());
            
            if (imagenOrigen.ColN() == 0 || imagenOrigen.RowN() == 0) {
                std::cerr << " Error: La imagen cargada tiene dimensiones invalidas (0x0)\n";
                return 1;
            }
            
            std::cout << " Informacion de la imagen:\n";
            std::cout << "   - Tamano: " << imagenOrigen.ColN() << "x" << imagenOrigen.RowN() << "\n";
            std::cout << "   - Profundidad de color: " << imagenOrigen.PaletteSize() << " colores\n";
        }
        catch (const std::exception& e) {
            std::cerr << " Error al cargar la imagen: " << e.what() << "\n";
            std::cerr << "   Verifique que:\n";
            std::cerr << "   1. La imagen esta en la carpeta 'Run'\n";
            std::cerr << "   2. El nombre del archivo es correcto\n";
            std::cerr << "   3. El formato es compatible (BMP, GIF, PNG)\n";
            return 1;
        }
        catch (...) {
            std::cerr << " Error desconocido al cargar la imagen.\n";
            return 1;
        }
        
        int ancho, alto;
        obtenerDimensiones(imagenOrigen.ColN(), imagenOrigen.RowN(), ancho, alto);
        
        if (ancho <= 0 || alto <= 0) {
            std::cerr << " Error: Las dimensiones de salida son invalidas\n";
            return 1;
        }
        
        std::string algoritmo = seleccionarAlgoritmo();
        
        C_Image imagenDestino(0, alto - 1, 0, ancho - 1, 0, imagenOrigen.PaletteSize());
        
        std::cout << "\n Procesando imagen...\n";
        try {
            if (algoritmo == "vecino") {
                redimensionarVecinoMasCercano(imagenOrigen, imagenDestino);
            } else if (algoritmo == "bilineal") {
                redimensionarBilineal(imagenOrigen, imagenDestino);
            } else {
                redimensionarBicubico(imagenOrigen, imagenDestino);
            }
        }
        catch (const std::exception& e) {
            std::cerr << " Error durante el procesamiento: " << e.what() << "\n";
            return 1;
        }
        
        std::string rutaSalida = generarRutaSalida(rutaEntrada, algoritmo);
        std::cout << " Guardando como: " << rutaSalida << "\n";
        
        try {
            imagenDestino.Write(rutaSalida.c_str());
            std::cout << "  ¡Proceso completado con exito!\n";
            std::cout << "   La imagen se ha guardado en: " << rutaSalida << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << " Error al guardar la imagen: " << e.what() << "\n";
            return 1;
        }
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << " Error: " << e.what() << "\n";
        return 1;
    }
}
