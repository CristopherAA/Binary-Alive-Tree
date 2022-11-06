#include<bits/stdc++.h>

template <typename T>
class alives_tree{
	
public:
		alives_tree(std::vector<T> v)
		: values(std::move(v)){
			nodes.resize(values.size());
			build(0,size(),0);
			update(0);
			
		}
		
		void build(int ini, int fin, int actual){
			if(actual > size() || ini == fin){
				return;
			}
			int mid = ini + (fin - ini)/2;
			nodes[actual] = {values[mid],true,0};
			build(ini,mid,left_son(actual));
			build(mid,fin,right_son(actual));
		}
		
		int update(int actual){
			if(actual >= size()){
				return 0;
			}
			nodes[actual].alives_behind = update(left_son(actual)) + update(right_son(actual));
			return nodes[actual].alives_behind + nodes[actual].alive;
		}
		
		//Devuelve el k-esimo elemento vivo
		T find(int i){
			int res = recursive_find(0,i);
			return nodes[res].value;
		}
		
		int recursive_find(int actual, int v){
			
			int izq = left_son(actual);
			int der = right_son(actual);
			
			if(izq < size() && nodes[izq].alives_behind + nodes[izq].alive == v-1 && nodes[actual].alive){
				return actual;
			}
			if(izq < size() && nodes[izq].alives_behind + nodes[izq].alive >= v){
				return recursive_find(izq,v);
			}
			if(der < size()){
				return recursive_find(der, v - (nodes[izq].alives_behind + nodes[izq].alive + nodes[actual].alive));
			}
			if(v == 1 && nodes[actual].alive){
				return actual;
			}
			return -1;
			
		}
		
		// Mata al i-esimo elemento vivo
		void kill(int i){
			int index = recursive_find(0,i);
			nodes[index].alive = false;
			
			int parent = (index - 1)/2;
			while(nodes[parent].value != nodes[(parent - 1)/2].value){
				nodes[parent].alives_behind -= 1;
				parent = (parent - 1)/2;
			}
		}
		
		int size( ) const {
			return nodes.size();
		}
		
		int left_son(int i){
			return 2*i + 1;
		}
		
		int right_son(int i){
			return 2*i + 2;
		}
		
private:
	struct node{
		T value;
		bool alive = true;
		int  alives_behind = 0;
	};
	std::vector<T>values;
	std::vector<node>nodes;
};




int main(){
	std::vector<char> arr = {'a','b','c','d','e','f','g'};
	alives_tree arbol(arr);
	
	std::cout<<arbol.find(3)<<"\n";  //Imprime c
	arbol.kill(3); 
	std::cout<<arbol.find(3)<<"\n"; // Imprime d
	
	
}
