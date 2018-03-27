#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
template <typename State, typename Status> class Observer;

template <typename State, typename Status> class Subject {
  std::vector<std::shared_ptr<Observer<State, Status>>> observers;
  State gameState;
  Status s;
 public:
  void setState(State newS);
  void detach(Observer<State, Status> *o);
  void attach(Observer<State, Status> *o);  
  void notifyAll();
  State getState() const;
  Status& getStatus();
};
template <typename State, typename Status>
void Subject<State, Status>::attach(Observer<State, Status> *o) {
  observers.emplace_back(o);
}

template <typename State, typename Status>
void Subject<State, Status>::detach(Observer<State, Status> *o) {
	for (typename std::vector<std::shared_ptr<Observer<State, Status>>>::iterator it = observers.begin(); it != observers.end();) {
		if ((*it) == o) {
			it = observers.erase(it);
		} else {
			++it;
		}
	}
}


template <typename State, typename Status>
void Subject<State, Status>::notifyAll() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename State, typename Status>
void Subject<State, Status>::setState(State newS) { gameState = newS; }

template <typename State, typename Status>
State Subject<State, Status>::getState() const { return gameState; }

template <typename State, typename Status>
Status& Subject<State, Status>::getStatus(){ return s; }
#endif
