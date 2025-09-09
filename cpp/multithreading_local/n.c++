#include <iostream>
#include <future>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

queue<packaged_task<int()>> tasks;
mutex m;
condition_variable cv;
bool done = false;

void worker() {
    while (true) {
        packaged_task<int()> task;
        {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [] { return !tasks.empty() || done; });
            if (done && tasks.empty()) break;
            task = move(tasks.front());
            tasks.pop();
        }
        task(); // run the task
    }
}

int main() {
    // Start worker thread
    thread t(worker);

    // Submit some tasks
    vector<future<int>> results;
    for (int i = 1; i <= 5; i++) {
        packaged_task<int()> task([i] {
            this_thread::sleep_for(chrono::seconds(2));
            return i * i;
        });
        results.push_back(task.get_future());

        {
            lock_guard<mutex> lock(m);
            tasks.push(move(task));
        }
        cv.notify_one();
    }

    // Signal worker to finish after tasks
    {
        lock_guard<mutex> lock(m);
        done = true;
    }
    cv.notify_all();

    // Collect results
    for (auto& f : results) {
        cout << "Result: " << f.get() << endl;
    }

    t.join();
}
