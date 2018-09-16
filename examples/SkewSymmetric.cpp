#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SkewSymmetric {
   public:
      int minChanges(vector <string> M);
};

int SkewSymmetric::minChanges(vector <string> M) 
{
    int temp;
    vector<int> row;
    vector<std::vector<int> > matrix;
    for(string &a : M)
    {
        istringstream ss(a);
        while(!(ss >> temp))
        {
            row.push_back(temp);
        }
        matrix.push_back(row);
        row.clear();
    }
    
}

int main() { 
  string line;
  vector<string> M;
  while (getline(cin, line)) 
     M.push_back(line);
  SkewSymmetric checker;
  cout << checker.minChanges(M) << endl;
}


