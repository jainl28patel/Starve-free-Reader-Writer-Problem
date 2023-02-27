class Process {
public:
  process *next;     // pointer to next process
  int ID;            // process ID
  bool state = true; // blocked = false, ready = true

  // helper functions like constructor, destructor, getter and setters
};

class blockedQueue {
  int size = 0;
  process *front, *back;

public:
  void push(int id) {
    process *newProcess = new process(id);
    if (size == 0) {
      front = back = newProcess;
    } else {
      back->next = newProcess;
      back = newProcess;
    }
    size++;
  }

  process *pop() {
    if (size == 0) {
      return NULL;
    }
    process *temp = front;
    front = front->next;
    size--;
    return temp;
  }
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

void wakeup(Semaphore *semaphore) {
  process *process = semaphore->queue->pop();
  if (process != NULL) {
    process->state = true;
  }
}

void signal(Semaphore *semaphore) {
  semaphore->value++;
  if (semaphore->value <= 0) {
    wakeup(semaphore.blockedQueue.pop());
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