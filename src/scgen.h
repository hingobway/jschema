//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Tracker data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::make_shared<T>(); else return std::make_shared<T>(j.get<T>());
        }
    };
    template <typename T>
    struct adl_serializer<std::optional<T>> {
        static void to_json(json & j, const std::optional<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::optional<T> from_json(const json & j) {
            if (j.is_null()) return std::make_optional<T>(); else return std::make_optional<T>(j.get<T>());
        }
    };
}
#endif

namespace schema {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_schema_HELPER
    #define NLOHMANN_UNTYPED_schema_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
    #endif

    #ifndef NLOHMANN_OPTIONAL_schema_HELPER
    #define NLOHMANN_OPTIONAL_schema_HELPER
    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, std::string property) {
        return get_heap_optional<T>(j, property.data());
    }
    template <typename T>
    inline std::optional<T> get_stack_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<std::optional<T>>();
        }
        return std::optional<T>();
    }

    template <typename T>
    inline std::optional<T> get_stack_optional(const json & j, std::string property) {
        return get_stack_optional<T>(j, property.data());
    }
    #endif

    /**
     * A geographical coordinate
     */
    struct Coord {
        double lat;
        double lon;
    };

    /**
     * A human person
     */
    struct Person {
        std::optional<std::string> email;
        std::string first_name;
        std::optional<std::string> last_name;
    };

    struct Tracker {
        Coord loc;
        Person person;
    };
}

namespace schema {
    void from_json(const json & j, Coord & x);
    void to_json(json & j, const Coord & x);

    void from_json(const json & j, Person & x);
    void to_json(json & j, const Person & x);

    void from_json(const json & j, Tracker & x);
    void to_json(json & j, const Tracker & x);

    inline void from_json(const json & j, Coord& x) {
        x.lat = j.at("lat").get<double>();
        x.lon = j.at("lon").get<double>();
    }

    inline void to_json(json & j, const Coord & x) {
        j = json::object();
        j["lat"] = x.lat;
        j["lon"] = x.lon;
    }

    inline void from_json(const json & j, Person& x) {
        x.email = get_stack_optional<std::string>(j, "email");
        x.first_name = j.at("firstName").get<std::string>();
        x.last_name = get_stack_optional<std::string>(j, "lastName");
    }

    inline void to_json(json & j, const Person & x) {
        j = json::object();
        j["email"] = x.email;
        j["firstName"] = x.first_name;
        j["lastName"] = x.last_name;
    }

    inline void from_json(const json & j, Tracker& x) {
        x.loc = j.at("loc").get<Coord>();
        x.person = j.at("person").get<Person>();
    }

    inline void to_json(json & j, const Tracker & x) {
        j = json::object();
        j["loc"] = x.loc;
        j["person"] = x.person;
    }
}
