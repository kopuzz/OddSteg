#include "app.h"


int main(const int argc, const char* argv[]) {
    int32_t err = 0;
    
    if (argc != 4) {
        err = 2;
        return err;
    }
    
    App app(400, 400, argv[1], argv[2], argv[3]);

    err = app.load();
    if (err)
        return err;
    

    return app.run();
}
