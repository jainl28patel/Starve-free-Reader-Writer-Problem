int resource = 1;                           // shared resource
int readcount = 0;                          // number of readers
Semaphore *mutex = new Semaphore(resource); // mutex lock for critical section
Semaphore *read_mutex = new Semaphore(resource);  // mutex lock for readcount
Semaphore *write_mutex = new Semaphore(resource); // mutex lock for writer

// This function is executed by the reader threads
void reader(process *process) {
  while (true) {
    wait(mutex, process);         // acquire mutex lock
    wait(read_mutex, process);    // acquire read_mutex lock
    readcount++;                  // increment the number of readers
    if (readcount == 1)           // if this is the first reader
      wait(write_mutex, process); // acquire lock to shared resource
    signal(read_mutex);           // release read_mutex lock

    signal(mutex); // release mutex lock

    /*************************/
    /*   CRITICAL SECTION   */
    /*************************/

    wait(read_mutex);      // acquire read_mutex lock
    readcount--;           // decrement the number of readers
    if (readcount == 0)    // if this is the last reader
      signal(write_mutex); // release lock to shared resource
    signal(read_mutex);    // release read_mutex lock
  }
}

// This function is executed by the writer threads
void writer(process *process) {
  while (true) {
    wait(mutex, process);       // acquire mutex lock
    wait(write_mutex, process); // acquire lock to shared resource
    signal(mutex);              // release mutex lock

    /*************************/
    /*   CRITICAL SECTION   */
    /*************************/

    signal(write_mutex); // release lock to shared resource
  }
}