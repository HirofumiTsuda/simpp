#include "event.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <boost/coroutine2/coroutine.hpp>

#include "core.hpp"


namespace simpp{
  using coro_t = boost::coroutines2::coroutine<std::shared_ptr<Event> >;  
    std::shared_ptr<Event> get_ptr();
    bool is_ok();
    bool is_pending();

  std::shared_ptr<Event> Event::get_ptr(){
    return shared_from_this();
  }

  bool Event::is_ok(){
    return ok;
  }

  bool Event::is_pending(){
    return pending;
  }

  bool Event::is_done(){
    return done;
  }

  void Event::set_done(){
    if(done)
      throw std::runtime_error("Event is already done!");
    done = true;
  }

  void Event::succeed(){
    ok = true;
    env->schedule(shared_from_this());
  }

  void Timeout::cast_into_queue(){
    ok = true;
    env->schedule(shared_from_this(), 1, delay);
  }

  Process::Process(const std::shared_ptr<simpp::Environment>& env, const std::function<void(coro_t::push_type&)> f)
    : Event(env) {
      generator = std::make_unique<coro_t::pull_type>(coro_t::pull_type(f));
  }

  void Process::execute(){
      auto ptr = std::dynamic_pointer_cast<Process>(Event::shared_from_this());
      std::shared_ptr<Initializer> ini = std::make_shared<Initializer>(env, std::move(ptr));
      ini->execute();
  }

  void Process::resume(std::shared_ptr<Event>& event){
    std::shared_ptr<Event> res;
    while(true){
      /*
      Check if the event is already triggered.
      If it is not yet, this is an error.
      Then, this process fails and the whole program should be shut down.
      */
      if(*generator){
        // generator is valid
	std::cout << "res" << event->is_ok() << std::endl;	
        if(event->is_ok()){
          res = generator->get();
          (*generator)();
        }else{
          throw std::runtime_error("Generator is invalid");
        }
      }else{
        /*
          This process has just finished. 
          Finally, this process is casted into the schedule-queue. 
        */
        env->schedule(shared_from_this());
        break;
      }
      if(res != nullptr && !res->is_done()){
	event->callbacks.push_back([&](std::shared_ptr<Event> &event){
				     resume(event);
				   });
	break;
      }
    }
  }
  
  void Initializer::execute(){
    std::function<void(std::shared_ptr<Event> &)> f = [&](std::shared_ptr<Event> &x){
      process->resume(x);
      };
    
    callbacks.push_back(f);
    ok = true;
    env->schedule(shared_from_this(), 0, 0.0);
  }
  
}

/*
    def _resume(self, event: Event) -> None:  # noqa: C901
        """Resumes the execution of the process with the value of *event*. If
        the process generator exits, the process itself will get triggered with
        the return value or the exception of the generator."""
        # Mark the current process as active.
        self.env._active_proc = self

        while True:
            # Get next event from process
            try:
                if event._ok:
                    event = self._generator.send(event._value)
                else:
                    # The process has no choice but to handle the failed event
                    # (or fail itself).
                    event._defused = True

                    # Create an exclusive copy of the exception for this
                    # process to prevent traceback modifications by other
                    # processes.
                    exc = type(event._value)(*event._value.args)
                    exc.__cause__ = event._value
                    event = self._generator.throw(exc)
            except StopIteration as e:
                # Process has terminated.
                event = None  # type: ignore
                self._ok = True
                self._value = e.args[0] if len(e.args) else None
                self.env.schedule(self)
                break
            except BaseException as e:
                # Process has failed.
                event = None  # type: ignore
                self._ok = False
                # Strip the frame of this function from the traceback as it
                # does not add any useful information.
                e.__traceback__ = e.__traceback__.tb_next  # type: ignore
                self._value = e
                self.env.schedule(self)
                break

            # Process returned another event to wait upon.
            try:
                # Be optimistic and blindly access the callbacks attribute.
                if event.callbacks is not None:
                    # The event has not yet been triggered. Register callback
                    # to resume the process if that happens.
                    event.callbacks.append(self._resume)
                    break
            except AttributeError:
                # Our optimism didn't work out, figure out what went wrong and
                # inform the user.
                if hasattr(event, 'callbacks'):
                    raise

                msg = f'Invalid yield value "{event}"'
                descr = _describe_frame(self._generator.gi_frame)
                error = RuntimeError(f'\n{descr}{msg}')
                # Drop the AttributeError as the cause for this exception.
                error.__cause__ = None
                raise error

        self._target = event
        self.env._active_proc = None
*/

