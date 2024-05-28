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
string current_dir;
string extension_default = ".txt";

//Vector
vector<string> extensiones = {".txt", ".cpp", ".c++", ".hpp", ".py", ".dll", ".7z", ".exe"};

// Funciones prototipo
void ordenararchivos();
void list_dir(const string& dir);
void init();
void bloquear();
void desbloquear();
void copiar();
void Comprimir_Descomprimir();
void ejecutar();
void buscar_archivo_por_nombre();
string agregar_extension(const string& archivo, const vector<string>& extensiones);


int main(int argc, char *argv[]){
    init();
    return 0;
}

// Funcion Inicial
void init() {
    string opcion;

    while (true) {
        
cout << "================================================================ \033[1m\033[34mGESTOR DE ARCHIVOS\033[0m ========================================================================\n"<<endl;
       
        cout << " ----------------------------------------------------------- Seleccione la accion a realizar ---------------------------------------------------------------" << endl;
        cout << "Salir [q]"<<endl;
        cout << "Limpiar pantalla [0]    [1] Ejecutar un programa                      [4] Bloquear un archivo                         [7] Buscar archivo por nombre\n";
        cout << "                        [2] Comprimir o descomprimir                  [5] Desbloquear un archivo\n";
        cout << "                        [3] Copiar un archivo                         [6] Ordenar archivos\n";
        cout << " ===========================================================================================================================================================" << endl;
        cout << "Opcion: ";
        getline(cin, opcion); // Cambio en la forma de leer la entrada del usuario
        cout << " ===========================================================================================================================================================\n" << endl;  
        
        // Manejo de la excepcion
        try {
            if (opcion == "q") {
                cout << "\n\033[1mSaliendo del programa...\033[0m\n";
                break;
            }

            int opcion_numero = stoi(opcion); // Convertir la entrada a un número entero

            switch (opcion_numero) {
                case 0:
                    system("cls"); // Limpiar la pantalla
                    break;
                case 1:
                    ejecutar();
                    break; // Volver al inicio del bucle para ingresar otra accion
                case 2:
                    Comprimir_Descomprimir();
                    break;
                case 3:
                    copiar();
                    break;
                case 4:
                    //bloquear();
                    break;
                case 5:
                    //desbloquear();
                    break;
                case 6:
                    ordenararchivos();
                    break;
                case 7: {
                    buscar_archivo_por_nombre();
                    break;
                }
                default:
                    cout << "\n\033[1;31mOpcion no valida. Por favor, intente de nuevo.\033[0m\n";
            }
        } catch (const invalid_argument& e) { // Manejar la excepcion invalid_argument
            cout << "\n\033[1;31mError: Opcion no valida. Por favor, ingrese un número valido.\033[0m\n";
        }
    }
}



// Funcion para listar archivos 
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
                    cout << "Nombre: " << elem << endl;
                } else {
                    cout << "Error" << elem << endl;
                }
            }
        }
    }
    closedir(directorio);
}

// Funcion auxiliar para agregar la extension si es necesario

string agregar_extension(const string& archivo, const vector<string>& extensiones) {
    size_t pos = archivo.find_last_of('.');
    if (pos != string::npos) {
        string ext = archivo.substr(pos);
        if (find(extensiones.begin(), extensiones.end(), ext) != extensiones.end()) {
            return archivo;
        }
    }
    return archivo + extension_default;
}

// Funcion para copiar un archivo
void copiar() {
    string origen, archivo, destino;
    
    cout << "\n\033[1mSeleccione el directorio de origen:\033[0m\n";
    cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
    cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
    cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
    cout << "[4] \033[1;31mVolver\033[0m\n"<<endl;
    cout << "\033[1mOpcion: \033[0m";
    getline(cin, origen);
    cout << " ===========================================================================================================================================================\n" << endl;
    if (origen == "1") {
        origen = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
        cout << " ===========================================================================================================================================================\n" << endl;
        list_dir(origen);
        cout << " ===========================================================================================================================================================\n" << endl;
        cout << " ===========================================================================================================================================================\n" << endl;
    } else if (origen == "2") {
        origen = "C:/Users/jasso/Desktop/VS_CODE";
        cout << " ===========================================================================================================================================================\n" << endl;
        list_dir(origen);
        cout << " ===========================================================================================================================================================\n" << endl;
        cout << " ===========================================================================================================================================================\n" << endl;
    } else if (origen == "3") {
        origen = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
        cout << " ===========================================================================================================================================================\n" << endl;
        list_dir(origen);
        cout << " ===========================================================================================================================================================\n" << endl;
        cout << " ===========================================================================================================================================================\n" << endl;
    } 
    else if (origen == "4"){
        return init();
    }
    else {
        cout << "\n\033[1mOpcion no valida.\033[0m\n";
        return;
    }
    
    cout << "\n\033[1mIngrese el nombre del archivo a copiar: \033[0m";
    getline(cin, archivo);
    archivo = agregar_extension(archivo, extensiones); // Agregar la extension.
    
    cout << " ===========================================================================================================================================================\n" << endl;
    cout << "\033[1mSeleccione el directorio de destino:\033[0m\n";
    cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
    cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
    cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
    cout << "[4] \033[34mBuscar otro archivo\033[0m\n"<<endl;
    cout << "\033[1mOpcion: \033[0m";
    getline(cin, destino);
    cout << " ===========================================================================================================================================================\n" << endl;
    if (destino == "1") {
        destino = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
    } else if (destino == "2") {
        destino = "C:/Users/jasso/Desktop/VS_CODE";
    } else if (destino == "3") {
        destino = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
    } 
    else if (destino == "4"){
        return init();
    }
    else {
        cout << "\n\033[1mOpcion no valida.\033[0m\n";
        return;
    }
    
    string ruta_origen = origen + "/" + archivo;
    string ruta_destino = destino + "/" + archivo;
    
    try {
        fs::copy(ruta_origen, ruta_destino, fs::copy_options::overwrite_existing);
        cout << "\n\033[1mArchivo copiado exitosamente a \033[32m" << ruta_destino << "\033[0m\033[1m.\033[0m\n";
        cout << " ===========================================================================================================================================================\n" << endl;
    } catch (const fs::filesystem_error& e) {
        cout << "\n\033[1mError al copiar el archivo: \033[31m" << e.what() << "\033[0m\033[1m.\033[0m\n";
        cout << " ===========================================================================================================================================================\n" << endl;
    }
}


// Funcion para ejecutar un programa
void ejecutar() {
    string valor;
    cout << "\n\033[1mSeleccione una opcion para ejecutar\033[0m\n";
    cout << "[1] \033[34mAbrir PSeInt\033[0m\n[2] \033[34mAbrir VS code\033[0m\n[3] \033[34mVolver\033[0m\n";
    cout << "\033[1mOpcion: \033[0m";
    cin >> valor;
    cin.ignore();

    if (valor == "1") {
        system("C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo/Abrir.psc");
        return init();
    } else if (valor == "2") {
        system("C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo/Abrir.c++");
        return init();
    } else if (valor == "3") {
        return init();
    } else {
        cout << "\n\033[1;31mOpcion no valida.\033[0m\n";
    }
    cout << " ===========================================================================================================================================================\n" << endl;
}


// Funcion para comprimir y descomprimir un archivo
void Comprimir_Descomprimir() {
    string opcion, origen, archivo, destino;

    cout << "[0] \033[34mVolver\033[0m\n"<<endl;
    cout << "\n\033[1m[1] Comprimir  [2] Descomprimir\033[0m\n"<<endl;
    cout << "\033[1mSeleccione una opcion: \033[0m";
    getline(cin, opcion);
    cout << " ===========================================================================================================================================================\n" << endl;

    if (opcion == "1") {
        cout << "\n\033[1mSeleccione el directorio de origen:\033[0m\n"<<endl;
        cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
        cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
        cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
        cout << "[4] \033[1;31mVolver\033[0m\n"<<endl;
        cout << "\033[1mOpcion: \033[0m";
        getline(cin, origen);
        cout << " ===========================================================================================================================================================\n" << endl;
        if (origen == "1") {
            origen = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
            list_dir(origen);
            cout << " ===========================================================================================================================================================\n" << endl;
        } else if (origen == "2") {
            origen = "C:/Users/jasso/Desktop/VS_CODE";
            list_dir(origen);
            cout << " ===========================================================================================================================================================\n" << endl;
        } else if (origen == "3") {
            origen = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
            list_dir(origen);
            cout << " ===========================================================================================================================================================\n" << endl;
        } 
        else if (origen == "4"){
            return init();
        }
        else {
            cout << "\n\033[1mOpcion no valida.\033[0m\n";
            return;
        }

        cout << "\n\033[1mIngrese el nombre del archivo a comprimir: \033[0m";
        getline(cin, archivo);
        cout << " ===========================================================================================================================================================\n" << endl;
        archivo = agregar_extension(archivo, extensiones); // Agregar la extension.

        string ruta_origen = origen + "/" + archivo;
        if (!fs::exists(ruta_origen)) {
            cout << "\n\033[1mEl archivo especificado no existe.\033[0m\n";
            cout << " ===========================================================================================================================================================\n" << endl;
            return;
        }

        // Modificacion aquí para asegurar que solo se agregue .7z 
        size_t pos = archivo.find_last_of('.');
        string nombre_sin_extension = archivo.substr(0, pos);
        string archivo_comprimido = nombre_sin_extension + ".7z";

        string comando = "7z a \"" + archivo_comprimido + "\" \"" + ruta_origen + "\"";
        int resultado = system(comando.c_str());

        if (resultado == 0) {
            cout << "\n\033[1;32mArchivo comprimido correctamente.\033[0m\n";
            cout << " ===========================================================================================================================================================\n" << endl;
        } else {
            cout << "\n\033[1;31mError al comprimir el archivo.\033[0m\n";
            cout << " ===========================================================================================================================================================\n" << endl;
        }} else if (opcion == "2") {
        cout << "\n\033[1mSeleccione el directorio del archivo comprimido:\033[0m\n";
        cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
        cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
        cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
        cout << "[4] \033[1;31mVolver\033[0m\n"<<endl;
        cout << "\033[1mOpcion: \033[0m";
        getline(cin, origen);
        cout << " ===========================================================================================================================================================\n" << endl;
        if (origen == "1") {
            origen = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
            list_dir(origen);
            cout << " ===========================================================================================================================================================\n" << endl;
        } else if (origen == "2") {
            origen = "C:/Users/jasso/Desktop/VS_CODE";
            list_dir(origen);
            cout << " ===========================================================================================================================================================\n" << endl;
        } else if (origen == "3") {
            origen = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
            list_dir(origen);
            cout << " ===========================================================================================================================================================\n" << endl;
        } 
         else if (origen == "4"){
            return init();
        }
        else {
            cout << "\n\033[1mOpcion no valida.\033[0m\n";
            return;
        }

        cout << "\n\033[1mIngrese el nombre del archivo comprimido: \033[0m";
        getline(cin, archivo);
        archivo = agregar_extension(archivo, extensiones); // Agregar la extension.

        cout << "\n\033[1mSeleccione el directorio de destino:\033[0m\n";
        cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
        cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
        cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
        cout << "[4] \033[34mBuscar otro archivo\033[0m\n"<<endl;
        cout << "\033[1mOpcion: \033[0m";
        getline(cin, destino);
        cout << " ===========================================================================================================================================================\n" << endl;
        if (destino == "1") {
            destino = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
        } else if (destino == "2") {
            destino = "C:/Users/jasso/Desktop/VS_CODE";
        } else if (destino == "3") {
            destino = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
        } 
         else if (destino == "4"){
            return Comprimir_Descomprimir();
        }
        else {
            cout << "\n\033[1mOpcion no valida.\033[0m\n";
            return;
        }

        string ruta_origen = origen + "/" + archivo;
        string ruta_destino = destino;

        if (!fs::exists(ruta_origen)) {
            cout << "\n\033[1mEl archivo comprimido especificado no existe.\033[0m\n";
            cout << " ===========================================================================================================================================================\n" << endl;
            return;
        }

        string comando = "7z x \"" + ruta_origen + "\" -o\"" + ruta_destino + "\"";
        int resultado = system(comando.c_str());

        if (resultado == 0) {
            cout << "\n\033[1mArchivo descomprimido correctamente.\033[0m\n";
            cout << " ===========================================================================================================================================================\n" << endl;
        } else {
            cout << "\n\033[1mError al descomprimir el archivo.\033[0m\n";
            cout << " ===========================================================================================================================================================\n" << endl;
        }
    }
     else if (origen == "0"){
            return init();
        }
     else {
        cout << "\n\033[1mOpcion no valida.\033[0m\n";
    }
}

// Funcion para buscar archivos por nombre en un directorio
void buscar_archivo_por_nombre() {
    string directorio;
    string nombre_archivo;
    string opcion;

    cout << "\n\033[1mSeleccione el directorio donde desea buscar el archivo:\033[0m\n";
    cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
    cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
    cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
    cout << "[4] \033[1;31mVolver\033[0m\n"<<endl;
    cout << "\033[1mOpcion: \033[0m";
    getline(cin, opcion);
    cout << " ===========================================================================================================================================================\n" << endl;

    if (opcion == "1") {
        directorio = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
        list_dir(directorio);
        cout << " ===========================================================================================================================================================\n" << endl;
    } else if (opcion == "2") {
        directorio = "C:/Users/jasso/Desktop/VS_CODE";
        list_dir(directorio);
        cout << " ===========================================================================================================================================================\n" << endl;
    } else if (opcion == "3") {
        directorio = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
        list_dir(directorio);
        cout << " ===========================================================================================================================================================\n" << endl;
    } 
     else if (opcion == "4"){
            return init();
        }
    else {
        cout << "\n\033[1mOpcion no valida.\033[0m\n";
        return;
    }

    cout << "\n\033[1mIngrese el nombre del archivo a buscar: \033[0m";
    getline(cin, nombre_archivo);

    bool encontrado = false;

    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file() && entry.path().filename() == nombre_archivo) {
            cout << "\n\033[1;32mArchivo encontrado: \033[0m" << entry.path() << endl;
            cout << " ===========================================================================================================================================================\n" << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "\n\033[1;31mNo se encontro ningun archivo con el nombre especificado en el directorio.\033[0m\n";
        cout << " ===========================================================================================================================================================\n" << endl;
    }
}

// Funcion para ordenar archivos
void ordenararchivos() {
    // Ruta de la carpeta que deseas organizar
    string folderPath = current_dir;
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

