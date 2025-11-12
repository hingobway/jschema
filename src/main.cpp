#include <fstream>
#include <iostream>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpatch/jsonpatch.hpp>
#include <jsoncons_ext/jsonschema/json_schema.hpp>
#include <jsoncons_ext/jsonschema/json_schema_factory.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "scgen.h"

using jsoncons::ojson;
namespace jsonschema = jsoncons::jsonschema;

std::string text = R"(
{
  "person": {
    "firstName": "Michael",
    "lastName": "Foster"
  },
  "loc": {
    "lat": 34,
    "lon": -29
  }
}
)";

static std::string read_file_to_string(const std::string& path) {
  std::ifstream in(path, std::ios::binary);
  if (!in) throw std::runtime_error("Unable to open file: " + path);
  std::ostringstream ss;
  ss << in.rdbuf();
  return ss.str();
}
int structure_and_print();

const std::string tracker_json = read_file_to_string("../schema/tracker.json");

int main() {
  ojson schema = ojson::parse(tracker_json);
  jsonschema::json_schema<ojson> compiled =
      jsonschema::make_json_schema(std::move(schema));

  try {
    ojson data = ojson::parse(text);
    compiled.validate(data);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return structure_and_print();
}

int structure_and_print() {
  std::cout << "validation success!\n";

  schema::Tracker abc = schema::json::parse(text);

  std::cout << "First Name: " << abc.person.first_name << "\n";
  std::cout << "Last Name: " << abc.person.last_name.value_or("** NO LAST NAME")
            << "\n";
  std::cout << "Last Name: " << abc.person.email.value_or("** NO EMAIL")
            << "\n";
  std::cout << "Latitude: " << abc.loc.lat << "\n";
  std::cout << "Longitude: " << abc.loc.lon << "\n";

  // std::cout << "latitude: " << obj.latitude.value_or(0.0) << "\n";
  // std::cout << "longitude: " << obj.longitude.value_or(0.0) << "\n";

  return 0;
}
