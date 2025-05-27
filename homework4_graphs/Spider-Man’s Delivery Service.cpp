{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <vector>\
#include <queue>\
#include <climits>\
#include <algorithm>\
\
using namespace std;\
\
struct Edge \{\
    int to;\
    int distance;\
    int capacity;\
\};\
\
struct Order \{\
    int id;\
    int src;\
    int dst;\
    int ts;\
    int traffic;\
    int totalDistance;\
    bool waiting;  \
    vector<int> pathToSource;\
    vector<int> pathToDestination;\
    bool completed;\
    int DriverID;\
\};\
\
struct Driver \{\
    int id;\
    int location;\
    bool available;\
\};\
\
struct Graph \{\
    int V;\
    vector<vector<Edge>> adj;\
    vector<vector<int>> trafficMap;\
\
    Graph(int vertices) : V(vertices) \{\
        adj.resize(vertices + 1);\
        trafficMap.resize(vertices + 1, vector<int>(vertices + 1, -1));\
    \}\
\
    void addEdge(int u, int v, int distance, int capacity) \{\
        adj[u].push_back(\{v, distance, capacity\});\
        adj[v].push_back(\{u, distance, capacity\});\
        trafficMap[u][v] = capacity;\
        trafficMap[v][u] = capacity;\
    \}\
\
 bool dijkstra(int src, int dst, int ts, int &distance, vector<int> &path) \{\
    vector<int> dist(V + 1, INT_MAX);\
    vector<int> parent(V + 1, -1);\
    vector<bool> visited(V + 1, false);\
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;\
\
    dist[src] = 0;\
    pq.push(\{0, src\});\
\
    while (!pq.empty()) \{\
        int u = pq.top().second;\
        pq.pop();\
\
        if (visited[u]) continue;\
        visited[u] = true;\
\
        // Manually sort neighbors by node id\
        vector<Edge> neighbors = adj[u];\
        for (int i = 0; i < neighbors.size(); ++i) \{\
            for (int j = i + 1; j < neighbors.size(); ++j) \{\
                if (neighbors[i].to > neighbors[j].to) \{\
                    swap(neighbors[i], neighbors[j]);\
                \}\
            \}\
        \}\
\
        for (auto &edge : neighbors) \{\
            int v = edge.to;\
            int weight = edge.distance;\
            int edgeCapacity = trafficMap[u][v];\
\
            if (!visited[v] && dist[u] + weight < dist[v] && edgeCapacity >= ts) \{\
                dist[v] = dist[u] + weight;\
                parent[v] = u;\
                pq.push(\{dist[v], v\});\
                // cout << "Exploring node " << v << " from node " << u << " with distance " << dist[v] << endl;\
            \}\
        \}\
    \}\
\
    if (dist[dst] == INT_MAX) \{\
        // cout << "No valid path found." << endl;\
        return false;\
    \}\
\
    distance = dist[dst];\
    int node = dst;\
    while (node != -1) \{\
        path.push_back(node);\
        node = parent[node];\
    \}\
    custom_reverse(path);\
    // cout << "Path found: from selecting ";\
    // for (int n : path) \{\
    //     cout << n << " ";\
    // \}\
    // cout << endl;\
    return true;\
\}\
bool customDijkstra(int src, int ts, int &distance, int &closestDriver, vector<vector<Driver>> &drivers, vector<int> &path) \{\
    vector<int> dist(V + 1, INT_MAX);\
    vector<int> parent(V + 1, -1);\
    vector<bool> visited(V + 1, false);\
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;\
\
    dist[src] = 0;\
    pq.push(\{0, src\});\
\
    // Check if there is a driver at the source node immediately\
    for (auto &driver : drivers[src]) \{\
        if (driver.available && driver.location == src) \{\
            distance = 0;\
            closestDriver = driver.id;\
            path.push_back(src);\
            return true;\
        \}\
    \}\
\
    int driverNode = -1;\
\
    while (!pq.empty()) \{\
        int u = pq.top().second;\
        pq.pop();\
\
        if (visited[u]) continue;\
        visited[u] = true;\
\
        // Manually sort neighbors by node id\
        vector<Edge> neighbors = adj[u];\
        sort(neighbors.begin(), neighbors.end(), [](const Edge &a, const Edge &b) \{\
            return a.to < b.to;\
        \});\
\
        for (auto &edge : neighbors) \{\
            int v = edge.to;\
            int weight = edge.distance;\
            int edgeCapacity = trafficMap[u][v];\
\
            if (!visited[v] && dist[u] + weight < dist[v] && edgeCapacity >= ts) \{\
                dist[v] = dist[u] + weight;\
                parent[v] = u;\
                pq.push(\{dist[v], v\});\
\
                // Check for a driver at this node\
                for (auto &driver : drivers[v]) \{\
                    if (driver.available) \{\
                        if (closestDriver == -1 || dist[v] < distance) \{\
                            distance = dist[v];\
                            closestDriver = driver.id;\
                            driverNode = v;  // Track the node where the closest driver is found\
                        \}\
                    \}\
                \}\
            \}\
        \}\
    \}\
\
    if (closestDriver == -1) \{\
        cout << "Just Walk. T-T" << endl;\
        return false;\
    \}\
\
    int node = driverNode;\
    while (node != -1) \{\
        path.push_back(node);\
        node = parent[node];\
    \}\
    reverse(path.begin(), path.end());  // Use the standard library reverse function\
\
    // cout << "Path found: main ";\
    // for (int n : path) \{\
    //     cout << n << " ";\
    // \}\
    // cout << endl;\
\
    return true;\
\}\
\
    void custom_reverse(vector<int> &path) \{ // Custom reverse function\
        int n = path.size();\
        for (int i = 0; i < n / 2; ++i) \{\
            swap(path[i], path[n - i - 1]);\
        \}\
    \}\
\};\
\
void reserveTrafficSpace(Graph &graph, const vector<int> &path, int ts) \{\
    for (int i = 0; i < path.size() - 1; ++i) \{\
        int u = path[i];\
        int v = path[i + 1];\
        graph.trafficMap[u][v] -= ts;\
        graph.trafficMap[v][u] -= ts;\
    \}\
\}\
\
void releaseTrafficSpace(Graph &graph, const vector<int> &path, int ts) \{\
    for (int i = 0; i < path.size() - 1; ++i) \{\
        int u = path[i];\
        int v = path[i + 1];\
        graph.trafficMap[u][v] += ts;\
        graph.trafficMap[v][u] += ts;\
    \}\
\}\
void processOrder(int id, int src, int ts, Graph &graph, vector<vector<Driver>> &drivers, vector<Order> &orders) \{\
    int closestDriver = -1;\
    int minDist = INT_MAX;\
    vector<int> tempPath;\
\
    // Use customDijkstra to find the closest driver\
    if (graph.customDijkstra(src, ts, minDist, closestDriver, drivers, tempPath)) \{\
        // cout<<"selected driver is "<<closestDriver<<endl;\
        int driverLocation = -1;\
        for (auto &driverList : drivers) \{\
            for (auto &driver : driverList) \{\
                if (driver.id == closestDriver) \{\
                    driver.available = false;\
                    driverLocation = driver.location;\
                    driver.location = src; // Move driver to the source location\
                    break;\
                \}\
            \}\
        \}\
        orders.push_back(\{id, src, -1, ts, ts, minDist, false, tempPath, \{\}, false, closestDriver\});\
        reserveTrafficSpace(graph, tempPath, ts);\
    cout << "Order " << id << " from: " << driverLocation << endl;\
    // for (int n : tempPath) \{\
    //     cout << n << " ";\
    // \}\
    // cout << endl;\
\
    \}\
\}\
\
void processDrop(int id, int dst, Graph &graph, vector<Order> &orders) \{\
    for (auto &order : orders) \{\
        if (order.id == id) \{\
            order.dst = dst;\
\
            // Release traffic space from the driver's initial location to the source of the order\
            releaseTrafficSpace(graph, order.pathToSource, order.ts);\
\
            vector<int> path;\
            int distance;\
            if (graph.dijkstra(order.src, dst, order.ts, distance, path)) \{\
                order.totalDistance += distance;\
                order.pathToDestination = path;\
                reserveTrafficSpace(graph, path, order.ts);\
                cout << "Order " << id << " distance: " << order.totalDistance << endl;\
                // cout << "Path: ";\
                // for (int node : path) \{\
                //     cout << node << " ";\
                // \}\
                // cout << "\\nDistance: " << distance << endl;\
            \} else \{\
                cout << "No Way Home" << endl;\
                order.waiting = true;  // Mark the order as waiting\
            \}\
            break;\
        \}\
    \}\
\}\
\
void processComplete(int id, Graph &graph, vector<vector<Driver>> &drivers, vector<Order> &orders) \{\
    for (int i = 0; i < orders.size(); ++i) \{\
        if (orders[i].id == id) \{\
            Order &order = orders[i];\
\
            // Releasing traffic space reserved for the order\
            releaseTrafficSpace(graph, order.pathToDestination, order.ts);\
\
            // Find and update the specific driver assigned to this order\
        for (auto &driverList : drivers) \{\
            for (auto &driver : driverList) \{\
                if (driver.id == order.DriverID) \{\
                    driver.available = true;\
                    driver.location = order.dst;\
                    // cout << "Driver " << driver.id << " at node " << driver.location << " is now available." << endl;\
                    break;\
                \}\
            \}\
        \}\
\
            // Collect waiting orders\
            vector<Order*> waitingOrders;\
            for (auto &waitingOrder : orders) \{\
                if (waitingOrder.waiting && waitingOrder.dst != -1) \{\
                    waitingOrders.push_back(&waitingOrder);\
                \}\
            \}\
\
            // Manually sort waiting orders by ID\
            for (int i = 0; i < waitingOrders.size(); ++i) \{\
                for (int j = i + 1; j < waitingOrders.size(); ++j) \{\
                    if (waitingOrders[i]->id > waitingOrders[j]->id) \{\
                        swap(waitingOrders[i], waitingOrders[j]);\
                    \}\
                \}\
            \}\
\
            for (auto &waitingOrder : waitingOrders) \{\
                vector<int> path;\
                int distance;\
                if (graph.dijkstra(waitingOrder->src, waitingOrder->dst, waitingOrder->ts, distance, path)) \{\
                    waitingOrder->totalDistance += distance;\
                    waitingOrder->waiting = false;\
                    waitingOrder->pathToDestination = path;\
                    reserveTrafficSpace(graph, path, waitingOrder->ts);\
                    cout << "Order " << waitingOrder->id << " distance: " << waitingOrder->totalDistance << endl;\
                \} else \{\
                    continue;\
                \}\
            \}\
\
            order.completed = true;\
        \}\
    \}\
\}\
\
\
void printGraph(const Graph &graph, const vector<vector<Driver>> &drivers) \{\
    cout << "Graph details:" << endl;\
\
    for (int u = 1; u <= graph.V; ++u) \{\
        bool hasEdges = false;\
        for (const auto &edge : graph.adj[u]) \{\
            int v = edge.to;\
            int distance = edge.distance;\
            int trafficSpace = graph.trafficMap[u][v];\
\
            cout << "From node " << u << " to node " << v << ": distance = " << distance \
                 << ", traffic space available = " << trafficSpace << " units" << endl;\
            hasEdges = true;\
        \}\
    \}\
\
    // Print updated driver information\
    cout << "Driver locations:" << endl;\
    for (int u = 1; u < drivers.size(); ++u) \{\
        for (const auto &driver : drivers[u]) \{\
            cout << "Driver ID: " << driver.id << " is at node " << driver.location <<" and is "<<driver.available<< endl;\
        \}\
    \}\
\}\
\
int main() \{\
    int V, E, D;\
    cin >> V >> E >> D;\
\
    Graph graph(V);\
    vector<vector<Driver>> drivers(V + 1);\
    vector<Order> orders;\
    int driverCount = 1;\
\
    for (int i = 0; i < D; i++) \{\
        string place;\
        int v, c;\
        cin >> place >> v >> c;\
        for (int j = 0; j < c; j++) \{\
            drivers[v].push_back(\{driverCount++, v, true\});\
        \}\
    \}\
\
    for (int i = 0; i < E; i++) \{\
        string edge;\
        int s, d, dis, t;\
        cin >> edge >> s >> d >> dis >> t;\
        graph.addEdge(s, d, dis, t);\
    \}\
\
    int C;\
    cin >> C;\
    for (int i = 0; i < C; i++) \{\
        string command;\
        cin >> command;\
\
        if (command == "Order") \{\
            int id, src, ts;\
            cin >> id >> src >> ts;\
            processOrder(id, src, ts, graph, drivers, orders);\
        \} else if (command == "Drop") \{\
            int id, dst;\
            cin >> id >> dst;\
            processDrop(id, dst, graph, orders);\
        \} else if (command == "Complete") \{\
            int id;\
            cin >> id;\
            processComplete(id, graph, drivers, orders);\
        \} else if (command == "PrintTraffic") \{\
            printGraph(graph, drivers);\
        \}\
    \}\
\
    return 0;\
\}\
}