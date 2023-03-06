class Process {
public:
  process *next;     // pointer to next process
  int ID;            // process ID
  bool state = true; // blocked = false, ready = true

  // helper functions like constructor, destructor, getter and setters
};

class Semaphore {
public:
  int value; // semaphore value
  Queue<process> blockedQueue;

  Semaphore(int value) {
    this->value = value;
    // this->queue = new blockedQueue();
  }

  void signal() {
    value++;
    if (value <= 0) {
      process *process = blockedQueue.pop();
      if (process != NULL) {
        process->state = true;
      }
    }
  }

  void wait(process *process) {
    value--;
    if (value < 0) {
      process->state = false;
      blockedQueue.push(process);
      while (process->state == false)
        ;
    }
  }
};