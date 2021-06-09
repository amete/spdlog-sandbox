#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

// Global sink
static const std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_sink { std::make_shared<spdlog::sinks::stdout_color_sink_mt >() };

/*
 * Base Class for Messaging
 */
class Messaging {
  public:
    Messaging(const std::string& name, const spdlog::level::level_enum& level = spdlog::level::info) :
      logger{ std::make_shared<spdlog::logger>(name, s_sink) } { 
        set_log_level(level);
      }

    void set_log_level(const spdlog::level::level_enum& level) {
      logger->set_level(level);
    }

    void debug(const std::string& message)   { logger->debug(message); }
    void info(const std::string& message)    { logger->info(message);  }
    void warning(const std::string& message) { logger->warn(message);  }
    void error(const std::string& message)   { logger->error(message); }
    
  private:
    std::shared_ptr<spdlog::logger> logger;
};

/*
 *  Derived Classes
 */
class Monitor1 : public Messaging {
  public:
    Monitor1(const std::string& name) : Messaging(name) { }
    void do_work() {
      debug("MY DEBUG");
      info("MY INFO");
      warning("MY WARNING");
      error("MY ERROR");
    }
};

class Monitor2 : public Messaging {
  public:
    Monitor2(const std::string& name) : Messaging(name) { }
    void do_work() { 
      debug("YOUR DEBUG");
      info("YOUR INFO");
      warning("YOUR WARNING");
      error("YOUR ERROR");
    }
};

/*
 * Main Function
 */
int main(int argc, char* argv[]) {

  // Monitor1 does its job and prints debug and up
  auto monitor1 = std::make_unique<Monitor1>("Monitor1");
  monitor1->set_log_level(spdlog::level::debug); // << Pass user setting
  monitor1->do_work(); // << Do the work and in there print some messages

  // Monitor2 does its job and prints warning and up
  auto monitor2 = std::make_unique<Monitor2>("Monitor2");
  monitor2->set_log_level(spdlog::level::warn); // << Pass user setting
  monitor2->do_work(); // << Do the work and in there print some messages

  // Shutdown all registered loggers
  spdlog::shutdown();

  // And we're all done!
  return 0;

}
