#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct HeadFile
{
    vector <string> position;
    vector <string> coordinate;
    vector <string> normal;
    string  color;
};

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string str;

    vector <vector <string> > vert_pos(0, vector <string>(0));
    vector <vector <string> > vert_coord(0, vector <string>(0));
    vector <vector <string> > vert_normal(0, vector <string>(0));
    vector <string> tmp;
    vector<HeadFile>  vertices;

    int i_pos = 0, i_coord = 0, i_normal = 0;
    vector <int> vert_pos_indic(0);
    vector <int> vert_coord_indic(0);
    vector <int> vert_normal_indic(0);


    while (getline(fin, str)) {
        str += ' ';
        string prefix = "", temp = "";
        int i = 0;
        while (str[i] != ' ') {
            prefix += str[i];
            i++;
        }
        i++;
        // cout << prefix << " ";
        if (prefix == "#") {

        }
        else if (prefix == "o") {

        }
        else if (prefix == "s") {

        }
        else if (prefix == "v") { // vertex pos
            vert_pos.push_back(tmp);

            while (i < str.size()) {
                if (str[i] == ' ') {
                    vert_pos[i_pos].push_back(temp);
                    temp = "";
                }
                else {
                    temp += str[i];
                }
                i++;
            }
            i_pos++;
            /*
             for (int ind = 0; ind < vert_pos[i_pos - 1].size(); ind++) {
                cout << vert_pos[i_pos - 1][ind] << " ";
            }
            cout << endl;
            */



        }
        else if (prefix == "vt") { // vertex coordinates
            vert_coord.push_back(tmp);

            while (i < str.size()) {
                if (str[i] == ' ') {
                    vert_coord[i_coord].push_back(temp);
                    temp = "";
                }
                else {
                    temp += str[i];
                }
                i++;
            }
            i_coord++;

            /*
              for (int ind = 0; ind < vert_coord[i_coord - 1].size(); ind++) {
                cout << vert_coord[i_coord - 1][ind] << " ";
            }
            cout << endl;
            */

        }
        else if (prefix == "vn") {// vertex normals
            vert_normal.push_back(tmp);

            while (i < str.size()) {
                if (str[i] == ' ') {
                    vert_normal[i_normal].push_back(temp);
                    temp = "";
                }
                else {
                    temp += str[i];
                }
                i++;
            }
            i_normal++;

            /*
            for (int ind = 0; ind < vert_normal[i_normal - 1].size(); ind++) {
                cout << vert_normal[i_normal - 1][ind] << " ";
            }
            cout << endl;
            */

        }
        else if (prefix == "f") {

            int counter = 0;
            int temp_pos = 0, temp_coord = 0, temp_normal = 0;

            while (i < str.size()) {

                if (str[i] == '/') {
                    counter++;
                }
                else
                    if (str[i] == ' ') {
                        counter = 0;
                        vert_coord_indic.push_back(temp_coord);
                        vert_normal_indic.push_back(temp_normal);
                        vert_pos_indic.push_back(temp_pos);

                        temp_coord = 0;
                        temp_normal = 0;
                        temp_pos = 0;
                    }
                    else {
                        if (counter == 0) {
                            temp_pos *= 10;
                            temp_pos += str[i] - '0';
                        }

                        else if (counter == 1) {
                            temp_coord *= 10;
                            temp_coord += str[i] - '0';
                        }

                        else if (counter == 2) {
                            temp_normal *= 10;
                            temp_normal += str[i] - '0';
                        }
                    }

                i++;
            }

            /*
            cout << "f ";
            for (int q = 0; q < vert_coord_indic.size(); q++) {
                cout << vert_pos_indic[q] << " " << vert_coord_indic[q] << " " << vert_normal_indic[q] << endl;
            }
            */
        }
        else {

        }



    }
    /*
     for (int j = 0; j < vertices.size(); j++) {
        fout << "v:";
        for (int q = 0; q < vertices[j].position.size(); q++) {
            fout << vertices[j].position[q] << " ";
        }
        fout << "\n vt:";
        for (int q = 0; q < vertices[j].coordinate.size(); q++) {
            fout << vertices[j].coordinate[q] << " ";
        }
        fout << "\n vn:";
        for (int q = 0; q < vertices[j].normal.size(); q++) {
            fout << vertices[j].normal[q] << " ";
        }
        fout << endl;
    }
    */

    for (int j = 0; j < vert_coord_indic.size(); j++) {
        HeadFile temp_head;
        if (vert_pos_indic[j] != 0) {
            temp_head.position = vert_pos[vert_pos_indic[j] - 1];
        }
        if (vert_coord_indic[j] != 0) {
            temp_head.coordinate = vert_coord[vert_coord_indic[j] - 1];
        }
        if (vert_normal_indic[j] != 0) {
            temp_head.normal = vert_normal[vert_normal_indic[j] - 1];
        }

        temp_head.color = "1.0f, 1.0f, 1.0f";
        vertices.push_back(temp_head);
    }

    /////////////////////////////////////////////////////////////////////////////
                            //couting .h file


   // fout << "//" << vertices.size() * 4 << endl;;
  //  fout << "#include " << '"' << "default_tower.h" << '"' << endl << "#include " << '"' << "shaderprogram.h" << '"' << endl << "#include <glm/gtc/type_ptr.hpp>" << endl << " #include <type_traits>" << endl << "#include <vector>";
   // fout << endl << endl << "default_tower::default_tower() {" << endl;
        

      // fout << "    this->vertices = std::vector<float>{" << endl;   

    //////////////////////////////////////////////      ADDING TO PROJECT

    /*
    fout << "#pragma once\n#ifndef ENEMY_DATA_H_INCLUDED\n#define ENEMY_DATA_H_INCLUDED\n#include <vector>\nusing namespace std; \n\n";

                
       fout << "vector <float> vert_enemy() {\nvector <float> a = { \n";
    
        for (int j = 0; j < vertices.size(); j++) {
        for (int q = 0; q < vertices[j].position.size(); q++) {
            fout << vertices[j].position[q] << "f, ";
        }
        fout << "1.0f, \n";
    }
    fout << "}; \n return a;\n}\n\n";
  

        fout << "vector <float> norm_enemy() {\nvector <float> b = { \n";

    for (int j = 0; j < vertices.size(); j++) {
        for (int q = 0; q < vertices[j].normal.size(); q++) {
            fout << vertices[j].normal[q] << "f, ";
        }
        fout << "1.0f, \n";
    }
    fout << "}; \n return b;\n}\n\n";
  
       
    
   // fout << "vector <float> tex() {\nvector <float> c = { \n";
  //  for (int j = 0; j < vertices.size(); j++) {
    //    for (int q = 0; q < vertices[j].coordinate.size(); q++) {
       //     fout << vertices[j].coordinate[q] << "f, ";
    //    }
    //    fout << "\n";
   // }
  //  fout << "}; \n return c;\n}\n\n";
    
    
    fout << "\n#endif\n";
    */
    
    

    ///////////////////////////////     CHECKING A MODEL
  //  /*
     fout << "#ifndef MYTEAPOT_H \n#define MYTEAPOT_H\n\nunsigned int myTeapotVertexCount=" << vertices.size() << ";\n";

    fout << "float myTeapotVertices[]={\n";
    for (int j = 0; j < vertices.size(); j++) {
        for (int q = 0; q < vertices[j].position.size(); q++) {
            fout << vertices[j].position[q] << "f, ";
        }
        fout << "1.0f, \n";
    }
    fout << "}; \n\n";

    fout << "float myTeapotVertexNormals[]={\n";
    for (int j = 0; j < vertices.size(); j++) {
        for (int q = 0; q < vertices[j].normal.size(); q++) {
            fout << vertices[j].normal[q] << "f, ";
        }
        fout << "0.0f, \n";
    }
    fout << "}; \n\n";

    fout << "float myTeapotColors[]={\n";
    for (int j = 0; j < vertices.size(); j++) {
        fout << "0.7f,1.0f,0.4f,1.0f,\n";
    }
    fout << "}; \n\n";

    fout << "float myTeapotTexCoords[]={ \n";
    for (int j = 0; j < vertices.size(); j++) {
        for (int q = 0; q < vertices[j].coordinate.size(); q++) {
            fout << vertices[j].coordinate[q] << "f, ";
        }
        fout << "\n";
    }
    fout << "}; \n\n #endif";

   // */
    

   
    return 0;
}
