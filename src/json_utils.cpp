#include "json/json_utils.h"

void jsonFileoutput(std::string filename, Json::Value jsonOut){
    std::ofstream outfile;
    outfile.open(filename);
    Json::StreamWriterBuilder builder;
    std::string json_file = Json::writeString(builder, jsonOut);
    outfile << json_file << std::flush;
    outfile.close();
};
