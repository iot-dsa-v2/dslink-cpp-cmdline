
#include "command_cd.h"

std::vector<int> CommandCD::_available_args_num_options() {
  return {0, 1};
}

void CommandCD::_print_usage_info() {
  std::cout<<"Printing cd usage info"<<std::endl;
}

COMMAND_RETURN_TYPE CommandCD::_execute() {
  // There is special case if only cd is typed. We are returning back to the root
  if(cmd_data.get_path_str().size() != 0)
    target_path = Command::merge_paths(current_path, cmd_data.get_path_str());
  else
    target_path = std::string("");

  bool is_triggered = false;
  auto incoming_cache = link->list(
      target_path.c_str(),
      [&](IncomingListCache &cache, const std::vector<string_> &str) {
        this->status = cache.get_status();
        is_triggered = true;
      });

  Command::wait_for_bool([&]()->bool{return is_triggered;});
  if(is_triggered && status == MessageStatus::OK){
    std::cout<<"Current directory will changing to : "<<target_path;
    if(target_path.size() == 0)
      std::cout<<"root";
    std::cout<<std::endl;
    current_path = target_path;
  }
  else{
    std::cout<<"Current directory Can NOT changing to : "<<target_path<<", it is invalid"<<std::endl;
  }

  incoming_cache->destroy();

  return COMMAND_RETURN_CONTINUE;
}

void CommandCD::_clear() {
}

void CommandCD::_print() {
}
