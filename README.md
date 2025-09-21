# json-cpp – A Minimal JSON-Like Library in C++

json-cpp is a lightweight C++ library that allows you to dynamically build, modify, and print JSON-like objects.  
It was inspired by nlohmann::json, but designed from scratch to be simpler, portable, and directly usable in custom projects.  

This project integrates naturally with Reactive-CPP (https://github.com/The-codeMachine/Reactive-CPP),  
but it works standalone as well.

---

## ✨ Features
- Store key–value pairs inside JSON-like objects  
- Supports string, int, long, and double types  
  (stored internally as strings but convertible back)  
- Add and remove fields dynamically  
- Nested JSON objects supported  
- Pretty-print with formatting  
- Simple and extensible design  

---

## 📦 Example Usage

#include "json.hpp"  
#include <iostream>  

int main() {  
    // Create a base JSON object  
    json root;  

    // Add simple key–value pairs  
    root.add(new json_data("name", "Alice"));  
    root.add(new json_data("age", 25));  
    root.add(new json_data("pi", 3.14159));  

    // Add nested JSON object  
    json* address = new json();  
    address->add(new json_data("city", "Calgary"));  
    address->add(new json_data("country", "Canada"));  

    root.add(new json_data("address", address));  

    // Print formatted JSON  
    std::cout << root.print() << std::endl;  

    return 0;  
}  

---

### ✅ Output

{  
  {name: Alice},  
  {age: 25},  
  {pi: 3.14159},  
  {address: {  
    {city: Calgary},  
    {country: Canada}  
  }}  
}  

---

## 🛠️ How It Works
- json is a container that holds json_data objects  
- json_data stores a key and a value  
- All values are stored internally as std::string,  
  but constructors accept string, int, long, and double  
- print() converts the JSON object into a formatted string  
- Nesting is achieved by passing another json* as the value of json_data  

---

## 🔮 Planned Features
- Proper JSON compliance (quoted keys, string escaping, etc.)  
- Array support ([ ... ])  
- Automatic memory management with std::unique_ptr instead of raw pointers  
- Type-safe getters (as_int(), as_double(), etc.)  
- Integration with Reactive-CPP for reactive updates  

---

## 📂 Project Structure
json-cpp/  
 ├── include/  
 │    └── json.hpp        # Main header file  
 ├── examples/  
 │    └── example.cpp     # Example usage  
 └── README.md  

---

## 🚀 Getting Started
1. Clone the repo:  
   git clone https://github.com/your-username/json-cpp.git  

2. Include json.hpp in your project  

3. Compile with C++17 or higher:  
   g++ -std=c++17 examples/example.cpp -o example  
   ./example  

---

## 📜 License
MIT License.  
Use freely in personal and commercial projects.  
