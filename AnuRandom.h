/*
 * AnuRandom.h
 *
 *  Created on: Sep 25, 2016
 *      Author: michal
 */

#ifndef ANURANDOM_H_
#define ANURANDOM_H_

#include <exception>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using DataType = unsigned int;


/**
 * \brief Anu json structur
 */
struct AnuJsonApi
{
  std::string type;
  std::size_t len;
  std::vector<DataType> data;
  bool status;
};


/**
 * \brief Data format
 */
enum TypeFormat
{
  uint16, uint8
};

class AnuRandom
{

  /**
   * \brief Anu server address
   */
  const std::string server{ "qrng.anu.edu.au" };

  /**
   * \brief Url command
   */
  std::string url;

  /**
   * \brief Download from url metod
   *
   * \brief[in] host ex. www.test.com
   * \brief[in] path ex. /path/to/file.html
   *
   * \return    stream
   */
  std::stringstream download(const std::string serverName, const std::string getCommand);

  /**
   * \Deserialize json file into struct
   *
   * \brief[in] json parser (property_tree object from boost)
   *
   * \return    Anu json structure
   */
  AnuJsonApi deserialize(boost::property_tree::ptree& ptree);

public:

  /**
   * \Constructor
   *
   * \brief[in] type data format, uint16 or uint8
   * \brief[in] len of data
   */
  AnuRandom(const TypeFormat format, const std::size_t len);

  /**
   * \Get Random numbers
   *
   * \return    vector of random data with size = len form constuctor
   */
  std::vector<DataType> get();

  /**
   * \Destructor
   */
  virtual ~AnuRandom();
};

#endif /* ANURANDOM_H_ */
