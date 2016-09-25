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

struct AnuJsonApi
{
	std::string type;
	std::size_t len;
	std::vector<DataType> data;
	bool status;
};

enum TypeFormat
{
	uint16,
	uint8
};

class AnuRandom {

	const std::string server {"qrng.anu.edu.au"};
	std::string url;

	std::stringstream download(const std::string serverName, const std::string getCommand);

	AnuJsonApi deserialize(boost::property_tree::ptree& ptree);

public:

	AnuRandom(const TypeFormat format, const std::size_t len);

	std::vector<DataType> get();

	virtual ~AnuRandom();
};

#endif /* ANURANDOM_H_ */
