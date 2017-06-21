#include <iostream>
#include <fstream>
#include <vector>
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
    // Configure here which fields (=> xml-nodes) to output, like `"Keywords"` for `<Keywords />`
    const std::vector<std::string> fieldsToOutput = {"Vorname",
                                                     "Nachname",
                                                     "Titel",
                                                     "Semester",
                                                     "Kurzfassung",
                                                     "Schlagwoerter"}; // TODO create external option
    const std::string outputFormat = "HTML"; // TODO create external option AND switch down below for different filetypes
                                                                        // Missing: Bachelor- or Masterthesis (wichtig)

    std::string dirToRead;
    std::cout << "Pfad zum Ordner:" << std::endl;
    std::getline (cin, dirToRead);
//    std::cout << "Eingegebner Pfad: " << dirToRead <<std::endl;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirToRead.c_str())) != NULL) {
        ofstream outputFile;
        outputFile.open("outputs.rtf"); // TODO path; default path; path option
                                        // actual path: C:\Users\Sarah\CLionProjects\PoP_PDF_project\cmake-build-debug\outputs.rtf

        bool first = true;

        while ((ent = readdir (dir)) != NULL) {
            // TODO check if XML
            if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") || !strcmp(ent->d_name, "?")) { // TODO fix ? for filenames with strange chars, like "B0144 Schr÷der.xml"
                // do nothing of ".", ".." or "?"
            } else {
                if (!first) {
                    outputFile << std::endl << std::endl;
                } else {
                    first = false;
                }

                std::cout << "File: " << ent->d_name << std::endl;

                XMLDocument xmlDocument;
                xmlDocument.LoadFile( (dirToRead + "\\" + ent->d_name).c_str() );
                const XMLElement* fields = xmlDocument.FirstChildElement("fields"); // TODO check if fields exist

                for (auto value : fieldsToOutput) {
                    if (fields->FirstChildElement(value.c_str())->GetText() != nullptr) {
                        const char* currentField = fields->FirstChildElement(value.c_str())->GetText();
                        std::cout << value << ": " << currentField << std::endl;
                        outputFile << value << ": " << currentField << std::endl;
                    } else {
                        std::cout << value << ": " << std::endl;
                        outputFile << value << ": " << std::endl;
                    }
                }
            }
        }
        closedir (dir);
        outputFile.close();
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return 0;
}
