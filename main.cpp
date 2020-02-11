#include "main.hpp"

//the main() for the program, but since catch framework is used, it takes care of the main
int pipelined_func () {

    std::string line;
    std::vector< Rectangle > rects;
    int i = 0;
    unsigned rect_num;
    bool error = false;


    // Reading input from input.txt
    std::ifstream infile("input.txt");
    if (!infile.is_open()){
        cout << "missing input file" << endl;
        return 0;
    }

    while (getline(infile, line)) {
        try{

            if (i == 0)
            {
                rect_num = std::stoi(line);
                i++;
                continue;
            }
            std::istringstream iss(line);
            if (line.length() == 0){
                cerr << "Error: empty line detected" <<endl;
                return 0;
            }
            std::vector<std::string> coordinates((std::istream_iterator<std::string>(iss)),std::istream_iterator<std::string>());
            Rectangle r (std::stof(coordinates[0]),std::stof(coordinates[1]),std::stof(coordinates[2]),std::stof(coordinates[3]));
            rects.push_back(r);
            for (unsigned k=0; k < rects.size()-1; k++){
                if (is_invalid(rects[k],r)){
                    print_rect(rects[k]);
                    print_rect(r);
                    cerr << "Error: Invalid input of overlapping/touching rectangles" <<endl;
                    return 0;
                }
            }

        } catch (const std::invalid_argument& ia) {
            std::cerr << "Error: Invalid input - " << ia.what() << '\n';
            return 0;
        } catch (const std::out_of_range& oor) {
            std::cerr << "Error: Invalid input - Out of Range error: " << oor.what() << '\n';
            return 0;
        }
    }
    infile.close();

    if (rect_num != rects.size()){
        cerr<< "Error: Invalid number of input rectangle " << endl;
        return 0;
    }


    Tree t;
    Node* node = t.set_root();
    unsigned j = 0;
    for ( j=0; j < rect_num; j++){
        if (!t.insert(node, rects[j])){
            error = true;
            break;
        }
    }

    if (error){
        cerr<< "Error: Invalid input at Rectangle " << j+1 << endl;
        return 0;
    } else {
        cout<< "Number of land: "<< t.get_count()<<endl;
        return 1;
    }
    
    return 0;
}

bool is_invalid(Rectangle a, Rectangle b){

    //boolean of whether coordinate of rectangle b is in range of rectangle a
    bool c1 = in_range(b.x1, a.x1, a.x2); //check if b.x1 is within a.x1 and a.x2
    bool c2 = in_range(b.y1, a.y1, a.y2);
    bool c3 = in_range(b.x2, a.x1, a.x2);
    bool c4 = in_range(b.y2, a.y1, a.y2);

    //boolean of whether coordinate of rectangle a is in range of rectangle b
    bool c5 = in_range(a.x1, b.x1, b.x2); //check if a.x1 is within b.x1 and b.x2
    bool c6 = in_range(a.y1, b.y1, b.y2);
    bool c7 = in_range(a.x2, b.x1, b.x2);
    bool c8 = in_range(a.y2, b.y1, b.y2);

    // return false if rectangle b is containing rectangle a, or vice versa
    if ((c1 & c2 & c3 & c4) || (c5 & c6 & c7 & c8)){
        return false;
    }

    if (is_touching(b.x1, b.y1, a) || is_touching(b.x2, b.y2, a)){
        return true;
    }

    // return false if they are disjoint
    if (!c1 & !c2 & !c3 & !c4 & !c5 & !c6 & !c7 & !c8){
        return false;
    }

    if (is_overlap(c1,c2,c3,c4)) {
        return true;
    }
    return false;
}

bool in_range(float x, float r1, float r2) {
    return(r1 < x && x < r2);
}

bool inclusive_in_range(float x, float r1, float r2) {
    return(r1 <= x && x <= r2);
}

bool three_identical_bool(bool a, bool b, bool c, bool d, bool val) {
    // check if there are three boolean among a,b,c,d equal to val
    if (val == false){
        return ((a && !b && !c && !d) || (!a && b && !c && !d) || (!a && !b && !c && d) || (!a && !b && !c && d));
    } else {
        return ((!a && b && c && d) || (a && !b && c && d) || (a && b && !c && d) || (a && b && c && !d));
    }
}

bool check_bool_pattern(bool a, bool b, bool c, bool d){
    //check if a,b,c,d are TFFT, FTTF, TTFF, FFTT pattern, if true, overlapping case
    if ((a && !b && !c && d) || (!a && b && c && !d) || (a && b && !c && !d) || (!a && !b && c && d)){
        return true;
    }
    return false;
}

bool is_touching(float x, float y, Rectangle a){
    if((x == a.x1 || x == a.x2) && inclusive_in_range(y, a.y1, a.y2)){
        return true;
    } 
    if ((y == a.y1 || y == a.y2) && inclusive_in_range(x, a.x1, a.x2)){
        return true;
    }
    return false;
}

bool is_overlap(bool c1, bool c2, bool c3, bool c4){

    //overlapping
    //checking for overlap between Rect a and Rect b, only need c1,c2,c3,c4
    if (three_identical_bool(c1,c2,c3,c4, false)){
        //if number of FALSE is 3, not overlapping, return false
        return false;
    } else if (three_identical_bool(c1,c2,c3,c4, true)){
        //if number of TRUE is 3, overlapping, return true
        return true;
    } else if (check_bool_pattern(c1,c2,c3,c4)){
        //if booleans are in the format of TFFT, FTTF, TTFF, FFTT, are overlapping
        return true;
    }
    return false;

}

void print_rect(Rectangle r){
    string x1 = to_string(r.x1);
    string y1 = to_string(r.y1);
    string x2 = to_string(r.x2);
    string y2 = to_string(r.y2);
    cout << x1 << " " << y1 << " " << x2 << " " << y2 <<endl;
}