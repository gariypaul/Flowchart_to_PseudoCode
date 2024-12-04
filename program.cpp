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
#include <algorithm> // for all_of

using namespace std;

// class to store node information
class Node
{
private:
    int nodeNumber;    // to store the node number
    string type;       // can either be START, END, IF, BLOCK
    string textWithin; // can be expression or statement - for START and END this will be empty string
    bool inLoop=false; //checks if the node is in a loop
    int pointCounter=0;//points the number of nodes that point to it
    int parentLoop = 0; //sets the parent loop index if node is in a loop
public:
    //construtors
    Node();
    Node(int nodeNum,string nodeType,string text);

    //getters
    int getNodeNumber()const;
    string getType()const;
    string getTextWithin()const;
    int getParentLoop();
    int checkCount();

    //setters
    void setNodeNumber(int number);
    void setType(string settype);
    void setTextWithin(string text);
    void setIfLoop(bool in);
    void setParentLoop(int n);
    void IncreaseCount( );

    bool isInLoop() const;

    void DecreaseCount();
};

//default constructor
Node::Node() {

}
//constructur with arguments to store node information
Node::Node(int nodeNum, string nodeType, string text) {
    nodeNumber = nodeNum;
    type = nodeType;
    textWithin=text;

}
//get the nodeNumber in FlowChart
int Node::getNodeNumber() const {
    return nodeNumber;
}
//get the Node Type
string Node::getType() const {
    return type;
}
//get the text within the operation
string Node::getTextWithin() const {
    return textWithin;
}
//set the nodeNumber in the flowChart
void Node::setNodeNumber(int number) {
    nodeNumber=number;
}
//set the type
void Node::setType(string settype) {
    type = settype;
}
//this sets the text that is stored within the Node
void Node::setTextWithin(string text) {
    textWithin = text;
}
//this sets a boolean that stores information whether the Node is in a loop (with programme IF is considered Loop)
void Node::setIfLoop(bool in) {
    inLoop = in;
}
//this uses the inLoop varibles to check if Node is in a loop
bool Node::isInLoop() const {
    return inLoop;
}
//this checks the count of the number of nodes pointing to It. It is used to check if if node is closed as well
int Node::checkCount() {
    return pointCounter;
}
//used to increase the number of pointers to the node
void Node::IncreaseCount() {
    pointCounter++;
}

//used to decrement the number of pointers after they have been processed
void Node::DecreaseCount(){
    pointCounter--;
}
//this gets the number of the parent loop to the node. 0 if node is not in loop (start as default)
int Node::getParentLoop() {
    return parentLoop;
}
//set the index of the parent loop to the node.
void Node::setParentLoop(int n) {
    parentLoop = n;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
 * Convert FlowChart Function
 * It uses a stack that holds a pair of the node number and bool of whether it is the start of a node or the end
 *
 * */
void convertFlowChart(vector<Node> allNodes, vector<vector<int>> adjList)
{
    stack<pair<int, bool>> flowStack; //keeps the next programme in the flowchart to be put into pseudo code
    //prints out start to indicate beginning of programme
    cout<<"start"<<endl;
    flowStack.push({allNodes[adjList[0][1]].getNodeNumber(), true}); // pushes the first node pointed to by start

    //processes the rest of the flowChart
    while (!flowStack.empty()) {
        pair<int, bool> current = flowStack.top();
        flowStack.pop();
        //takes value of whether it is a start or not
        bool isStart = current.second;
        Node n; //node variable to keep node and allow for modifications of the nodes in the AllNodes vector


        //if the int in the pair is -1 it is the end of the first condition to a loop hence an ELSE part is to be processed
        if(current.first!=-1){
            n = allNodes[current.first];
        }
        else{
            Node newN(current.first,"ELSE","");
            n=newN;
        }

        //Start of conditions to check which type is being processed
        if (n.getType() == "IF") {
            if (isStart) {
                cout << "if(" << n.getTextWithin() << ")"<<endl<<"{" << endl;
                //push end

                flowStack.push({current.first, false});
                //push children
                for (int i = adjList[current.first].size()-1; (int)i > 0; i--) {
                   if(allNodes[adjList[current.first][i]].getType()=="BLOCK"){
                       allNodes[adjList[adjList[current.first][i]][1]].setIfLoop(true);
                       allNodes[adjList[adjList[current.first][i]][1]].setParentLoop(current.first);
                       allNodes[adjList[adjList[current.first][i]][1]].IncreaseCount();
                   }
               }
                vector<int> connected = adjList[current.first];
                flowStack.push({connected[2], true});
                if(connected.size()>2){
                    flowStack.push({-1, true});
                    flowStack.push({connected[1], true});
                }


            }
            else {

                if(!flowStack.empty() && (allNodes[flowStack.top().first].getNodeNumber() != 1)){
                    cout<<"}" <<endl<<endl;
                }
                else if(flowStack.empty() && allNodes[n.getNodeNumber()].checkCount() == 0){
                    cout << "}" << endl;
                }


            }
        }
        else if (n.getType() == "BLOCK") {
            if (isStart) {
                if(!(n.isInLoop() && allNodes[adjList[current.first][1]].getType()=="END")) {
                    cout << n.getTextWithin()<<endl;
                    allNodes[adjList[current.first][1]].DecreaseCount();
                }

                //push end
                flowStack.push({current.first, false });
                //push children
                vector<int> connected = adjList[current.first];
                for (int i = 1; (int)i < connected.size(); i++) {
                    flowStack.push({connected[i], true });
                }
            }
            else {
                if(current.first!=1){
                    if((n.isInLoop() && allNodes[adjList[current.first][1]].getType()=="END")&&n.checkCount()==0) {
                        cout<<"}"<<endl;
                        cout<<n.getTextWithin()<<endl;
                    }
                }
            }
        }
        else if (n.getType() == "END") {
            cout << " " <<endl;
        }
        else if(n.getType()=="ELSE"){
            if(isStart){
                cout<<"}"<<endl;
                cout <<"else" << endl;
                cout << "{" << endl;
            }
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

    string nodeNumber; //to store the number of the Node
    string nodeType; //to store node Type
    string nodeText; //to store nodeText


    //start Node input
    cin >> nodeNumber >> nodeType;
    allNodes[stoi(nodeNumber)].setNodeNumber(stoi(nodeNumber));
    allNodes[stoi(nodeNumber)].setType(nodeType);

    //read the rest of the Nodes in the FlowChart
    for(int i=1;i<numNodesInFlowChart-1;i++){
        cin >> nodeNumber >> nodeType >>nodeText;
        allNodes[i].setNodeNumber(stoi(nodeNumber));
        allNodes[i].setType(nodeType);
        allNodes[i].setTextWithin(nodeText);
    }

    //End node input
    cin>>nodeNumber>>nodeType;
    allNodes[stoi(nodeNumber)].setNodeNumber(stoi(nodeNumber));
    allNodes[stoi(nodeNumber)].setType(nodeType);

    // adjacency list to store the flow chart
    vector<vector<int>> adjList;

    //Reading the adjacency list
    string operation; //stores the line read

    while(getline(cin,operation)){ //while loop to separate the operation data using whitespace
        if(!operation.empty()){
            vector<int> newVector;
            size_t pos = 0;

            while(pos<operation.length()){
                size_t endpos = operation.find(' ',pos);

                if(endpos==string::npos){
                    endpos=operation.length();
                }
                string numstr = operation.substr(pos,endpos-pos);
                 if (!numstr.empty() && all_of(numstr.begin(), numstr.end(), ::isdigit)) {
                    int num = stoi(numstr);
                    newVector.push_back(num);
                }

                pos=endpos+1;
            }
            adjList.push_back(newVector);
        }else{
            cout << "Empty line" << endl;
        }

    }
    //prints out allNodes Vector
    for(auto c:allNodes){
        cout<<c.getNodeNumber()<<": "<<c.getType()<<" node";
        if(!c.getTextWithin().empty()){
            cout<<" - "<<c.getTextWithin();
            cout<<endl;
        }
        else{
            cout<<endl;
        }
    }
    //Prints out the AdjList Vector
    for(auto c:adjList){
        for(auto d:c){
            cout<<d<<" ";
        }
        cout<<endl;
    }

    //Convert FlowChart
    convertFlowChart(allNodes,adjList);
    return 0;
}