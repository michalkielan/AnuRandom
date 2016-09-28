/*
 * main.cpp
 *
 *  Created on: Sep 25, 2016
 *      Author: michal
 */

#include "AnuRandom.h"
#include <iostream>

int main()
{
  AnuRandom anu{ TypeFormat::uint16, 5 };

  auto const& data = anu.get();

  for (auto& value : data)
  {
    std::cout << value << " ";
  }

  return 0;
}
