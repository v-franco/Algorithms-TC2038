//Victor Hugo Franco Juárez
//07 septiembre 2021
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//Clase DivideAndConquer contiene métodos de ordenamiento y búsqueda binaria utilizando vectores
class DivideAndConquer{
private:

    //Método binarySearch realiza busqueda binaria de forma recursiva para vectores ordenados de forma descendente
    //Recibe vector para buscar, límite superior, límite inferior, y número a buscar
    //Regresa el índice donde se encuentra el valor, o -1 en caso de que no se encuentre
    //Complejidad en el peor de los casos: O(log(n))
    int binarySearch( vector<int>arr, int h, int l, int n){
        if (l <= h){
            int m = floor((l+h) / 2);
            if (arr[m] == n){
                return m;
            }
            if (arr[m] < n){
                return binarySearch(arr, m-1, l, n);
            }
            else{
                return binarySearch(arr, h, m+1, n);
            }   
        }
        else{
            return -1;
        }
    }

    //Método merge junta ambas partes del vector en orden descendente
    //Recibe vector, limite inferior (l),  limite superior (h) y valor medio
    //No regresa ningún parametro
    void merge(vector<int>& arr, int l, int h, int m){
        int i = l;
        int j = m + 1;
        vector<int> tempArr;
        while (i <= m && j <= h){
            if (arr[i] >= arr[j]){
                tempArr.push_back(arr[i]);
                i++;
            }
            else {
                tempArr.push_back(arr[j]);
                j++;
            }
        }
        for (i; i <= m; i++){
            tempArr.push_back(arr[i]);
        }
        for (j; j <= h; j++){
            tempArr.push_back(arr[j]);
        }
        for (int i = l; i <= h; i++){
            arr[i] = tempArr[i-l];
        }
    }

    //Método mergeS divide el vector, y utiliza merge() para juntarlo ordenado
    //Recibe el vector a ordenar, límite inferior (l), límite superior (h)
    //No regresa ningún parametro
    //Complejidad computacional en el peor caso: O(nlog(n))
    void mergeS(vector<int>& arr, int l, int h){
        if (l < h){
            int m = floor((l+h) / 2);
            mergeS(arr, l, m);
            mergeS(arr, m + 1, h);
            merge(arr, l, h, m);
        }
    }

public:
    int n;
    int m;
    vector<int> arr;
    vector<int> arrToFind;

    //Método receiveNM recibe la longitud del vector (arr) y la cantidad de números a buscar (longitud de arrToFind)
    //No regresa ningún parametro
    void receiveNM(){
        cin >> n >> m;
    }

    //Método receiveToSort obtiene los números a ordenar (insertados desde consola) , y los inserta en el vector 'arr'
    //El método no recibe ningún parametro
    //No regresa ningun parametro
    void receiveToSort(){
        int input;
        for (int i = 0; i < n; i++){
            cin >> input;
            arr.push_back(input);
        }
    }

    //Método helper para realizar mergeSort
    //No recibe ningún parametro
    //No regresa ningún parametro
    //Manda a mergeS el vector, limite inferior 0, y limite superior el tamaño del vector - 1
    void mergeSort(){
        mergeS(arr, 0, arr.size()-1);
    }

    //Método receiveToFind obtiene los números a buscar (insertados desde consola) y los inserta en el vector 'arrToFind'
    //El método no recibe ningún parametro
    //No regresa ningún parametro
    void receiveToFind(){
        int input;
        for (int i = 0; i < m; i++){
            cin >> input;
            arrToFind.push_back(input);
        }
    }

    //Método printArr imprime el vector 'arr'
    //No recibe ningún parametro
    //No regresa ningún parametro
    void printArr(){
        for (int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    //Método searchArr busca los valores del vector 'arrToFind' en el vector 'arr' que ya fue ordenado con mergesort
    //No recibe ningún parametro
    //No regresa ningún parametro
    void searchArr(){
        for (int i = 0; i < arrToFind.size(); i++){
            int index = binarySearch(arr, arr.size(), 0, arrToFind[i]);
            cout << arrToFind[i] << " " << index << "\n";
        }
    }
};

int main(){
    DivideAndConquer DaC;
    //Recibe valores N y M para ambos vectores
    DaC.receiveNM();
    //Recibe los valores a ordenar 
    DaC.receiveToSort();
    //Recibe los valores a buscar
    DaC.receiveToFind();
    //Ordena el vector 'arr' con merge sort
    DaC.mergeSort();
    //Imprime el vector ordenado
    DaC.printArr();
    //Busca los valores indicados y los imprime
    DaC.searchArr();
}