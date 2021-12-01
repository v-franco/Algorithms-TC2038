/*
-----------------------------------------------
------------Actividad Integradora I------------
---A01366795 Miguel Angel Santamaria Viclhis---
---- A01366475 Victor Hugo Franco Juárez ------
---------------15 Octubre 2021-----------------
-----------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

//Clase Quaerit contiene metodos de busqueda de substrings en un string, busqueda de palindromo mas largo, y de substring comun mas larga
class Quaerit{

private:

    //Metodo kmpPreprocess realiza preprocesamiento del patron a ser buscado en el texto (utilizado por KMP)
    //Recibe el patron p y el vector v
    //No regresa ningun parametro
    //Complejidad computacional en el peor caso: O(m) donde m = longitud de patron
    void kmpPreprocess(string p, vector<int>& v){
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

    //Metodo kmp realiza la busqueda de patron en el texto
    //Recibe patron p a buscar y texto t donde buscar 
    //Utiliza el metodo kmpPreprocess para preprocesamiento del patron
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
        kmpPreprocess(p, v);
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

    //Metodo manacher encuentra el palindromo mas largo en un string utilizando el algoritmo de Manacher
    //Recibe string en la cual encontrar el palindromo
    //Regresa un vector con el indice (base 1) de inicio y fin del palindromo mas largo en el string
    //Complejidad computacional en el peor de los casos: O(n) donde n = longitud de la string
    vector<int> manacher(string str){
		
		vector<int> res(3,0); // resultado(inicio, final, longitud)
	  	
	  	int stringLength, maxLength, maxCenter, center, Li, Ri;
	  	bool expansion;
	  	string strAux;
        
        // Si el String es Null, return
	  	if (str.length() == 0){ 
	  		return res;
		}
	    
	    // Se crea un string auxiliar con | entre cada caracter y en los limites
		strAux = "";
		for (char c:str){
			strAux = strAux+"|"+c;
		}
		strAux = strAux+"|";
	  	
	  	stringLength = strAux.length();

        // Se crea un vector con el radio del palindromo mas largo para cada elemento en el string auxiliar
	  	vector<int> PalindromeRadius (stringLength,0);   
	  	
	  	// longitud y centro del maximo palindromo encontrado
	  	maxLength = 1;
	  	maxCenter = 1;		
	  	
	  	center = 1;
	  	Li = 0;
	  	Ri = 0;
	 	
	  	expansion = false; // true si requiere expandir el radio para revisar si el palidnromo extiende
	
	  	PalindromeRadius[0]=0; 
		PalindromeRadius[1]=1;
	  	
	  	for (Ri = 2; Ri < stringLength; Ri++){
	  		
	    	expansion = false;
	    	Li = center - (Ri - center);
	    	
	    	if ((center + PalindromeRadius[center])-Ri >= 0){
	    		
	    		// Caso 1
	      		if (PalindromeRadius[Li] < (center+PalindromeRadius[center])-Ri){
	      			PalindromeRadius[Ri] = PalindromeRadius[Li];
				}
				
				// Caso 2
				else if (PalindromeRadius[Li] == (center+PalindromeRadius[center])-Ri && (center+PalindromeRadius[center]) == stringLength-1){
					PalindromeRadius[Ri] = PalindromeRadius[Li];
				}
				
				// Caso 3
				else if(PalindromeRadius[Li] == (center+PalindromeRadius[center])-Ri && (center+PalindromeRadius[center]) < stringLength-1){ 
					PalindromeRadius[Ri] = PalindromeRadius[Li];
					expansion = true; // requiere expansion del radio
				}
				
				// Caso 4
				else if(PalindromeRadius[Li] > (center+PalindromeRadius[center])-Ri){ 
					PalindromeRadius[Ri] = (center+PalindromeRadius[center])-Ri;
					expansion = true; // requiere expansion del radio
				}
			
			}
			
		    else{
		    	PalindromeRadius[Ri] = 0;
		    	expansion = true;  // requiere expansion del radio
		    }
			    
			    
		    // hacer la expansion del radio mientras siga siendo palindromo
		    if (expansion){
		    	while ((Ri+PalindromeRadius[Ri] < stringLength) && (Ri-PalindromeRadius[Ri] > 0) && (strAux[Ri+PalindromeRadius[Ri]+1] == strAux[Ri-PalindromeRadius[Ri]-1])){
		    		PalindromeRadius[Ri]++;
				}
			}
		    	
		    // si el nuevo palindromo se expande mas alla del centro    	
		    if (Ri + PalindromeRadius[Ri] > (center + PalindromeRadius[center])){
		    	center = Ri;
			}
				
			// Guardar longitud y centro del palindromo mas grande hasta ahora	
		    if(PalindromeRadius[Ri] > maxLength){ 
				maxLength = PalindromeRadius[Ri];
				maxCenter = Ri;
			}
		
	    }
	  	
		// obtener inicio y longitud del maximo palindromo encontrado 
		
		// Calcular las posiciones de inicio y final recordando que el string auxiliar es el doble que el original
        res[0] = ((maxCenter - maxLength)/2) + 1; // inicio en S
        res[1] = res[0] + maxLength - 1; // final en S
        res[2] = maxLength; // longitud en S
            
	  	return res;
	  	
	}

    //Metodo LCS encuentra el substring comun mas largo (longest common substring / LCS) entre dos strings
    //Recibe ambos strings para buscar el LCS
    //No retorna ningun valor
    //Imprime los indices (base 1) donde inicia y termina el LCS
    //Utiliza programacion dinamica 
    //Complejidad computacional en el peor de los casos: O(n*m) donde n = string 1 y m = string 2
    void lcs(string trans1, string trans2){
    
        int m, n, start, end;
        string res;

        m = trans1.size(), 
        n = trans2.size();

        // cout << m << " " << n << endl;

        int lcsMatrix[m+1][n+1];

        // Incializa la primera columna y primera fila con 0's
        for(int j=0; j<=n; j++){
            lcsMatrix[0][j] = 0;
        }
        for(int i=0; i<=m; i++){
            lcsMatrix[i][0] = 0;
        }

        // Llena la matriz con 0 y cuando encuentra coincidencia suma 1 a la diagonal anterior
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(trans1[i-1] == trans2[j-1]){
                    lcsMatrix[i][j] = lcsMatrix[i-1][j-1] + 1;
                }
                else{
                    lcsMatrix[i][j] = 0;
                }
            }
        }

        // Busca la diagonal con el valor mas grande
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(lcsMatrix[i][j] > res.length()){
                    start = (i-lcsMatrix[i][j]+1);
                    end = start + lcsMatrix[i][j];
                    res = trans1.substr((i-lcsMatrix[i][j]+1) -1, lcsMatrix[i][j]);
                }
                    
            }
        }
        cout << "The LCS range found in Transmission 1 and Transmission 2 goes from: " << start << " to " << end - 1<< "\n";
    }

public:
    string file = "";
    string transmission1 = "";
    string transmission2 = "";
    string mcode1 = "";
    string mcode2 = "";
    string mcode3 = "";

    //Metodo printPositions imprime en consola las posiciones (base 1) de coincidencia encontrados por el metodo kmp
    //Recibe como parametro vector con posiciones
    //No regresa ningun parametro
    void printPositions(vector<int> positions){
        for (int i = 0; i < positions.size(); i++){
            cout << positions[i] << " ";
        }
        cout << "\n";
    }

    //Metodo openTrans1 abre el archivo transmission1.txt y almacena su contenido en el string transmission1
    //No recibe ni regresa ningun parametro
    void openTrans1(){
        file = "transmission1.txt";
        ifstream in(file);
        if (in.is_open()){
            getline(in, transmission1, '\0');
            in.close();
        }
        else{
            cout << "No se puede abrir el archivo: "<< file << "\n";
        }
    }

    //Metodo openTrans1 abre el archivo transmission2.txt y almacena su contenido en el string transmission2
    //No recibe ni regresa ningun parametro
    void openTrans2(){
        file = "transmission2.txt";
        ifstream in(file);
        if (in.is_open()){
            getline(in, transmission2, '\0');
            in.close();
        }
        else{
            cout << "No se puede abrir el archivo: "<< file << "\n";
        }
    }

    //Metodo openMcode1 abre el archivo mcode1.txt y almacena su contenido en el string mcode1
    //No recibe ni regresa ningun parametro
    void openMcode1(){
        file = "mcode1.txt";
        ifstream in(file);
        if (in.is_open()){
            getline(in, mcode1, '\0');
            in.close();
        }
        else{
            cout << "No se puede abrir el archivo: "<< file << "\n";
        }
    }

    //Metodo openMcode2 abre el archivo mcode2.txt y almacena su contenido en el string mcode2
    //No recibe ni regresa ningun parametro
    void openMcode2(){
        file = "mcode2.txt";
        ifstream in(file);
        if (in.is_open()){
            getline(in, mcode2, '\0');
            in.close();
        }
        else{
            cout << "No se puede abrir el archivo: "<< file << "\n";
        }
    }

    //Metodo openMcode3 abre el archivo mcode2.txt y almacena su contenido en el string mcode3
    //No recibe ni regresa ningun parametro
    void openMcode3(){
        file = "mcode3.txt";
        ifstream in(file);
        if (in.is_open()){
            getline(in, mcode3, '\0');
            in.close();
        }
        else{
            cout << "No se puede abrir el archivo: "<< file << "\n";
        }
    }

    //Metodo kmpTransmissions realiza la busqueda de un codigo malicioso en una transmision
    //Recibe el nombre del codigo malicioso a probarse, el nombre de la transmision en la cual buscar, y numeros de codigo malicioso y transmision
    //Utiliza el metodo KMP para encontrar los indices de coincidencia
    //Imprime los indices de coincidencia en la consola
    //No retorna ningun parametro
    void kmpTransmissions(string code, string trans, string codeNo, string transNo){
        vector<int> positions;
        positions = kmp(code, trans);
        if (positions[0] == -1){
            cout << "False, "<< codeNo <<  " not found in " << transNo << "\n";
        }
        else{
            cout << "True, "<< codeNo <<" found in "<< transNo <<"  on indexes: ";
            printPositions(positions);
        }
    }

    //Metodo findPalindrome busca el palindromo mas largo en una transmision
    //Recibe el nombre de la transmision, y el numero de transmision
    //Utiliza el metodo manacher para encontrar el palindromo
    //Imprime los indices de inicio y fin del palindromo en la consola
    //No retorna ningun parametro
    void findPalindrome(string trans, string transNo){
        vector<int> res = manacher(trans);
        cout << "Longest palindrome in "<< transNo << " is between indexes: " << res[0] << " and " << res[1] << "\n";
    }

    //Metodo findMCodes realiza la busqueda de los 3 codigos maliciosos en las transmisiones
    //Utiliza metodos openTrans1, openTrans2, openMcode1, openMcode2, openMcode3 para abrir los archivos maliciosos y de transmision
    //Utiliza metodo kmpTransmissions para realizar las busquedas
    //No recibe ni retorna ningun parametro 
    void findMCodes(){
        string transNo = "";
        string codeNo = "";
        openTrans1();
        openTrans2();
        openMcode1();
        openMcode2();
        openMcode3();
        cout << "\n";
        cout << "------------------------------PART 1-----------------------------" <<"\n";
        transNo = "Transmission 1";
        codeNo = "Malicious code 1";
        kmpTransmissions(mcode1, transmission1, codeNo, transNo);
        codeNo = "Malicious code 2";
        kmpTransmissions(mcode2, transmission1, codeNo, transNo);
        codeNo = "Malicious code 3";
        kmpTransmissions(mcode3, transmission1, codeNo, transNo);
        transNo = "Transmission 2";
        codeNo = "Malicious code 1";
        kmpTransmissions(mcode1, transmission2, codeNo, transNo);
        codeNo = "Malicious code 2";
        kmpTransmissions(mcode2, transmission2, codeNo, transNo);
        codeNo = "Malicious code 3";
        kmpTransmissions(mcode3, transmission2, codeNo, transNo);
        //cout << "------------------------------------------------------------------" << "\n";
    }

    //Metodo findPalindromeInTrans busca los palindromos mas largos en ambos archivos de transmision
    //Utiliza metodos openTrans1 y openTrans2 para obtener las transmisiones
    //Utiliza el metodo findPalindrome para encontrar los palindromos de cada transmision
    //No recibe ni retorna ningun valor
    void findPalindromeInTrans(){
        cout << "\n";
        cout << "------------------------------PART 2-----------------------------" <<"\n";
        string trans1 = "Transmission 1";
        string trans2 = "Transmission 2";
        openTrans1();
        openTrans2();
        findPalindrome(transmission1, trans1);
        findPalindrome(transmission2, trans2);
        //cout << "------------------------------------------------------------------" << "\n";
    }

    //Metodo findLCS busca el LCS entre ambos archivos de transmision
    //Utiliza metodos openTrans1 y openTrans2 para obtener las transmisiones
    //Utiliza el metodo LCS para encontrar el LCS entre las transmisiones
    //No recibe ni retorna ningun valor
    void findLCS(){
        openTrans1();
        openTrans2();
        cout << "\n";
        cout << "------------------------------PART 3-----------------------------" <<"\n";
        lcs(transmission1, transmission2);
    }
};

int main(){
    Quaerit qu;
    //Busca codigos maliciosos en las transmisiones
    qu.findMCodes();
    //Busca el palindromo mas largo de cada transmision
    qu.findPalindromeInTrans();
    //Busca el LCS entre ambas transmisiones
    qu.findLCS();
}
