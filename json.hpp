#pragma once
#include <string>
#include <list>
#include <memory>
#include <iostream>

// Forward declaration
class json_data;

// Base json object
class json {
private:
    std::list<std::unique_ptr<json_data>> data;

public:
    json() = default;

    // Adds and takes ownership
    void add(std::unique_ptr<json_data> jd);

    std::string print() const;

    void remove(const std::string& key);
};

// Value type enum
enum class json_type { string, number, boolean, null, object };

// json_data: key + value (stored as string) + type
class json_data {
private:
    std::string key;
    std::string value;   // always stored as string
    json_type type;
    std::unique_ptr<json> nested_json;

public:
    // Primitive constructors
    json_data(const std::string& k, const std::string& v)
        : key(k), value(v), type(json_type::string) {
    }

    json_data(const std::string& k, const char* v)
        : key(k), value(v), type(json_type::string) {
    }

    json_data(const std::string& k, int v)
        : key(k), value(std::to_string(v)), type(json_type::number) {
    }

    json_data(const std::string& k, long v)
        : key(k), value(std::to_string(v)), type(json_type::number) {
    }

    json_data(const std::string& k, double v)
        : key(k), value(std::to_string(v)), type(json_type::number) {
    }

    json_data(const std::string& k, bool v)
        : key(k), value(v ? "true" : "false"), type(json_type::boolean) {
    }

    // Nested object
    json_data(const std::string& k, std::unique_ptr<json> child)
        : key(k), type(json_type::object), nested_json(std::move(child)) {
    }

    const std::string& get_key() const { return key; }

    std::string printval() const {
        if (type == json_type::object && nested_json) {
            return "\"" + key + "\": " + nested_json->print();
        }
        if (type == json_type::string)
            return "\"" + key + "\": \"" + value + "\"";
        // number/bool/null
        return "\"" + key + "\": " + value;
    }

    // Conversions
    int as_int() const { return std::stoi(value); }
    long as_long() const { return std::stol(value); }
    double as_double() const { return std::stod(value); }
    bool as_bool() const { return value == "true"; }
    std::string as_string() const { return value; }
};

// === json definitions ===
inline void json::add(std::unique_ptr<json_data> jd) {
    data.push_back(std::move(jd));
}

inline std::string json::print() const {
    std::string result;
    for (auto const& jd : data) {
        result += jd->printval() + ", \n";
    }
    if (result.empty()) return "{}";
    return "{\n" + result.substr(0, result.size() - 3) + "\n}";
}

inline void json::remove(const std::string& key) {
    data.remove_if([&key](const std::unique_ptr<json_data>& jd) {
        return jd->get_key() == key;
        });
}
