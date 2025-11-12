#include <iostream>
#include <string>

#include "schema.h"

using nlohmann::json;

int main()
{
  std::cout << "hi\n";

  std::string text = R"({
    "$schema": "base.json",
    "latitude": 4,
    "longitudde": 8
  })";

  quicktype::Coordinate obj;
  quicktype::from_json(json::parse(text), obj);

  std::cout << "latitude: " << obj.latitude.value_or(0.0) << "\n";
  std::cout << "longitude: " << obj.longitude.value_or(0.0) << "\n";

  return 0;
}
