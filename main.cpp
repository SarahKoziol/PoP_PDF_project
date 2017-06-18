#include <iostream>
#include "lib/tinyxml2/tinyxml2.h"
#include "lib/dirent/dirent.h" // TODO include only on windows

/*
 * Author: Sarah Koziol
 *
 * Auswertung von PDF-Formularen
 */

using namespace std;
using namespace tinyxml2;

int main() {
    std::string dirToRead;
    std::cout << "Pfad zum Ordner:" << std::endl;
    std::getline (cin, dirToRead);
//    std::cout << "Eingegebner Pfad: " << dirToRead <<std::endl;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirToRead.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") || !strcmp(ent->d_name, "?")) { // TODO fix ? for filenames with strange chars, like "B0144 Schr÷der.xml"
                // do nothing of ".", ".." or "?"
            } else {
                std::cout << "File: " << ent->d_name << std::endl;

                XMLDocument xmlDocument;
                xmlDocument.LoadFile( (dirToRead + "\\" + ent->d_name).c_str() );

                const char* keywords = xmlDocument.FirstChildElement("fields")->FirstChildElement("Keywords")->GetText();

                std::cout << keywords << std::endl;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return 0;
}
