#ifndef RUNTIME_V8_MESSAGE_LOOP_H_
#define RUNTIME_V8_MESSAGE_LOOP_H_

#include <condition_variable>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>

// class LoopThread {
// public:
//  LoopThread() {
//    message_loop_ = new MessageLoop();
//    thread_.reset(new std::thread(
//      std::bind(&LoopThread::ThreadMain, this, message_loop_)));
//  }
//  virtual ~LoopThread() {
//    if (message_loop_) {
//      StopSoon();
//    }
//  }
//
//  void ThreadMain(MessageLoop *message_loop) {
//    std::unique_ptr<MessageLoop> loop(message_loop);
//    loop->DoRunLoop();
//  }
//
//  void StopSoon() {
//    thread_->detach();
//    thread_.reset();
//    message_loop_->StopSoon();
//    message_loop_ = nullptr;
//  }
//
//  MessageLoop *message_loop() const { return message_loop_; }
//
// private:
//  std::unique_ptr<std::thread> thread_;
//  MessageLoop *message_loop_ = nullptr;
//};
//
// void calc(int a, int b) {
//  cout << a << " + " << b << " = " << a + b << endl;
//}
//
// int main() {
//  MessageLoop message_loop;
//  {
//    LoopThread t;
//    MessageLoop::Task task = std::bind(calc, 4, 5);
//    t.message_loop()->AddTask(task);
//
//    MessageLoop::Task task2 = std::bind(calc, 676, 898);
//    t.message_loop()->AddTask(task2);
//    MessageLoop::Task task3 = std::bind(calc, 7667, 45);
//    t.message_loop()->AddTask(task3);
//  }
//
//  message_loop.DoRunLoop();
//  return 0;
//}

namespace mini_app {
  class MessageLoop {
  public:
    typedef std::function<void(void)> Task;

    MessageLoop();
    ~MessageLoop();

    void DoRunLoop();
    void AddTask(const Task& task);
    void StopSoon();

  private:
    // Disallow copy and assign.
    MessageLoop(const MessageLoop&) = delete;
    MessageLoop& operator=(const MessageLoop&) = delete;

    void WaitForWork();

    std::deque<Task> tasks_;
    std::mutex task_mutex_;
    std::condition_variable work_event_;
    std::mutex work_mutex_;
    bool is_need_exit_ = false;
  };
}  // namespace mini_app

#endif  // RUNTIME_V8_MESSAGE_LOOP_H_