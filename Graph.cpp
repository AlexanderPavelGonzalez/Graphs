#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;

// Creates a simple graph on vertices 0..4
void sampleGraphInitialization(vector< vector<int> >& adjList){
	// edge 0-2
	adjList[0].push_back(2); 
	adjList[2].push_back(0);	
	
	// edge 0-3
	adjList[0].push_back(3);
	adjList[3].push_back(0);
	
	// edge 1-2
	adjList[1].push_back(2); 
	adjList[2].push_back(1);
	
	// edge 1-4
	adjList[1].push_back(4); 
	adjList[4].push_back(1);
	
	// edge 2-3
	adjList[2].push_back(3); 
	adjList[3].push_back(2);	
	
	// edge 3-4
	adjList[3].push_back(4); 
	adjList[4].push_back(3);
	
}

int maxDegree(vector< vector<int> >& adjList){
	int max = 0;
	for(int j = 0; j < adjList.size(); j++){
		if(adjList[j].size() > max){
			max = adjList[j].size();
	    }
	}
	return max;
}

int minDegree(vector< vector<int> >& adjList){
	int min = adjList.size();
	for(int j = 0; j < adjList.size(); j++){
		if(adjList[j].size() < min){
			min = adjList[j].size();
	    }
	}
	return min;
}
// Read in edge set from inputFile and create adjacency list
// for graph with n vertices
void graphFromFile(vector< vector<int> >& adjList, int n){
	ifstream inFile("facebook_combined.txt");
  	int v1;
        int v2;
        int degree;
       
        while(inFile >> v1){
	  inFile >> v2;
	  /*
          cout << v1 <<" "<< endl;
          cout << v2 <<" "<< endl;
	  */
	  
	  adjList[v1].push_back(v2);
	  adjList[v2].push_back(v1);	  
	}
        int min = minDegree(adjList);
        int max = maxDegree(adjList);
        double lowDegree;
        for(int i = 0; n>i;i++){
	 degree = adjList[i].size();
          if(degree <= min + (max-min)/10){
            lowDegree++; 
	  }
	}
        cout << "Facebook Low Degree % = " << (lowDegree/n)*100 << endl;
	// adjList[0].push_back[1];
}

// Create adjacency list for a random graph with n vertices and m edges
void randomGraph(vector< vector<int> >& adjList, int n, int m){
  vector<int>::iterator it;
        
  while(m>0){
		int  y = rand()%n;
                int  x = rand()%n; 
                it = find(adjList[x].begin(),adjList[x].end(),y);
		if(y!=x && it == adjList[x].end() ){
                   	adjList[x].push_back(y);
                    	adjList[y].push_back(x);
			m--; 
		  }
		
  }
  int min = minDegree(adjList);
  int max = maxDegree(adjList);
  int degree;
  double lowDegree;
        for(int i = 0; n>i;i++){
	 degree = adjList[i].size();
          if(degree <= min + (max-min)/10){
            lowDegree++; 
	  }
	}
        cout << "Random Graph Low Degree % = " << (lowDegree/n)*100 << endl;	
}


int average(vector< vector<int> >& adjList){
  int sum = 0;
  for(int i = 0; i < adjList.size(); i++){
    sum = sum + adjList[i].size();
  }
    return sum/adjList.size(); 
}

// Create a regular graph on n vertices each vertex degree d (even)
// I have commented out the debug print lines, but you can put these in 
// to see the edge list of a small regular network
void regularGraph(vector< vector<int> >& adjList, int n, int d){
	for (int i=0; i < n; i++){
		//cout << "neighbors of " << i << ":  ";
		for (int j = 1; j <= d/2; j++){
			int left = ((i-j)>=0)?(i-j):(n+i-j);
			int right = (i+j)%n;
			//cout << left << "  " << right << "  ";
			adjList[i].push_back(left); 
			adjList[i].push_back(right);
		}
		//cout << endl;
	}	
	//cout << endl;
		
}
double clusteringCoefficient(vector< vector<int> >& adjList, int n){
  vector<int>::iterator it;
  double counter=0;
  int v1;
  int v2;
  int cluster;

  int k = adjList[n].size();
  int sum;

  for(int i = 0; i<k-1; i++){
    for(int j = i+1; j < k;j++){
      v1 = adjList[n][i];
      v2 = adjList[n][j];
      it = find(adjList[v1].begin(),adjList[v1].end(),v2);
      if(it != adjList[v1].end()){
        counter++;
      }
    }
   }
  
  if (k > 1)
    return (2 * counter)/(k*(k-1));
  return 0;
  //cout << "Clustering Coefficient Average " << sum/n << endl;
}

double clusterAvg(vector< vector<int> >& adjList) {
  // loop through vertices
  //    sum up clustering coefficients
  double sum = 0;
  for(int i =0; i<adjList.size(); i++){
    sum += clusteringCoefficient(adjList, i);
  }
  // divide by num vertices
  return sum/4039;
}
int shortestPath(vector< vector<int> >& adjList, int i, int j, int size){
  vector<int>::iterator it;
  int  distance[size];
  queue<int> queue;

  queue.push(i); 
  
  for(int x = 0; x < size;x++){
    distance[x] = -1;
  }
  distance[i]=0;

  while(!queue.empty()){
    int front = queue.front();
    for(int i = 0; i < adjList[front].size(); i ++){
      int nb = adjList[front][i];
      //cout << "considering neighbor " << nb << endl;
      if (distance[nb] == -1){
	distance[nb] = distance[front]+1;
        queue.push(nb);
      }
    }
    //cout << "distance to " << front << " =  " << distance[front] << endl;
    queue.pop(); 
  }
  return  distance[j];
}

double shortestAvgPath(vector< vector<int> >& adjList, int i, int size){
  int  distance[size];
  queue<int> queue;

  queue.push(i); 
  
  for(int x = 0; x < size;x++){
    distance[x] = -1;
  }
  distance[i]=0;

  while(!queue.empty()){
    int front = queue.front();
    for(int i = 0; i < adjList[front].size(); i ++){
      int nb = adjList[front][i];
      //cout << "considering neighbor " << nb << endl;
      if (distance[nb] == -1){
	distance[nb] = distance[front]+1;
        queue.push(nb);
      }
    }
    //cout << "distance to " << front << " =  " << distance[front] << endl;
    queue.pop(); 
  }

  // return avg of values in the distance array
  double total = 0;
  for(int j = 0; j < size; j++){
    total += distance[j];
  } 

  // cout<<"Total "<< total<< " Avg "<<total/size<<endl;
  return total/size;
}
double pathLength(vector< vector<int> >& adjList, int size){
  double total = 0; 
   
  for(int i = 0; i < size; i++){
    total += shortestAvgPath(adjList, i , size);
  }
  
  return total/size;
} 

int main() {

	// Create sampele graph & compute maximum degree
	vector< vector<int> > sampleAdj(5);
	sampleGraphInitialization(sampleAdj);
	cout << "Max degree sample graph " << maxDegree(sampleAdj) << endl;
	cout << "Min degree sample graph " << minDegree(sampleAdj) << endl;
        cout << "Average degree sample graph " << average(sampleAdj) << endl;
	cout << "friends of 2 " <<  clusteringCoefficient(sampleAdj,3) << endl;
       	cout << "Average Path Length " <<  pathLength(sampleAdj,5) << endl;

	// Read in the Facebook network
	vector< vector<int> > regAdj1(4039);
	graphFromFile(regAdj1,4039);
        cout << "Max degree facebook graph " << maxDegree(regAdj1) << endl;
	cout << "Min degree facebook graph " << minDegree(regAdj1) << endl;
        cout << "Average degree facebok graph " << average(regAdj1) << endl;
	cout << "Cluster Facebook Average " <<  clusterAvg(regAdj1) << endl;
	cout << "Average Facebook Path Length " <<  pathLength(regAdj1,4039) << endl;
	// Generate Random network
       	vector< vector<int> > regAdj2(4039);
        randomGraph(regAdj2,4039,88234);
        cout << "Max degree random graph " << maxDegree(regAdj2) << endl;
	cout << "Min degree random graph " << minDegree(regAdj2) << endl;
        cout << "Average degree random graph " << average(regAdj2) << endl;
        cout << "Cluster Random Average " <<  clusterAvg(regAdj2) << endl;
        cout << "Average Random Path Length " <<  pathLength(regAdj2,4039) << endl;
	// Regular graph of size close to the facebook network
	vector< vector<int> > regAdj(4039);
	regularGraph(regAdj,4039,44);
	cout << "Max degree regular graph " << maxDegree(regAdj) << endl;
	cout << "Min degree regular graph " << minDegree(regAdj) << endl;
        cout << "Average degree regular graph " << average(regAdj) << endl;
        cout << "Average Reg Path Length " <<  pathLength(regAdj,4039) << endl;
        
	return EXIT_SUCCESS;
}
