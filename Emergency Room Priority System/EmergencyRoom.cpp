#include "EmergencyRoom.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <queue>

using namespace std;

void EmergencyRoom::heapifyUp(int childIndex)
{
    if (childIndex <= 0)
        return;

    int parentIndex = (childIndex - 1) / 2;

    // If the child is larger than its parent, swap and continue upward
    if (heap[childIndex] > heap[parentIndex])
    {
        swap(heap[childIndex], heap[parentIndex]);
        heapifyUp(parentIndex);
    }
}

void EmergencyRoom::heapifyDown(int parentIndex)
{
    int leftChildIndex = 2 * parentIndex + 1;  // l = 2i (for 1's indexing basis)
    int rightChildIndex = 2 * parentIndex + 2; // r = 2i + 1 (for 1's indexing basis)
    int largestNodeIndex = parentIndex;

    // Check if the left child exists and is larger than the current largest
    if (leftChildIndex < (int)heap.size() && heap[leftChildIndex] > heap[largestNodeIndex])
    {
        largestNodeIndex = leftChildIndex;
    }

    // Check if the right child exists and is larger than the current largest
    if (rightChildIndex < (int)heap.size() && heap[rightChildIndex] > heap[largestNodeIndex])
    {
        largestNodeIndex = rightChildIndex;
    }

    // If the largest is not the parent, swap them and continue heapifying downward
    if (largestNodeIndex != parentIndex)
    {
        swap(heap[parentIndex], heap[largestNodeIndex]);
        heapifyDown(largestNodeIndex);
    }
}

void EmergencyRoom::printPatientData(Patient patient) const
{
    cout << "id: " << patient.id << endl;
    cout << "Name: " << patient.name << endl;
    cout << "Arrival time: " << patient.arrivalTime << endl;
    cout << "severity: " << patient.severity << endl;
}

EmergencyRoom::EmergencyRoom() {}

void EmergencyRoom::insert(Patient newPatient)
{
    heap.push_back(newPatient);
    heapifyUp((int)heap.size() - 1);
}

void EmergencyRoom::treatNext()
{
    if (heap.empty())
    {
        cout << "The Emergency room is empty\n";
        return;
    }

    Patient treated = heap[0];

    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty())
        heapifyDown(0);

    cout << "\n========================================================\n";
    cout << "=================The patient that treated===============\n";
    printPatientData(treated);
    cout << "========================================================\n";
}

void EmergencyRoom::viewNext() const
{
    if (heap.empty())
    {
        cout << "The Emergency room is empty\n";
        return;
    }

    Patient next = heap[0];

    cout << "\n========================================================\n";
    cout << "==============The patient that next treated==============\n";
    printPatientData(next);
    cout << "========================================================\n";
}

void EmergencyRoom::updateSeverity(int patientId, int newSeverity)
{
    for (int i = 0; i < (int)heap.size(); i++)
    {
        if (heap[i].id == patientId)
        {
            if (newSeverity > heap[i].severity)
            {
                heap[i].severity = newSeverity;
                heapifyUp(i);
                return;
            }

            else if (newSeverity < heap[i].severity)
            {
                heap[i].severity = newSeverity;
                heapifyDown(i);
                return;
            }

            return;
        }
    }
}

void EmergencyRoom::displayAllPatients() const
{
    if (heap.empty())
        return;

    cout << "\n========================================================\n";
    cout << "========================Patients========================\n";

    queue<int> q;
    q.push(0);

    while (!q.empty())
    {

        int currentIndex = q.front();
        q.pop();

        printPatientData(heap[currentIndex]);

        int leftChildIndex = 2 * currentIndex + 1;
        int rightChildIndex = 2 * currentIndex + 2;

        if (leftChildIndex < (int)heap.size())
            q.push(leftChildIndex);

        if (rightChildIndex < (int)heap.size())
            q.push(rightChildIndex);
    }
    cout << "========================================================\n";
}

EmergencyRoom::~EmergencyRoom() {}