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
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include <string.h>

#include <string.h>
#include <string>


#define Nb 4 
#define KeySize  240
#pragma warning(disable: 4996)
namespace fs = std::filesystem;
using namespace std;

//Variables 
//======================================================================================================
//											COMMON VARIABLES
//======================================================================================================
int Nr = 0;
int Nk = 0;

string str_in;
char* tempt, * a, * b;
char* source, * dest;
unsigned char Key[32] =
{ 'a', 'b', 'c', 'd',
'e', 'f', 'g', 'h',
'i', 'j', 'k', 'l',
'm', 'n', 'o', 'p',
'a', 'b', 'c', 'd',
'e', 'f', 'g', 'h',
'i', 'j', 'k', 'l',
'm', 'n', 'o', 'p' };

unsigned char RoundKey[240];
int Isbox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	/*1*/  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	/*2*/  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	/*3*/  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	/*4*/  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	/*5*/  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	/*6*/  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	/*7*/  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	/*8*/  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	/*9*/  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	/*a*/  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	/*b*/  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	/*c*/  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	/*d*/  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	/*e*/  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	/*f*/  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
int Sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
int Rcon[255] = {
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb };


//======================================================================================================
//											CPU VARIABLES
//======================================================================================================
unsigned char State_CPU[4][4];
FILE* in_file_CPU, * input_file_CPU, * output_file_CPU;
LARGE_INTEGER start_CPU, end_CPU, frequency_CPU;
double processingTimeCPU;

//variables
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
void Encriptar_Desencriptar();

// Funciones CPU
char* CreatText(char type[]);
int getSBoxValue(int num);
int get_ISBoxValue(int num);
unsigned char gf_mult(unsigned char a, unsigned char b);
void KeyExpansion();
void AddRoundKey(int round);
void SubBytes();
void Inv_SubBytes();
void ShiftRows();
void Inv_ShiftRows();
int gfmultby01(int b);
int gfmultby02(int b);
int gfmultby03(int b);
int gfmultby09(int b);
int gfmultby0b(int b);
int gfmultby0d(int b);
int gfmultby0e(int b);
void MixColumns();
void InvMixCoLumns();
void Cipher();
void Inv_Cipher();


int main(int argc, char* argv[]){
    init();
    return 0;
}

// Funcion Inicial
void init() {
    string opcion;

    while (true) {
        
cout << "================================================================ \033[1m\033[34mGESTOR DE ARCHIVOS\033[0m ========================================================================\n"<<endl;
       
        cout << " ----------------------------------------------------------- Seleccione la accion a realizar ---------------------------------------------------------------" << endl;
        cout << "[q] \033[1;31mSalir\033[0m\n[0] \033[1;31mLimpiar pantalla\033[0m\n";
        
        cout << "                         [1] Ejecutar un programa                      [4] Buscar archivo por nombre                                               \n";    
        cout << "                         [2] Comprimir o descomprimir                  [5] Ordenar archivos                                                        \n";
        cout << "                         [3] Copiar un archivo                         [6] Encriptar o desencriptar un archivo                                     \n";
        cout << " ===========================================================================================================================================================" << endl;
        cout << "Opcion: ";
        getline(cin, opcion); // Cambio en la forma de leer la entrada del usuario
        cout << " \n===========================================================================================================================================================\n" << endl;  
        
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
                    buscar_archivo_por_nombre();
                    break;
                case 5:
                    ordenararchivos();
                    break;
                
                case 6: 
                    Encriptar_Desencriptar();
                    break;
                    
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
    cout << "[1] \033[34mAbrir PSeInt\033[0m\n[2] \033[34mAbrir VS code\033[0m\n[3] \033[1;31mVolver\033[0m\n";
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

    cout << "[0] \033[1:31mVolver\033[0m\n"<<endl;
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

// Función para ordenar archivos
void ordenararchivos() {
    string folderPath;
    string opcion;

    // Seleccionar la carpeta a ordenar
    cout << "\n\033[1mSeleccione la carpeta a ordenar:\033[0m\n";
    cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
    cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
    cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
    cout << "\033[1mOpcion: \033[0m";
    getline(cin, opcion);
    cout << " ===========================================================================================================================================================\n" << endl;

    if (opcion == "1") {
        folderPath = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
    } else if (opcion == "2") {
        folderPath = "C:/Users/jasso/Desktop/VS_CODE";
    } else if (opcion == "3") {
        folderPath = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
    } else {
        cout << "\n\033[1mOpcion no valida.\033[0m\n";
        return;
    }

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

    // Crear una nueva carpeta en el escritorio para los archivos ordenados
    string newFolderPath = "C:/Users/jasso/Desktop/Archivos_Ordenados";
    fs::create_directory(newFolderPath);

    // Crear subcarpetas por letra inicial y copiar los archivos
    for (char c = 'A'; c <= 'Z'; c++) {
        string subFolderPath = newFolderPath + "/" + string(1, c);
        fs::create_directory(subFolderPath);

        for (const auto& fileName : fileNames) {
            if (toupper(fileName[0]) == c) {
                string srcPath = folderPath + "/" + fileName;
                string dstPath = subFolderPath + "/" + fileName;
                fs::copy(srcPath, dstPath, fs::copy_options::overwrite_existing);
            }
        }
    }

    cout << "\n\033[1;32mArchivos ordenados y copiados a la carpeta 'Archivos_Ordenados' en el escritorio.\033[0m\n";
    cout << "\033[1mLos archivos ordenados se han separado en subcarpetas por letra inicial:\033[0m\n";

    for (char c = 'A'; c <= 'Z'; c++) {
        string subFolderPath = newFolderPath + "/" + string(1, c);
        if (fs::is_directory(subFolderPath)) {
            cout << "\n\033[1m" << string(1, c) << ":\033[0m\n";
            for (const auto& entry : fs::directory_iterator(subFolderPath)) {
                cout << entry.path().filename() << endl;
            }
        }
    }

    cout << "\n ===========================================================================================================================================================\n" << endl;
}



//Funcion para encriptar y desencriptar un archivo
void Encriptar_Desencriptar() {
    cout << "\033[1m\033[34m                       Encriptación con AES-CPU                           \033[0m" << endl;

    int element = 0;
    string inputFile, outputFile;
    int codeOrder;
    string origen, destino, nombreArchivo;

    // Seleccionar el archivo de entrada
    cout << "\n\033[1mSeleccione el directorio de origen:\033[0m\n";
    cout << "[1] \033[34mC:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo\033[0m\n"<<endl;
    cout << "[2] \033[34mC:/Users/jasso/Desktop/VS_CODE\033[0m\n"<<endl;
    cout << "[3] \033[34mC:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal\033[0m\n"<<endl;
    cout << "[4] \033[1;31mVolver\033[0m\n"<<endl;
    cout << "\033[1mOpción: \033[0m";
    getline(cin, origen);
    cout << " ===========================================================================================================================================================\n" << endl;

    if (origen == "1") {
        origen = "C:/Users/jasso/Desktop/VS_CODE/Manejo_de_archivos_en_grupo";
        list_dir(origen);
    } else if (origen == "2") {
        origen = "C:/Users/jasso/Desktop/VS_CODE";
        list_dir(origen);
    } else if (origen == "3") {
        origen = "C:/Users/jasso/Desktop/VS_CODE/progra_tarea_grupal";
        list_dir(origen);
    } 
    else if (origen == "4"){
        return init();
    }
    else {
        cout << "\n\033[1mOpción no válida.\033[0m\n";
        return;
    }

    cout << " ===========================================================================================================================================================" << endl;
    cout << "\n\033[1mIngrese el nombre del archivo de entrada: \033[0m";
    getline(cin, nombreArchivo);
    inputFile = origen + "/" + nombreArchivo;

    // Seleccionar la opción de encriptación o desencriptación
    cout << "\n\033[1mSeleccione una opcion:\033[0m\n"<<endl;

    cout << "[1] Encriptar   [2] Desencriptar  [3] Volver  \n";

    while (true) {
        cout << "Opcion:";
        cin >> codeOrder;
        cin.ignore(); // Limpiar el buffer después de leer el entero
        if (codeOrder == 1 || codeOrder == 2 || codeOrder == 3)
            break;
        cout << "\n\033[1;31mOpcion no valida. Intente de nuevo.\033[0m\n";
    }

    // Generar el nombre del archivo de salida
    if (codeOrder == 1) {
        size_t pos = nombreArchivo.find_last_of('.');
        string nombreSinExtension = nombreArchivo.substr(0, pos);
        outputFile = nombreSinExtension + "_INVERT" + nombreArchivo.substr(pos);
        cout << "\n\033[1mEl archivo de salida es: \033[32m" << outputFile << "\033[0m\n";
    } else if (codeOrder == 2) {
        size_t pos = nombreArchivo.find_last_of('.');
        string nombreSinExtension = nombreArchivo.substr(0, pos);
        outputFile = nombreSinExtension + "_INVERT" + nombreArchivo.substr(pos);
        cout << "\n\033[1mEl archivo de salida es: \033[32m" << outputFile << "\033[0m\n";
    } else if (codeOrder == 3){
        return init();
    }

    char* sourceFile = (char*)malloc(inputFile.length() * sizeof(char));
    for (int i = 0; i < inputFile.length() + 1; i++)
        sourceFile[i] = inputFile[i];

    int count = 0;
    bool lack = false;
    Nr = 256;
    Nk = Nr / 32;
    Nr = Nk + 6;

    cout << "\n\n\033[1m---------------------------- INICIO ----------------------------\033[0m\n";

    in_file_CPU = fopen(sourceFile, "rb");
    input_file_CPU = fopen(sourceFile, "rb");
    output_file_CPU = fopen(outputFile.c_str(), "wb");

    while (true) {
        int ch = fgetc(in_file_CPU);
        if (ch == EOF)
            break;
        ++count;
    }

    cout << "\n\033[1mTamaño total: \033[32m" << count / 1000 << " Kb\033[0m\n";

    if (codeOrder == 1)
        cout << "\n\033[1mIniciando encriptación en CPU...\033[0m";
    else if (codeOrder == 2)
        cout << "\n\033[1mIniciando desencriptación en CPU...\033[0m";

    ::QueryPerformanceFrequency(&frequency_CPU);
    QueryPerformanceCounter(&start_CPU);

    KeyExpansion();

    while (element < count) {
        int countInner = 0;
        unsigned char c;
        for (countInner = 0; countInner < 16; countInner++) {
            element++;
            if (codeOrder == 1)
                if (element == (count + 1)) {
                    State_CPU[countInner % 4][countInner / 4] = 170;
                    for (int i = countInner + 1; i < 16; i++)
                        State_CPU[i % 4][i / 4] = 0;
                    goto cycle;
                }
            if (codeOrder == 2)
                if (element == count)
                    lack = true;
            c = fgetc(input_file_CPU);
            State_CPU[countInner % 4][countInner / 4] = c;
        }

    cycle:
        if (codeOrder == 1)
            Cipher();
        if (codeOrder == 2)
            Inv_Cipher();

        int dele = 16;
        if (codeOrder == 2)
            for (int i = 0; i < dele; i++) {
                unsigned char x = State_CPU[i % 4][i / 4];
                if ((State_CPU[i % 4][i / 4] == 170) && (lack))
                    break;
                fputc(x, output_file_CPU);
            }
        if (codeOrder == 1)
            for (int i = 0; i < dele; i++) {
                unsigned char x = State_CPU[i % 4][i / 4];
                fputc(x, output_file_CPU);
            }
    }

    cout << "\n\n\033[1;32mCompleto!\033[0m";
    ::QueryPerformanceCounter(&end_CPU);
    processingTimeCPU = (double)(end_CPU.QuadPart - start_CPU.QuadPart) / frequency_CPU.QuadPart;

    printf("\n\n\033[1mTiempo total de encriptación en CPU: \033[32m%.3f (s)\033[0m\n\n\n", processingTimeCPU);

    for (int i = 0; i < 240; i++)
        RoundKey[i] = 0;

    fclose(output_file_CPU);
    fclose(input_file_CPU);
    fclose(in_file_CPU);

    double speedCPU = count / processingTimeCPU / 1000000;
    printf("\n\n\n\033[1mVelocidad de CPU: \033[32m%.3f Mb/s \033[0m", speedCPU);

    cout << "\n\n\033[1m----------------------------- FIN -----------------------------\033[0m\n";

    return init();
    getchar();
	getchar ();
    
}

//======================================================================================================
//										     CPU METHODS
//======================================================================================================
char* CreatText (char type[]) {
	int length = str_in.length ();
	char* tempt = (char*)malloc (length * sizeof (char));
	char* a = (char*)malloc (length * sizeof (char));
	char* b = (char*)malloc (length * sizeof (char));

	for (int i = 0; i < length + 1; i++)
		tempt[i] = str_in[i];


	for (int i = 0; i < strlen (tempt); i++) {
		if (tempt[i] == '.') {
			a[i] = '\0'; break;
		}
		a[i] = tempt[i];
	}

	for (int i = strlen (a); i < strlen (tempt) + 1; i++)
		b[i - strlen (a)] = tempt[i];

	char* str_ou = (char*)malloc ((length + strlen (type)) * sizeof (char));
	for (int i = 0; i < strlen (a); i++)
		str_ou[i] = a[i];
	for (int i = strlen (a); i < strlen (a) + strlen (type) + 1; i++)
		str_ou[i] = type[i - strlen (a)];

	for (int i = strlen (a) + strlen (type); i < strlen (a) + strlen (type) + strlen (b) + 1; i++)
		str_ou[i] = b[i - strlen (a) - strlen (type)];

	return str_ou;
}

int getSBoxValue (int num) {
	return Sbox[num];
}

int get_ISBoxValue (int num) {
	return Isbox[num];
}

unsigned char gf_mult (unsigned char a, unsigned char b) {
	int i;
	int retval;

	retval = a * b;
	if (retval < 128)
		return retval;
	else
		retval = 0;

	for (i = 0; i < 8; i++) {
		if ((b & 1) == 1)
			retval ^= a;

		if ((a & 0x80) == 0x80) {
			a <<= 1;
			a ^= 0x1b;
		} else {
			a <<= 1;
		}

		b >>= 1;
	}

	return (unsigned char)retval;
}

void KeyExpansion () {
	int i, j;
	unsigned char temp[4], k;


	for (i = 0; i < Nk; i++) {
		RoundKey[i * 4] = Key[i * 4];
		RoundKey[i * 4 + 1] = Key[i * 4 + 1];
		RoundKey[i * 4 + 2] = Key[i * 4 + 2];
		RoundKey[i * 4 + 3] = Key[i * 4 + 3];
	}


	while (i < (Nb * (Nr + 1))) {
		for (j = 0; j < 4; j++)   // chép 4 word trước đó lại 
		{// i = 8 
			temp[j] = RoundKey[(i - 1) * 4 + j];   // 28 29 30 31
		}
		if (i % Nk == 0)  // các w số 8  16  24 ... 
		{
			//  RotWord()
			{
				k = temp[0];
				temp[0] = temp[1];
				temp[1] = temp[2];
				temp[2] = temp[3];
				temp[3] = k;
			}

			//  Subword()
			{
				temp[0] = getSBoxValue (temp[0]);
				temp[1] = getSBoxValue (temp[1]);
				temp[2] = getSBoxValue (temp[2]);
				temp[3] = getSBoxValue (temp[3]);
			}
			// Xor RCON
			temp[0] = temp[0] ^ Rcon[i / Nk];
		} else if (Nk > 6 && i % Nk == 4) //  Nk = 8  i = 12  20  28   36   44   52  60  
		{
			//  Subword()
			{
				temp[0] = getSBoxValue (temp[0]);
				temp[1] = getSBoxValue (temp[1]);
				temp[2] = getSBoxValue (temp[2]);
				temp[3] = getSBoxValue (temp[3]);
			}
		}
		RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ temp[0];
		RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ temp[1];
		RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ temp[2];
		RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ temp[3];
		i++;
	}
}

void AddRoundKey (int round) {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			State_CPU[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];

}

void SubBytes () {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			State_CPU[i][j] = getSBoxValue (State_CPU[i][j]);

		}
	}
}

void Inv_SubBytes () {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			State_CPU[i][j] = get_ISBoxValue (State_CPU[i][j]);

		}
	}
}

void ShiftRows () {
	unsigned char temp;

	temp = State_CPU[1][0];
	State_CPU[1][0] = State_CPU[1][1];
	State_CPU[1][1] = State_CPU[1][2];
	State_CPU[1][2] = State_CPU[1][3];
	State_CPU[1][3] = temp;

	temp = State_CPU[2][0];
	State_CPU[2][0] = State_CPU[2][2];
	State_CPU[2][2] = temp;

	temp = State_CPU[2][1];
	State_CPU[2][1] = State_CPU[2][3];
	State_CPU[2][3] = temp;

	temp = State_CPU[3][0];
	State_CPU[3][0] = State_CPU[3][3];
	State_CPU[3][3] = State_CPU[3][2];
	State_CPU[3][2] = State_CPU[3][1];
	State_CPU[3][1] = temp;
}

void Inv_ShiftRows () {
	unsigned char temp;

	temp = State_CPU[1][3];
	State_CPU[1][3] = State_CPU[1][2];
	State_CPU[1][2] = State_CPU[1][1];
	State_CPU[1][1] = State_CPU[1][0];
	State_CPU[1][0] = temp;

	temp = State_CPU[2][2];
	State_CPU[2][2] = State_CPU[2][0];
	State_CPU[2][0] = temp;

	temp = State_CPU[2][3];
	State_CPU[2][3] = State_CPU[2][1];
	State_CPU[2][1] = temp;

	temp = State_CPU[3][1];
	State_CPU[3][1] = State_CPU[3][2];
	State_CPU[3][2] = State_CPU[3][3];
	State_CPU[3][3] = State_CPU[3][0];
	State_CPU[3][0] = temp;
}

int gfmultby01 (int b) {
	return (b % 256);
}

int gfmultby02 (int b) {
	if (b < 0x80) // nếu b7 =0
		return ((b << 1) % 256);
	else // nếu b7 =1
		return (((b << 1) % 256 ^ (int)(0x1b))); // 0x1b = 00011011 ; b7b6b5b4b3b2b1b0 << 1 = b6b5b4b3b2b1b00 (dịch bít trái)
}

int gfmultby03 (int b) {
	return ((gfmultby02 (b) ^ b) % 256);
}

int gfmultby09 (int b) {
	return ((gfmultby02 (gfmultby02 (gfmultby02 (b))) ^ b) % 256);
}

int gfmultby0b (int b) {
	return ((gfmultby02 (gfmultby02 (gfmultby02 (b))) ^ gfmultby02 (b) ^ b) % 256);
}

int gfmultby0d (int b) {
	return ((gfmultby02 (gfmultby02 (gfmultby02 (b))) ^ gfmultby02 (gfmultby02 (b)) ^ b) % 256);
}

int gfmultby0e (int b) {
	return ((gfmultby02 (gfmultby02 (gfmultby02 (b))) ^ gfmultby02 (gfmultby02 (b)) ^ gfmultby02 (b)) % 256);
}

void MixColumns () {
	int temp[4][4];
	for (int r = 0; r < 4; ++r)  // copy State_CPU into temp[]
	{
		for (int c = 0; c < 4; ++c) {
			temp[r][c] = State_CPU[r][c];
		}
	}

	for (int c = 0; c < 4; ++c) {
		State_CPU[0][c] = ((int)gfmultby02 (temp[0][c]) ^ (int)gfmultby03 (temp[1][c]) ^
			(int)gfmultby01 (temp[2][c]) ^ (int)gfmultby01 (temp[3][c]));
		State_CPU[1][c] = ((int)gfmultby01 (temp[0][c]) ^ (int)gfmultby02 (temp[1][c]) ^
			(int)gfmultby03 (temp[2][c]) ^ (int)gfmultby01 (temp[3][c]));
		State_CPU[2][c] = ((int)gfmultby01 (temp[0][c]) ^ (int)gfmultby01 (temp[1][c]) ^
			(int)gfmultby02 (temp[2][c]) ^ (int)gfmultby03 (temp[3][c]));
		State_CPU[3][c] = ((int)gfmultby03 (temp[0][c]) ^ (int)gfmultby01 (temp[1][c]) ^
			(int)gfmultby01 (temp[2][c]) ^ (int)gfmultby02 (temp[3][c]));
	}
}  // MixColumns

void InvMixCoLumns () {
	int temp[4][4];
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			temp[r][c] = State_CPU[r][c];

	for (int c = 0; c < 4; ++c) {
		State_CPU[0][c] = (gfmultby0e (temp[0][c]) ^ gfmultby0b (temp[1][c]) ^
			gfmultby0d (temp[2][c]) ^ gfmultby09 (temp[3][c]));
		State_CPU[1][c] = (gfmultby09 (temp[0][c]) ^ gfmultby0e (temp[1][c]) ^
			gfmultby0b (temp[2][c]) ^ gfmultby0d (temp[3][c]));
		State_CPU[2][c] = (gfmultby0d (temp[0][c]) ^ gfmultby09 (temp[1][c]) ^
			gfmultby0e (temp[2][c]) ^ gfmultby0b (temp[3][c]));
		State_CPU[3][c] = (gfmultby0b (temp[0][c]) ^ gfmultby0d (temp[1][c]) ^
			gfmultby09 (temp[2][c]) ^ gfmultby0e (temp[3][c]));
	}
}

void Cipher () {
	int i, j, round = 0;

	AddRoundKey (0);

	for (round = 1; round < Nr; round++) {
		SubBytes ();
		ShiftRows ();
		MixColumns ();
		AddRoundKey (round);
	}

	SubBytes ();
	ShiftRows ();
	AddRoundKey (Nr);
}

void Inv_Cipher () {
	int i, j, round = 0;

	AddRoundKey (Nr);

	for (round = Nr - 1; round > 0; round--) {
		Inv_ShiftRows ();
		Inv_SubBytes ();
		AddRoundKey (round);
		InvMixCoLumns ();

	}

	Inv_ShiftRows ();
	Inv_SubBytes ();
	AddRoundKey (0);

}
