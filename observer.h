#ifndef OBSERVER_H
#define OBSERVER_H

template <typename State, typename Status> class Subject;

template <typename State, typename Status> class Observer{
 public:
  virtual void notify(Subject<State, Status>&data){}; // pass the Subject that called the notify method
  virtual ~Observer() = default;
};
#endif
