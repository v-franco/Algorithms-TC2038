//Programa en C++ de implementación del algoritmo de Dijkstra con matriz de adyacencia
//A01366475 Victor Hugo Franco Juarez
//03 Noviembre 2021
#include <iostream>

using namespace std;

//Clase Dijkstra contiene metodos para encontrar la ruta mas corta de todo nodo i a todo nodo j en un grafo dirigido
class Dijkstra{
public:
    int n = 0;

    //Metodo receiveN recibe de la consola el tamaño de la matriz de adyacencia del grafo
    //No recibe ni retorna ningún parametro
    void receiveN(){
        cin >> n;
    }

    /*
     * Metodo DIjkstra encuentra el camino mas corto de todo nodo i a todo nodo j en un grafo dirigido
     * Recibe la matriz de adyacencia del grafo de tamaño n de la consola
     * Realiza un ciclo para encontrar todos los caminos (todos los nodos)
     * Utiliza el algoritmo de Dijkstra (greedy) para encontrar todos los caminos
     * Imprime las distancias mas cortas de todo nodo i a todo nodo j cuya distancia no sea 0, ya que esta representaria que se esta visitando a si mismo
     * No recibe ni retorna ningún parametro
     * Complejidad computacional en el peor de los casos: O(n^2)
     * La complejidad computacional se podría reducir a O(mlog(n)) si el grafo es recibido como lista de adyacencia y se usa un min heap
       Sin embargo, el input de esta actividad se da como matriz de adyacencia, y la complejidad computacional de transformar el grafo
       de matriz a lista, es de O(n^2), perdiendo la "ganancia" que se tiene con una lista de adyacencia, por lo que se decidio
       mantener la estructura original del input, y realizar el algoritmo de la forma no-optima.
     */
    void dijkstra(){
        //Crea la matriz de adyacencia del grafo de tamaño n
        int adjMatrix[n][n];
        //Llena la matriz con el input de la consola
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                cin >> adjMatrix[i][j];
                //Sí se ingresa un -1, se reemplaza por 0 para que funcione el algoritmo (no hay ruta entre esos nodos)
                if (adjMatrix[i][j] == -1){
                    adjMatrix[i][j] = 0;
                }
            }
        }
        //Ciclo para encontrar las distancias de todo nodo i a todo nodo j
        for (int curNode = 0; curNode < n; curNode++){
            int min = INT_MAX; //distancia posible inicial se inicializa como infinito porque no se conoce
            int node = 0; //Siguiente nodo
            int distance[n]; //Arreglo de tamaño n que guarda las distancias del nodo i hacia el resto
            bool visited[n]; //Arreglo booleano de tamaño n que registra nodos ya visitados
            //Ciclo para declarar inicialmente las distancias como infinito, y los visitados como Falso
            for (int i = 0; i < n; i++){
                distance[i] = INT_MAX;
                visited[i] = false;
            }
            //La distancia al nodo raiz actual es 0
            distance[curNode] = 0;
            //Ciclo para encontrar la distancia minima comparando caminos de nodos no visitados
            for (int i = 0; i < n; i++){
                //Para cada iteración, se reasigna una distancia minima inicial como infinito
                //Y un valor del siguiente vertice no visitado como 0
                min = INT_MAX;
                node = 0;
                for(int j = 0; j < n; j++){
                    //Sí el nodo no ha sido visitado y es menor que el minimo, se guarda la distancia mas pequeña
                    if(visited[j] == false && distance[j] <= min){
                        //Se actualiza la distancia minima 
                        min = distance[j];
                        //Se actualiza el nodo
                        node = j;
                    }
                }
                //Se marca el nodo elegido como visitado
                visited[node] = true;
                //Ciclo para actualizar el valor de la distancia menor
                for (int i = 0; i < n; i++){
                    //Si el nodo no ha sido visitado, si tiene arista al siguiente nodo j, y el peso total del nodo inicial i al nodo j es menor que la distancia actual,
                    //se actualiza la distancia
                    if (!visited[i] && adjMatrix[node][i] && distance[node] != INT_MAX && distance[i] > distance[node] + adjMatrix[node][i]){
                        distance[i] = distance[node] + adjMatrix[node][i];
                    }
                }
            }
            //Ciclo para imprimir las distancias minimas de todo nodo i a los nodos j
            for(int i = 0; i<n; i++){
                //Si la distancia no es 0, se imprime 
		        if(distance[i] != 0){ 
        	        cout<< "Node " << curNode + 1<< " to node " << i + 1 << ": " <<distance[i]<<"\n";
		        }
            }  
        }
    }
};  

int main(){
    Dijkstra djk;
    //Recibe el tamaño de la matriz
    djk.receiveN();
    //Recibe matriz de adyacencia del grafo y realiza algoritmo de Dijkstra para encontrar las distancias minimas
    djk.dijkstra();
}