#include <time.h>

class SortTimer
{
private:
    struct timespec start, end;

public:
    void Start();
    void Stop();
    struct timespec GetElapsed();
};