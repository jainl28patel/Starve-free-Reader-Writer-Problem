class Process {
public:
  process *next;     // pointer to next process
  int ID;            // process ID
  bool state = true; // blocked = false, ready = true

  // helper functions like constructor, destructor, getter and setters
};

class Semaphore {
public:
  int value;           // semaphore value
  blockedQueue *queue; // queue of blocked processes

  Semaphore(int value) {
    this->value = value;
    this->queue = new blockedQueue();
  }
};

void signal(Semaphore *semaphore) {
  semaphore->value++;
  if (semaphore->value <= 0) {
    process* process = semaphore->queue->pop();
    if (process != NULL) {
      process->state = true;
    }
  }
}

void wait(Semaphore *semaphore, process *process) {
  semaphore->value--;
  if (semaphore->value < 0) {
    process->state = false;
    semaphore->queue->push(process);
    while (process->state == false)
      ;
  }
}