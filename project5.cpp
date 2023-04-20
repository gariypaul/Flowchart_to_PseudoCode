// Project 5
// CS 2413 Data Structures
// Spring 2023

// Code generated for input 1 would be:
// if(expression1)
// {
// 	statement1;
// }
// else
// {
// 	statement2;
// }

#include <iostream>
#include <string> // for the fields in the class
#include <vector> // for the flowchart structures
#include <stack>  // for conversion

using namespace std;

// class to store node information
class Node
{
private:
	int nodeNumber;    // to store the node number
	string type;       // can either be START, END, IF, BLOCK
	string textWithin; // can be expression or statement - for START and END this will be empty string
    int counterPnt=0; //points the number of nodes that point to it
public:
	//construtors
    Node();
    Node(int nodeNum,string nodeType,string text);
    //getters
    int getNodeNumber()const;
    string getType()const;
    string getTextWithin()const;

    //setters
    void setNodeNumber(int number);
    void setType(string settype);
    void setTextWithin(string text);

    int getCountPnt() const;

    void setCountPnt(int num);
};

Node::Node() {

}

Node::Node(int nodeNum, string nodeType, string text) {
    nodeNumber = nodeNum;
    type = nodeType;
    textWithin=text;

}

int Node::getNodeNumber() const {
    return nodeNumber;
}

string Node::getType() const {
    return type;
}

string Node::getTextWithin() const {
    return textWithin;
}
int Node::getCountPnt() const{
    return counterPnt;
}
void Node::setNodeNumber(int number) {
    nodeNumber=number;
}

void Node::setType(string settype) {
    type = settype;
}

void Node::setTextWithin(string text) {
    textWithin = text;
}

void Node::setCountPnt(int num){
    counterPnt=num;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// function to convert the given flowchart to generate code
void convertFlowChart(vector<Node> allNodes, vector<vector<int>> adjList)
{
    // TODO: use stack (no recursion) to convert the flowchart into psuedo code
    stack<int> flowStack;
    /*vector<bool> visited(allNodes.size(), false);*/
    flowStack.push(0);
    cout << allNodes[0].getTextWithin() << endl;
    bool isIfEnd =false;
    while (!flowStack.empty()){
        int current = flowStack.top();
        flowStack.pop();
//      visited[current] = true;

        if(allNodes[current].getType()=="START"){
            cout<<"start"<<endl;
            current = adjList[current][1];
        }

        if (allNodes[current].getType() == "BLOCK"){
                if(allNodes[adjList[adjList[current][1]][1]].getType()=="END"||allNodes[adjList[adjList[current][1]][1]].getType()=="BLOCK"){
                    cout << allNodes[current].getTextWithin() << ";" << endl;
                    allNodes[adjList[adjList[current][1]][1]].setCountPnt(allNodes[adjList[adjList[current][1]][1]].getCountPnt()+1);
                }
                else{
                    flowStack.push(adjList[current][1]);
                    cout << allNodes[current].getTextWithin() << ";" << endl;
                }

                if(isIfEnd){
                    flowStack.push(-2);
                }


        }
        else if (allNodes[current].getType() == "IF"){
            cout << "if (" << allNodes[current].getTextWithin() << ")" << endl;
            cout << "{" << endl;
            flowStack.push(adjList[current][2]);
            if(adjList[current].size()>2){
                flowStack.push(-1);
                flowStack.push(adjList[current][1]);
            }

        }
        else if (allNodes[current].getType() == "END"){
            if(!flowStack.empty()) {
                cout << " " << endl;
            }
        }
        else if(current==-1){
            cout<<"}"<<endl;
            cout <<  "else" << endl;
            cout <<  "{" << endl;
            isIfEnd=true;
            /*if(allNodes[adjList[adjList[flowStack.top()][1]][1]].getType()=="END"){

            }*/

        }
        else if(current==-2){
            cout<<endl;
            cout<<"}"<<endl;
            isIfEnd=false;
        }
    }
    cout<<"end"<<endl;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    int numNodesInFlowChart; // number of nodes in the flow chart

    cin >> numNodesInFlowChart;
    cout << "Number of nodes: " << numNodesInFlowChart << endl;

    // Node objects array to store all the information
    vector<Node> allNodes(numNodesInFlowChart);

    // TODO: read in the information about the nodes and store it in allNodes
    string nodeNumber;
    string nodeType;
    string nodeText;

    cin >> nodeNumber >> nodeType;
    allNodes[stoi(nodeNumber)].setNodeNumber(stoi(nodeNumber));
    allNodes[stoi(nodeNumber)].setType(nodeType);

    for(int i=1;i<numNodesInFlowChart-1;i++){
        cin >> nodeNumber >> nodeType >>nodeText;
        allNodes[i].setNodeNumber(stoi(nodeNumber));
        allNodes[i].setType(nodeType);
        allNodes[i].setTextWithin(nodeText);
    }

    cin>>nodeNumber>>nodeType;
    allNodes[stoi(nodeNumber)].setNodeNumber(stoi(nodeNumber));
    allNodes[stoi(nodeNumber)].setType(nodeType);

    // adjacency list to store the flow chart
    vector<vector<int>> adjList;

    // TODO: read in the adjacency list
    string operation;
    while(getline(cin,operation)){
        if(!operation.empty()){
            vector<int> newVector;
            size_t pos = 0;

            while(pos<operation.length()){
                size_t endpos = operation.find(' ',pos);

                if(endpos==string::npos){
                    endpos=operation.length();
                }
                string numstr = operation.substr(pos,endpos-pos);
                int num = stoi(numstr);

                newVector.push_back(num);

                pos=endpos+1;
            }
            adjList.push_back(newVector);
        }

    }

    // TODO: call the convertFlowChart function with the allNodes and adjList parameters
    convertFlowChart(allNodes,adjList);
    return 0;
}
