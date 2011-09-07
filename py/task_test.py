import thread

def task(id):
  print "task"

done = thread.allocate_lock()
thread.start_new_thread(task, (0,))
done.acquire()
print "main"
