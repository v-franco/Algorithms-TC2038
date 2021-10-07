//A01366475 Victor Hugo Franco Juárez
//20 septiembre 2021
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//Clase DynamicChange contiene metodo de programacion dinamica para encontrar el minimo numero de monedas del cambio
class DynamicChange{
public:
    //Metodo dpChange encuentra el minimo numero de monedas utilizando programacion dinamica
    //Recibe un vector con las distintas denominaciones disponibles, y el valor de cambio a retornar
    //Utiliza el vector neededCoins para memorization
    //Imprime en la consola los valores de las monedas del cambio, y retorna el no. de monedas del cambio
    //Complejidad computacional en el peor caso: O(n*m) donde n = cantidad y m = no. de denominaciones disponibles
    int dpChange(vector<int>coins, int quantity){
        int tempQuantity = quantity;
        int numCoins = 0;
        vector<int> neededCoins;
        vector<int> whichCoins;
        neededCoins.push_back(0);
        whichCoins.push_back(0);
        for (int m = 1; m <= quantity; m++){
            neededCoins.push_back(INT_MAX);
            whichCoins.push_back(INT_MAX);
            for (int i = 0; i < coins.size(); i++){
                if (m >= coins[i]){
                    numCoins = neededCoins[m-coins[i]]+1;
                    if (numCoins < neededCoins[m]){
                        neededCoins[m] = numCoins;
                        whichCoins[m] = coins[i];
                    }
                }
            }
        }
        while (tempQuantity > 0){
            cout << whichCoins[tempQuantity] << "\n";
            tempQuantity -= whichCoins[tempQuantity];
        }
        return neededCoins[quantity];
    }
};

//Clase GreedyChange contiene metodo con algoritmo avaro para encontrar el minimo numero de monedas del cambio
class GreedyChange{
public:
    //Metodo greedyChange encuentra el minimo numero de monedas utilizando un algoritmo avaro
    //Recibe un vector con las distintas denominaciones disponibles, y el valor de cambio a retornar
    //Necesita las denominaciones de forma ordenada para encontrar el minimo no. de monedas
    //Imprime en la consola los valores de las monedas del cambio, y retorna el no. de monedas del cambio
    //Complejidad computacional en el peor caso: O(n) donde n = cantidad
    int gaChange(vector<int> coins, int quantity){
        vector<int> neededCoins;
        int numCoins = 0;
        for (int i = 0; i < coins.size(); i++){
            while (coins[i] <= quantity){
                quantity -= coins[i];
                neededCoins.push_back(coins[i]);
                numCoins++;
            }
        }
        for (int i = 0; i < numCoins; i++){
            cout << neededCoins[i] << "\n";
        }
        return numCoins;
    }
};

//Clase Coins contiene metodos de ordenamiento mergesort para un vector, metodos que reciben entradas del programa, y metodos helper
//para utilizar los metodos de DynamicChange y GreedyChange
class Coins{
private:
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
    DynamicChange DC;
    GreedyChange GC;
    int n = 0;
    int p = 0;
    int q = 0;
    int value = 0;
    vector<int> coins;

    //Metodo receiveN recibe de la consola n, que es la longitud del vector/cantidad de denominaciones distintas
    //No recibe ni regresa ningun parametro
    void receiveN(){
        cin >> n;
    }

    //Metodo receiveCoins recibe de la consola  las denominaciones de la monedas y las inserta en el vector coins
    //Utiliza el metodo mergeS para ordenar de forma descendente el vector
    //No recibe ni regresa ningun parametro
    void receiveCoins(){
        int input;
        for (int i = 0; i < n; i++){
            cin >> input;
            coins.push_back(input);
        }
        mergeS(coins, 0, coins.size()-1);
    }

    //Metodo receivePriceAndPay recibe de la consola el precio a pagar, y el billete o moneda con la que se paga
    //Calcula el cambio a entregar que sera utilizado por los metodos dpChange y gaChange
    //No recibe ni regresa ningun parametro
    void receivePriceAndPay(){
        cin >> p >> q;
        value = q - p;
    }

    //Metodo helper que utiliza el metodo dpChange para obtener el cambio utilizando programacion dinamica
    //No recibe ni regresa ningun parametro
    void dynamicChange(){
        DC.dpChange(coins, value);
    }

    //Metodo helper que utiliza el metodo gaChange para obtener el cambio utilizando algoritmo avaro
    //No recibe ni regresa ningun parametro
    void greedyChange(){
        GC.gaChange(coins, value);
    }
};

int main(){
    Coins myCoins;
    //Recibe n
    myCoins.receiveN();
    //Recibe las denominaciones de las monedas
    myCoins.receiveCoins();
    //Recibe precio y billete/moneda de pago
    myCoins.receivePriceAndPay();
    //Solucion con programacion dinamica
    cout << "Cambio utilizando programacion dinamica: \n";
    myCoins.dynamicChange();
    //Solucion con algoritmo avaro
    cout << "Cambio utilizando algoritmo avaro: \n";
    myCoins.greedyChange();
}
