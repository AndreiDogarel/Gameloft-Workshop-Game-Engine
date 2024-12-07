#include "stdafx.h"
#include "../Include/RapidXML/rapidxml.hpp"
#include "../Include/RapidXML/rapidxml_utils.hpp"
#include "../Utilities/utilities.h"
#include <iostream>
#include <string>
#include <exception>


void parseNode(rapidxml::xml_node<>* node, int depth) {
    std::string indent(depth * 4, ' ');
    std::cout << indent << "Element: " << node->name();

    for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::cout << " " << attr->name() << "=\"" << attr->value() << "\"";
    }
    std::cout << std::endl;

    if (node->value() && *node->value()) {
        std::cout << indent << "  Conținut: " << node->value() << std::endl;
    }

    for (rapidxml::xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
        parseNode(child, depth + 1);
    }
}

void parseAndPrintXML(const std::string& filePath) {
    rapidxml::file<> xmlFile(filePath.c_str());
    rapidxml::xml_document<> doc;
    
    try {
        doc.parse<0>(xmlFile.data());
    }
    catch (const rapidxml::parse_error& e) {
        std::cerr << "Eroare la parsare: " << e.what() << std::endl;
        return;
    }

    rapidxml::xml_node<>* root = doc.first_node("root");
    if (!root) {
        std::cerr << "Nu s-a găsit nodul rădăcină!" << std::endl;
        return;
    }

    std::cout << "Nod rădăcină: " << root->name() << std::endl;
    parseNode(root, 0);
}


int main() {
    std::string filePath = "example.xml";
    parseAndPrintXML(filePath);
    return 0;
}
