/*
------------------------------------------------
------------Actividad Integradora II------------
---A01366795 Miguel Angel Santamaria Viclhis----
---- A01366475 Victor Hugo Franco Juárez -------
---------------Noviembre 2021-------------------
------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;

#define INF 10000

//Clase Quaerit contiene metodos para resolver la situacion problema 2
class Quaerit{

//Metodos privados
private: 
    int n; //cantidad de colonias
    int m; //numero de conexiones existentes entre colonias
    int q; //Numero de nuevas colonias que se desean aceptar

    //Vector que almacena nombres de colonias y si son centrales
    vector<pair<string, int>> cityNames;   // [cityName, central]

    //Vector que almacena posiciones en el plano de las colonias
    vector<vector<double>> cityPos;        // [posX, posY]

    //Matriz de adyacencia del grafo proporcionado
    vector<vector<int>> matrix;            // [i][j]

    //Vector que almacena nombres de nuevas colonias
    vector<string> cityNamesNew;           // [cityName]

    //Vector que almacena posiciones en el plano de las colonias nuevas
    vector<vector<double>> cityPosNew;     // [posX, posY]

    //Matrices utilizadas para el algoritmo de FLoyd Warshall
    vector<vector<int>> FWnext; //Matriz que guarda siguiente colonia

    //Vectores utilizados en el algoritmo del agente viajero 
    vector<int> pathTSPindexes; //Almacena indices de la ruta del TSP 
    vector<bool> visitedNodes; //Almacena colonias ya visitadas
    int minTSPWeight = INF; //Inicializa el valor de minimo costo como INF

    //String que almacena todos los outputs para guardarlos en un archivo
    string output = "Actividad Integradora 2 realizada por Miguel Angel Santamaria Vilchis & Victor Hugo Franco Juárez \n\n";


    //Metodo receiveInput recibe y procesa todo el input de la ActInt 2
    void receiveInput(){

        cin >> n; // vertices
        cin >> m; // numero de conexiones / aristas
        cin >> q; // ciudades nuevas

        pair<string, int> city ("0", 0);
        vector<double> pos (2, 0);
        vector<vector<int>> matriz ( n, vector<int>(n, INF)); 
        vector<vector<int>> next(n, vector<int>(n, -1));

        string v;
        int a, b;

        //Ciclo que almacena los datos de las colonias en sus respectivos vectores
        for (int i=0; i<n; i++){

            cin >> city.first;
            cin >> pos[0];
            cin >> pos[1];
            cin >> city.second;

            cityNames.push_back(city);
            cityPos.push_back(pos); 

            matriz[i][i] = 0; // Inicializa la diagonal en 0's de la matriz de adyacencia
            next[i][i] = 0;// Inicializa la diagonal en 0's de la matriz de Floyd Warshall

        }
        
        //Ciclo que llena la matriz de adyacencia del grafo de acuerdo al input
        for (int i=0; i<m; i++){

            cin >> v; 
            a = busquedaPair(cityNames, v);
            cin >> v; 
            b = busquedaPair(cityNames, v);

            cin >> matriz[a][b];
            matriz[b][a] = matriz[a][b]; 

            next[a][b] = b;
			next[b][a] = a;

        }

        //Ciclo que llena los vectores de las nuevas colonias
        for (int i=0; i<q; i++){

            cin >> v;
            cin >> pos[0];
            cin >> pos[1];

            cityNamesNew.push_back(v);
            cityPosNew.push_back(pos);
        
        }

        //Asignacion de matrices de adyacencia y FW
        matrix = matriz;
        FWnext = next;

    }

    //Metodo que retorna el indice asociado al nombre de la colonia
	int busquedaPair(vector<pair<string, int>> dict, string x){
		
		int index = 0;
		for(const auto& pair : dict) {
		    if(pair.first == x) {
		        break;
		    }
		    index++;
		}
		return index;
	}


/*------------------------------------------------------
------------ Algoritmo de Floyd Warshall ---------------
------------------------------------------------------*/

    // El Algoritmo de Floyd Warshall compara todos los caminos posibles entre cada par de vértices
    // para encontrar la ruta mas corta entre todos los nodos
    // Complejidad computacional en el peor de los casos: O(n^3)
    
    //Metodo floydWarshall realiza el algoritmo de FW utilizando la matriz de adyacencia del grafo
    //No recibe ni retorna ningun parametro
    void floydWarshall(){
        //Inicializa matriz de soluciones con 0s
        vector<vector<int>> FWsolutions(n, vector<int>(n, 0));
		
		// Matriz con los vertices para construir el alrbol del camino mas corto entre nodos
		vector<vector<int>> next = FWnext;
		
        //LLena matriz de soluciones con los valores de la matriz de adyacencia original
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                FWsolutions[i][j] = matrix[i][j];
                FWsolutions[j][i] = matrix[i][j];
            }
        }
        
        // Itera por cada nodo
        for (int k = 0; k < n; k++){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    //Si el vertice k esta en el camino mas corto de i a j, actualiza el valor de solutions[i][j]
                    if(FWsolutions[i][j] > (FWsolutions[i][k] + FWsolutions[k][j]) && (FWsolutions[k][j] != INF && FWsolutions[i][k] != INF)){
                        
                        FWsolutions[i][j] = FWsolutions[i][k] + FWsolutions[k][j];
                        
                        // Guarda el vertice al que se debe conectar para formar el arbol del camino mas corto
                        next[i][j] = next[i][k];    
                     
                    }
                }
            }
        }
		
		output +=  "3 - Caminos mas cortos entre centrales\n\n";
		
		// Ciclo para el camino  de las colonia centrales
		for (int i = 0; i < n; i++){
			for (int j = i; j < n; j++){
                //Para cada colonia  que sea central, se genera el camino
				if (cityNames[i].second==1 && cityNames[j].second==1 && i!=j){
					camino(next, i, j);
					output += " = " + to_string(FWsolutions[i][j]) + "\n";	
				}
			}
		}
		output += "\n";

    }
    

    // Funcion que reconstruye el arbol del camino mas corto
    // Recibe la matriz del que guarda los arboles dle camino mas corot y los indices de los vertices de los que se quiere buscar
    void camino(vector<vector<int>> next, int u, int v){

		if (next[u][v] == -1){
    		output += " - No hay camino \n";
		} 
		else{
			output += cityNames[u].first;
		}
		
    	while (u != v){ 
    		u = next[u][v];
    		output += " - " + cityNames[u].first;
		}
	}
    
    
/*------------------------------------------------------
------------ Traveling Salesman Problem ----------------
------------------------------------------------------*/
// El problema del agente viajero TSP busca conocer la ruta optima al visitar todos los nodos 1 vez y regresar al origen
//Implementacion realizada con el metodo Branch & bound
// Complejidad computacional en el peor de los casos: O(2^n)
//Una implementacion mas optima hubiera sido con programacion dinamica y el uso de modificadores de bits


    //Metodo saveInPathTSP que copia la solucion al vector final 
    //Recibe el vector que contiene el camino actual seleccionado    
    void saveInPathTSP(vector<int> path){
        //Llena el vector del camino con 0s
        vector<int> aux(n, 0);
        pathTSPindexes = aux;
        //Llena el vector final del camino con el vector actual seleccionado
        for (int i = 0; i < n; i++){
            pathTSPindexes[i] = path[i];
        }
        //Regresa a la colonia inicial
        pathTSPindexes[n] = path[0];
    }

    //Metodo que encuentra el minimo costo de arista teniendo como fin el nodo i
    int firstMin(vector<vector<int>> matrix, int i){
        int min = INF;
        for (int j = 0; j < n; j++){
            if (matrix[i][j] < min && i != j){
                min = matrix[i][j];
            }
        }
        return min;
    }

    //Metodo que encuentra el segundo minimo costo de arista teniendo como fin el nodo i
    int secondMin(vector<vector<int>> matrix, int i){
        int first = INF;
        int second = INF;
        for(int j = 0; j < n; j++){
            if (i == j){
                continue;
            }  
            if (matrix[i][j] <= first){
                second = first;
                first = matrix[i][j];
            }
            else if (matrix[i][j] <= second && matrix[i][j] != first){
                second = matrix[i][j];
            }
        }
        return second;
        
    }

    //Metodo TSPBB (TSP Branch & Bound) recursivo para resolver el TSP con branch & bound
    //Recibe la matriz de adyacencia del grafo, el limite inferior del nodo raiz, el peso actual del camino, el nivel de larbol, y el vector con los caminos
    void TSPBB(vector<vector<int>> matrix, int lowerLimit, int currentWeight, int level,  vector<int> path){
        //Caso base cuando se ha llegado al ultimo nivel del arbol
        //Ya se han recorrido todos los nodos
        if (level == n){
            //Revisa si hay un camino de la ultima colonia a la primera
            if  (matrix[path[level-1]][path[0]] != 0){
                //Se almacena el peso total actualizado
                int currentSol = currentWeight + matrix[path[level-1]][path[0]];
                //Si el peso total de currentSol es mejor que el minimo almacenado, el cual es INF, se actualiza y se guarda el nuevo camino en el vector
                if (currentSol < minTSPWeight){
                    saveInPathTSP(path);
                    minTSPWeight = currentSol;
                }
            }
            return;
        }

        //Si no se ha llegado al nivel final, se iteran todos los nodos para construir el arbol de busqueda
        for (int i = 0; i<n; i++){
            //Si el siguiente nodo no es el mismo, y no se ha visitado
            if(matrix[path[level-1]][i] != 0 && visitedNodes[i] == false){
                int aux = lowerLimit;
                //Se suma el peso 
                currentWeight += matrix[path[level-1]][i];

                //Para el nivel 2 del arbol, el limite inferior se calcula utilizando la suma de los minimos 
                if (level==1){
                    lowerLimit -= ((secondMin(matrix, path[level-1]) + secondMin(matrix, i)) / 2);
                }
                else{
                    lowerLimit -= ((firstMin(matrix, path[level-1]) + secondMin(matrix, i)) / 2);
                }

                //El limite inferior actual del nodo al que se llega es la suma del limite inferior + el peso actual
                //Si es menor, se debe continuar explorando
                if(lowerLimit + currentWeight < minTSPWeight){
                    path[level] = i;
                    visitedNodes[i] = true;
                    
                    //Se pasa al siguiente nivel
                    TSPBB(matrix, lowerLimit, currentWeight, level+1, path);
                }
                //se restablece el nodo desactualizando los cambios al limite y al peso
                currentWeight -= matrix[path[level-1]][i];
                lowerLimit = aux;
                
                //Se reestablece el vector booleano de visitados
                visitedNodes = vector<bool>(n, false);
                for(int j = 0; j<= level-1; j++){
                    visitedNodes[path[j]] = true;
                }
            }
        }
    }

    //Metodo principal del TSP
    //No recibe ni retorna ningun parametro
    void TSP(){

        // Guarda los nodos del camino actual
        vector<int> path(n+1, -1);
        
        // Inicializa los nodos visitados en false
         vector<bool> aux (n, false);
         visitedNodes = aux;

        int lowerLimit = 0;
        
        // Calcular el limite inicial 
        for (int i=0; i<n; i++){
            lowerLimit += (firstMin(matrix, i) + secondMin(matrix, i));
        }

        // Redondea el limite inferior a un entero
        lowerLimit = ceil(lowerLimit/2);
  
        // Como se inicia en el vertice 1, el current path es 0
        visitedNodes[0] = true;
        path[0] = 0;

        // Se hace la llamada recursiva del algoritmo 
        TSPBB(matrix, lowerLimit, 0, 1, path);

        output += "2 - La ruta optima es: \n\n";   
        for(int i = 0; i<n; i++){
            output+= cityNames[pathTSPindexes[i]].first + " - ";
        }
        output += cityNames[pathTSPindexes[n]].first + "\n";
        
       output += "Costo total = " + to_string(minTSPWeight) + "\n\n";
        
       
    }


/*------------------------------------------------------
------------ Algoritmo de MST Prim ---------------------
------------------------------------------------------*/
//El algoritmo de Prim es un algoritmo Greedy para encontrar el MST de un grafo
//Contiene dos sets de nodos, uno de nodos incluidos en el arbol y otro de nodos no incluidos
//Complejidad computacional en el peor de los casos: O(n^3)
//La complejidad computacional puede ser mejor si se realiza una implementacion con un min heap o con una lista de adyacencia

//Algoritmo de MST prim

    //Metodo checkPath identifica si una arista es valida para ser incluida en el MST
    //Recibe los nodos de la arista (u, v) y el vector booleano si se encuentra en el MST
    bool checkPath(int u, int v, vector<bool> includedInMST){
        //Si u es igual a v, no hay arista
        if (u == v){
            return false;
        }
        //Si no esta ningun nodo en el vector booleano, no es valida
        if (includedInMST[u] == false && includedInMST[v] == false){
            return false;
        }
        //Si se ambos nodos se sencuentran en el vector, no es valida
        else if (includedInMST[u] == true && includedInMST[v] == true)
            return false;

        return true;
    }

    //Metodo primAlgorithm realiza el algoritmo de Prim para encontrar el MST 
    void primAlgorithm(){

        // Inicializa un vector para saber si un vertice ya fue visitado
        vector<bool>includedInMST(n, false);
        
        int pathCount = 0; //Numero de caminos tomados
        int solution = 0; //Costo minimo
        int weight = 0;
        int a = 0; 
        int b = 0;

        output += "1 - Cableado optimo de nueva conexion\n\n";

        includedInMST[0] = true;    // El primer vertice se encuentra en el MST

        while (pathCount < n-1){
            weight = INF;
            a = -1;
            b = -1;

            // Itera para encontrar el vertice valido con menor peso  
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (matrix[i][j] < weight){
                        if (checkPath(i,j, includedInMST)){
                            weight = matrix[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }

            //Si se encontro un camino valido, se suma el contador y se agrega la ruta del MST
            if (a != -1 && b != -1){
                pathCount++;
                output += cityNames[a].first + " - " + cityNames[b].first + " : " + to_string(weight) + "\n";
                solution = solution + weight;
                includedInMST[a] = true; //Se agrega al vector de vertices visitados
                includedInMST[b] = true; //Se agrega al vector de vertices visitados
            }
        } 
        output +=  "Costo Total - " + to_string(solution) + "\n\n";
    }

/*------------------------------------------------------
------------ Distancia mas corta -----------------------
------------------------------------------------------*/

    // Funcion que calcula la distancia mas corto usando la distancia euclidiana entre dos puntos
    // Complejidad de tiempo O(1)
    double distance(double x1, double y1, double x2, double y2){

        double diffx = x2 - x1;
        double diffy = y2 - y1;
		
        return sqrt ((diffx * diffx) + (diffy * diffy));
    }
    

    // Funcion que determina la central a la que se debe conectar una colonia nueva
    // Usa la formula de la distancia de Euclides para determinar cual es la central mas cercana
    // Complejidad de tiempo en el peor de los casos O(n) por cada colonia nueva que se quiera conectar
    void conexionesNuevas(){
        
        int city;
        double min, dis;
		
		output += "4 - Conexion de nuevas colonias \n\n";
		
        // Itera por cada ciudad nueva
        for (int i=0; i<q; i++){
            
            min = INF;
            
            // Itera por cada ciudad existente
            for (int j=0; j<n; j++){

                // Solo puede conectarse a una colonia que sea central
                if (cityNames[j].second == 1){

                    // Calcula la distancia minima entre ambas colonias
                    dis = distance(cityPosNew[i][0], cityPosNew[i][1], cityPos[j][0], cityPos[j][1]);
                    
                    // Guarda la distancia minima y el indice de la colonia
                    if (dis < min){
                        min = dis;
                        city = j;
                    }
                } 
            }

        output += cityNamesNew[i] + " debe conectarse con " + cityNames[city].first + "\n";

        }
        
        output += "\n"; 
        
    }

    
public:
    //Metodo Solution genera solucion a la ActIn2 utilizando los metodos privados
    void Solution(){
        //Inputs
		receiveInput(); 

        //Algoritmo de Prim MST
        primAlgorithm(); 
        
        // Algortimo para resolver el problema del agente viajero 
        TSP();

        // Algoritmo de floyd warshall
        floydWarshall();

        // Conexiones Nuevas
        conexionesNuevas();

        // Guardar resultados en el archivo
        ofstream myfile;
        myfile.open("checkingA01366475.txt");   
        if(myfile.is_open()){
            myfile << output;
            cout << "Output saved to checkingA01366475" ;
        }
        else{   // Si no lo encuentra ni puede crearlo, imprime un mensaje de error
            cout << "Couldn't create/open file";
        }
    
    }
	
};

int main(){
    Quaerit qu;
    qu.Solution();
}