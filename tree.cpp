#include<bits/stdc++.h>

template <typename T>
class alives_tree{
	
public:
		alives_tree(const std::vector<T>& v){
			nodes.resize(2 * v.size());
			build(0,v.size(),0,v);
			update(0);
		}
		
		void build(int ini, int fin, int actual,const std::vector<T>& values){
			if(actual >= size() || ini == fin){
				return;
			}
			int mid = ini + (fin - ini)/2;
			nodes[actual] = {values[mid],true,0};
			build(ini,mid,left_son(actual),values);
			build(mid+1,fin,right_son(actual),values);
		}
		
		int update(int actual){
			if(actual >= size()){
				return 0;
			}
			nodes[actual].alives_behind = update(left_son(actual)) + update(right_son(actual));
			return nodes[actual].alives_behind + nodes[actual].alive;
		}
		
		//Return the k-th element alive
		T query(int i){
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
		
		// Kill the i-th element alive
		void erase(int i){
			int index = recursive_find(0,i);
			nodes[index].alive = false;
			
			if(index == 0){
				return;
			}
			
			int parent = std::floor((index - 1)/2);
			while(parent != 0){
				nodes[parent].alives_behind--;
				parent = std::floor((parent - 1)/2);
			}
			nodes[0].alives_behind--;
			
		}
		int size( ) const {
			return nodes.size();
		}
		
		int left_son(int& i){
			return 2*i + 1;
		}
		
		int right_son(int& i){
			return 2*i + 2;
		}
		
private:
	struct node{
		T value;
		bool alive = false;
		int  alives_behind = 0;
	};
	std::vector<node>nodes;
};




int main(){
	
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	
	std::vector<char> arr = {'A','B','C','D','E'};
	
	alives_tree tree(arr);
	
	std::cout<<tree.query(2)<<"\n"; // Prints 'B'
	tree.erase(2);
	std::cout<<tree.query(2)<<"\n"; // Prints 'C'
	
}
