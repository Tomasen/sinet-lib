#ifndef SINET_POOL_IMPL_H
#define SINET_POOL_IMPL_H

#include "pool.h"

typedef void CURLM;
typedef void CURL;
typedef void* HANDLE;

namespace sinet
{

class pool_impl:
  public threadsafe_base<pool>
{
public:
  pool_impl(void);
  ~pool_impl(void);

  virtual void execute(refptr<task> task_in);
  virtual void cancel(refptr<task> task_in);
  virtual int is_running(refptr<task> task_in);
  virtual int is_queued(refptr<task> task_in);
  virtual int is_running_or_queued(refptr<task> task_in);
  virtual void clear_all();

  typedef struct _task_info{
    CURLM* hmaster;
    std::vector<CURL*> htasks;
    int running_handle;
  }task_info;

  // threading details for the pool
  static void _thread_dispatch(void* param);
  void _thread();

private:
  // iterates thru refptr<task> and translate them into CURL details
  // called by pool_impl::execute
  void _prepare_task(refptr<task> task_in, task_info& taskinfo_in);
  // tell CURL to stop running tasks
  // called by pool_impl::cancel, pool_impl::clear_all, pool_impl::_clean_finished
  void _cancel_running_task(CURLM*& hmaster, std::vector<CURL*>& htasks);

  // stopping and cleanup master pool thread
  // called by destructor
  void _stop_thread();

  HANDLE  m_thread;
  HANDLE  m_stop_event;

  critical_section                  m_cstasks_running;
  critical_section                  m_cstask_queue;
  critical_section                  m_cstask_finished;
  std::map<refptr<task>, task_info> m_tasks_running;
  std::vector<refptr<task> >        m_task_queue;
  std::vector<refptr<task> >        m_task_finished;
};

} // namespace sinet

#endif // SINET_POOL_IMPL_H