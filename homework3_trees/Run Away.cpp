{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <vector>\
#include <algorithm>\
#include <stack>\
using namespace std;\
int length = 0;\
class Tree \{\
private:\
    struct TreeNode \{\
        int parentIdx = -1;\
        vector<int> childIdxVector;\
        long long nodeDistance = 0;\
        long long deepestPath = -1; \
    \};\
\
    vector<TreeNode> nodeArray;\
    vector<int> activeNodeVector;\
    const int initialCapacity = 100; //empezamos con 100 para evitar problemas con la memory\
    const int maxCapacity = 10001; // 10000 nodes + 1 root\
\
public:\
    Tree() \{\
        nodeArray.resize(initialCapacity); //\
    \}\
\
    void addTreeNode(int parentIdx, int childIdx, int distance) \{ // anadir nuevos nodos, resize si llegan mas babies\
        if (childIdx >= nodeArray.size()) \{\
            if (nodeArray.size() < maxCapacity) \{\
                int newSize = min(maxCapacity, 2 * (int)nodeArray.size());\
                nodeArray.resize(newSize);\
            \}\
        \}\
\
        nodeArray[childIdx].parentIdx = parentIdx;\
        nodeArray[childIdx].nodeDistance = distance;\
        activeNodeVector.push_back(childIdx);\
\
        if (parentIdx != -1) \{          // llegaron los nietos papa\
            if (parentIdx >= nodeArray.size()) \{\
                if (nodeArray.size() < maxCapacity) \{\
                    int newSize = min(maxCapacity, 2 * (int)nodeArray.size());\
                    nodeArray.resize(newSize);\
                \}\
            \}\
\
            nodeArray[parentIdx].childIdxVector.push_back(childIdx);\
            activeNodeVector.push_back(parentIdx);\
        \}\
    \}\
\
    // quiero dormiIIIRRR\
    void initializeDeepestPath(int startIdx) \{  \
        stack<int> dfsStack;\
        vector<bool> visited(nodeArray.size(), false);\
        dfsStack.push(startIdx);\
\
        while (!dfsStack.empty()) \{\
            int nodeIdx = dfsStack.top();\
            if (!visited[nodeIdx]) \{\
                visited[nodeIdx] = true;\
                for (int i = nodeArray[nodeIdx].childIdxVector.size() - 1; i >= 0; --i) \{\
                    int childIdx = nodeArray[nodeIdx].childIdxVector[i];\
                    if (!visited[childIdx]) \{\
                        dfsStack.push(childIdx);\
                       // cout<<dfsStack.top()<<endl;\
                    \}\
                \}\
            \} else \{\
                dfsStack.pop();\
                nodeArray[nodeIdx].deepestPath = nodeArray[nodeIdx].nodeDistance;\
                for (size_t i = 0; i < nodeArray[nodeIdx].childIdxVector.size(); ++i) \{\
                    int childIdx = nodeArray[nodeIdx].childIdxVector[i];\
                    nodeArray[nodeIdx].deepestPath = max(nodeArray[nodeIdx].deepestPath, nodeArray[nodeIdx].nodeDistance + nodeArray[childIdx].deepestPath);\
                \}\
            \}\
        \}\
        nodeArray[startIdx].deepestPath = nodeArray[startIdx].nodeDistance;\
        for (size_t i = 0; i < nodeArray[startIdx].childIdxVector.size(); i++) \{\
            int childIdx = nodeArray[startIdx].childIdxVector[i];\
            nodeArray[startIdx].deepestPath = max(nodeArray[startIdx].deepestPath, nodeArray[startIdx].nodeDistance + nodeArray[childIdx].deepestPath);\
        \}\
    \}\
\
    void updateDeepestPathUpward(int startIdx) \{\
        int currentIdx = startIdx;\
        while (currentIdx != -1) \{\
            long long originalDeepest = nodeArray[currentIdx].deepestPath;\
            nodeArray[currentIdx].deepestPath = nodeArray[currentIdx].nodeDistance; // Reset to own distance\
\
            for (int childIdx : nodeArray[currentIdx].childIdxVector) \{\
                nodeArray[currentIdx].deepestPath = max(nodeArray[currentIdx].deepestPath, nodeArray[currentIdx].nodeDistance + nodeArray[childIdx].deepestPath);\
            \}\
\
            // If no change, break the loop early\
            if (originalDeepest == nodeArray[currentIdx].deepestPath) \{\
                break;\
            \}\
\
            // Move to the parent\
            currentIdx = nodeArray[currentIdx].parentIdx;\
        \}\
    \}\
\
    // Dioos auxilio :(\
    void check() \{\
        long long maxPathLength = -9223372036854775808;\
        int optimalRoot = -1;\
        for (size_t i = 0; i < activeNodeVector.size(); i++) \{\
            int nodeIdx = activeNodeVector[i];\
            long long largestDepth = 0, secondLargestDepth = 0;\
            for (size_t j = 0; j < nodeArray[nodeIdx].childIdxVector.size(); j++) \{\
                int childIdx = nodeArray[nodeIdx].childIdxVector[j];\
                long long currentDepth = nodeArray[childIdx].deepestPath;\
                if (currentDepth >= largestDepth) \{\
                    secondLargestDepth = largestDepth;\
                    largestDepth = currentDepth;\
                \} else if (currentDepth > secondLargestDepth) \{\
                    secondLargestDepth = currentDepth;\
                \}\
            \}\
            long long pathLength = largestDepth + secondLargestDepth + nodeArray[nodeIdx].nodeDistance;\
            if (pathLength > maxPathLength) \{\
                maxPathLength = pathLength;\
                optimalRoot = nodeIdx;\
            \}\
        \}\
        cout << "Maximum Value: " << maxPathLength << endl;\
        cout << "Root of the Path: " << optimalRoot << endl;\
    \}\
    //como check pero sin la suma\
    void finalRoot() \{\
        long long maxPathLength = -9223372036854775808;\
        int optimalRoot = -1;\
        for (size_t i = 0; i < activeNodeVector.size(); i++) \{\
            int nodeIdx = activeNodeVector[i];\
            long long largestDepth = 0, secondLargestDepth = 0;\
            for (size_t j = 0; j < nodeArray[nodeIdx].childIdxVector.size(); j++) \{\
                int childIdx = nodeArray[nodeIdx].childIdxVector[j];\
                long long currentDepth = nodeArray[childIdx].deepestPath;\
                if (currentDepth >= largestDepth) \{\
                    secondLargestDepth = largestDepth;\
                    largestDepth = currentDepth;\
                \} else if (currentDepth > secondLargestDepth) \{\
                    secondLargestDepth = currentDepth;\
                \}\
            \}\
            long long pathLength = largestDepth + secondLargestDepth + nodeArray[nodeIdx].nodeDistance;\
            if (pathLength > maxPathLength) \{\
                maxPathLength = pathLength;\
                optimalRoot = nodeIdx;\
            \}\
        \}\
        cout << "Final Root: " << optimalRoot << endl;\
    \}\
\
void addNode(int parentIdx, int childIdx, int distance) \{\
    if (childIdx >= nodeArray.size()) \{\
        if (nodeArray.size() < maxCapacity) \{\
            int newSize = min(maxCapacity, 2 * (int)nodeArray.size());\
            nodeArray.resize(newSize);\
        \}\
    \}\
\
    // el nuevo familiar\
    TreeNode newNode;\
    newNode.parentIdx = parentIdx;\
    newNode.nodeDistance = distance;\
    newNode.deepestPath = distance; // Initial deepest path is its own distance\
    nodeArray[childIdx] = newNode;\
	\
    if (find(activeNodeVector.begin(), activeNodeVector.end(), childIdx) == activeNodeVector.end()) \{\
        activeNodeVector.push_back(childIdx);\
    \}\
\
    // si solo esta el padrote\
    if (parentIdx != -1) \{\
        nodeArray[parentIdx].childIdxVector.push_back(childIdx);\
        // Make sure the parent is in activeNodeVector for recalculations\
        if (find(activeNodeVector.begin(), activeNodeVector.end(), parentIdx) == activeNodeVector.end()) \{\
            activeNodeVector.push_back(parentIdx);\
        \}\
        updateDeepestPathUpward(parentIdx);\
    \} else \{\
        updateDeepestPathUpward(childIdx);\
    \}\
\}\
\
\
\
void deleteNode(int idx) \{\
    // cout << nodeArray.size() << endl;\
    // Ensure the node index is within bounds and that the node has not been previously deleted or is the root with no parent.\
    if (idx < 0 || idx >= length || nodeArray[idx].parentIdx == -1) \{\
        //cout << "Sereno moreno" << endl;\
        return;\
    \}\
\
TreeNode& nodeToDelete = nodeArray[idx];  \
    int parentIdx = nodeToDelete.parentIdx;\
\
    //el abuelito: mas hijos :(\
    if (!nodeToDelete.childIdxVector.empty()) \{\
        for (size_t i = 0; i < nodeToDelete.childIdxVector.size(); i++) \{\
            int childIdx = nodeToDelete.childIdxVector[i];\
            nodeArray[childIdx].parentIdx = parentIdx;\
            if (parentIdx != -1) \{\
                nodeArray[parentIdx].childIdxVector.push_back(childIdx);\
            \}\
        \}\
    \}\
\
    //con el abuelito mijitos\
    if (parentIdx != -1) \{\
        vector<int>& siblings = nodeArray[parentIdx].childIdxVector;\
        siblings.erase(remove(siblings.begin(), siblings.end(), idx), siblings.end());\
        updateDeepestPathUpward(parentIdx);  // Update deepest path starting from the parent\
    \}\
\
    //echandolo de casa\
    nodeToDelete.childIdxVector.clear();\
    nodeToDelete.parentIdx = -1; // esta dead\
    nodeToDelete.nodeDistance = 0;\
    nodeToDelete.deepestPath = -1;    \
\
    // Remove the deleted node from activeNodeVector\
    activeNodeVector.erase(remove(activeNodeVector.begin(), activeNodeVector.end(), idx), activeNodeVector.end());\
\}\
\
// void print() \{\
//     cout<<length<<endl;\
//     cout << "Current Tree Structure:" << endl;\
//     for (size_t i = 0; i < length; ++i) \{\
//         if (nodeArray[i].parentIdx != -2) \{ // Check if the node has not been marked as deleted\
//             cout << "Node " << i << ": Distance = " << nodeArray[i].nodeDistance \
//                  << ", Deepest Path = " << nodeArray[i].deepestPath \
//                  << ", Parent = " << (nodeArray[i].parentIdx == -1 ? "None" : to_string(nodeArray[i].parentIdx)) \
//                  << ", Children = [";\
            \
//             // List children\
//             for (size_t j = 0; j < nodeArray[i].childIdxVector.size(); ++j) \{\
//                 cout << nodeArray[i].childIdxVector[j];\
//                 if (j < nodeArray[i].childIdxVector.size() - 1) \{\
//                     cout << ", ";\
//                 \}\
//             \}\
//             cout << "]" << endl;\
//         \}\
//     \}\
// \}\
\
\};\
\
\
int main() \{\
    int numberOfNodes, numberOfOperations;\
    cin >> numberOfNodes >> numberOfOperations;\
\
    Tree myTree;\
\
    int root, rootValue;\
    cin >> root >> rootValue;\
    myTree.addTreeNode(-1, root, rootValue);\
    length = 1;\
\
    for (int i = 0; i < numberOfNodes; i++) \{\
        int parentIdx, childIdx, distance;\
        cin >> parentIdx>>childIdx>>distance;\
        myTree.addTreeNode(parentIdx, childIdx, distance);\
        length++;\
        if (i== numberOfNodes -1 )\{\
            myTree.initializeDeepestPath(root);\
        \}\
    \}\
\
\
\
    for (int i = 0; i < numberOfOperations; i++) \{\
        string operation;\
        cin >> operation;\
        if (operation == "Check") \{\
            myTree.check();\
        \}\
\
        else if (operation == "Add")\{\
            int parentIdx, childIdx, distance;\
            cin >> parentIdx>>childIdx>>distance;\
            myTree.addNode(parentIdx, childIdx, distance);\
            length++;\
        \}\
\
        else if(operation == "Delete")\{\
            int nodeToDelete;\
            cin>>nodeToDelete;\
            myTree.deleteNode(nodeToDelete);\
\
        \}\
    \}\
\
    myTree.finalRoot();\
    // myTree.print();\
\
    return 0;\
\}\
}