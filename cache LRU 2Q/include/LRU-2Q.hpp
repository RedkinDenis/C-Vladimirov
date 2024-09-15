#include <unordered_map>
#include <list>

using namespace std;

typedef list<int> List;
typedef unordered_map<int, List::iterator> Hashtable;

void list_dump (List lst);

int count_hits (const char* testName);