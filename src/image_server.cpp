//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <fstream>
using boost::asio::ip::tcp;

std::vector<uint8_t> get_image()
{
   // open the file:
    std::streampos fileSize;
    std::ifstream file("cat.jpg", std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<uint8_t> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
  
    std::cout<< "return image data" << std::endl;
    //return data
    return fileData;
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      //pass cat.jpg to get_image to get info about cat 
      auto message = get_image();

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}