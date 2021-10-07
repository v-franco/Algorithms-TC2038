//Programa en C++ que busca un patron dentro de un genoma, utilizando el algoritmo KMP
//A01366475 Victor Hugo Franco Juarez
//05 Octubre 2021

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Clase KMP contiene metodos para encontrar un patron dentro de un string (genoma) utilizando el algoritmo KMP
class KMP{
private:

    //Metodo preprocess realiza preprocesamiento del patron a ser buscado en el texto (genoma)
    //Recibe el patron p y el vector v
    //No regresa ningun parametro
    //Complejidad computacional en el peor caso: O(m) donde m = longitud de patron
    void preprocess(string p, vector<int>& v){
        int m = p.length();
        int j = 0;
        int i = 1;
        v[0] = 0;
        while (i < m){
            if (p[i] == p[j]){
                v[i] = j+1;
                i++;
                j++;
            }
            else{
                if (j == 0){
                    v[i] = 0;
                    i++;
                }
                else{
                    j = v[j-1];
                }
            }
        }
    }

    //Metodo kmp realiza la busqueda de patron en el texto (genoma)
    //Recibe patron p a buscar y texto t donde buscar (genoma)
    //Utiliza el metodo preprocess para preprocesamiento del patron
    //Almacena las posiciones de coincidencia (base 1) en el vector positions, o -1 en caso de que no haya coincidencias
    //Regresa el vector positions
    //Complejidad computacional en el peor de los casos: O(m+n) donde m = longitud de patron y n = longitud de texto (tomando en cuenta el preprocesamiento del patron)
    vector<int> kmp(string p, string t){
        int m = p.length();
        int n = t.length();
        int j = 0;
        int i = 0;
        vector<int> v(m);
        vector<int> positions;
        preprocess(p, v);
        while (i < n){
            if (t[i] == p[j]){
                j++;
                i++;
            }
            if (j == m){
                positions.push_back(i-j+1);
                j = v[j-1];
            }
            else if (i < n && t[i] != p[j]){
                if (j == 0){
                    i++;
                }
                else{
                    j = v[j-1];
                }
            }
        }
        if (positions.size() == 0){
            positions.push_back(-1);
            return positions;
        }
        else{
            return positions;
        }
    }

public:
    int n = 0;
    string file = "";
    string nString = "";
    string t = "";
    string p = "";

    
    //Metodo printPositions imprime en consola las posiciones (base 1) de coincidencia encontrados por el metodo kmp
    //Recibe como parametro vector con posiciones
    //No regresa ningun parametro
    void printPositions(vector<int> positions){
        for (int i = 0; i < positions.size(); i++){
            cout << positions[i] << " ";
        }
    }

    //Metodo receiveFile recibe de la consola el nombre del archivo con extension donde se encuentran los casos de prueba
    //No recibe ni regresa ningun parametro
    void receiveFile(){
        cout << "Ingrese nombre de archivo con extension que contenga casos de prueba:" << "\n";
        cin >> file;
    }

    //Metodo testCases abre el archivo con nombre recibido por receiveFile
    //Lee la primer linea del archivo y la convierte a int para realizar el numero n de casos de prueba
    //Obtiene el patron p y el texto t (genoma) del archivo
    //Utiliza el metodo kmp para encontrar los indices de coincidencia entre el patron y el genoma
    //No recibe ni regresa ningun parametro
    void testCases(){
        vector<int> positions;
        ifstream in(file);
        if (in.is_open()){
            getline(in, nString);
            n = stoi(nString);
            for (int i = 0; i < n; i++){
                getline(in, p);
                getline(in, t);
                positions = kmp(p, t);
                printPositions(positions);
                cout << "\n";
            }
            in.close();
        }
        else{
            cout << "No se puede abrir el archivo: "<< file << "\n";
        }
    }
};

int main(){
    KMP kmp;
    //Recibe nombre de archivo con extension
    kmp.receiveFile();
    //Realiza n casos de prueba establecidos en el archivo
    kmp.testCases();
}
