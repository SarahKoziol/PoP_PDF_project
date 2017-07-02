#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "lib/tinyxml2/tinyxml2.h"
#include "lib/dirent/dirent.h" // TODO include only on windows

/*
 * Author: Sarah Koziol
 * Date: 05.06.2017
 * Project: Auswertung von PDF-Formularen
 * For: Prozessorientierte Programmierung (Sommersemester 2016)
 */

using namespace std;
using namespace tinyxml2;

int main() {
    // TODO create external options for all these variables

    // defaultFirstChildElement defines the root XML-element for all the fields
    const char* defaultFirstChildElement = "fields";

    // defaultFieldsToOutput defines the selected XML-elements e.g. `"Keywords"` for `<Keywords />`
    // and sets the order, independent of the order of the input XML
    const std::vector<std::string> defaultFieldsToOutput = {"Vorname",
                                                            "Nachname",
                                                            "Titel",
                                                            "AbschlussarbeitArt",
                                                            "Semester",
                                                            "Kurzfassung",
                                                            "Schlagwoerter"};

    // this map AbschlussarbeitArt maps the actual values of AbschlussarbeitArt to the corresponding strings
    const std::map<std::string,std::string> AbschlussarbeitArt = {{"1", "Abschlussarbeit"},
                                                                  {"2", "Bachelorarbeit"},
                                                                  {"3", "Masterarbeit"}};

    std::string dirToRead;
    std::cout << "Pfad zum Ordner:" << std::endl;
    std::getline (cin, dirToRead);
//    std::cout << "Eingegebner Pfad: " << dirToRead <<std::endl;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirToRead.c_str())) != NULL) {
        ofstream outputFile(dirToRead + "/outputs.html"); // TODO path is currently dirToRead; path option?

        outputFile << "<!DOCTYPE html><html><head><meta charset=\"utf-8\"/></head><body><h1>Abschlussarbeiten</h1>";

        while ((ent = readdir (dir)) != NULL) {
            // TODO returns "?" for filenames with strange chars, like "B0144 Schr÷der.xml", because of tinyxml2 and unicode is hard
            const string fileName(ent->d_name);

            if (fileName.find(".xml") != std::string::npos) {
                std::cout << "File: " << ent->d_name << std::endl;

                XMLDocument xmlDocument;
                xmlDocument.LoadFile( (dirToRead + "/" + ent->d_name).c_str() );

                const XMLElement* fields = xmlDocument.FirstChildElement(defaultFirstChildElement); // e.g. "fields"

                outputFile << "<ul>" << std::endl; // HTML-element unordered list (ul)

                for (auto value : defaultFieldsToOutput) {
                    string currentField = "";
                    if (fields->FirstChildElement(value.c_str())->GetText() != nullptr) {
                        currentField = fields->FirstChildElement(value.c_str())->GetText();
                    }

                    if (value == "AbschlussarbeitArt") {
                        currentField = AbschlussarbeitArt.find(currentField)->second;
                    }

                    std::cout << value << ": " << currentField << std::endl;
                    outputFile << "<li><strong>" << value << ":</strong> " << currentField << "</li>" << std::endl;
                }

                outputFile << "</ul>" << std::endl; // end ul
            } else {
                // do nothing if ".", ".." or "?" (strange char in filename) or doesnt contain ".xml"
            }
        }
        closedir (dir); // close dir after reading

        outputFile << "</body></html>";
        outputFile.close();
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return 0;
}
