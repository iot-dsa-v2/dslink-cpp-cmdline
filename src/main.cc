#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "dslink.h"
#include "util/app.h"

#include <module/default/console_logger.h>

#include "cmdline.h"


using namespace dsa;

ref_<DsLink> cmd_link;

bool connect_dslink(int argc, const char* argv[], std::shared_ptr<App> app) {
  cmd_link = make_ref_<DsLink>(argc, argv, "cmd-dslink", "1.0.0", app);
  cmd_link->init_responder();

  static_cast<ConsoleLogger &>(cmd_link->strand->logger()).filter =
      Logger::WARN__ | Logger::ERROR_ | Logger::FATAL_;

  bool is_connected = false;
  cmd_link->connect([&](const shared_ptr_<Connection> connection) {
    is_connected = true;
  });

  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
  if(!is_connected){
    std::cout<<"cannot connect to the broker!"<<std::endl;
    return false;
  }

  std::cout<<"\n cmd-dslink is connected, you can go for it!\n"<<std::endl;

  return true;
}

int main(int argc, const char* argv[]) {

  auto app = std::make_shared<App>();

  // Connect to the broker
  if(!connect_dslink(argc, argv, app)) {
    cmd_link->destroy();
    return 1;
  }

  auto cmdline = CmdLine(app, cmd_link);
  cmdline.run();

  return 0;
}