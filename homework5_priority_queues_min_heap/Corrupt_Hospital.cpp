{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <vector>\
#include <string>\
#include <tuple>\
#include <stdexcept>  \
\
using namespace std;\
\
struct PatientRecord \{\
    string fullName;\
    int years;\
    int financialStatus;\
    int memberLevel;\
    string enrollmentDate;\
    int entryOrder;\
\
    bool operator==(const PatientRecord& other) const \{\
        return tie(fullName, years, financialStatus, memberLevel, enrollmentDate, entryOrder) ==\
               tie(other.fullName, other.years, other.financialStatus, other.memberLevel, other.enrollmentDate, other.entryOrder);\
    \}\
\};\
\
template<typename T, typename Comparator>\
class CustomHeap \{\
public:\
    CustomHeap(Comparator comp) : comp(comp) \{\}\
\
    void insert(const T& value) \{\
        heapData.push_back(value);\
        heapifyUp(heapData.size() - 1);\
    \}\
\
    void removeTop() \{\
        if (!heapData.empty()) \{\
            swap(heapData[0], heapData.back());\
            heapData.pop_back();\
            heapifyDown(0);\
        \}\
    \}\
\
    T getTop() const \{\
        return heapData.front();\
    \}\
\
    bool isEmpty() const \{\
        return heapData.empty();\
    \}\
\
    size_t getSize() const \{\
        return heapData.size();\
    \}\
\
private:\
    vector<T> heapData;\
    Comparator comp;\
\
    void heapifyUp(int index) \{\
        while (index != 0) \{\
            int parentIndex = (index - 1) / 2;\
            if (comp(heapData[parentIndex], heapData[index])) \{\
                swap(heapData[parentIndex], heapData[index]);\
                index = parentIndex;\
            \} else \{\
                break;\
            \}\
        \}\
    \}\
\
    void heapifyDown(int index) \{\
        int leftChild = 2 * index + 1;\
        int rightChild = 2 * index + 2;\
        int largest = index;\
\
        if (leftChild < heapData.size() && comp(heapData[largest], heapData[leftChild])) \{\
            largest = leftChild;\
        \}\
        if (rightChild < heapData.size() && comp(heapData[largest], heapData[rightChild])) \{\
            largest = rightChild;\
        \}\
        if (largest != index) \{\
            swap(heapData[largest], heapData[index]);\
            heapifyDown(largest);\
        \}\
    \}\
\};\
\
template<typename T, typename Comparator>\
class QuickSelect \{\
public:\
    QuickSelect(Comparator comp) : comp(comp) \{\}\
\
    T select(vector<T>& data, int k) \{\
        if (k < 0 || k >= data.size()) \{\
            throw out_of_range("k is out of range");\
        \}\
        quickSelect(data, 0, data.size() - 1, k);\
        return data[k];\
    \}\
\
private:\
    Comparator comp;\
\
    void quickSelect(vector<T>& data, int left, int right, int k) \{\
        while (left <= right) \{\
            int pivotIndex = partition(data, left, right);\
            if (pivotIndex == k) \{\
                return;\
            \} else if (pivotIndex < k) \{\
                left = pivotIndex + 1;\
            \} else \{\
                right = pivotIndex - 1;\
            \}\
        \}\
    \}\
\
    int partition(vector<T>& data, int left, int right) \{\
        int pivotIndex = left + rand() % (right - left + 1);\
        T pivotValue = data[pivotIndex];\
        swap(data[pivotIndex], data[right]);\
        int storeIndex = left;\
\
        for (int i = left; i < right; i++) \{\
            if (comp(data[i], pivotValue)) \{\
                swap(data[i], data[storeIndex]);\
                storeIndex++;\
            \}\
        \}\
        swap(data[storeIndex], data[right]);\
        return storeIndex;\
    \}\
\};\
\
class Hospital \{\
public:\
    Hospital(int numPatients, int numDays) : numPatients(numPatients), numDays(numDays) \{\}\
\
    void addNewPatient(const string& name, int age, int money, int membership, const string& joinDate, int order) \{\
        allPatients.push_back(\{ name, age, money, membership, joinDate, order \});\
    \}\
\
    void DailyOperations(int P, int X, int K, vector<PatientRecord>& newAdmissions) \{\
        addNewAdmissions(newAdmissions);\
        cout << "DAY #" << dayNumber << endl;\
\
        vector<PatientRecord> treatedPandaPatients = PandaHospital(X);\
        int dailyIncome = calculateDailyIncome(treatedPandaPatients);\
        cout << "INCOME TODAY: " << dailyIncome << endl;\
\
        if (!allPatients.empty() && treatedPandaPatients.size() == X && K > 0) \{\
            BearHospital(K);\
        \}\
\
        dayNumber++;\
    \}\
\
private:\
    int numPatients, numDays;\
    int dayNumber = 1;\
    vector<PatientRecord> allPatients;\
\
    void addNewAdmissions(vector<PatientRecord>& newAdmissions) \{\
        int highestOrder = getHighestEntryOrder();\
        for (auto& patient : newAdmissions) \{\
            patient.entryOrder = ++highestOrder;\
            allPatients.push_back(patient);\
        \}\
    \}\
\
    int getHighestEntryOrder() const \{\
        int highestOrder = -1;\
        for (const auto& patient : allPatients) \{\
            if (patient.entryOrder > highestOrder) \{\
                highestOrder = patient.entryOrder;\
            \}\
        \}\
        return highestOrder;\
    \}\
\
    int calculateDailyIncome(const vector<PatientRecord>& treatedPandaPatients) const \{\
        int dailyIncome = 0;\
        for (const auto& p : treatedPandaPatients) \{\
            cout << p.fullName << " " << p.years << endl;\
            dailyIncome += p.financialStatus * 0.9;\
        \}\
        return dailyIncome;\
    \}\
\
    vector<PatientRecord> PandaHospital(int X) \{\
        // cout << "PandaHospital: X = " << X << ", allPatients.size() = " << allPatients.size() << endl;\
\
        if (allPatients.size() <= X) \{\
            vector<PatientRecord> treatedPandaPatients = allPatients;\
            CustomHeap<PatientRecord, decltype(&Hospital::PandaHeapComparator)> pandaHeap\{Hospital::PandaHeapComparator\};\
            for (const auto& patient : treatedPandaPatients) \{\
                pandaHeap.insert(patient);\
            \}\
            treatedPandaPatients.clear();\
            while (!pandaHeap.isEmpty()) \{\
                treatedPandaPatients.push_back(pandaHeap.getTop());\
                pandaHeap.removeTop();\
            \}\
            allPatients.clear();\
            return treatedPandaPatients;\
        \}\
\
        if (X > 0) \{\
            // cout << "Before QuickSelect - Size: " << allPatients.size() << ", X: " << X << endl;\
            QuickSelect<PatientRecord, decltype(&Hospital::PandaQuickSelectComparator)> quickSelect(PandaQuickSelectComparator);\
            quickSelect.select(allPatients, X - 1);\
            // cout << "After QuickSelect - Size: " << allPatients.size() << ", X: " << X << endl;\
        \}\
\
        CustomHeap<PatientRecord, decltype(&Hospital::PandaHeapComparator)> pandaHeap\{Hospital::PandaHeapComparator\};\
        for (int i = 0; i < X; ++i) \{\
            pandaHeap.insert(allPatients[i]);\
        \}\
        vector<PatientRecord> treatedPandaPatients;\
        while (!pandaHeap.isEmpty()) \{\
            treatedPandaPatients.push_back(pandaHeap.getTop());\
            pandaHeap.removeTop();\
        \}\
        allPatients.erase(allPatients.begin(), allPatients.begin() + X);\
        return treatedPandaPatients;\
    \}\
\
    void BearHospital(int K) \{\
        // cout << "BearHospital: K = " << K << ", allPatients.size() = " << allPatients.size() << endl;\
\
        if (K == 0) \{\
            return;  // No patients to send to Bear Hospital if K is 0\
        \}\
\
        if (allPatients.size() <= K) \{\
            CustomHeap<PatientRecord, decltype(&Hospital::BearHeapComparator)> bearHeap\{Hospital::BearHeapComparator\};\
            for (const auto& patient : allPatients) \{\
                bearHeap.insert(patient);\
            \}\
            vector<PatientRecord> treatedBearPatients;\
            while (!bearHeap.isEmpty()) \{\
                treatedBearPatients.push_back(bearHeap.getTop());\
                bearHeap.removeTop();\
            \}\
            allPatients.clear();\
            return;\
        \}\
\
        // cout << "Before QuickSelect - Size: " << allPatients.size() << ", K: " << K << endl;\
        QuickSelect<PatientRecord, decltype(&Hospital::BearQuickSelectComparator)> quickSelect(BearQuickSelectComparator);\
        quickSelect.select(allPatients, K - 1);\
        // cout << "After QuickSelect - Size: " << allPatients.size() << ", K: " << K << endl;\
\
        CustomHeap<PatientRecord, decltype(&Hospital::BearHeapComparator)> bearHeap\{Hospital::BearHeapComparator\};\
        for (int i = 0; i < K; ++i) \{\
            bearHeap.insert(allPatients[i]);\
        \}\
        vector<PatientRecord> treatedBearPatients;\
        while (!bearHeap.isEmpty()) \{\
            treatedBearPatients.push_back(bearHeap.getTop());\
            bearHeap.removeTop();\
        \}\
        allPatients.erase(allPatients.begin(), allPatients.begin() + K);\
    \}\
\
    static bool PandaHeapComparator(const PatientRecord &a, const PatientRecord &b) \{\
        if (a.memberLevel != b.memberLevel)\
            return a.memberLevel < b.memberLevel; \
        if (a.enrollmentDate != b.enrollmentDate)\
            return a.enrollmentDate > b.enrollmentDate; \
        if (a.fullName != b.fullName)\
            return a.fullName > b.fullName; \
        return a.entryOrder > b.entryOrder; \
    \}\
\
    static bool BearHeapComparator(const PatientRecord &a, const PatientRecord &b) \{\
        if (a.financialStatus != b.financialStatus)\
            return a.financialStatus < b.financialStatus; \
        return a.entryOrder > b.entryOrder; \
    \}\
\
    static bool PandaQuickSelectComparator(const PatientRecord &a, const PatientRecord &b) \{\
        if (a.memberLevel != b.memberLevel)\
            return a.memberLevel > b.memberLevel; \
        if (a.enrollmentDate != b.enrollmentDate)\
            return a.enrollmentDate < b.enrollmentDate; \
        if (a.fullName != b.fullName)\
            return a.fullName < b.fullName; \
        return a.entryOrder < b.entryOrder; \
    \}\
\
    static bool BearQuickSelectComparator(const PatientRecord &a, const PatientRecord &b) \{\
        if (a.financialStatus != b.financialStatus)\
            return a.financialStatus > b.financialStatus; \
        return a.entryOrder < b.entryOrder; \
    \}\
\};\
\
int main() \{\
    int numPatients, numDays;\
    cin >> numPatients >> numDays;\
    Hospital hospitalManager(numPatients, numDays);\
\
    cin.ignore(); \
\
    for (int i = 0; i < numPatients; i++) \{\
        string name;\
        getline(cin, name);\
        int age, money, membership;\
        string joinDate;\
        cin >> age >> money >> membership >> joinDate;\
        cin.ignore(); \
        hospitalManager.addNewPatient(name, age, money, membership, joinDate, i);\
    \}\
\
    for (int day = 1; day <= numDays; day++) \{\
        int P, X, K;\
        cin >> P >> X >> K;\
        cin.ignore(); \
        vector<PatientRecord> newAdmissions;\
        for (int i = 0; i < P; i++) \{\
            string name;\
            getline(cin, name);\
            int age, money, membership;\
            string joinDate;\
            cin >> age >> money >> membership >> joinDate;\
            cin.ignore(); \
            newAdmissions.push_back(\{ name, age, money, membership, joinDate, 0 \});\
        \}\
\
        hospitalManager.DailyOperations(P, X, K, newAdmissions);\
    \}\
\
    return 0;\
\}\
}