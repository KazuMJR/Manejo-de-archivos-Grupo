#include <experimental/filesystem>
#include <iostream>
#include <dirent.h>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sys/stat.h>

namespace fs = std::filesystem;
using namespace std;

// Variables
string ruta_archivo;
string nuevoruta_archivo;
string destino;
string archivo;

// Funciones prototipo
void ordenararchivos();
void identificador();
void list_dir(const string& dir);
void init();
void abrir();
void eliminar();
void renombrar_archivo();
void mover();
void comprimir();
void descomprimir();
void ejecutar();
void buscar_archivo_por_nombre(const string& directorio, const string& nombre_archivo);
void crear_directorio(const string& ruta);
bool existeArchivo(const char* nombreArchivo);

int main(int argc, char *argv[]){
    init();
    return 0;
}

// Función para ingresar ruta
void init(){
    string dir;
    string opcion; // Cambio en el tipo de dato

    while (true) {
cout << "-------------------------------------------------------------------------------------------------------------------\n" << endl;
cout << "Ingrese la ruta del directorio que desee listar siguiendo el ejemplo:\n no deje espacios al momento de ingresar el directorio.\nC:\\Users\\jasso\\Desktop\\VS_CODE\\Manejo_de_archivos_en_grupo"<<endl;
    cout << "\n-------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Ruta del directorio a listar (o 'q' para salir): ";
        getline(cin, dir);
        cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

        if (dir == "q") {
            cout << "Saliendo del programa..." << endl;
            break;
        }

        // Mostrar los archivos dentro del directorio ingresado
        list_dir(dir);
        cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

        cout << "---------------------------------------------Seleccione la proxima accion----------------------------------------" << endl;

        cout<<"Salir [q], Listar otro directorio [1], Abrir archivo [2], Eliminar archivo [3], Renombrar archivo [4],\nMover archivo [5], Ejecutar programa[6], Comprimir[7], Descomprimir[8], Buscar archivo por nombre[9],\nCrear directorio [10], Ordenar Archivos [11]."<<endl;
        cout << "------------------------------------------------------------------------------------------------------------------" << endl;

        cout<<"Opcion: ";
        getline(cin, opcion); // Cambio en la forma de leer la entrada del usuario
        cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;

        // Manejo de la excepción
        try {
            int opcion_numero = stoi(opcion); // Convertir la entrada a un número entero
            switch (opcion_numero) {
                case 2: abrir(); break;
                case 3: eliminar(); break;
                case 4: renombrar_archivo(); break;
                case 5: mover(); break;
                case 6: ejecutar(); break;
                case 7: comprimir(); break;
                case 8: descomprimir(); break;
                case 9: {
                    cout << "Ingrese el nombre del archivo a buscar: ";
                    getline(cin, archivo);
                    buscar_archivo_por_nombre(dir, archivo);
                    break;
                }
                case 10: {
                    string nuevo_dir;
                    cout<<"Ingrese la ubicacion como se muestra en el ejemplo:\n no deje espacios en el nuevo directorio\nC:\\Users\\jasso\\Desktop\\VS_CODE\\Manejo_de_archivos_en_grupo\\'+Nombre del nuevo directorio"<<endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

                    cout << "Ingrese la ruta del nuevo directorio: ";
                    getline(cin, nuevo_dir);
                    crear_directorio(nuevo_dir);
                    break;
                }
                case 11: ordenararchivos(); break;
                case 1: continue; // Volver al inicio del bucle para ingresar otro directorio
                default: cout << "Opcion no valida. Por favor, intente de nuevo." << endl;
            }
        } catch (const invalid_argument& e) { // Manejar la excepción invalid_argument
            cout << "Error: Opcion no valida. Por favor, ingrese un numero valido." << endl;
        }
    }
}
    
// Función para listar archivos con sus tamaños en MB
void list_dir(const string& dir){
    DIR* directorio;
    struct dirent* elemento;
    string elem;
    if (directorio = opendir(dir.c_str())) {
        while (elemento = readdir(directorio)) {
            elem = elemento->d_name;
            if (elem != "." && elem != "..") {
                string ruta_completa = dir + "/" + elem;
                struct stat st;
                if (stat(ruta_completa.c_str(), &st) == 0) {
                    // Convertir el tamaño a MB
                    float tamano_mb = static_cast<float>(st.st_size) / (1024 * 1024);
                    cout << "Nombre: " << elem << ", Tamano: " << tamano_mb << " MB" << endl;
                } else {
                    cout << "Error al obtener el tamano de " << elem << endl;
                }
            }
        }
    }
    closedir(directorio);
}

// Función para abrir archivo
void abrir(){
    identificador();

    ifstream archivo(ruta_archivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    
    string linea, texto;
    while (getline(archivo, linea)) {
        texto += linea + "\n";
    }
    cout << "Contenido del archivo:\n" << texto << endl;
    archivo.close();
}

// Función para eliminar archivo
void eliminar(){
    identificador();

    if (remove(ruta_archivo.c_str()) == 0) {
        cout << "Archivo eliminado correctamente." << endl;
    } else {
        cout << "Error al eliminar el archivo." << endl;
    }
}

// Función para renombrar un archivo
void renombrar_archivo() {
    char originalNombre[100], nuevoNombre[100];
cout<<"Ingrese la ubicacion como se muestra en el ejemplo:\nAl final en nombre ingrese el nombre del archivo\nC:\\Users\\jasso\\Desktop\\VS_CODE\\Manejo_de_archivos_en_grupo\\'+Nombre"<<endl;
cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Ingresa la ruta completa del archivo a renombrar: ";
    cin.getline(originalNombre, 100);

    if (existeArchivo(originalNombre)) {
        cout << "Ingresa el nuevo nombre para el archivo: ";
        cin.getline(nuevoNombre, 100);

        if (rename(originalNombre, nuevoNombre) == 0) {
            cout << "El archivo se ha renombrado correctamente.\n";
        } else {
            cout << "No se pudo renombrar el archivo.\n";
        }
    } else {
        cout << "El archivo no existe en la ruta proporcionada.\n";
    }
}

// Función para mover archivo
void mover(){
    cout<<"Ingrese la ubicacion como se muestra en el ejemplo:\nAl final en nombre ingrese el nombre del archivo\nC:\\Users\\jasso\\Desktop\\VS_CODE\\Manejo_de_archivos_en_grupo\\'+Nombre"<<endl;
cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
     cout << "Ingrese la ruta de la carpeta que desea organizar: ";
    string folderPath;
    cin >> folderPath;

    // Lee los archivos en la carpeta
    for (const auto& entry : filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            string fileName = entry.path().filename().string();
            string extension = entry.path().extension().string();

            // Elimina el punto inicial de la extensión
            if (!extension.empty() && extension[0] == '.') {
                extension = extension.substr(1);
            }

            // Crea una carpeta para la extensión si no existe
            string extensionFolder = folderPath + "/" + extension;
            filesystem::create_directory(extensionFolder);

            // Mueve el archivo a la carpeta correspondiente
            filesystem::rename(entry.path(), extensionFolder + "/" + fileName);
        }
    }

    cout << "Archivos organizados en carpetas por extension." << endl;
}

// Función para obtener la ruta del archivo
void identificador(){

    cout << "Para poder abrir un archivo ingrese la ruta como se muestra en el ejemplo:\n no deje espacios al momento de ingresar el nombre.\nC:\\Users\\jasso\\Desktop\\VS_CODE\\Manejo_de_archivos_en_grupo\\'+ Nombre"<<endl;
    cout << "\n-------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Escriba la ruta del archivo: ";
    getline(cin, ruta_archivo);
}

// Función para ejecutar un programa
void ejecutar(){
    string valor;
    cout << "Seleccione una opción para ejecutar" << endl;
    cout << "[1]Abrir PSeInt \n[2]Abrir VS code \n[3]Volver \n";
    cin >> valor;
    cin.ignore();

    if (valor == "1") {
        system("C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo/Abrir.psc");
    } else if (valor == "2") {
        system("C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo/Abrir.c++");
    } else if (valor == "3") {
        return;
    } else {
        cout << "Opcion no válida." << endl;
    }
}

// Función para comprimir un archivo
void comprimir() {
    cout << "Para poder Comprimir un archivo ingrese la ruta como se muestra en el ejemplo:\n no deje espacios al momento de ingresar el nombre.\nC:\\Users\\jasso\\Desktop\\VS_CODE\\Manejo_de_archivos_en_grupo\\'+ Nombre"<<endl;
    cout << "\n-------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Ingrese la ruta del archivo que desea comprimir: ";
    getline(cin, ruta_archivo);

    // Verificar si el archivo existe
    if (!fs::exists(ruta_archivo)) {
        cout << "El archivo especificado no existe." << endl;
         cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
        return;
    }

    // Construir el comando para comprimir usando 7zip
    string comando = "7z a COMPRIMIENDO.7z \"" + ruta_archivo + "\"";

    // Ejecutar el comando
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "Archivo comprimido correctamente." << endl;
         cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
    } else {
        cout << "Error al comprimir el archivo." << endl;
         cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
    }
}

// Función para descomprimir un archivo
void descomprimir() {
    string archivoComprimido, directorioDestino;

    cout << "Para poder decomprimir un archivo ingrese la ruta como se muestra en el ejemplo:\n no deje espacios al momento de ingresar el nombre.\nC:\\Users\\jasso\\Desktop\\VS_CODE\\Manejo_de_archivos_en_grupo\\'+ Nombre"<<endl;
    cout << "\n-------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Ingrese la ruta del archivo comprimido: ";
    getline(cin, archivoComprimido);

    cout << "Ingrese la ruta del directorio destino: ";
    getline(cin, directorioDestino);

    // Verificar si el archivo comprimido existe
    if (!fs::exists(archivoComprimido)) {
        cout << "El archivo comprimido especificado no existe." << endl;
        cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
        return;
    }

    // Crear el comando para descomprimir usando 7zip
    string comando = "7z x \"" + archivoComprimido + "\" -o\"" + directorioDestino + "\"";

    // Ejecutar el comando
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        cout << "Archivo descomprimido correctamente." << endl;
         cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
    } else {
        cout << "Error al descomprimir el archivo." << endl;
         cout << "\n-------------------------------------------------------------------------------------------------------------------\n" << endl;
    }
}

// Función para buscar archivos por nombre en un directorio
void buscar_archivo_por_nombre(const string& directorio, const string& nombre_archivo) {
    bool encontrado = false;

    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file() && entry.path().filename() == nombre_archivo) {
            cout << "Archivo encontrado: " << entry.path() << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontro ningún archivo con el nombre especificado en el directorio." << endl;
    }
}

// Función para crear un nuevo directorio
void crear_directorio(const string& ruta) {
    if (fs::create_directory(ruta)) {
        cout << "Directorio creado correctamente." << endl;
    } else {
        cout << "Error al crear el directorio." << endl;
    }
}

// Función para ordenar archivos
void ordenararchivos() {
    // Ruta de la carpeta que deseas organizar
    string folderPath = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
    // Vector para almacenar los nombres de los archivos
    vector<string> fileNames;

    // Lee los archivos en la carpeta
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            fileNames.push_back(entry.path().filename().string());
        }
    }

    // Ordena los nombres de los archivos alfabéticamente
    sort(fileNames.begin(), fileNames.end());

    // Imprime los nombres de los archivos ordenados
    for (const auto& fileName : fileNames) {
        cout << fileName << endl;
    }
}

// Función para verificar si un archivo existe
bool existeArchivo(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo) {
        fclose(archivo);
        return true;
    }
    return false;
}
