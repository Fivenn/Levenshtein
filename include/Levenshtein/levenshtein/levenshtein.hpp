#ifndef LEVENSHTEIN_LEVENSHTEIN_HPP
#define LEVENSHTEIN_LEVENSHTEIN_HPP

#include <iostream>
#include <vector>

#include "useful/matrix.hpp"  // Matrix

/**
 * Name space of the project
 */
namespace levenshtein {

class Levenshtein {
 public:
  Levenshtein(const std::string& wordH,
              const std::string& wordV,
              size_t cellWidth = 7);
  Levenshtein() = delete;
  Levenshtein(Levenshtein const& other) = default;
  Levenshtein& operator=(Levenshtein const& other) = delete;
  Levenshtein(Levenshtein&& other) = default;
  Levenshtein& operator=(Levenshtein&& other) = delete;
  ~Levenshtein() = default;

  /**
   * @brief Return the Levenshtein distance between the two word (and compute it
   * if not already done).
   * */
  int64_t compute_lev();


  /**
   * @brief Return the Levenshtein distance between the two word. Use a linear in space algorithme (but do not allows backtrack or display).
   * */
  int64_t compute_lev_compact();

  typedef enum Operation {
    Unk,        ///< Unknown
    Ins,        ///< Insertion
    Del,        ///< Deletion
    Rep         ///< Replacement
  } Operation;  ///< Operations available for edition.

  static const std::string op_to_string(Operation o);
  
  /**
   * @brief Find an optimal sequence of operations to edit one word into the
   * other.
   * */
  std::vector<Operation> backtrace();

  /**
   * @brief print a Levenshtein table (and compute it
   * if not already done).
   **/
  friend std::ostream& operator<<(std::ostream& os, Levenshtein& l);

 protected:
  void init_lev_matrix();


  class LevNode {
   public:
    LevNode();
    LevNode(LevNode const& other) = default;
    LevNode& operator=(LevNode const& other) = default;
    LevNode(LevNode&& other) = default;
    LevNode& operator=(LevNode&& other) = default;
    ~LevNode() = default;

    int64_t score;
    Operation op;
    bool bestPath;
  };

  bool computed;

  const std::string wordH;
  const std::string wordV;

  useful::matrix::Matrix<LevNode> m;

  size_t cellWidth;

 private:
};

/**
 * A compressed levenshtein (linear in space)
 * */ 
class LevenshteinComp {
 public:
  LevenshteinComp(const std::string& wordH,
              const std::string& wordV,
              size_t cellWidth = 7);
  LevenshteinComp() = delete;
  LevenshteinComp(LevenshteinComp const& other) = default;
  LevenshteinComp& operator=(LevenshteinComp const& other) = delete;
  LevenshteinComp(LevenshteinComp&& other) = default;
  LevenshteinComp& operator=(LevenshteinComp&& other) = delete;
  ~LevenshteinComp() = default;

  /**
   * @brief Return the Levenshtein distance between the two word (and compute it
   * if not already done).
   * */
  int64_t compute_lev();

  // typedef enum Operation {
  //   Unk,        ///< Unknown
  //   Ins,        ///< Insertion
  //   Del,        ///< Deletion
  //   Rep         ///< Replacement
  // } Operation;  ///< Operations available for edition.

  // static const std::string op_to_string(Operation o);
  
  /**
   * @brief Find an optimal sequence of operations to edit one word into the
   * other.
   * */
  //std::vector<Operation> backtrace();

  /**
   * @brief print a Levenshtein table (and compute it
   * if not already done).
   **/
  // friend std::ostream& operator<<(std::ostream& os, Levenshtein& l);

 protected:
  void init_lev_queue();



  bool computed;

  const std::string wordH;
  const std::string wordV;

  size_t cellWidth;

 private:
};



/**
 *@brief Print "Hello world!".
 */
void print_hello();

/**
 * @brief Print a random integer between 0 and 100.
 */
void print_rnd_int();

/**
 * @brief Test the matrix structure.
 */
void test_mat();

}  // namespace levenshtein

#endif /* End LEVENSHTEIN_LEVENSHTEIN_HPP guard */
