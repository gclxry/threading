#include "message_loop.h"

namespace mini_app {
  MessageLoop::MessageLoop() {}

  MessageLoop::~MessageLoop() {}

  void MessageLoop::DoRunLoop() {
    while (!is_need_exit_) {
      if (!tasks_.empty()) {
        Task task;
        {
          std::lock_guard<std::mutex> guard(task_mutex_);
          task = tasks_.front();
          tasks_.pop_front();
        }
        task();
      }

      WaitForWork();
    }
  }

  void MessageLoop::AddTask(const MessageLoop::Task& task) {
    {
      std::lock_guard<std::mutex> guard(task_mutex_);
      tasks_.push_back(task);
    }
    std::unique_lock<std::mutex> lock(work_mutex_);
    work_event_.notify_all();
  }

  void MessageLoop::StopSoon() {
    std::lock_guard<std::mutex> guard(task_mutex_);
    tasks_.clear();
    is_need_exit_ = true;
  }

  void MessageLoop::WaitForWork() {
    if (is_need_exit_) {
      return;
    }

    {
      std::lock_guard<std::mutex> guard(task_mutex_);
      if (!tasks_.empty()) {
        return;
      }
    }
    std::unique_lock<std::mutex> lock(work_mutex_);
    work_event_.wait(lock);
  }
}  // namespace mini_app
