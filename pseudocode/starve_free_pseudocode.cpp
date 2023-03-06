int resource = 1;                           // shared resource
int readcount = 0;                          // number of readers
Semaphore *mutex = new Semaphore(resource); // mutex lock for critical section
Semaphore *read_mutex = new Semaphore(resource);  // mutex lock for readcount
Semaphore *write_mutex = new Semaphore(resource); // mutex lock for writer

// This function is executed by the reader threads
void reader(process *process) {
  while (true) {
    mutex
        .wait(process)           // acquire mutex lock
        read_mutex.wait(process) // acquire read_mutex lock
        readcount++;             // increment the number of readers
    if (readcount == 1)          // if this is the first reader
      write_mutex
          .wait(process)       // acquire lock to shared resource
          read_mutex.signal(); // release read_mutex lock

    mutex.signal(); // release mutex lock

    /*************************/
    /*   CRITICAL SECTION   */
    /*************************/

    read_mutex.wait(process); // acquire read_mutex lock
    readcount--;              // decrement the number of readers
    if (readcount == 0)       // if this is the last reader
      write_mutex.signal();   // release lock to shared resource
    read_mutex.signal();      // release read_mutex lock
  }
}

// This function is executed by the writer threads
void writer(process *process) {
  while (true) {
    mutex.wait(process);       // acquire mutex lock
    write_mutex.wait(process); // acquire lock to shared resource
    mutex.signal();            // release mutex lock

    /*************************/
    /*   CRITICAL SECTION   */
    /*************************/

    write_mutex.signal(); // release lock to shared resource
  }
}