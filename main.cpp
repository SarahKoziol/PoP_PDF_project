#include <iostream>
#include "lib/tinyxml2/tinyxml2.h"

/*
 * Author: Sarah Koziol
 *
 * Auswertung von PDF-Formularen
 */

using namespace std;
using namespace tinyxml2;

int main() {
    std::string fileToRead;
    std::cout << "Pfad zur Datei:" << std::endl;
    std::getline (cin, fileToRead);
    std::cout << "Eingegebner Pfad: " << fileToRead <<std::endl;

    XMLDocument xmlDocument;
    xmlDocument.LoadFile( fileToRead.c_str() );

    const char* keywords = xmlDocument.FirstChildElement("fields")->FirstChildElement("Keywords")->GetText();

    std::cout << keywords << std::endl;
    return 0;
}
