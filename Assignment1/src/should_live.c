/*
    should_live():  check if a cell should live or die in the 
        next generation of the playground. 
    @param
    k:      size of the squre matrix that's going to rapresent
            the playground
    i:      index of the cell to check
    world:  pointer to the playground
    maxVal: pointer to the maximum value of the playground
    @return
    &maxVal: the cell should live
    0:       the cell should die
*/
unsigned char should_live(unsigned const int k,  unsigned const long i, unsigned const char *world, unsigned const int *maxVal)
{
    int result = 0;   // char is not enough to store the first sum
    register unsigned const int row = i/k;
    register unsigned const int col = i%k;
    result  = world[(k+row-1)%k*k + (k+col-1)%k]  // top left
            + world[(k+row+0)%k*k + (k+col-1)%k]  // top middle
            + world[(k+row+1)%k*k + (k+col-1)%k]  // top right
            + world[(k+row-1)%k*k + (k+col+0)%k]  // middle left
            + world[(k+row+1)%k*k + (k+col+0)%k]  // middle right
            + world[(k+row-1)%k*k + (k+col+1)%k]  // bottom left
            + world[(k+row+0)%k*k + (k+col+1)%k]  // bottom middle
            + world[(k+row+1)%k*k + (k+col+1)%k]; // bottom right
    result /= (*maxVal);
    result = ((result == 2) || (result == 3)) ? *maxVal : 0;
    return (unsigned char)result;
}