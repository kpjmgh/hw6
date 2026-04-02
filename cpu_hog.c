/*
 * cpu_hog.c
 *
 * CPU-bound infinite loop.
 *
 */

int main() {
    // TODO - write a CPU bound program. Nothing fancy.
    int n = 10;
    
    while(1){
        n = n+7;
        n = n/3;
        n = n*6;
        n = 4-n;
    }
    /*
    for(int i = 1; i>0; i++){
        n = n+7;
        n = n/3;
        n = n*6;
        n = 4-n;
    }
    */
}
