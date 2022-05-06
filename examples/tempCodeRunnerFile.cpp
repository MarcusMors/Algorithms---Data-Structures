std::cout << "\n";
  list.pop_back();// NOLINT magic numbers
  for (const auto &elem : list) { std::cout << elem << ','; }