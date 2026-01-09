
    //just getting started with json.hpp. this will be moved into another file eventually{
    // Using (raw) string literals and json::parse
    std::ifstream f("Data/temp.json");
    json jsonObj = json::parse(f);
    //json jsonObj = "Data/temp.json";

    float pi = jsonObj["pi"];
    bool happy = jsonObj["happy"];
    int firstNum = jsonObj["numbers"][0];

    int numsum = 0;
    json numArray = jsonObj["numbers"];
    for (int i = 0; i < numArray.size(); i++) {
        numsum += numArray[i];
    }

    std::string bryan = jsonObj["goose"]["goslings"][1];



    //}