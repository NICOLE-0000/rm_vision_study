#include <string>
#include <iostream>

using namespace std;

int main()
{
    string name = "rm_vision";
    string config = name + "_config.yaml";
    cout << config << endl;

    cout << name.size() << endl;
    cout << name[0] << endl;
    cout << name.substr(0,2) << endl;

    if(name == "rm_vision")
    {
        cout << "match!" << endl;
    }
    return 0;
}