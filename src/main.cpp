#include <iostream>
#include <string>

#include "scgen.h"

int main()
{
  std::cout << "hi\n";

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

  schema::Tracker abc = schema::json::parse(text);

  std::cout << "First Name: " << abc.person.first_name << "\n";
  std::cout << "Last Name: " << abc.person.last_name.value_or("** NO LAST NAME") << "\n";
  std::cout << "Last Name: " << abc.person.email.value_or("** NO EMAIL") << "\n";
  std::cout << "Latitude: " << abc.loc.lat << "\n";
  std::cout << "Longitude: " << abc.loc.lon << "\n";

  // std::cout << "latitude: " << obj.latitude.value_or(0.0) << "\n";
  // std::cout << "longitude: " << obj.longitude.value_or(0.0) << "\n";

  return 0;
}
