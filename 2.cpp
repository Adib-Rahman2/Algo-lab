#include <iostream>
using namespace std;

struct Activity {
    int start;
    int finish;
};

int duration(Activity a) {
    return a.finish - a.start;
}

void mergeByFinish(Activity a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Activity L[n1];
    Activity R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i].finish <= R[j].finish) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortByFinish(Activity a[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSortByFinish(a, left, mid);
    mergeSortByFinish(a, mid + 1, right);

    mergeByFinish(a, left, mid, right);
}

void mergeByDuration(Activity a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Activity L[n1];
    Activity R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (duration(L[i]) <= duration(R[j])) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortByDuration(Activity a[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSortByDuration(a, left, mid);
    mergeSortByDuration(a, mid + 1, right);

    mergeByDuration(a, left, mid, right);
}

int main() {
    int n;

    cout << "Enter number of activities: ";
    cin >> n;

    Activity activities[n];

    cout << "Enter start and finish times:\n";

    for (int i = 0; i < n; i++) {
        cin >> activities[i].start >> activities[i].finish;
    }

    mergeSortByFinish(activities, 0, n - 1);

    cout << "\nActivities sorted by finish time:\n";

    for (int i = 0; i < n; i++) {
        cout << "(" << activities[i].start << ", " << activities[i].finish << ")" << "\n";
    }

    cout << "\nSelected activities using finish time:\n";

    int lastFinish1 = activities[0].finish;
    int count1 = 1;

    cout << "(" << activities[0].start << ", " << activities[0].finish << ")\n";

    for (int i = 1; i < n; i++) {
        if (activities[i].start >= lastFinish1) {
            cout << "(" << activities[i].start << ", " << activities[i].finish << ")\n";

            lastFinish1 = activities[i].finish;
            count1++;
        }
    }

    cout << "Total number of selected activities: " << count1 << endl;

    mergeSortByDuration(activities, 0, n - 1);

    cout << "\nActivities sorted by duration:\n";

    for (int i = 0; i < n; i++) {
        cout << "(" << activities[i].start << ", " << activities[i].finish << ")" << "\n";
    }

    cout << "\nSelected activities using duration:\n";

    int lastFinish2 = -1;
    int count2 = 0;

    for (int i = 0; i < n; i++) {
        if (activities[i].start >= lastFinish2) {
            cout << "(" << activities[i].start << ", " << activities[i].finish << ")"  << "\n";

            lastFinish2 = activities[i].finish;
            count2++;
        }
    }

    cout << "Total number of selected activities: " << count2 << endl;

    return 0;
}