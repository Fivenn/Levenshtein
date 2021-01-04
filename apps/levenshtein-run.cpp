/* STD */
#include <time.h>

/* levenshtein */
#include "useful/various.hpp"
INITIALIZE_EASYLOGGINGPP
const std::string message_OK = "\e[32m[OK]\e[39m";

/* levenshtein */
#include "levenshtein/levenshtein.hpp"

/* Options */
#include "optionsParser/optionsParser.hpp"

ADD_SWITCH("General",
           verbose,
           "Add verbose messages (if cmake called with -DDEBUG=ON).")
ADD_SWITCH("General", quiet, "Only display error messages.")

ADD_OPTION("Input", w1, "First word for computation", std::string, "chien")
ADD_OPTION("Input", w2, "Second word for computation", std::string, "niches")

ADD_SWITCH(
    "Mode",
    compact,
    "Use a memory efficient levenshtein algorithm (no bactrace in this case).")
ADD_SWITCH("Mode",
           backtrace,
           "Provide an optimal path (if not in compact mode).")
ADD_SWITCH("Mode",
           matrix,
           "Print the Levenshtein matrix (if not in compact mode).")

// Examples :
/*
./build.sh  -d && valgrind ./bin/levenshtein --w1 "Le petit chat" --w2 "Les chats sont petits"
./build.sh  -d && valgrind --tool=massif  ./bin/levenshtein --w1 "Le petit chat est gentil mais sauvage. Je l'aime quand meme. Et vous ? Les aimez-vous ?Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum." --w2 "Les chats sont petits et voraces mais c'est pour cela qu'ils sont mignons. Et vous ? Les aimez-vous ? Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
*/

int main(int argc, char** argv) {
  /* Parse options */
  TOOLS_PARSE_OPTIONS(argc, argv);

  /* Init Logger */
  useful::config_logger(ARG_verbose, ARG_quiet);

  /* Main */
  levenshtein::Levenshtein l(ARG_w1, ARG_w2);

  if (ARG_compact) {
    int64_t levScoreCompact = l.compute_lev_compact();
    LOG(INFO) << "Lev Compact(\"" << ARG_w1 << "\",\"" << ARG_w2
              << "\") = " << levScoreCompact;
  } else {
    int64_t levScore = l.compute_lev();

    LOG(INFO) << "Lev(\"" << ARG_w1 << "\",\"" << ARG_w2
              << "\") = " << levScore;
    // std::cout << l << std::endl;

    if (ARG_backtrace) {
      std::stringstream ss;
      for (auto op : l.backtrace()) {
        ss << levenshtein::Levenshtein::op_to_string(op) << " , ";
      }
      LOG(INFO) << "An optimal path: " << ss.str() << std::endl;
    }

    if (ARG_matrix) {
      std::cout << l << std::endl;
    }
  }

  return 0;
}