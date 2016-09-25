/*
 * AnuRandom.cpp
 *
 *  Created on: Sep 25, 2016
 *      Author: michal
 */

#include "AnuRandom.h"

AnuRandom::AnuRandom(const TypeFormat format, const std::size_t len)
{
  std::string formatStr;
  const std::string lenStr { std::to_string(len) };

  switch (format)
  {
    case TypeFormat::uint16: formatStr = "uint16"; break;
    case TypeFormat::uint8:  formatStr = "uint8";  break;
    default: formatStr = "unknown"; break;
  }

  url = "/API/jsonI.php?length=" + lenStr + "&type=" + formatStr;
}

AnuRandom::~AnuRandom()
{
// TODO Auto-generated destructor stub
}

std::stringstream AnuRandom::download(const std::string serverName,
    const std::string getCommand)
{
  using namespace boost::asio;
  using boost::asio::ip::tcp;

  boost::asio::io_service io_service;

// Get a list of endpoints corresponding to the server name.
  tcp::resolver resolver(io_service);
  tcp::resolver::query query(serverName, "http");
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
  tcp::resolver::iterator end;

// Try each endpoint until we successfully establish a connection.
  tcp::socket socket(io_service);
  boost::system::error_code error = boost::asio::error::host_not_found;

  while (error && endpoint_iterator != end)
  {
    socket.close();
    socket.connect(*endpoint_iterator, error);
  }

  boost::asio::streambuf request;
  std::ostream request_stream(&request);

  request_stream << "GET " << getCommand << " HTTP/1.0\r\n";
  request_stream << "Host: " << serverName << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Connection: close\r\n\r\n";

// Send the request.
  boost::asio::write(socket, request);

// Read the response status line.
  boost::asio::streambuf response;
  boost::asio::read_until(socket, response, "\r\n");

// Check that response is OK.
  std::istream response_stream(&response);
  std::string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  std::string status_message;
  std::getline(response_stream, status_message);

// Read the response headers, which are terminated by a blank line.
  boost::asio::read_until(socket, response, "\r\n\r\n");

// Process the response headers.
  std::string header;
  while (std::getline(response_stream, header) && header != "\r");

  std::stringstream ss;

// Write whatever content we already have to output.
  if (response.size() > 0)
  {
    ss << &response;
  }
// Read until EOF, writing data to output as we go.
  while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
  {
    ss << &response;
  }

  return ss;
}

AnuJsonApi AnuRandom::deserialize(boost::property_tree::ptree& ptree)
{
  AnuJsonApi anu{};

  anu.type = ptree.get<std::string>("type");
  anu.len = ptree.get<std::size_t>("length");
  const std::string status = ptree.get<std::string>("success");
  (status == "false") ? anu.status = false : anu.status = true;

  if (anu.status == false)
  {
    throw;
  }

  anu.data.reserve(anu.len);

  auto data = ptree.get_child("data");

  for (auto& actual : data)
  {
    anu.data.push_back(actual.second.get_value<unsigned int>());
  }

  return anu;
}

std::vector<DataType> AnuRandom::get()
{
  auto ss = download(server, url);

  boost::property_tree::ptree ptree;
  boost::property_tree::read_json(ss, ptree);

  auto anuApi = deserialize(ptree);

  return anuApi.data;
}
