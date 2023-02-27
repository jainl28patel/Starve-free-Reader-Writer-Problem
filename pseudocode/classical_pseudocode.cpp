// This function is executed by the reader threads
void reader() {
  while (true) {
    wait(mutex);        // acquire mutex lock
    readcount++;        // increment the number of readers
    if (readcount == 1) // if this is the first reader
      wait(db);         // acquire lock to shared resource
    signal(mutex);      // release mutex lock

    /*************************/
    /*   CRITICAL SECTION   */
    /*************************/

    wait(mutex);        // acquire mutex lock
    readcount--;        // decrement the number of readers
    if (readcount == 0) // if this is the last reader
      signal(db);       // release lock to shared resource
    signal(mutex);      // release mutex lock
  }
}

// This function is executed by the writer threads
void writer() {
  while (true) {
    wait(db); // acquire lock to shared resource

    /*************************/
    /*   CRITICAL SECTION   */
    /*************************/

    signal(db); // release lock to shared resource
  }
}