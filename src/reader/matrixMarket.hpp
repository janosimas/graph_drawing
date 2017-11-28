#include "../graphDraw.hpp"

#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef READER_MATRIX_MARKET
#define READER_MATRIX_MARKET


namespace reader {
  std::unique_ptr<GraphDraw> MatrixMarket(const std::string& filePath);
} /* reader */

#endif // READER_MATRIX_MARKET
