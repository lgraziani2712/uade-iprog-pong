#include <functional>

#include "./clean_up.hpp"

FinalAction::FinalAction(std::function<void()> fn) : cleanUp(std::move(fn)) {}
FinalAction::~FinalAction() { cleanUp(); }

FinalAction cleanUpCreation(std::function<void()> fn) {
  return FinalAction(std::move(fn));
}
