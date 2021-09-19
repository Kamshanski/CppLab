
double** createCMatrix(int rows, int cols) {
    // Random seed
    srand(rows * cols);

    // create matrix
    double **matrix = (double**) malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; ++i) {
        matrix[i] = (double*) malloc(cols * sizeof(double));
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = (rand() & 63) - 32; // -32..31
        }
    }
    return matrix;
}

double** createCppMatrix(int rows, int cols, int seed = -1) {
    // Random seed
    if (seed == -1) {
        srand(rows * cols);
    } else {
        srand(seed);
    }

    // create matrix
    double **matrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = (rand() & 63) - 32; // -32..31
        }
    }
    return matrix;
}

