//Programa en C++ que resuelve el knapsack problem con programacion dinamica
//A01366475 Victor Hugo Franco Juarez
//20 Octubre 2021

#include <iostream>
#include <vector>

using namespace std;

//Clase KnapsackProblem contiene métodos para resolver el "knapsack problem" utilizando programacion dinamica
class KnapsackProblem{

public:
    int n = 0;
    int W = 0;
    vector<int> v;
    vector<int> w;

    //Metodo knapsack encuentra la ganancia o beneficio optimo de elementos para llevar en la mochila
    //No recibe ningun parametro, ya que estos se encuentran definidos de forma publica en la clase
    //Utiliza el no. de elementos = n, el peso max. de la mochila = W, y los valores y pesos de cada elemento (vectores v y w)
    //Utiliza programacion dinamica para determinar la ganancia optima
    //Complejidad computacional en el peor de los casos: O(n*W), donde n = no. de elementos, y W = peso de la mochila
    void knapsack(){
        //Inicializa una matriz con la cantidad de elementos + 1 * el peso de la mochila + 1
        int value[n+1][W+1];
        //Llena la matriz de 0s
        for (int i = 0; i <= n; i++){
            value[i][0] = 0;
        }
        for (int j = 0; j <= W; j++){
            value[0][j] = 0;
        }
        //Ciclo de la cantidad de elementos
        for (int i = 1; i <= n; i++){
            //Ciclo de pesos, teniendo como limite el peso max. de la mochila
            for (int j = 0; j <= W; j++){
                //Si el elemento pesa mas que el limite actual, se descarta
                if (w[i-1] > j){
                    value[i][j] = value[i-1][j];
                }
                //Si no pasa del limite de peso, actualiza la matriz con la maxima ganancia si se incluye o no el elemento actual
                else{
                    //Si el valor anterior es maximo, se mantiene
                    if (value[i-1][j] > value[i-1][j-w[i-1]]+v[i-1]){
                        value[i][j] = value[i-1][j];
                    }
                    else{
                        //Si no, se agrega el valor nuevo
                        value[i][j] = value[i-1][j-w[i-1]]+v[i-1];
                    }
                }
            }
        }
        //Imprime el beneficio optimo
        cout << value[n][W] << "\n";
    }

    //Metodo receiveN recibe de la consola el no. de elementos posibles disponibles
    //No recibe ni retorna ningún parametro
    void receiveN(){
        cin >> n;
    }

    //Metodo receiveValues recibe de la consola los valores de los n elementos disponibles
    //Almacena los valores recibidos en un vector v
    //No recibe ni retorna ningún parametro
    void receiveValues(){
        int input;
        for (int i = 0; i < n; i++){
            cin >> input;
            v.push_back(input);
        }
    }

    //Metodo receiveWeights recibe de la consola los pesos de los n elementos disponibles
    //Almacena los pesos recibidos en un vector w
    //No recibe ni retorna ningún parametro
    void receiveWeights(){
        int input;
        for (int i = 0; i < n; i++){
            cin >> input;
            w.push_back(input);
        }
    }

    //Metodo receiveW recibe el peso maximo de la mochila
    //No recibe ni retorna ningún parametro
    void receiveW(){
        cin >> W;
    }
};

int main(){
    KnapsackProblem KsP;
    //Recibe numero de elementos
    KsP.receiveN();
    //Recibe valores de elementos
    KsP.receiveValues();
    //Recibe pesos de elementos
    KsP.receiveWeights();
    //Recibe peso total de la mochila
    KsP.receiveW();
    //Calcula beneficio optimo
    KsP.knapsack();
}
