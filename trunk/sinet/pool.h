#ifndef SINET_POOL_H
#define SINET_POOL_H

#include "api_base.h"
#include "api_refptr.h"
#include "task.h"

namespace sinet
{

class pool:
  public base
{
public:
  static refptr<pool> create_instance();

  // execute a task
  virtual void execute(refptr<task> task_in) = 0;
  // cancel executing of a task
  virtual void cancel(refptr<task> task_in) = 0;
  // check if a task is running
  virtual int is_running(refptr<task> task_in) = 0;
  // check if a task is in queue
  virtual int is_queued(refptr<task> task_in) = 0;
  // check if a task is running or in queue
  // this method puts two checks inside one lock, to avoid
  // race condition
  virtual int is_running_or_queued(refptr<task> task_in) = 0;
  // cancel and erase all tasks
  virtual void clear_all() = 0;
};

} // namespace sinet

#endif // SINET_POOL_H